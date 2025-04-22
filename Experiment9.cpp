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
   int height;
   struct node *RC;
}NODE;
 
class AVL
{
	NODE *root;
	int count;
	public:
	AVL()
	{
		root=NULL;
		count=0;
	}
	NODE* getroot()
	{
		return root;
	}
	
	int height(NODE *T)
	{
		int lh,rh;
		if(T==NULL)
			return 0;
		if(T->LC ==NULL && T->RC==NULL)
			return 0;
		lh=height(T->LC);
		rh=height(T->RC);
		if(lh>rh)
			return lh+1;
		else
			return rh+1;
	}
	
	int difference(NODE* T)
	{
		int l_height = height(T->LC);
		int r_height = height(T->RC);
		int b_factor = l_height - r_height;
		return b_factor;
	}
	
    NODE *rr_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->RC;
		Pptr->RC = Aptr->LC;
		Aptr->LC = Pptr;
		cout<<"Right-Right Rotation";
		return Aptr;
	}
	
    NODE *ll_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->LC;
		Pptr->LC = Aptr->RC;
		Aptr->RC = Pptr;
		cout<<"Left-Left Rotation";
		return Aptr;
	}
	
    NODE *lr_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->LC;
		Pptr->LC = rr_rotate(Pptr);
		cout<<"Left-Right Rotation";
		return ll_rotate(Pptr);	
	}
	
    NODE *rl_rotate(NODE * Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->RC;
		Pptr->RC = ll_rotate(Pptr);
		cout<<"Right-Left Rotation";
		return rr_rotate(Pptr);
	}
	
    NODE* balance(NODE* T)
	{
		int bal_factor = difference(T);
		if (bal_factor > 1) {
			if (difference(T->LC) > 0)
				T = ll_rotate(T);
			else
				T = lr_rotate(T);
		} else if (bal_factor < -1) {
			if (difference(T->RC) > 0)
				T = rl_rotate(T);
			else
				T = rr_rotate(T);
		}
		return T;	
	}
	
    NODE* insert(NODE* T,WORD w)
	{
		if (T == NULL) {
			T = new NODE;
			T->data = w;
			T->LC = NULL;
			T->RC = NULL;
			root=T;
			return T;
		} else if(strcmp(w.key,T->data.key)<0) {
				T->LC = insert(T->LC, w);
				T = balance(T);
		} else if (strcmp(w.key,T->data.key)>0) {
				T->RC = insert(T->RC, w);
				T = balance(T);
		} 
		
		root=T;
		return T;
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
};

int main(void)
{
   AVL B;
   int val,cho,n,cho1;
   WORD w;
   NODE* r;
   char key[30];
   cho=0;
   while(cho != 3)
   {
     cout<<"\n********DICTIONARY STORAGE using AVL*********";
     cout<<"\n1-ADD WORD";
     cout<<"\n2-DISPLAY DICTIONARY";
     cout<<"\n3-EXIT";
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
		r=B.insert(B.getroot(),w);
		break;
       case 2:
		B.displayIN(B.getroot());
		break;
	   case 3:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
   }

   return 0;
}
