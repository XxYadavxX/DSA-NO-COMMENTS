#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

struct node
{
	struct node* left;
	char data;
	struct node* right;
};

class Stack
{
	private:
		struct node* S[30];
		int top;
	public:
		Stack()
	    {
	      top=-1;
	    }

		int empty()
	    {
			if(top==-1)
				return 1;
			return 0;
	    }

		void push(struct node* val)
	    {
			S[++top]=val;
	    }

		struct node* pop()
	    {
			return(S[top--]);
	    }
};

class ExpTree
{   
	private:
		char Exp[30];
		struct node* root;
		Stack s;
	public:
		ExpTree()
		{
			root=NULL;
		}
		
		void initialize()
		{
			root=NULL;
		}
		
		void readExpression() 
		{
			cout<<"Enter the Prefix Expression"<<endl;
			cin>>Exp;
		}
		
		void printExpression()
		{
			cout<<"The expression is ::"<<Exp<<endl;
		}
		
		bool isOperand(char t)
		{	
			if((t>='a' && t<='z')||(t>='A' && t<='Z') ||(t>=0 && t<=9))
				return true;
			else
				return false;	
		}
		
		bool isOperator(char t)
		{
			if(t=='*' || t=='+' || t=='-' || t=='/' || t=='%')
				return true;
			else
				return false;
		}

		void addNode(char token)
		{	 
			struct node *p;
			p= new struct node;
			p->left=NULL;
			p->data=token;
			p->right=NULL;

			if(isOperand (token))
			{  	 
				s.push(p);
				root=p;
			}
			else if(isOperator (token))
			{
				p->left=s.pop();
				p->right=s.pop();
				s.push(p);
				root=p;
			}
			else
				cout<<"INVALID EXPRESSION"<<endl;
		}
		
		void buildTree()
		{
			initialize();
			for(int i=strlen(Exp)-1;i>=0;i--){         
				addNode(Exp[i]);
			}	
		}
		
		void inorder(struct node* t)
		{
			if(t)
			{
				inorder(t->left);
				cout<<t->data;
				inorder(t->right);
			}
		}
		
		struct node* getRoot()
		{ 
			return root;
		}

		void nonRecursivePost(struct node* root)
		{
			if (root == NULL)
				return;

			Stack stack1, stack2;

			stack1.push(root);
			struct node* node;

			while (!stack1.empty()) {
				node = stack1.pop();
				stack2.push(node);

				if (node->left)
					stack1.push(node->left);
				if (node->right)
					stack1.push(node->right);
			}

			while (!stack2.empty()) {
				node = stack2.pop();
				cout << node->data << " ";
			}	
		}
};

int main(){
  	ExpTree e1;
  	int choice=0;
  	
  	while(choice!=6)
  	{	
  		cout<<"\n*************Expression Tree***************";
  		cout<<"\n1. Read Expression";
  		cout<<"\n2. Print Expression";
  		cout<<"\n3. Build Tree ";
  		cout<<"\n4. Print Tree Inorder";
		cout<<"\n5. Print Tree Non Recurssive Postorder";
  		cout<<"\n6. Exit Application";
  		cout<<"\nEnter your choice::";
		cin>>choice;
  		switch (choice){
  			case 1:
				e1.readExpression();
  			 	break;
  			case 2:
  			 	e1.printExpression();
  			 	break;
  			case 3:
  			 	e1.buildTree();
  			 	break;
  			case 4:
  			 	e1.inorder(e1.getRoot());
  			 	break;
			case 5:
  			 	e1.nonRecursivePost(e1.getRoot());
  			 	break;
  			case 6:
  			 	break;
  			default :
  			    cout<<"\nWrong choice!!";
  		}
  	}
}
