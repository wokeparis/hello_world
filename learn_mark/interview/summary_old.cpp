//static成员函数和普通成员函数的区别 static没有this指针，不属于某一个对象而是属于类
//构造函数可不可以是虚函数：不可以是虚函数，虚函数的调用需要使用虚函数表指针，函数没构造的时候没有虚函数表指针。
//析构函数如果不是虚函数，作为基类会出现什么问题？   B：A    A* a = new B；这个a释放的时候(delete a) 只析构基类不析构派生类
//函数重载参数有const不构成重载(顶层指针，普通的const相当于顶层指针)，const成员函数可以和非const成员函数重载(本质上是因为const成员函数的this是底层const指针)。底层const也构成重载。
//基类和派生类只要有同名函数(不论参数和返回值)，没有被virtual修饰，那么基类的成员函数被隐藏。被virtual修饰就得满足虚函数的要求，参数数量要一致。
//reinterpret_cast  重新解释指针的意义为整型，或解释整型为指针，const_cast 只能用于去除指针或引用的常量性，底层指针的常量性
//static_cast的转换就是最普通的转换 在从大类型转到小类型时，先截断，在解释。如果位数一致，直接解释（如果两个位数一致但值范围不一致，unsigned 会根据位重新解释）。
//没有用到this指针的成员函数，是可以用一个nullptr对象来调用的。
//红黑树时间复杂度，插入全部数据的时间复杂度是nlogn，插入删除查找的时间复杂度是logn,哈希表的插入删除查找一般认为是1  
//三次握手如果丢包了tcp栈会怎么样？具体是要看实现，可能会有不同。 第一个包如果丢包了，相当于这个过程没有开始，client应该重发。第二个包如果丢了，server一定时间后应该重发，client也会重发，如果server收到了client的重发包，它会回复一个没有sync的ack，然后导致client发送一个rst，连接断开。或者server发送指定次数的第二个包始终守不到第三个包，那么也会断开连接。 第三个包丢了，client认为连接已经建立，会正常发送数据，这个时候如果server收到了，会回复一个rst，断开这个连接，也有可能不发，直接正常。第二个包和第三个包丢失的情况可以被用来泛洪攻击
//字节对齐问题：字节问题是和系统有关系的，是否和其他东西有关未知，但是一般的情况是：64位系统的指针8字节，32位系统指针4字节。如果没有使用#pragma pack，那么每个成员的起始地址必须和它自身的大小对齐，最后struct的大小要和它内部最大的元素的大小对齐。如果设置了#pragma pack，那么取该成员大小和#pragma pack的最小值作为对齐大小。
//vector清空的方法，清空 vector<int> a  vector<int>().swap(a);   将a与一个新建的vector交换，只是将大小和首尾指针进行交换，原来的数据变成临时值，会被析构掉。另一种用法： vector<int>(a).swap(a);可以将a变成最适合的大小。
//1.一个可执行文件 由代码段（text）、只读数据段.rodata（const全局变量）、已初始化的读写数据段data（static，全局变量），未初始化数据区bss(只存储大小和符号等信息，并不事实分配空间)。
//c++11 final的作用有两个，一个用来标记类不能作为基类，一个用来标记函数无法被重写。 override的作用是标记一定要进行重写，防止出现某些手误造成的错误，而且能更直观。 还有default和delete，delete并不是只能用于那几个默认生成的函数，也能用于转换函数，new重载等
//构造函数里是可以有this指针的，但是初始化列表里不能有。
//必须需要初始化列表的变量：引用、const、无默认构造函数的类。
//内存泄漏如何调查：
//1.参加一个华为的认证，对源代码使用cppcheck，可以检测出来很多隐藏的内存泄漏。
//2.使用valgrind的memcheck，但是我们的项目跑不起来，当时具体原因未知，要么是多线程要么是内存不够。
//3.重载new （operator new   placecement new（即带参数的new））添加一些统计内存分配和释放的信息，自己维护一个内存状态的数据结构(行号，函数等)，然后可以打印出来看看是不是有意料之外的内存。没用过，看effective c++的时候看到过。
//4.尽可能使用智能指针，如果不能使用智能指针靠经验管理好
//5.free查看当前使用的内存，是否有上升趋势。
//6./proc/进程号/map查看虚拟内存分布




/*
算法	      是否稳定	是否为原地排序	时间复杂度	   空间复杂度	             备注
选择排序	    否	          是	    N^2	              1	
插入排序	    是	          是	   介于N和N^2之间	   1	             取决于输入元素的排列情况
希尔排序	    否	          是	    NlogN？N^(6⁄5)	  1	
快速排序	    否	          是	     NlogN	          lgN	             运行效率由概率提供保证
三向快速排序	否	          是	    介于N和NlogN之间   lgN	         运行效率由概率保证，同时也取决于输入元素的分布情况
归并排序	    是	          否	      NlogN	          N	
堆排序	        否	          是	     NlogN	           1	
*/
/*
如何让一个对象只能在堆上创建：  构造函数或析构函数私有或protect
将类中构造，析构定义为私有或保护，然后定义一个公有的静态成员函数，此种方法，只能使用new创建对象，即只能在堆上创建对象。
解析：
当对象建立在栈上时，是由编译器分配内存的，调用构造函数和析构函数，编译器管理了对象的整个周期。如果编译器无法调用析构是怎样的呢？
如果类的析构函数是私有的，编译器将无法调用析构函数来释放内存。所以，编译器在为类对象分配栈空间时，会先检查析构函数的访问性，不光是析构函数，只要是非静态函数，
编译器都会检查，如果类的析构函数是私有的，则编译器不会在栈空间上为类对象分配内存。

class AA
{
public:
	AA(){}
	void destory(){delete this;}//析构的时候不能用delete，因为析构私有  用这个函数
private:
	~AA(){}
};

class A  //这样格式统一些，且能够解决无法继承的问题
{
 
protected:  
    A(){}
    ~A(){}
    
public:
    static A* create()
    {
        return new A();
    }
    
    void destory()
    {  
        delete this;
    }
}
 
int main()
{
	//AA q;   //在栈上创建对象
	AA* p = new AA;   //在堆上创建对象
	system("pause");
	return 0;
}

class AA
{
public:
	~AA(){}
	static AA* get(){
		return new AA;
	}
	//void destory(){delete this;}
private:
	AA(){}

};

int main()
{
	AA* a = AA::get();
	delete a;
}
*/

