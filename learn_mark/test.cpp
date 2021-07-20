#include <iostream>
#include <stack>
using namespace std;
	class  Node
	{
	public:
	    Node(int v) : value_(v) {}
	    void access() {
	        std::cout << value_ << std::endl;
	    }
	public:
	    Node* left = nullptr;
	    Node* right = nullptr;
	private:
	    int value_ = 0;
	};
	
	class BinaryTree
	{
	public:
	    Node* head = nullptr;
	};
	void inOrder(BinaryTree* tree) {
      	//vector<int> ret;
    	if(tree==nullptr)
          return; 
      	std::stack<Node*> tmp_stack;
      	tmp_stack.push(tree->head);
      	Node* prev = tree->head;
    	while(tmp_stack.size())
        {
        	Node* tmp_node = tmp_stack.top();
          	if(prev == tmp_node->left&&tmp_node->right)
            {
            	tmp_stack.push(tmp_node->right);
              	prev = tmp_node;
              	tmp_node = tmp_node->right;
            }
          	else if(prev == nullptr||prev == tmp_node->right||prev == tmp_node->left)
            {
            	tmp_node->access();
              	prev = tmp_node;
              	tmp_stack.pop();
            }
            else
            {
              while(tmp_node->left)
              {
                  tmp_stack.push(tmp_node->left);
                  prev = tmp_node;
                  tmp_node = tmp_node->left;
              }
              if(tmp_node->right)
              {
                  tmp_stack.push(tmp_node->right);
                  prev = tmp_node;
                  tmp_node = tmp_node->right;
              }
              if(tmp_node->left==nullptr)
              {
                  prev = nullptr;
              }
          	}
        }
	}
int main()
{
    Node tmp1(1);
    Node tmp2(2);
    Node tmp3(3);
    Node tmp4(4);
    Node tmp5(5);
    Node tmp6(6);
    Node tmp7(7);
    Node tmp8(8);
    Node tmp9(9);
    
    inOrder(nullptr);
}
/////prob2  就是单独处理了一下0的情况，  prob3在有概率分布的情况下 每次选择的 flag_data值尽可能要处于中央


