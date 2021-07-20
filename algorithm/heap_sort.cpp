#include <vector>
using namespace std;

void HeapSort::exch(int i , int j)
{
    int tmp = heap_vector_[i];
    heap_vector_[i] = heap_vector_[j];
    heap_vector_[j] = tmp;
}

bool HeapSort::less(int i , int j)
{
    return heap_vector_[i] < heap_vector_[j];
}

void HeapSort::swim(int k)
{
    while(k>=2&&less(k/2,k))
    {
        exch(k, k/2);
        k = k/2;
    }
}

void HeapSort::sink(int k)
{
    int i;
    while(k*2<=low_flag_)
    {
        i = k*2;
        if(i<low_flag_&&less(i,i+1))
        {
            i = i+1;
        }
        if(less(k,i))
        {
           exch(k, i); 
           k = i;
        }
        else
            break;
    }
}

class HeapSort()
{
public:
    HeapSort(int num = 0):heap_vector_(num),count_(num),low_flag_(0){}
    ~HeapSort();

    bool isempty()
    {
        return count_ == 0;
    }

    int size()
    {
        return count_;
    }

    void insert(int para)
    {
        if(low_flag_<count_)
        {
            heap_vector_[++low_flag_] = para;
            swim(low_flag_);
        }  
    }

    int delmax()
    {
        if(low_flag_ == 0)
            exit(-1);
        int max = heap_vector_[1];
        exch(1,low_flag--);
        sink(1);
        return max;
    }
private:
    vector<int> heap_vector_;
    int count_;
    int low_flag_;
    bool less(int i , int j);
    void exch(int i , int j);
    void swim(int k);
    void sink(int k);
}