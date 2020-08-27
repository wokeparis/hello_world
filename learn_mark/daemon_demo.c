/*daemon process 拥有单独的进程组和单独的会话，与终端无关*/
void init_daemon()
{
	int pid = 0, i = 0;
	
	//由于当前进程有可能是进程组的leader，但是进程组的leader不能使用setsid
	//所以先fork一下，确保当前进程肯定不是进程组leader
	//同时可以把这个进程变成一个孤儿进程
	if(pid = fork())
		exit(0);
	else if(pid < 0)
		exit(1);
	
	//最重要的一步，创建一个新的session 并成为session leader
	//同时也会创建一个新的进程组  并成为进程组leader
	//同时断开子进程与当前终端的联系
	setsid();
	
	//这一步是可以忽略的，由于新的会话依然有可能创建一个新的终端
	//如果创建了，终端退出程序也会退出，依然会受到终端的影响
	//所以再fork一次，子进程不是session leader 不会再打开终端
	if(pid = fork())
		exit(0);
	else if(pid < 0)
		exit(1);


	//子进程会继承已经打开的文件，它们占用系统资源，且可能导致所在文件系统无法卸载。
	//此时守护进程与终端脱离，常说的输入、输出、错误描述符也应该关闭。
	for(i = 0; i < NOFILE; i++)
		if(i != 1)
			close(i);
		
	//创建文件的屏蔽信息是从父进程继承来的，有可能不是想要的
	//所以重新设置一下
	umask(0);
	
	//修改工作目录，举个例子，如果当前程序是在U盘中运行的，
	//如果没有修改工作目录，卸载U盘可能会报错
	chdir("/");
	
	//有些时候会有这个步骤，作用是占用stdin 或stdout、stderr
	open("/dev/null", O_RDWR);
}