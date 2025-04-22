#include<iostream>
#include<cstring>
#include<ios>
#include<limits>

using namespace std;
typedef struct keyword{
	char key[20];
	char meaning[100];
}WORD;
typedef struct node
{
   struct node *LC;
   WORD data;
   struct node *RC;
}NODE;

class Stack
{
	private:
		int top;
		NODE *data[30];
	public:
	Stack()
    {
		top=-1;
    }
	int isEmpty()
    {
		if(top == -1)
			return 1;
		else
			return 0;
    }
	void push(NODE* p)
    {
		data[++top]=p;
    }
   
	NODE* pop()
    {
		return(data[top--]);
    }
};
 
class BST
{
	NODE *root;
	int count;
	public:
	BST()
	{
		root=NULL;
		count=0;
	}
	NODE* getroot()
	{
		return root;
	}
	
	void displayIN(NODE *T)
	{
		if(T)
		{
			displayIN(T->LC);
			cout<<T->data.key<<":"<<T->data.meaning<<endl;
			displayIN(T->RC);
		}
	}
	
	void displayDesending(NODE* root)
	{
		WORD words[100];
		Stack s;
		NODE *p;
		p=root;
		int i=0,n=0;
		while(p!=NULL)
		{
			s.push(p);
			p=p->LC;
		}
		while(!s.isEmpty())
		{
			p=s.pop();
			strcpy(words[n].key,p->data.key);
			strcpy(words[n].meaning,p->data.meaning);
			n++;
			p=p->RC;
			while(p!=NULL)
			{
				s.push(p);
				p=p->LC;
			}
		}
		cout<<"\n";
		for(i=n-1;i>=0;i--)
			cout<<words[i].key<<":"<<words[i].meaning<<endl;
	}
	
	void addNode(WORD w)
	{
		NODE *p,*q,*cur;
		p=new NODE;
		p->data=w;
		p->LC=p->RC=NULL;
		if(root==NULL)
			root=p;
		else
		{
			cur=root;

			while(cur)
			{
				q=cur;
				if(strcmp(cur->data.key,w.key)==0)
				{
					cout<<"\nDuplicate Node!";
					return ;
				}
				if(strcmp(cur->data.key,w.key)>0)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
			if(strcmp(q->data.key,w.key)>0)
				q->LC=p;
			else
				q->RC=p;
			
		}
		return;
	}
	
	void deleteNode(char key[])
	{
		NODE *parent,*cur,*p,*q,*t;
		bool found=false;
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;

			while(cur)
			{
				if(strcmp(cur->data.key,key) == 0)
				{
					cout<<cur->data.key<<" : "<<cur->data.meaning<<" will be deleted!";
					found=true;
					if(cur == root)
					{
						cout<<"\nNode "<<cur->data.key<<" is root node!";
						if(cur->LC ==NULL && cur->RC == NULL)
						{
							root=NULL;
							delete cur;
						}
						else
						if(cur->LC !=NULL && cur->RC == NULL)
						{
							root=root->LC;
							delete cur;
						}
						else
						if(cur->RC != NULL)
						{
							if((cur->RC)->LC == NULL)
							{
								p=cur->RC;
								cur->data=p->data;
								cur->RC=p->RC;
								delete p;
							}
							else
							{
								p=t=cur->RC;
								while(t)
								{
								q=p;
								p=t;
								t=t->LC;
								}
								cur->data=p->data;
								q->LC=NULL;
								delete p;
							}
						}
					}
					else
					if(cur->LC == NULL && cur->RC == NULL)
					{
						cout<<"\nLeaf Node of "<<parent->data.key;
						if(strcmp((parent->LC)->data.key,key)==0)
						{
							cout<<"\nLeft Child!!";
							parent->LC=NULL;
						}
						else
						{
							cout<<"\nRight Child!!";
							parent->RC=NULL;
						}
						delete cur;
					}
					else
					if(strcmp((parent->LC)->data.key,key)==0)
					{
						cout<<"\nLeft child Node of "<<parent->data.key;
						if(cur->LC != NULL && cur->RC == NULL)
							parent->LC=cur->LC;
						else if(cur->LC == NULL && cur->RC != NULL)
							parent->LC=cur->RC;
						
						delete cur;
					}
					else
					if(strcmp((parent->RC)->data.key,key)==0)
					{
						cout<<"\nRight child Node of "<<parent->data.key;
						if(cur->LC != NULL && cur->RC == NULL)
							parent->RC=cur->LC;
						else if(cur->LC == NULL && cur->RC != NULL)
							parent->RC=cur->RC;
						
						delete cur;
					}
					else
					if(cur->LC != NULL && cur->RC != NULL)
					{
						cout<<"\nNode "<<cur->data.key<<" has both left & right child!";
						if((cur->RC)->LC ==NULL)
						{
							p=cur->RC;
							cur->data=p->data;
							cur->RC=p->RC;
							delete p;
						}
						else
						{
							p=t=cur->RC;
							while(t)
							{
								q=p;
								p=t;
								t=t->LC;
							}
							cur->data=p->data;
							q->LC=NULL;
							delete p;
						}
					}
					
					return;
				}
				if(strcmp(cur->data.key,key)>0)
				{
					parent=cur;
					cur=cur->LC;
				}
				else
				{
					parent=cur;
					cur=cur->RC;;
				}
			}
			cout<<"\nNode with "<<key<<" not found!!";
		}
		
	}

