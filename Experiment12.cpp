#include<iostream>
#include<fstream>
#include<cstring>
#include<ios>
#include<limits>

using namespace std;

typedef struct EMPLOYEE
{
    int emp_id;
    char name[20];
    char designation[20];
    int salary;
}Rec;

typedef struct INDEX
{
    int emp_id;
    int position;
}Ind_Rec;

class Employee
{
    private:
        Rec Records;
        Ind_Rec Ind_Records;
    public:
        Employee();
        void Create();
        void Display();
        void Update();
        void Delete();
        void Append();
        void Search();
};

Employee::Employee()
{
    Records.emp_id=-1;
    strcpy(Records.name,"");
    strcpy(Records.designation,"");
    Records.salary=0;
}

void Employee::Create()
{
    int i,j;
    char ch='y';
    fstream seqfile;
    fstream indexfile;
    i=0;
    indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
    seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
    do
    {
        cout<<"\n Enter Emp_ID: ";
        cin>>Records.emp_id;
        cout<<"\n Enter Name: ";
        cin>>Records.name;
        cout<<"\n Enter Designation: ";
        cin>>Records.designation;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\n Enter Salary: ";
        cin>>Records.salary;
        seqfile.write((char*)&Records,sizeof(Records))<<flush;
        Ind_Records.emp_id=Records.emp_id;
        Ind_Records.position=i;
        indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
        i++;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\nDo you want to add more records?";
        cin>>ch;
    }while(ch=='y');
    seqfile.close();
    indexfile.close();
}

void Employee::Display()
{
    fstream seqfile;
    fstream indexfile;
    int n,i,j;
    seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
    indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
    indexfile.seekg(0,ios::beg);
    seqfile.seekg(0,ios::beg);
    cout<<"\n The Contents of file are ..."<<endl;
    i=0;
    while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
    {
        i=Ind_Records.position*sizeof(Rec);
        seqfile.seekg(i,ios::beg);
        seqfile.read((char *)&Records,sizeof(Records));
        if(Records.emp_id!=-1)
        {
            cout<<"\nEmp_ID: "<<Records.emp_id;
            cout<<"\nName: "<<Records.name<<flush;
            cout<<"\nDesination: "<<Records.designation;
            cout<<"\nSalary: "<<Records.salary;
            cout<<"\n";
        }
    }
    seqfile.close();
    indexfile.close();
}

void Employee::Update()
{
    int pos,id;
    int New_emp_id;
    char New_name[10];
    char New_desig[20];
    int New_salary;
    cout<<"\n For updation,";
    cout<<"\n Enter the Emp_ID for for searching ";
    cin>>id;
    fstream seqfile;
    fstream indexfile;
    seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
    indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
    indexfile.seekg(0,ios::beg);
    pos=-1;
    while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
    {
        if(id==Ind_Records.emp_id)
        {
            pos=Ind_Records.position;
            break;
        }
    }
    if(pos==-1)
    {
        cout<<"\n The record is not present in the file";
        return;
    }
    else
    {
        cout<<"\n Enter the values for updation...";
        cout<<"\n Name: ";cin>>New_name;
        cout<<"\n Designation: ";cin>>New_desig;
        cout<<"\n Salary: ";cin>>New_salary;
        int offset=pos*sizeof(Rec);
        seqfile.seekp(offset);
        Records.emp_id=id;
        strcpy(Records.name,New_name);
        strcpy(Records.designation,New_desig);
        Records.salary=New_salary;
        seqfile.write((char*)&Records,sizeof(Records))<<flush;
        cout<<"\n The record is updated!!!";
    }
    seqfile.close();
    indexfile.close();
}

