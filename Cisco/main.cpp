#include<iostream>
#include<cstring>
#include<fstream>
#include "auto.h"
using namespace std;

int flagg=0;

class student
{
    
     public:
        char name[100],des[500];
        char *ret_des()
        {
            return des;
        }
        char * ret_name()
        {
            return name;
        }
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

student read_pass(char* s)
{
	ifstream fin;
	student obj;
    char *p;
	fin.open("sample1.dat",ios::binary|ios::in);
    while(fin.read((char*)&obj,sizeof(obj)))
    {	
        char * temp =obj.ret_name();
        if(strcmp(s,temp)==0)
        {
            flagg=1;
            fin.close();
            return obj;
            break;
        }
    }
    return obj;
}

int ver_mode(string com,char *p1, char *p2, char *p3,int mode)
{
    //cout<<"\t"<<com<<"\t"<<p1<<"\t"<<p2<<"\t"<<p3;
    char p[50];
    if(com.compare("enable")==0)
    {
        cout<<endl<<"Passowrd: ";
        cin.getline(p,50);
        if(strcmp(p,p1)==0)
            mode = 2;
        else
            cout<<"Incorrect Password\n";
    }
    if((com.compare("config t")==0))
    {
        cout<<endl<<"Passowrd: ";
        cin.getline(p,50);
        if(strcmp(p,p2)==0)
            mode = 3;
        else
            cout<<"Incorrect Password\n";
    }
    if(com.compare("exit")==0)
    {
        mode = mode -1;
    }
    
    
    return mode;
}

void read_record(trie * t1,trie * t2,trie * t3,int mode)
{
	ifstream fin;
	student obj;
        fin.open("command1.dat",ios::binary|ios::in);
        while(fin.read((char*)&obj,sizeof(obj)))
        {	
            data *d = new data;
            d->command = obj.name;
            d->desc = obj.des;
            t1->insert(d);
            //cout<<"\nInserted "<<d->command;
        }
        fin.close();

        fin.open("command2.dat",ios::binary|ios::in);
        while(fin.read((char*)&obj,sizeof(obj)))
        {	
            data *d = new data;
            d->command = obj.name;
            d->desc = obj.des;
            t2->insert(d);
            //cout<<"\nInserted "<<d->command;
        }
        fin.close();
    
        fin.open("command3.dat",ios::binary|ios::in);
        while(fin.read((char*)&obj,sizeof(obj)))
        {	
            data *d = new data;
            d->command = obj.name;
            d->desc = obj.des;
            t3->insert(d);
            //cout<<"\nInserted "<<d->command;
        }
        fin.close();
}

string pref(int mode)
{
    string pre;
    switch(mode)
    {
        case 1: pre='>';
            break;
        case 2: pre='#';
            break;
        case 3: pre="(config-term)";
            break;
        default:
            pre='>';
    }
    return pre;
}

int main()
{
    trie t1,t2,t3;
    int mode=1;
    student tf,ts,te;
    flagg=0;
    string s;
    char *p_conf,*p_cons,*p_en;
    tf = read_pass("config");
    p_conf = tf.ret_des();
    ts = read_pass("Console");
    p_cons = ts.ret_des();
    te = read_pass("enable");
    p_en = te.ret_des();
    
    char com[50];
    string pre;
    
    read_record(&t1,&t2,&t3,mode);
    string com1;
    data *e;
    do
    {
        pre = pref(mode);
        s = "Router" + pre;
        cout<<endl<<"Router"<<pre<<" ";
        if(mode == 1)
        {
            com1 = t1.autocomplete(s);
        }
        else if (mode == 2)
        {
            com1 = t2.autocomplete(s);
        }
        else if(mode == 3)
        {
            com1 = t3.autocomplete(s);
        }
        mode = ver_mode(com1,p_cons,p_en,p_conf,mode);
        if((com1.compare("clear")==0))
            clrscr;
    }while(mode>0);
    return 0;
}