	void updateNode(char key[])
	{
		NODE *q,*cur;
		char meaning[100];
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;

			while(cur)
			{
				q=cur;
				if(strcmp(cur->data.key,key) == 0)
				{
					cout<<cur->data.key<<" : "<<cur->data.meaning;
					cout<<"\nEnter new meaning of "<<cur->data.key<<" ::";
					cin.clear();
					fflush(stdin);
					cin.getline(meaning,100);
					strcpy(cur->data.meaning,meaning);
					cout<<"Dictionary word updated!!";
					return ;
				}
				if(strcmp(cur->data.key,key)>0)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
		}
		cout<<"\nNode with "<<key<<" not found!!";
		return;
	}	
	
	void searchNode(char key[])
	{
		NODE *q,*cur;
		
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;
			count=0;
			while(cur)
			{
				count++;
				q=cur;
				if(strcmp(cur->data.key,key) == 0)
				{
					cout<<cur->data.key<<" : "<<cur->data.meaning;
					cout<<"\nFound after "<<count<<" no. of comparisons";
					return ;
				}
				if(strcmp(cur->data.key,key)>0)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
		}
		cout<<"\nNode with word "<<key<<" not found "<<" after "<<count<<" comparisons";
		return;
	}
};

int main(void)
{
   BST B;
   int val,cho,n,cho1;
   WORD w;
   char key[30];
   cho=0;
   while(cho != 7)
   {
     cout<<"\n********DICTIONARY STORAGE*********";
     cout<<"\n1-ADD WORD";
     cout<<"\n2-DISPLAY WORD";
	 cout<<"\n3-DELETE WORD FROM DICTIONARY";
	 cout<<"\n4-UPDATE WORD OF DICTIONARY";
	 cout<<"\n5-DISPLAY DICTIONARY WORDS ASCENDING OR DECENDING ORDER";
	 cout<<"\n6-SEARCH WORD IN DICTIONARY";
     cout<<"\n7-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
     switch(cho)
     {
       case 1:
		cout<<"\nEnter keyword:";
		cin.clear();
		fflush(stdin);
		cin.getline(w.key,20);
		cout<<"\nEnter meaning of the word:";
		cin.clear();
		fflush(stdin);
		cin.getline(w.meaning,100);
		B.addNode(w);
		break;
       case 2:
		B.displayIN(B.getroot());
		break;
       
	   case 3:
		cout<<"\nEnter keyword to be deleted:";
		cin.clear();
		fflush(stdin);
		cin.getline(key,30);
		B.deleteNode(key);
		break;
	   case 4:
		cout<<"\nEnter keyword to be Updated:";
		cin.clear();
		fflush(stdin);
		cin.getline(key,30);
		B.updateNode(key);
		break;
	   case 5:
		cout<<"\n1. Ascending Order";
		cout<<"\n2. Descending Order";
		cout<<"\nEnter your choice::";
		cin>>cho1;
		if (cho1==1)
			B.displayIN(B.getroot());
		else
			B.displayDesending(B.getroot());
		break;
	   case 6:
		cout<<"\nEnter keyword to be searched:";
		cin.clear();
		fflush(stdin);
		cin.getline(key,30);
		B.searchNode(key);
		break;
	   case 7:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
   }
   return 0;
}
