#include<iostream>
#include<unistd.h>
#include <termios.h>
#include<string>

#define clrscr cout<<"\033[2J\033[1;1H" 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

using namespace std;
const int ALPHABET_SIZE = 26;


int getch() 
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

typedef struct contacts
{
    string command;
    string desc;
}data;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    data *d;
    bool eow;  //End of Word
};
class trie
{
private:
    struct TrieNode *root;
public:
    trie()
    {
        root = createnode();   
    }
    bool islastnode(TrieNode* r) 
    { 
        for (int i = 0; i < ALPHABET_SIZE; i++) 
            if (r->children[i]) 
                return 0; 
        return 1; 
    } 
    struct TrieNode *createnode(void) 
    { 
        struct TrieNode *temp =  new TrieNode; 
        temp->eow = false; 
        for (int i = 0; i < ALPHABET_SIZE; i++) 
            temp->children[i] = NULL; 
        return temp; 
    } 
    void insert(data *d1) 
    { 
        struct TrieNode *temp = root; 
        for (int i = 0; i < d1->command.length(); i++) 
        { 
            int index = d1->command[i] - 'a'; 
            if (!temp->children[index]) 
                temp->children[index] = createnode(); 
            temp = temp->children[index]; 
        } 
        temp->eow = true; 
        temp->d = d1;
    } 
    data* search(const string key) 
    { 
        int length = key.length(); 
        struct TrieNode *temp = root; 
        for (int level = 0; level < length; level++) 
        { 
            int index = CHAR_TO_INDEX(key[level]); 
            if (!temp->children[index]) 
                return NULL; 
            temp = temp->children[index]; 
        } 
        if (temp != NULL && temp->eow)
            return temp->d;
    } 
    string currPrefix;
    void suggestionsRec(TrieNode* r) 
    {        
        if (r->eow) 
        { 
            cout << currPrefix;
            data *f = search(currPrefix);
            cout<<"\t\t\t"<<f->desc;
            cout << endl; 
        } 
        if (islastnode(r)) 
        {
            currPrefix.pop_back();
            return; 
        }
        for (int i = 0; i < ALPHABET_SIZE; i++) 
        { 
            if (r->children[i]) 
            { 
                currPrefix.push_back(97 + i); 
                
                suggestionsRec(r->children[i] ); 
            } 
        } 
        currPrefix.pop_back();
    } 
    int printAutoSuggestions(const string str) 
    { 
        struct TrieNode* temp = root; 
        int level; 
        int n = str.length(); 
        //cout<<"\n";
        for (level = 0; level < n; level++) 
        { 
            int index = CHAR_TO_INDEX(str[level]); 
            if (!temp->children[index]) 
                return 0; 
            temp = temp->children[index]; 
        } 
        bool isword = (temp->eow == true); 
        bool islast = islastnode(temp); 
        if (isword && islast) 
        { 
            cout<<str<< endl; 
            return -1; 
        } 
        if (!islast) 
        { 
            string prefix = str; 
            currPrefix = prefix;
            suggestionsRec(temp); 
            return 1; 
        } 
    } 
    bool success = 1;
    string autocomplete(string x)
    {
        int i;
        char ch = 'a';
        string str = "";
        while(ch != '\n')
        {
            ch = getch();
            if(ch != 127 && (char)ch != '\n' && (char)ch != '?')
            {
                cout<<(char)ch;
                str = str + (char)ch;
            } 
            else if((char)ch=='\n')
            {
                data *k;
                k = search(str);
                if(k)
                {
                    cout<<endl<<k->command<<"\t\t\t"<<k->desc;
                }
                else
                {
                    cout<<"\nInvalid Command\n";
                }
            }
            else if(ch == 127)
            {
                if(str.size() > 0)
                {
                    string temp;
                    for(int i =0;i<str.size()-1;i++)
                    {
                        temp = temp + str[i];
                    }
                    cout<<'\b';
                    str = temp;
                }
            }

            else if(ch == '?')
            {
                cout<<ch;
                cout<<endl;
                if(str.size() == 0)
                {
                    for(int i=0;i<26;i++)
                    {
                        string y = "";
                        y = y + (char)(i + 'a');
                        int j = printAutoSuggestions(y);
                    }
                }
                else
                {
                    int j;
                    j = printAutoSuggestions(str);
                }
                ch='\n';
            }
            
        }
        return str;
    }
};