void Employee::Delete()
{
    int id,pos;
    cout<<"\n For deletion,";
    cout<<"\n Enter the Emp_ID for for searching ";
    cin>>id;
    fstream seqfile;
    fstream indexfile;
    seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
    indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
    seqfile.seekg(0,ios::beg);
    indexfile.seekg(0,ios::beg);
    pos=-1;
    while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
    {
        if(id==Ind_Records.emp_id)
        {
            pos=Ind_Records.position;
            Ind_Records.emp_id=-1;
            break;
        }
    }
    if(pos==-1)
    {
        cout<<"\n The record is not present in the file";
        return;
    }
    int offset=pos*sizeof(Rec);
    seqfile.seekp(offset);
    strcpy(Records.name,"");
    strcpy(Records.designation,"");
    Records.emp_id=-1;
    Records.salary=-1;
    seqfile.write((char*)&Records,sizeof(Records))<<flush;
    offset=pos*sizeof(Ind_Rec);
    indexfile.seekp(offset);
    Ind_Records.emp_id=-1;
    Ind_Records.position=pos;
    indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
    seqfile.seekg(0);
    indexfile.close();
    seqfile.close();
    cout<<"\n The record is Deleted!!!";
}

void Employee::Append()
{
    fstream seqfile;
    fstream indexfile;
    int pos;
    indexfile.open("IND.txt",ios::in|ios::binary);
    indexfile.seekg(0,ios::end);
    pos=indexfile.tellg()/sizeof(Ind_Records);
    indexfile.close();
    indexfile.open("IND.txt",ios::app|ios::binary);
    seqfile.open("EMP.txt",ios::app|ios::binary);
    cout<<"\n Enter the record for appending";
    cout<<"\nEmp_ID: ";cin>>Records.emp_id;
    cout<<"\nName: ";cin>>Records.name;
    cout<<"\nDesination: ";cin>>Records.designation;
    cout<<"\nSalary: ";cin>>Records.salary;
    seqfile.write((char*)&Records,sizeof(Records));
    Ind_Records.emp_id=Records.emp_id;
    Ind_Records.position=pos;
    indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
    seqfile.close();
    indexfile.close();
    cout<<"\n The record is Appended!!!";
}

void Employee::Search()
{
    fstream seqfile;
    fstream indexfile;
    int id,pos,offset;
    cout<<"\n Enter the Emp_ID for searching the record ";
    cin>>id;
    indexfile.open("IND.txt",ios::in|ios::binary);
    pos=-1;
    while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
    {
        if(id==Ind_Records.emp_id)
        {
            pos=Ind_Records.position;
            break;
        }
    }
    if(pos==-1)
    {
        cout<<"\n Record is not present in the file";
        return;
    }
    offset=pos*sizeof(Records);
    seqfile.open("EMP.txt",ios::in|ios::binary);
    seqfile.seekg(offset,ios::beg);
    seqfile.read((char *)&Records,sizeof(Records));
    if(Records.emp_id==-1)
    {
        cout<<"\n Record is not present in the file";
        return;
    }
    else
    {
        cout<<"\n The Record is present in the file and it is...";
        cout<<"\n Emp_ID: "<<Records.emp_id;
        cout<<"\n Name: "<<Records.name;
        cout<<"\n Designation: "<<Records.designation;
        cout<<"\n Salary: "<<Records.salary;
    }
    seqfile.close();
    indexfile.close();
}

int main()
{
    Employee List;
    char ans='y';
    int choice,key;
    fstream out;
    out.open("EMP.txt",ios::out);
    out.close();
    out.open("IND.txt",ios::out);
    out.close();
    choice=0;
    while(choice !=7)
    {
        cout<<"\n***************Index Sequential File**************"<<endl;
        cout<<"\n 1.Create File";
        cout<<"\n 2.Display All Employee Records";
        cout<<"\n 3.Update an Employee Information";
        cout<<"\n 4.Delete a Record";
        cout<<"\n 5.Append a Record";
        cout<<"\n 6.Search an Employee";
        cout<<"\n 7.Exit";
        cout<<"\n Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                List.Create();
                break;
            case 2:
                List.Display();
                break;
            case 3:
                List.Update();
                break;
            case 4:
                List.Delete();
                break;
            case 5:
                List.Append();
                break;
            case 6:
                List.Search();
                break;
            case 7:
                break;
            default:
                cout<<"Wrong Choice!!";
        }
    }
    return 0;
}
