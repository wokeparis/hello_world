//static成员函数和普通成员函数的区别 static没有this指针，不属于某一个对象而是属于类
//构造函数可不可以是虚函数：不可以是虚函数，虚函数的调用需要使用虚函数表指针，函数没构造的时候没有虚函数表指针。
//析构函数如果不是虚函数，作为基类会出现什么问题？   B：A    A* a = new B；这个a释放的时候(delete a) 只析构基类不析构派生类
//函数重载参数有const不构成重载(顶层指针，普通的const相当于顶层指针)，const成员函数可以和非const成员函数重载(本质上是因为const成员函数的this是底层const指针)。底层const也构成重载。
//基类和派生类只要有同名函数(不论参数和返回值)，没有被virtual修饰，那么基类的成员函数被隐藏。被virtual修饰就得满足虚函数的要求，参数数量要一致。
//reinterpret_cast  重新解释指针的意义为整型，或解释整型为指针，const_cast 只能用于去除指针或引用的常量性，底层指针的常量性
//static_cast的转换就是最普通的转换 在从大类型转到小类型时，先截断，在解释。如果位数一致，直接解释（如果两个位数一致但值范围不一致，unsigned 会根据位重新解释）。

  
