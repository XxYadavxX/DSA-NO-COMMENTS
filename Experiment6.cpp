#include <iostream>
#include <cstdlib>
#include <cstdio>     
#include <cstring>
using namespace std;
typedef struct Node
{
	int data;
	struct Node *next;
}NODE;

class stack
{
	int data[30];
	int top;
	public:
	stack()
	{
		top=-1;
	}
	int empty()
	{
		if(top==-1)
			return 1;
		return 0;
	}
	void push(int x)
	{
		data[++top]=x;
	}
	int pop()
	{
		return(data[top--]);
	}
};

class Queue
{
	private:
	int r,f;
	int data[30];
	public:
	Queue()
	{
		r=f=-1;
	}
	void init()
	{
		r=f=-1;
	}
	int empty()
	{
		if(r==-1)
			return 1;
		return 0;
	}
	void insert(int x)
	{
		if(r==-1)
		{
			r=f=0;
			data[r]=x;
		}
		else
		{
			r=r+1;
			data[r]=x;
		}
	}
	int delet()
	{
		int x=data[f];
		if(r==f)
			f=r=-1;
		else	
			f=f+1;
		return(x);
	}
};

class Graph
{
	int G[10][10];
	NODE Header[10];
	int visited[10];
	int mNodes;
	int lNodes;
	const char landmark[5][30]={"Comp","Admin","Library","Canteen","Garden"};
	public:
	Graph()
	{
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
		}
		for (int i=0;i<10;i++)
			visited[i]=0;
		mNodes=0;
		lNodes=0;
	}
	void initAM()
	{
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
	}
	void initAL()
	{
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
		}
		lNodes=0;
	}
	void initVisited()
	{
		for (int i=0;i<10;i++)
			visited[i]=0;
	}
	void printHeader()
	{
		for (int i=0;i<10;i++)
		{
			cout<<"\n["<<landmark[Header[i].data-1]<<"|"<<Header[i].next<<"]->NULL";
		}
	}
	void readGAM()
	{
		int i,j;
		int flag=1;
		mNodes=5;
		while(flag==1)
		{
			cout<<"\nEnter source node:";
			cin>>i;
			cout<<"\nEnter destination node:";
			cin>>j;
			G[i][j]=1;
			cout<<"\nDo you want to add more edge yes=1 or no=0:";
			cin>>flag;
		}
	}
	void printGAM()
	{
		int i,j,k=0;
		cout<<"\n\t";
		for (i=0;i<mNodes;i++)
			cout<<landmark[i]<<"\t";
		cout<<"\n";
		for (i=1;i<=mNodes;i++)
		{
			cout<<landmark[i-1]<<"\t";
			for(j=1;j<=mNodes;j++)
				cout<<G[i][j]<<"\t";
			cout<<"\n";
		}
	}
	void addNode(int pos,int val)
	{
		NODE *p,*cur;
		p=new NODE;
		p->data=val;
		p->next=NULL;
		if (Header[pos].next ==NULL)
			Header[pos].next=p;
		else
		{
			cur=Header[pos].next;
			while(cur->next !=NULL)
				cur=cur->next;
			cur->next=p;
		}
	}
	void readGAL(int n)
	{
		int i,j;
		int nan,val;
		lNodes=n;
		for (i=0;i<n;i++)
		{
			cout<<"\nHow many no. of adjacent nodes to node "<<Header[i].data<<" :";
			cin>>nan;
			if(nan !=0)
				for (j=1;j<=nan;j++)
				{
					cout<<"\nEnter value of "<<j<<" node::";
					cin>>val;
					addNode(i,val);
				}
		}
		cout<<"\nNo. of Nodes in List::"<<lNodes;
	}
	void printGAL()
	{
		int i,j;
		int nan,val;
		NODE *cur;
		for (i=0;i<lNodes;i++)
		{
			cur=Header[i].next;
			cout<<"\n["<<landmark[Header[i].data-1]<<"|"<<Header[i].next<<"]->";
			while(cur !=NULL)
			{
				cout<<"["<<landmark[cur->data-1]<<"|"<<cur->next<<"]->";
				cur=cur->next;
			}
			cout<<"NULL";
		}
	}
	void DFS_RECURSIVE(int i)
	{
		int j;
		cout<<" "<<landmark[i-1];
		visited[i]=1;
		for(j=1;j<=mNodes;j++)
			if(!visited[j] && G[i][j]==1)
				DFS_RECURSIVE(j);
	}
	void DFS_NON_RECURSIVE(int v)
	{
		stack s;
		int i;
		for (int i=0;i<10;i++)
			visited[i]=0;
		s.push(v);
		while(!s.empty())
		{
			v=s.pop();
			if(!visited[v])
			{
				visited[v]=1;
				cout<<"  "<<landmark[v-1];
				for(i=1;i<=mNodes;i++)
				{
					if(visited[i]==0 && G[v][i]!=0)
						s.push(i);
				}
			}
		}
	}
	void BFS_Matrix(int v)
	{
		Queue q;
		int i,j;
		for (int i=0;i<10;i++)
			visited[i]=0;
		q.insert(v);
		cout<<"  "<<landmark[v-1];
		while(!q.empty())
		{
			v=q.delet();
			for(i=1;i<=mNodes;i++)
				if(visited[i]==0 && G[v][i]!=0)
				{
					q.insert(i);
					visited[i]=1;
					cout<<"  "<<landmark[i-1];
				}
		}
	}
	void BFS_List(int v)
	{
		Queue q;
		int i,j;
		NODE *cur;
		for (int i=0;i<10;i++)
			visited[i]=0;
		q.init();
		q.insert(v);
		visited[v]=1;
		while(!q.empty())
		{
			v=q.delet();
			cout<<landmark[v-1]<<"  ";
			cur=Header[v-1].next;
			while(cur!=NULL)
			{
				if(visited[cur->data]==0)
				{
					q.insert(cur->data);
					visited[cur->data]=1;
				}
				cur=cur->next;
			}
			cout<<"\n";
		}
	}
};

