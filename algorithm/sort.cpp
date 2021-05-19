#include <vector>
#include <iostream>

using namespace std;

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void sort_maopao(vector<int>& list)
{
    int size = list.size();
    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0; j <size-1-i; j++)
        {
            if(list[j]>list[j+1])
            {
                swap(list[j], list[j+1]);
            }
        }
    }
}

void sort_chose(vector<int>& list)
{
    int size = list.size();
    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0; j < size-1-i; j++)
        {
            if(list[j]>list[size-1-i])
                swap(list[j],list[size-1-i]);
        }
    }
}

void sort_insert(vector<int>& list)
{
    int size = list.size();
    for(int i = 1; i <size; i++)
    {
        for(int j = i ; j > 0 ; j--)
        {
            if(list[j]<list[j-1])
                swap(list[j], list[j-1]);
            else 
                break;
        }
    }
}
/*
void sort_shell(vector<int>& list)
{
    int size = list.size();
    int h = 1;
    while(h<size/3)
        h = 3*h+1;//生成递增序列 1，4，13，40
    while(h>=1)//最后h肯定是1      间隔 从40-》13-》4-》1    一开始 h >= size/3   举例如果size是 11 h=4
    {
        for(int i = h ; i < size; i++)//举例的第一次 4-10
        {
            for(int j = i; i >= h; j-=h)
            {
                if(list[j]<list[j-h])
                {
                    swap(list[j], list[j-h]);
                }
            }
            h = h/3;
        }
    }
}
*/
void sort_shell(vector<int>& list)
{
    int size = list.size();
    int h = 1;
    while(h<size/2)
    {
        h*=2;
    }
    for(; h >= 1; h/=2)
    {
        for(int j = h; j < size ; j++)
        {
            for(int k = j; k >= h; k-=h)
            {
                if(list[k]<list[k-h])
                {
                    swap(list[k],list[k-h]);
                }
            }
        }
    }
}

void merge(vector<int>& list, int first, int mid, int last)
{
    int size = last-first;
    vector<int> tmp(size+1);
    for(int i = first, j = 0; i <= last; i++, j++)
    {
        tmp[j] = list[i];
    }
    for(int i = first, j =  size/2+1, k = 0; i <= last; i++)
    {
        if(k > size/2)
            list[i] = tmp[j++];
        else if(j>size)
            list[i] = tmp[k++];
        else if(tmp[j]<tmp[k])
        {
            list[i] = tmp[j++];
        }
        else
        {
            list[i] = tmp[k++];
        }
    }
}

void sort_guibing_fen(vector<int>& list, int first, int last)
{
    if(first>=last)
        return;
    int mid = first+(last-first)/2;
    sort_guibing_fen(list, first, mid);
    sort_guibing_fen(list, mid+1, last);
    merge(list, first, mid, last);
}

void sort_guibing_up_down(vector<int>& list)
{
    sort_guibing_fen(list, 0, list.size()-1);
}

int partition_1(vector<int>& list, int first, int end)
{
    if(first>=end)
        return -1;
    int size = end-first+1;
    int tmp = first+1;//1   [0   3]
    for(int i = 1; i < size; i++)//size 4   123
    {
        if(list[tmp]<list[first])
            tmp++;
        else
            swap(list[tmp], list[end--]);
    }
    if(list[tmp]<list[first])
    {
        swap(list[tmp], list[first]);
        return tmp;
    }
    else
    {
        swap(list[tmp-1], list[first]);
        return tmp-1;        
    }
}

int partition_2(vector<int>& list, int first, int end, int& mid_1, int& mid_2)
{
    if(first>=end)
        return -1;
    mid_1 = mid_2 = first;//4 
    for(int i = first+1; i <= end;)//size 4   123
    {
        if(list[i]==list[mid_1])
        {
            mid_2++;
            i++;
        }
        else if(list[i]>list[mid_1])
        {
            swap(list[i], list[end--]);
        }
        else
        {
            swap(list[i], list[mid_1++]);
            mid_2++;
            i++;
        }
    }
}

void sort_quick_sub(vector<int>& list, int first, int end)
{
    int mid_1, mid_2;
    int mid = partition_2(list, first, end, mid_1, mid_2);
    if(mid == -1)
        return;
    sort_quick_sub(list, first, mid_1-1);
    sort_quick_sub(list, mid_2+1, end);
}

void sort_quick(vector<int>& list)
{
    int size = list.size();
    int first = 0;
    int end = size-1;
    sort_quick_sub(list, first, end);
}




int main()
{
    vector<int> list = {3,4,7,1,8,2,9,0,5,6};
    sort_quick(list);
    for(auto i : list)
        cout<<i<<endl;
}