#include<vector>
#include<map>
#include<string.h>
#include<fstream>
#include<malloc.h>
#define CHAR_TYPES 128

using namespace std;
typedef class Node{
public:
    bool isLeaf=false;
    char* bin_rep;
    int value;
    char mChar=-1;          //ascii character
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} node;
node *temp_left;
node *temp_right;
void InsertionSort(vector<node *> *A,int size){
    for(int i=1;i<size;i++){
        node *temp=(*A)[i];
        int j=i-1;
        while(j>=0&& (temp->value)>=((*A)[j]->value)){
               (* A)[j+1]=(*A)[j];
                j--;
        }
       (* A)[j+1]=temp;
    }
}
node* CreateNewNode(){
    node *A=(node *)malloc(sizeof(node));
    return A;
}


char* appendCharToCharArray(char* array, char a)
{
    size_t len = strlen(array);

    char* ret = new char[len+2];

    strcpy(ret, array);
    ret[len] = a;
    ret[len+1] = '\0';

    return ret;
}
void NameItAll(node *A,char mBit){

    A->bin_rep=appendCharToCharArray(A->parent->bin_rep,mBit);
    if(!A->isLeaf){
        NameItAll(A->left,'1');
        NameItAll(A->right,'0');
    }
}



int main(){
    vector<node *>all_nodes;        //for making the tree
    vector<node *>queue;            //for the priority queue
    int freqs[CHAR_TYPES];
    char ch;
    fill_n(freqs,CHAR_TYPES,0);           //giving 0 as default
    string InputFileName="input.txt";
    ifstream fin(InputFileName);
    while(fin>>ch){
        freqs[(int)ch]++;               //noting down the frequencies of each character
    }
    fin.close();
    int my_size=0;
    for(int i=0;i<CHAR_TYPES;i++){
        if(freqs[i]!=0){
            my_size++;
            node * temp=CreateNewNode();
            temp->mChar=(char)i;
            temp->isLeaf=true;
            temp->value=freqs[i];
            all_nodes.push_back(temp);
            queue.push_back(temp);
        }
    }

    InsertionSort(&queue,queue.size());              //fix this using priority queue.
    node *mParent;
    int some_size=queue.size();
    while(some_size>=2){            //memory leak happening here!!DANGLING POINTER HANDLE HERE!!
        node *left=queue[some_size-1];
        node *right=queue[some_size-2];
        mParent=CreateNewNode();
        mParent->left=left;
        mParent->right=right;
        mParent->value=(left->value)+(right->value);
        left->parent=mParent;
        right->parent=mParent;
        queue[some_size-2]=mParent;
        queue[some_size-1]=left;
        queue.push_back(right);
        some_size--;
        all_nodes.push_back(mParent);
        InsertionSort(&queue,some_size);             //fix this using priority queue.
    }

queue[0]->parent=CreateNewNode();
queue[0]->parent->bin_rep="";
NameItAll(queue[0],0);
map<char ,string>BitRep;
for(int i=0;i<my_size;i++){
    //cout<<"char:"<<(char)all_nodes[i]->mChar<<" bit_rep:"<<all_nodes[i]->bin_rep<<endl;
    BitRep[all_nodes[i]->mChar]=all_nodes[i]->bin_rep;
}
//now write it to a output file.
//in the format of bit representation.
 ifstream in(InputFileName);
 ofstream out("output.txt");
    while(in>>ch){
        string out_bit=BitRep[ch];
        out<<out_bit;

        }
    in.close();
    out.close();

    return 0;
}