int main()
{
	Graph g1;
	int n,val;
	int cho=0;
	while(cho != 8)
	{
		cout<<"\n********GRAPH TRAVERSAL*********";
		cout<<"\n1-Read Graph Adjacency Matrix";
		cout<<"\n2-Print Graph Adjacency Matrix";
		cout<<"\n3-Read Graph Adjacency List";
		cout<<"\n4-Print Graph Adjacency List";
		cout<<"\n5-Recursive DFS on Adjacency Matrix";
		cout<<"\n6-Non Recursive DFS on Adjacency Matrix";
		cout<<"\n7-BFS on Adjacency List";
		cout<<"\n8-EXIT";
		cout<<"\nEnter ur choice:";
		cin>>cho;
		switch(cho)
		{
			case 1:
				g1.initAM();
				g1.readGAM();
				break;
			case 2:
				g1.printGAM();
				break;
			case 3:
				g1.initAL();
				g1.printHeader();
				cout<<"\nHow many nodes in graph:";
				cin>>n;
				g1.readGAL(n);
				break;
			case 4:
				g1.printHeader();
				cout<<"\nAdjecancy List\n";
				g1.printGAL();
				break;
			case 5:
				cout<<"\nEnter the starting node::";
				cin>>val;
				g1.initVisited();
				g1.DFS_RECURSIVE(val);
				break;
			case 6:
				cout<<"\nEnter the starting node::";
				cin>>val;
				g1.DFS_NON_RECURSIVE(val);
				break;
			case 7:
				cout<<"\nEnter the starting node::";
				cin>>val;
				g1.BFS_List(val);
				break;
			case 8:
				cout<<"\nProgram Exits!!";
				break;
			default:
				cout<<"\nWrong choice!";
		}
	}
	return 0;
}
