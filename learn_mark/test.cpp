#include <set>
#include <tuple>
#include <iostream>
using namespace std;

class BASE
{
    int a;
};

class Derive: public BASE
{
    int b;
};

int main()
{
    BASE* b = new BASE;
    Derive* a = dynamic_cast<Derive*>(b);
    cout<<"ok"<<endl;
}