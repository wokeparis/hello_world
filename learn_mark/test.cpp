#include <iostream>
#include <stack>
using namespace std;
/*
struct Node
{
	Node(Node* node = nullptr, int lval = 0):next(node),val(lval)
	{

	}
	Node* next;
	int val;
};

Node* deleteFunc(Node* root)
{
	Node node_head;
	node_head.next = root;

	Node* prev = &node_head;
	Node* node_tmp = root;
	while(node_tmp)
	{
		if(node_tmp->next&&node_tmp->val != node_tmp->next->val)
		{
			prev = node_tmp;
			node_tmp = node_tmp->next;
			cout<<"test"<<endl;
		}
		else
		{
			while(node_tmp->next&&node_tmp->val == node_tmp->next->val)
			{
				cout<<node_tmp<<endl;
				node_tmp = node_tmp->next;
			}
			prev->next = node_tmp->next;
			//cout<<"test123"<<node_tmp->next<<endl;
			node_tmp = node_tmp->next;
		}
		cout<<"test1"<<endl;
	}
	return node_head.next;
}

int main()
{
	//Node* tmp1 = new Node();
	Node* tmp2 = new Node();
	Node* tmp3 = new Node(tmp2, 5);
	Node* tmp4 = new Node();
	Node* tmp5 = new Node(nullptr, 4);
	Node* tmp6 = new Node(tmp5, 3);
	Node* tmp7 = new Node(tmp6, 3);
	Node* tmp8 = new Node(tmp7, 2);
	Node* tmp9 = new Node(tmp8, 1);
	Node* test = deleteFunc(tmp9);
	while(test)
	{
		cout<<test->val<<endl;
		test = test->next;
	}

}
*/
/*
输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]

输入：head = [1,1,1,2,3]
输出：[2,3]
*/

/*
示例 1：
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：
输入：l1 = [], l2 = []
输出：[]
示例 3：
输入：l1 = [], l2 = [0]
输出：[0]
*/
/*
struct ListNode {
int val;
ListNode *next;
ListNode() : val(0), next(nullptr){}
ListNode(int x): val(x), next(nullptr) {}
ListNode(int x,ListNode *next):val(x), next(next) {}
};

ListNode* merge(ListNode* list1, ListNode* list2)
{
	if(list1==nullptr)
		return list2;
	else if(list2 == nullptr)
		return list1;
	ListNode prev;
	ListNode* tmp = &prev;
	while(list1&&list2)
	{
		if(list1->val<list2->val)
		{
			tmp->next = list1;
			list1 = list1->next;
			tmp = tmp->next;
		}
		else
		{
			tmp->next = list2;
			list2 = list2->next;
			tmp = tmp->next;			
		}
	}
	if(list1)
	{
		tmp->next = list1;
	}
	else if(list2)
	{
		tmp->next = list2;
	}
	return prev.next;
}
*/
class AA
{
public:
	~AA(){}
	static AA* get(){
		return new AA;
	}
	//void destory(){delete this;}//析构的时候不能用delete，因为析构私有  用这个函数
private:
	AA(){}

};

int main()
{
	AA* a = AA::get();
	delete a;
}

template<class T>
class Smart_ptr
{
	private:
		T * ptr_;
		int * count_;
	public:
		Smart_ptr(T* para):ptr_(para)
		{
			if(ptr_)
			{
				count_ = new int(1);
			}
		}

		~Smart_ptr()
		{
			(*count_)--;
			if(*count_==0)
			{
				delete count_;
				delete ptr_;
			}
		}	

		Smart_ptr(const Smart_ptr& tmp)
		{
			count_ = tmp.count_;
			ptr_ = tmp.ptr_;
			*count_++;
		}

		Smart_ptr& operator = (Smart_ptr& tmp)
		{
			if(&tmp == this)
				return *this;
			*count--;
			if(*count_==0)
			{
				delete count_;
				delete ptr_;
			}			
			count_ = tmp.count_;
			ptr_ = tmp.ptr_;
			*count_++;	
			return *this;		
		}
		T& operator*()
		{
			assert(ptr_!=nullptr);
			return *ptr_;
		}
		T* operator->()
		{
			assert(ptr_!=nullptr);
			return ptr_;
		}
}