/*
让一个对象只能在栈上创建：把operator new重载并设置为private或delete,最好delete也做一样的操作，否则不能new 但是能delete，容易发生错误。
class AA
{
private:
	void* operator new(size_t){}
	void operator delete(void*){}
public:
	AA()
	{
		cout << "AA()" << endl;
	}
	~AA()
	{
		cout << "~AA()" << endl;
	}
};
*/

/*
epoll水平模式和触发模式
https://blog.csdn.net/halfclear/article/details/78061771
https://zhuanlan.zhihu.com/p/63179839
    下面说的全是触发模式：
    触发模式的触发条件，以读为例子（写差不多）。 在已经添加的条件下，1.ctl的时候如果里面有值 2.数据从无到有 3.数据值变化。
    (EPOLLIN|EPOLLOUT)可以这样一次性指定一个文件描述符。读写都检测。  触发读的时候同时会触发是否可写的检测
    两个epoll监测同一个fd，两个都能收到事件。
    epoll文件描述符也是可读的。
    如果读的时候又来数据了，然后读完了，直接触发再来一次recv直接报错也相当于读完。
    如果读的时候一直来数据。会造成饥饿，所有的其他fd无法操作，然后可以自己维护一个列表，每个fd操作一定次，然后循环操作，直到所有fd都不是active
    触发条件测试。如果收到一个fin，水平模式和触发模式的情况
        都会触发，通过判断read返回值=0。也可以通过触发epollrdhup来判断。 
*/
/*
单例模式：
class Test
{
	private:
		Test();
		Test(const Test&) = delete;
		Test& operator = (const Test&) = delete;
	public:
		static Test&  get_instance()
		{
			static Test tmp;
			return tmp;
		}
}
*/

/*  shared_ptr
template<class T>
class SmartPtr
{
	private:
		T* ptr_;
		size_t* count_;
	public:
		SmartPtr(T* tmp = nullptr):ptr_(tmp)
		{
			count_ = new size_t(1);
		}	
		~SmartPtr()
		{
			if(--(*count_) == 0)
			{
				delete count_;
				delete ptr_;
			}
		}
		SmartPtr(const SmartPtr& tmp)
		{
			ptr_ = tmp.ptr_;
			count_ = tmp.count_;
			++(*count_);
		}	
		SmartPtr& operator=(const SmartPtr& tmp)	
		{
			if(ptr_ == tmp.ptr_)
				return *this;
			else
			{
				if(--(*count_) == 0)
				{
					delete count_;
					delete ptr_;
				}				
				ptr_ = tmp.ptr_;
				count_ = tmp.count_;
				++(*count_);
				return *this;
			}
		}
		T& operator*()
		{
			assert(_ptr != nullptr);
			return *ptr_;
		}

		T* operator->()
		{
			assert(_ptr != nullptr);
			return ptr_;
		}
    T* get()
    {
        return ptr_;
    }
    void reset(T* tmp)
    {
		if(ptr_ == tmp.ptr_)
			return ;
		else
		{
			if(--(*count_) == 0)
			{
				delete count_;
				delete ptr_;
			}				
			ptr_ = tmp.ptr_;
			count_ = tmp.count_;
			++(*count_);
			return ;
		}	
    }
}
*/
/*unique_ptr
template<class T>
class auto_p{
private:	
	T *ptr_;
public:
	auto_p(T *tmp = nullptr):ptr_(tmp){}		//构造函数 
	~auto_p()	//虚构函数 
    {
        if(ptr_) 
            delete ptr_;
    }    
	auto_p(auto_p&& rhs):ptr_(rhs.ptr_)
	{
        rhs.ptr_ = nullptr;
    }
	//移动构造函数   
	auto_p& operator=(auto_p &&rhs)
    {
        if(ptr_ != rhs.ptr_)
        {
            if(ptr_)
                delete ptr_;          
            ptr_ = rhs.ptr_;
            rhs.ptr_ = nullptr;
        }
        return *this;
    }

	auto_p(const auto_p&) = delete;			//拷贝构造与赋值不能使用 
	auto_p& operator=(const auto_p &) = delete;
    T* operator->()
    {
        assert(ptr_!=nullptr);
        return ptr_;
    }
    
    T& operator*()
    {
        assert(ptr_!=nullptr);
        return *ptr_;
    }

    T* release()
    {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    T* get()
    {
        return ptr_;
    }

    void reset(T* para)
    {
        if(ptr_)
            delete ptr_;
        ptr_ = para;
    }
}
*/


/* map<structA, structB> 
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