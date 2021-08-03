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
			_count = new size_t(0);//传入nullptr，初始引用计数为0
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

	T *operator->()//s->draw()相当于是(s.operator->())->draw()  所以只需要返回指针就可以了
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

2.内存泄漏如何调查：内存泄漏一般有两种结果，一个是程序down掉，也有可能不会down掉但是内存不足。或者莫名其妙被占用一大块内存，性能降低。
内存泄漏的原因是堆内存申请后没有释放。有的时候也可以指文件描述符或者socket资源没有回收。同时也可以通过重载new来实现内存泄漏的定位，可以使用placecement new（即带参数的new）
自己维护一个内存状态的数据结构(行号，函数等)，然后可以打印出来看看是不是有意料之外的内存。


如果down掉，查看core文件，如果没有发现异常的退出点，就应该怀疑是内存泄漏。
如果怀疑内存泄漏，通过free命令查看内存用量是否上升或者螺旋上升。也可以使用top和ps -aux来看
查看/proc/进程号/map

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



static 局部变量内存是在程序加载的时候就已经预留了，初始化是在第一次使用的时候。

模板的优点:1. 灵活性, 可重用性和可扩展性;2. 可以大大减少开发时间，模板可以把用同一个算法去适用于不同类型数据，在编译时确定具体的数据类型;3. 模版模拟多态要比C++类继承实现多态效率要高, 无虚函数, 无继承;
缺点:1. 易读性比较不好，调试比较困难;2. 模板的数据类型只能在编译时才能被确定;3. 所有用基于模板算法的实现必须包含在整个设计的.h头文件中, 当工程比较大的时候, 编译时间较长;

模板一般实现和定义都要放在头文件里，但是也可以放在cpp里。如果放在cpp里，想要使用必须实例化。
模板导致代码冗余。。。。看看


重载的实现原理，通过返回值，函数名，参数值来生成对应的函数名。   但是真正起判断作用的只有参数，为什么不用返回值，如果使用返回值的话就必须依赖于上下文。
如果有作用域/命名空间/类，还要加上作用域在最前面

线程切换：进程是资源分配的基本单位  线程是CPU调度的基本单位  一个进程下可能有多个线程   线程共享进程的资源

接收一个网络包会进去几次内核态：

实现一个unique_ptr:
#include <iostream>
using namespace std;
template<typename T>
class munique_ptr{
    T *ptr;
    public:
    munique_ptr(T *_ptr=NULL):ptr(_ptr){}
    ~munique_ptr()
    {
        delete ptr;
    }
    //删除拷贝构造函数
    munique_ptr(const munique_ptr &r)=delete;
    //删除赋值运算符重载函数
    munique_ptr &operator=(const munique_ptr &r)=delete;

    T operator*()
    {
        return *ptr;
    }
};
int main(void)
{
    munique_ptr<double> ptr(new double(3.14));
    cout<<*ptr<<endl;
    munique_ptr<double> ptr1=ptr;
    munique_ptr<double> ptr2;
    ptr2=ptr;
}





迭代器的种类：
输入迭代器， 输出迭代器，正向迭代器，双向迭代器，随机访问迭代器
            input         output
              \            /
                 forward
                     |
                bidirectional
                     |
               random access
————————————————
https://blog.csdn.net/kai8wei/article/details/77606685


设计一个迭代器：

/*
    自定义迭代器的实现
*/
#include <iostream>
using namespace std;
class num
{
    int val;    //具体的数字
    int length; //数字的位数
    void getlength(){
        if(val/10==0){      //这个数字只有1位
            length=1;
            return;
        }
        int x=10;           //这里就是不断重复除直到为0，从而得出数字的具体位数
        int pow=0;
        int num=val;
        while(num!=0){
            num/=10;
            pow++;
        }
        length=pow;
    }
public:
    num(int num)
    { //以下是一些基本的函数，用于设置值
        val=num;
        getlength();
    }
    void set(int num)
    {
        val = num;
        getlength();
    }
    int get()
    {
        return val;
    }
    //以下是迭代器的部分
    class iterator
    {
        int pos;    //数字的下标
        num* obj;   //如果要在迭代器里面访问num的内容，必须要这个
    public:
        /*
            迭代器，要重载*,++,--
        */
        iterator(num* ptr,int n)
        {
            pos = n;
            obj = ptr;
        }
        iterator()
        {
            //空构造器
            pos = 0;
            obj = nullptr;
        }
        //操作符
        void operator++(){  //注意，这种没有参数的++重载的是前置的++   ++it
            pos++;
        }
        void operator++(int i){  //这种有任意int参数的重载的是后缀++  it++
            pos++;
        }
        void operator--(){
            pos--;
        }
        void operator--(int i){  
            pos--;
        }
        int operator*()const{
            //13324 取第二位10位：  (13324%100)/10
            //num  去除第n位     (num % 10^(n))/ 10^(n-1)
            if(pos>=obj->length) return -1;
            if(pos==0)return obj->val%10;
 
            int o=10;
            int pow=0;
            while(pow<(pos-1)){
               // cout<<pow<<" "<<pos<<endl;
                o*=10;
                pow++;
            }
            return (obj->val%(o*10))/(o);
        }
        bool operator!=(const iterator& it){
            return it.pos!=pos;
        }
        bool operator==(const iterator& it){
            return it.pos==pos;
        }
    };
    //获取迭代器，常见的比如begin,end;
    iterator begin()
    {
        return iterator(this,0);
    }
    iterator end()
    {
        return iterator(this,length);
    }
};
int main()
{
    num a(123456789);
    for(auto it=a.begin();it!=a.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    
    return 0;




3.vector erase删除数据的时候要注意删除后迭代器已经不能使用了，删除vector中所有某一个值的情况一般先用remove，remove返回值是新的end 迭代器 p， 然后使用erase（p,end()）
所有的stl容器erase后当前迭代器都不能用了，可以用返回值。

构造函数 赋值构造函数 移动构造函数什么时候生成 什么时候不生成

stone:
1.如何让程序只启动一个，程序启动的时候ps查看进程中是否有同名进程，如果有的话退出报错.

https://blog.csdn.net/Fly_as_tadpole/article/details/88378410