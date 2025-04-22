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

class Graph
{
	int G[10][10];
	NODE Header[10];
	const char city[5][20]={"Pune","Mumbai","Delhi","Jaipur","Chakan"};
	int visited[10];
	int mNodes;
	int lNodes;
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
			visited[i]=0;
		}
		mNodes=0;
		lNodes=0;
	}
	
	void init_Matrix()
	{
		mNodes=5;
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
	}
	
	void init_List()
	{
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
			visited[i]=0;
		}
	}
	
	void init_visited()
	{
		for (int i=0;i<10;i++)
			visited[i]=0;
	}
	
	void readGAM()
	{
		int i,j;
		int flag=1;
		init_Matrix();
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
			cout<<city[i]<<"\t";
		cout<<"\n";
		for (i=1;i<=mNodes;i++)
		{
			cout<<city[i-1]<<"\t";
			for(j=1;j<=mNodes;j++)
				cout<<G[i][j]<<"\t";
			
			cout<<"\n";
		}
	}

	void DFS_RECURSIVE(int i)
	{
		int j;
		cout<<" "<<i;
		visited[i]=1;
		for(j=1;j<=mNodes;j++)
			if(!visited[j] && G[i][j]==1)
				DFS_RECURSIVE(j);
	}
	
	bool isConnected()
	{
		int i;
		init_visited();
		DFS_RECURSIVE(1);
		for(i=1;i<=mNodes;i++)
			if(visited[i]==0)
				return false;
		
		return true;
	}
};

int main()
{
    Graph g1;
	int n;
	int cho=0;
	while(cho != 4)
	{
     cout<<"\n********CONNECTED GRAPH*********";
     cout<<"\n1-Read Graph Adjacency Matrix";
     cout<<"\n2-Print Graph Adjacency Matrix";
	 cout<<"\n3-Check Graph Connected or Not Connected";
     cout<<"\n4-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
     switch(cho)
     {
       case 1:
		g1.readGAM();
		break;
       case 2:
		g1.printGAM();
		break;
	   case 3:
		if (g1.isConnected())
			cout<<"\nGraph is connected!";
		else
			cout<<"\nGraph is not connected!";
		break;
	   case 4:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
    }
	
    return 0;
}
