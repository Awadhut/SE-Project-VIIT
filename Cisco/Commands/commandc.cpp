#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

class student
{
    
    
    public:
    char name[100],des[500];
        void print_data()
        {
            cout<<"\nName : - "<<name;
            cout<<"\nDescroption : - "<<des;
        }
        void read_data()
        {
            //cin.ignore();
            cout<<"\nEnter Name : - ";
            cin.getline(name,100);
            //cin.ignore();
            cout<<"Enter Description : - ";
            cin.getline(des,500);
            //cin.ignore();
            cout<<"\n";
        }
};

void write_record()
{
	fstream fout;
    student s;
    s.read_data();
	fout.open("command1.dat", ios::binary|ios::out|ios::app);
	fout.write((char*)&s,sizeof(s));
	fout.close();
    
    cout<<"Wrote Successfully";
}

void read_record()
{
	ifstream fin;
	student obj;
    
	fin.open("command1.dat",ios::binary|ios::in);
    while(fin.read((char*)&obj,sizeof(obj)))
    {	
        
		obj.print_data();
    }
	fin.close();
}

int main()
{
    student obj;
    //obj.read_data();
    //obj.print_data();
    int choice;
    do
    {
        cout<<"\n1.Insert\n2.Read\n3.Quit";
        cin>>choice;
        cin.ignore();
        switch(choice)
        {
            case 1: write_record();
                break;
            case 2: read_record();
                break;
            case 3:
                return 0;
            default:
                cout<<"Invlaid OPtions";
        }
        
    }while(1);
    
	return 0;
}
