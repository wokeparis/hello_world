小米：
1.static成员函数和普通成员函数的区别
    static没有this指针，不属于某一个对象而是属于类
2.epoll水平模式和触发模式
    下面说的全是触发模式：
    触发模式的触发条件，以读为例子（写差不多）。 在已经添加的条件下，1.ctl的时候如果里面有值 2.数据从无到有 3.数据值变化。
    (EPOLLIN|EPOLLOUT)可以这样一次性指定一个文件描述符。读写都检测。  触发读的时候同时会触发是否可写的检测
    两个epoll监测同一个fd，两个都能收到事件。
    epoll文件描述符也是可读的。
    如果读的时候又来数据了，然后读完了，直接触发再来一次recv直接报错也相当于读完。
    如果读的时候一直来数据。会造成饥饿，所有的其他fd无法操作，然后可以自己维护一个列表，每个fd操作一定次，然后循环操作，直到所有fd都不是active
    触发条件测试。如果收到一个fin，水平模式和触发模式的情况
        都会触发，通过判断read返回值=0。也可以通过触发epollrdhup来判断。
3.构造函数可不可以是虚函数，不可以是虚函数，虚函数需要使用虚函数表指针，函数没构造的时候没有虚函数表指针，如果构造函数是虚函数怎么构造函数呢？
4.析构函数如果不是虚函数，作为基类会出现什么问题？   派生类的析构函数即使是非默认的，也会调用基类的析构函数
B：A    A* a = new B；这个a析构的时候 只析构基类不析构派生类  
5.字节对齐是和系统位数对应的
结构体模数对齐，该模数是【#pragma pack指定的数值】、【未指定#pragma pack时，系统默认的对齐模数（32位系统为4字节，64位为8字节）】
和【结构体内部最大的基本数据类型成员】长度中数值较小者。结构体的长度应该是该模数的整数倍。
 	 	           char	short	int	long float	double	long long	long double
Win-32	    长度	1	  2	     4	  4	   4	   8	  8	           8
            模数	1	  2	     4	  4	   4	   8	  8	            8
Linux-32	长度	1	  2	     4	  4	   4	   8	  8	           12
            模数	1	  2	     4	  4	   4	   4	  4	            4
Linux-64	长度	1	  2	     4	  8	   4	   8	  8	             16
            模数	1	  2	     4	  8	   4	   8	  8	             16

6.三次握手如果丢包了怎么办
第一个包如果丢包了，相当于这个过程没有开始，client应该重发
第二个包如果丢了，server一定时间后应该重发
第三个包丢了和第二个包的情况一样
第二个包和第三个包丢失的情况可以被用来泛洪攻击
7.函数重载参数有const不构成重载，const成员函数可以和非const成员函数重载。只有成员函数才有const，非成员函数没有。底层const也构成重载。
基类和派生类只要有同名函数，没有被virtual修饰，那么基类的成员函数被隐藏。被virtual修饰就得满足虚函数的要求，参数数量要一致
8.reinterpret_cast  目标和源必须有一个是指针或引用。从位上重新解释
static_cast 在从大类型转到小类型时，先截断，在解释。如果位数一致，直接解释（如果两个位数一致但值范围不一致，unsigned 会根据位重新解释）。
const_cast 只能用于去除指针或引用的常量性，底层指针的常量性

金山：
1.vector清空的方法，清空 vector<int> a  vector<int>().swap(a);   将a与一个新建的vector交换，只是将大小和首尾指针进行交换，原来的数据变成临时值，会被析构掉
另一种用法： vector<int>(a).swap(a);可以将a变成最适合的大小。

商汤：
1.智能指针的实现，找时间可以看一下

template <typename T>
class SmartPtr
{
private : 
	T *_ptr;
	size_t *_count;//用一个指针，复制时就可以只使用一份count了

public:
	SmartPtr(T *ptr = nullptr) : _ptr(ptr)
	{
		if (_ptr)
		{
			_count = new size_t(1);
		}
		else
		{
			_count = new size_t(0);//这里直接不管_ptr是否是0就可以了吧，判断了还会出现内存泄漏
		}
	}

