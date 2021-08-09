//5本西游记，num = 5，索引条件变量，多线程，


#include <iostream>
#include <mutex>

using namespace std;

#include <memory>
#include <vector>
 
struct A {
    std::vector<std::unique_ptr<int> > vec;
};
 
int main(int argc, char* argv[]) {
    std::vector<A> vec;
 
    A a;
    a.vec.emplace_back(new int{0});
 
    vec.emplace_back(std::move(a));
 
    return 0;
}