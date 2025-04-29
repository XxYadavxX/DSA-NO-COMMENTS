#include<iostream>
#include<cstring>
#include<ios>
#include<limits>

using namespace std;
typedef struct patient{
    int patientID;
    int severity;
}PATIENT;

class priorityQ
{
    private:
        int nop;
        PATIENT P[50];
        const char priority[3][10]={"Least","Medium","Top"};
    public:
    priorityQ()
    {
        for (int i=0;i<50;i++)
        {
            P[i].patientID=0;
            P[i].severity=0;
        }
        nop=0;
    }
    
    void displayQueue()
    {
        for (int i=1;i<=nop;i++)
            cout<<"\n"<<P[i].patientID<<"  "<<priority[P[i].severity];
    }
    
    void addPatient(PATIENT p)
    {
        int i;
        PATIENT t;
        i=nop;
        if(i==0)
        {
            P[++i]=p;
            nop=i;
        }
        else
        {
            P[++i]=p;
            nop=i;
            while(i>1 && P[i].severity > P[i/2].severity)
            {
                t=P[i];
                P[i]=P[i/2];
                P[i/2]=t;
                i=i/2;
            }
        }
    }
    
    void deletePatient()
    {       
        PATIENT t;
        int i,j;
        t=P[1];
        P[1]= P[nop];
        P[nop]=t;
        nop--;
        i=1;
        
        while(2*i<=nop)
        {
            j=2*i;
            if(j+1<=nop && P[j+1].severity>P[j].severity)
                j++;

            if(P[i].severity<P[j].severity)
            {
                t=P[i];
                P[i]=P[j];
                P[j]=t;
                i=j;
            }
            else
                break;
        }
    }
};

int main(void)
{
   priorityQ B;
   int cho,n,cho1;
   PATIENT p;
   char key[30];
   cho=0;
   while(cho != 4)
   {
     cout<<"\n************PATIENT QUEUE*************";
     cout<<"\n1-ADD PATIENT TO QUEUE";
     cout<<"\n2-DISPLAY QUEUE";
     cout<<"\n3-DELETE PATIENT FROM QUEUE";
     cout<<"\n4-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
     switch(cho)
     {
       case 1:
        cout<<"\nEnter patient ID:";
        cin>>p.patientID;
        cout<<"\nEnter severity\n\t2. Top \n\t1. Medium \n\t0. Least\n\t::";
        cin>>n;
        p.severity=n;    
        B.addPatient(p);
        break;
       case 2:
        B.displayQueue();
        break;
       case 3:
        B.deletePatient();
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