	~SmartPtr()
	{
		(*this->_count)--;//这个计数的变化要考虑一下线程安全
		if (*this->_count == 0)
		{
			delete this->_ptr;
			delete this->_count;
		}
	}

	SmartPtr(const SmartPtr &ptr) // 拷贝构造：计数 +1
	{
		if (this != &ptr)
		{
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}

	SmartPtr &operator=(const SmartPtr &ptr) // 赋值运算符重载 
	{
		if (this->_ptr == ptr._ptr)
		{
			return *this;
		}
		if (this->_ptr) // 将当前的 ptr 指向的原来的空间的计数 -1
		{
			(*this->_count)--;
			if (this->_count == 0)
			{
				delete this->_ptr;
				delete this->_count;
			}
		}
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++; // 此时 ptr 指向了新赋值的空间，该空间的计数 +1
		return *this;
	}

	T &operator*()
	{
		assert(this->_ptr != nullptr);
		return *(this->_ptr);
	}

	T *operator->()
	{
		assert(this->_ptr != nullptr);
		return this->_ptr;
	}

	size_t use_count()
	{
		return *this->count;
	}
};

百度：
1.一个可执行文件 由代码段（text）、只读数据段.rodata（const全局变量）、已初始化的读写数据段data（static，全局变量），未初始化数据区bss(只存储大小和符号等信息，并不事实分配空间)。
2.内存泄漏如何调查：内存泄漏一般有两种结果，一个是程序down掉，也有可能不会down掉但是内存不足。或者莫名其妙被占用一大块内存，性能降低。
内存泄漏的原因是堆内存申请后没有释放。有的时候也可以指文件描述符或者socket资源没有回收。同时也可以通过重载new来实现内存泄漏的定位，可以使用placecement new（即带参数的new）
自己维护一个内存状态的数据结构(行号，函数等)，然后可以打印出来看看是不是有意料之外的内存。


如果down掉，查看core文件，如果没有发现异常的退出点，就应该怀疑是内存泄漏。
如果怀疑内存泄漏，通过free命令查看内存用量是否上升或者螺旋上升。也可以使用top和ps -aux来看

解决办法，尽可能使用只能指针。重载new delete方法添加统计内存分配和释放的模块。经验new delete自己控制好。
使用valgrind的memcheck检查。面试官说大型工程不能用可以试一下。
cppcheck华为。

map<structA, structB> 
/*
struct hello
{
    int name;
    int value;
    bool operator <(const hello& a)const
    {
        return name < a.name;
    }
};

struct compare
{
    bool operator()(hello a, hello b)//这里感觉还是像上面一样规范一点比较好，使用const引用而且函数为const函数
    {
        return a.name>b.name;
    }
};

int main()
{
    hello test[10];
    map<hello,int> tmp1;
    map<hello,int, compare> tmp2;
    for(int i = 0; i < 10; i++)
    {
        test[i].name = i;
        test[i].value = i;
        tmp1.insert(make_pair(test[i],i));
        tmp2.insert(make_pair(test[i],i));
    }   
    for(auto i: tmp1)
    {
        cout<<i.second<<endl;
    }    
    for(auto i: tmp2)
    {
        cout<<i.second<<endl;
    }
}
*/

如何使返回值也作为重载的判断依据：//感觉是歪门邪道
又想到的法子，如果只是想要达到效果，把返回值作为参数，使用引用或指针返回。
/*
class my_cast {
    const char* s;
public:
    template<class Target>
    operator Target() const {
        return static_cast<Target>(s);
    }
    my_cast(const char* s) : s(s) {}
};
string ss = my_cast("abcde");
double dd = my_cast(('3' + string(".2222")).c_str());
*/
stl容器里可以用引用吗？stl会对保存在东西进行构造，stl里面会有指针指向存进来的对象，首先引用不是对象，然后指针是不能指向引用的，引用只是一个别名没有地址。
stack和queue为什么没有迭代器


必须需要初始化列表的变量：引用 const 无默认构造函数的类

3.自己的职业规划，离职相关： 


4.虚函数表的调用方式。//知乎

5.如何使用函数指针调用成员函数

{
	class A
	{
		public:
			int func(int a)
			{
				cout<<"test"<<endl;
				return 0;
			}
	};

	int (A::*func_t)(int a);//必须加A::

	int main()
	{
		A a;
		func_t = &A::func;//必须用取址 
		(a.*func_t)(1);//如果是非成员函数可以func_t(1),成员函数必须是左边这样
	}
}

360：
线程池的设计：
https://zhuanlan.zhihu.com/p/356564167
https://www.cnblogs.com/harlanc/p/8596211.html    条件变量相关

需要注意的地方： 应该有一个job队列，使用条件变量控制job的获取，push job时用锁保护起来，signal后unlock
然后线程消耗job时也应该加锁，然后要判断线程池退出时的一些处理                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

左值和右值的概念区别：  左值可以取地址，右值不能取地址，左值表达式结束后还存在，右值不存在。

stl容器里如何放一个unique_ptr,使用std::move(),被move的原指针不能再使用
unique_ptr能够被当作返回值返回：1.返回值会有一个返回值优化的操作，不会进行copy操作2.即使没有返回值优化，也会优先判断移动构造

动态库相关，动态库只有代码段是共享的 
动态库-l 和dlopen的区别： -l链接后，会在程序运行之前就把该库载入内存；dlopen则是在程序运行到这个调用才会载入．
如果是常用库，最好-l,如果是比较少程序使用，而且你的程序也不一定每次运行都会使用，那么为了内存考虑，可以用dlopen

动态库中(cpp里)如果有模板，如果要用的话必须要实例化

内存交换最近最久未使用算法：
实现方式一：
在内存中维护一个所有页面的链表。当一个页面被访问时，将这个页面移到链表表头。这样就能保证链表表尾的页面时最近最久未访问的。
实现方式二：
为每个页面设置一个访问字段，来记录页面自上次被访问以来所经历的时间，淘汰页面时选择现有页面中值最大的予以淘汰。
LRU算法

pb相关，pb的缺点，有人说生成代码量太多，实际使用并没有体会到。可读性差，抓到看不到具体数据，相当于简单加密。
为什么高效？使用二进制方式存储，整型还会做简单的压缩处理。
pb的string和byte的区别 string对于某些字符类型会有错误判断，所以如果确定不使用这些字符类型，byte的效率更高
pb的问题：默认值必须代表不设置的意思，因为没设置的话就会变成默认值。如果设置为默认值的话，压缩之后会被省略掉，解压之后又被设置为默认值。

override的作用是标记一定要重写。

static 局部变量内存是在程序加载的时候就已经预留了，初始化是在第一次使用的时候。

模板的优点:1. 灵活性, 可重用性和可扩展性;2. 可以大大减少开发时间，模板可以把用同一个算法去适用于不同类型数据，在编译时确定具体的数据类型;3. 模版模拟多态要比C++类继承实现多态效率要高, 无虚函数, 无继承;
缺点:1. 易读性比较不好，调试比较困难;2. 模板的数据类型只能在编译时才能被确定;3. 所有用基于模板算法的实现必须包含在整个设计的.h头文件中, 当工程比较大的时候, 编译时间较长;

模板一般实现和定义都要放在头文件里，但是也可以放在cpp里。如果放在cpp里，想要使用必须实例化。
模板导致代码冗余。。。。看看

排序算法复杂度。。看看

重载的实现原理，通过返回值，函数名，参数值来生成对应的函数名。   但是真正起判断作用的只有参数，为什么不用返回值，如果使用返回值的话就必须依赖于上下文。
如果有作用域/命名空间/类，还要加上作用域在最前面

线程切换：进程是资源分配的基本单位  线程是CPU调度的基本单位  一个进程下可能有多个线程   线程共享进程的资源


阿里：
1.没有用到this指针的成员函数，可以用一个nullptr对象来调用。