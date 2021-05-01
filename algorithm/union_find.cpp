//////并查集
#include <vector>
#include <iostream>

using namespace std;

class UF
{
public:
    UF(int n = 0);
    ~UF(){};

    void union_func(int p, int q);//p 和 q之间创建一个连接
    int find(int p);//查询p 对应的标识符
    bool connected(int p, int q);//查询p 和 q是否连接
    int count();//查询当前总共有多少未连接的情况
private:
    std::vector<int> union_find_vector_;
    int count_;
    int max_;
};

UF::UF(int n):count_(n), union_find_vector_(n),max_(n)
{
    for(int i = 0; i < n; i++)
    {
        union_find_vector_[i] = i;
    }
}

int UF::count()
{
    return count_;
}

void UF::union_func(int p, int q)
{
    if(p == q)
    {
        return;
    }
    else
    {
        for(int i = 0; i < max_; ++i)
        {
            if(union_find_vector_[i] == p)
                union_find_vector_[i] = q;
        }
        --count_;
    }
}

int UF::find(int p)
{
    return union_find_vector_[p];
}

bool UF::connected(int p, int q)
{
    if(union_find_vector_[p] == union_find_vector_[q])
        return true;
    else
        return false;
}


class UF2
{
public:
    UF2(int n = 0);
    ~UF2(){};

    void union_func(int p, int q);//p 和 q之间创建一个连接
    int find(int p);//查询p 对应的标识符
    bool connected(int p, int q);//查询p 和 q是否连接
    int count();//查询当前总共有多少未连接的情况
private:
    int find_key(int);
    std::vector<int> union_find_vector_;
    int count_;
    int max_;
};

UF2::UF2(int n):count_(n), union_find_vector_(n),max_(n)
{
    for(int i = 0; i < n; i++)
    {
        union_find_vector_[i] = i;
    }
}

int UF2::find_key(int key)
{
    while(key != union_find_vector_[key])
    {
        key = union_find_vector_[key];
    }
    return key;
    
}

int UF2::count()
{
    return count_;
}

void UF2::union_func(int p, int q)
{
    if(find_key(p) == find_key(q))
    {
        return;
    }
    else
    {
        union_find_vector_[find_key(p)] = union_find_vector_[find_key(q)];
        --count_;
    }
}

int UF2::find(int p)
{
    return find_key(p);
}

bool UF2::connected(int p, int q)
{
    if(find_key(p) == find_key(q))
        return true;
    else
        return false;
}



int main()
{
    UF2 tmp(200);
    cout<<tmp.count()<<endl;
    cout<<tmp.find(100)<<endl;
    cout<<tmp.find(120)<<endl;
    cout<<tmp.connected(100,120)<<endl;
    tmp.union_func(100,120);
    cout<<tmp.count()<<endl;
    cout<<tmp.find(100)<<endl;
    cout<<tmp.find(120)<<endl;
    cout<<tmp.connected(100,120)<<endl;
}