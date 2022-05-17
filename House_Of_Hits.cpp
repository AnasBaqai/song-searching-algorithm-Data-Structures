#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<bits/stdc++.h> 
#include<windows.h>
#include<conio.h>
#include<algorithm>
#include<tuple>
using namespace std;
class node;
int disp();
void most_played_song(vector<vector<string>>);
node* search(node*,string);
COORD coord= {0,0}; // this is global variable
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


// An AVL tree node 
class node 
{ 
    public:
     vector<string> record;
        node* left;
        node* right;
        int height;
        node(vector<string> val)
        {
            record=val;    
            left=NULL;
            right=NULL;
            height=1;
        }
        node(){
           
            left=NULL;
            right=NULL;
        }
}; 

// A utility function to get maximum
// of two integers 
int max(int a, int b); 

// A utility function to get the 
// height of the tree 
int height(node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 

// A utility function to get maximum
// of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

/* Helper function that allocates a 
   new node with the given key and 
   NULL left and right pointers. */


// A utility function to right
// rotate subtree rooted with y 
// See the diagram given above. 
node *rightRotate(node *y) 
{ 
    node *x = y->left; 
    node *T2 = x->right; 

    // Perform rotation 
    x->right = y; 
    y->left = T2; 

    // Update heights 
    y->height = max(height(y->left),
                    height(y->right)) + 1; 
    x->height = max(height(x->left),
                    height(x->right)) + 1; 

    // Return new root 
    return x; 
} 

// A utility function to left 
// rotate subtree rooted with x 
// See the diagram given above. 
node *leftRotate(node *x) 
{ 
    node *y = x->right; 
    node *T2 = y->left; 

    // Perform rotation 
    y->left = x; 
    x->right = T2; 

    // Update heights 
    x->height = max(height(x->left),    
                    height(x->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 

    // Return new root 
    return y; 
} 

// Get Balance factor of node N 
int getBalance(node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree. 
node* insert(node* root, vector<string> row) 
{ 
    // 1. Perform the normal BST insertion

    if (root == NULL) 
        return new node(row); 

    if(root->record[0]==row[0])
        return root;
    if (row[8]<  root->record[8]) 
        root->left = insert(root->left,row); 
    else if (row[8] > root->record[8]) 
        root->right = insert(root->right, row); 
    else // Equal keys are not allowed in BST 
        return root; 

    // 2. Update height of this ancestor node 
    root->height = 1 + max(height(root->left), 
                        height(root->right)); 

    /* 3. Get the balance factor of this ancestor 
        node to check whether this node became 
        unbalanced */
    int balance = getBalance(root); 

    // If this node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && row[8] < root->left->record[8]) 
        return rightRotate(root); 

    // Right Right Case 
    if (balance < -1 && row[8]> root->right->record[8]) 
        return leftRotate(root); 

    // Left Right Case 
    if (balance > 1 && row[8] > root->left->record[8]) 
    { 
        root->left = leftRotate(root->left); 
        return rightRotate(root); 
    } 

    // Right Left Case 
    if (balance < -1 && row[8] < root->right->record[8]) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 

    // return the (unchanged) node pointer 
    return root; 
}

 stack<vector<string>> st;
 
queue<vector<string>> q;
 void Inorder(node* root)
        {
            if (!root) 
                return;
                Inorder(root->left);
                st.push(root->record);
                q.push(root->record);
                Inorder(root->right);
        }

        // most streamed songs.
  void top_10(){
      cout<<"SONG\t\tRANK\t\tDATE\t\tNAME\t\t\n";
            for(int i=0;i<10;i++)
            {
            vector<string> disp=st.top();
            st.pop();
            for(int j=0;j<4;j++)
            {
                cout<<disp[j]<<"|";
            }
            cout<<endl;
        }
        }

tuple<node*,bool>iterativeSearch( node* root, string name)
{
    // Traverse until root reaches to dead end
    while (root != NULL) {
        // pass right subtree as new tree
        if ( name> root->record[8])
            root = root->right;
 
        // pass left subtree as new tree
        else if (name < root->record[8])
            root = root->left;
        else
            return {root,true}; // if the key is found return 1
    }
    return {root,false};
}

void search_by_stream(node* root)
{
    string name;
    cout<<"\nEnter the stream number of a song you want to search:";
    cin>>name;
  // bool isFound;
  // node* temp;
   auto [temp,isFound] =iterativeSearch(root,name);
   //temp=search(root,name);
    if(isFound==false)
            cout<<"record not found";
    else{
       cout<<"record found";
       cout<<endl;
      for(int i=0;i<9;i++)
        {
            cout<<temp->record[i]<<" ";
        }
        if(isFound==false)
            cout<<"record not found";
    }

}

/*tuple<node*,bool> search(node* root,string name)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL )
    { 
       return {root,false};
    }
    // Key is greater than root's key
    if (root->record[8] < name)
       return {search(root->right, name),false};

    // Key is smaller than root's key
    else if(root->record[8]> name)
    return {search(root->left, name),false};
    else
     return {root,true};
}*/


void search_by_name(string fname){
     vector<vector<string>> c;
            int isFound=0;    	
	    vector<string> row;
	    string line, word;
        string name;
        cout<<"Enter the name you want to search:";
        cin>>name;
            fstream file (fname, ios::in);
	    if(file.is_open())
	    {
            cout<<"searching......\n";
		    while(getline(file, line))
		    {
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
                row.push_back(word);

                for(int k=0;k<row.size();k++)
                {
                    if(row[k]==name)
                    {
                        c.push_back(row);
                        isFound=1;
                        break;
                    }
                }
             if(isFound==1)
                    {
                        break;
                    }
		
		}
	}
	else
		cout<<"Could not open the file\n";
        if(isFound!=1)
        {
            cout<<"record not found";
        }
    else{
	for(int i=0;i<c.size();i++)
	{
		for(int j=0;j<c[i].size();j++)
		{
			cout<<c[i][j]<<" ";
		}
		cout<<"\n";
	}    
    }
    file.close();
}

//least recommended songs
void random_recommendation(node* root)
{
    Inorder(root);
     cout<<"SONG\t\tRANK\t\tDATE\t\tNAME\t\t\n";
    for(int i=0;i<10;i++){
        for(int i=0;i<5;i++)
        {
            vector<string> disp=q.front();
            q.pop();
            for(i=0;i<4;i++)
            {
                cout<<disp[i]<<"|";
            }
            cout<<endl;
        }
    }

}
//our recommandation
void rod(vector<vector<string>> content)
{
        vector<vector<string>> temp=content;
        random_shuffle(temp.begin(),temp.end());
    cout<<"SONG\t\tRANK\t\tDATE\t\tNAME\t\t\n";
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<4;j++)
            {
                cout<<temp[i][j]<<"|";
            }
            cout<<endl;
        }
}

int main()
{

    node* root=NULL;
    long int count;
	string fname;
    vector<vector<string>> content;
	cout<<"Enter the file name: ";
	cin>>fname;
 
	
	vector<string> row;
	string line, word;
   
	fstream file (fname, ios::in);
	if(file.is_open())
	{
        
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
            {
                row.push_back(word);
            }
            count++;
             root=insert(root,row);
             content.push_back(row);
          if(count==100000)
              break;
               
		}
        
    }
	else
		cout<<"Could not open the file\n";
    file.close();
    system("cls");
    Inorder(root);
   display:
	    int b=disp();
    do{
	
		if(b==1){
            system("cls");
          most_played_song(content);
           getch();
           system("cls");
			goto display;
			break;
        }
		if(b==2){
            system("cls");
            search_by_stream(root);
            getch();
            system("cls");
			goto display;
        }
        
        if(b==3){
            system("cls");
            search_by_name(fname);                  //needy        
            getch();                                //Happier
            system("cls");                         //2002
             goto display;                        // Sixteen
            
        }
       if(b==4){
            system("cls");
            top_10();     
            getch();
            system("cls");
            goto display;
            
            }
        if(b==5)
        {
            system("cls");
            rod(content);
            getch();
            system("cls");
            goto display;
        }
        if(b==6)
        {
            system("cls");
            random_recommendation(root);
             getch();
            system("cls");
            goto display;
            
        }
        if(b==7)
        {
            exit(1);
            
      }
        if(b>6)
        {
            system("cls");
            cout<<"please select from the given choice\n";
            getch();
            system("cls");
            goto display;
        }
    }while(true);
    return 0;
}

    
   

int disp()
{
    for(int i=0;i<50;i++)
	cout<<"**\t";
    int ch;
    gotoxy(50,10);
    cout<<"\n\t********* Welcome to HOUSE OF HITS ************\n";
    gotoxy(30,14);
    cout<<"1.Top 10 songs\n";
    gotoxy(30,15);
    cout<<"2.Search by song streams\n";
    gotoxy(30,16);
    cout<<"3.Search by song name\n";
    gotoxy(30,17);
    cout<<"4.Most streamed songs\n";
    gotoxy(30,18);
    cout<<"5.Our Recommendation";
    gotoxy(30,19);
    cout<<"6.Least recommended songs\n";
    gotoxy(30,20);
    cout<<"7.exit";
     gotoxy(0,25);
	for(int i=0;i<100;i++)
    cout<<"--";
    gotoxy(30,21);
    cout<<"enter your choice:";
    gotoxy(30,22);
    cin>>ch;
    return ch;
}
void most_played_song( vector<vector<string>> content)
{   
    cout<<"SONG\t\tRANK\t\tDATE\t\tNAME\n";
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<content[i][j]<<"|";
        }
        cout<<endl<<endl;
    
    }
}
