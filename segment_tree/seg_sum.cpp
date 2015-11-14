#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
typedef struct node{
	long long int sum;
	int left_index;
	int right_index;
	struct node* left_child;
	struct node* right_child;
	long int height;
}node;
class SegTree{
public:
	node *root;
	SegTree(long int *A,int size);
	long int get_sum(node *current,int left_index,int right_index);
};
node *create_parent(node *a,node *b){
	node *new_node=new node;
	if(b!=NULL){
		new_node->sum=a->sum+b->sum;
		new_node->left_child=a;
		new_node->right_child=b;
		new_node->left_index=a->left_index;
		new_node->right_index=b->right_index;
		//for debugging
		if(a->height!=b->height)
			cout<<"There is some problem with the height"<<endl;
		new_node->height=a->height+1;
	}
	else{ 
		delete new_node;
		new_node=a;
		new_node->height=a->height+1;
	}
	return new_node;}
SegTree::SegTree(long int *A,int size){
	queue<node *>q;
	for(int i=0;i<size;i++){
		node *new_node=new node;
		new_node->sum=A[i];
		new_node->left_index=i;
		new_node->right_index=i;
		new_node->left_child=NULL;
		new_node->right_child=NULL;
		new_node->height=0;
		q.push(new_node);
	}
	node *temp1;
	node *temp2;
	while(true){
		temp1=q.front();
		q.pop();
		if(q.front()->height!=temp1->height)
			temp2=NULL;
		else {
			temp2=q.front();
			q.pop();
		}
		node *new_node= create_parent(temp1,temp2);
		if(q.empty()){
			this->root=new_node;
			break;
		}
		q.push(new_node);
	}}
long  int SegTree::get_sum(node *root, int left_index, int right_index){
	//TODO::left_index and right_index bound checking
	long int a=0;
	if(root->left_index==left_index && root->right_index==right_index)
		a = root->sum;
	else if(right_index<=root->left_child->right_index)
		a= get_sum(root->left_child,left_index,right_index);
	else if(left_index >= root->right_child->left_index)
		a= get_sum(root->right_child,left_index,right_index);
	else 
		a= get_sum(root->left_child,left_index,root->left_child->right_index)+get_sum(root->right_child,root->right_child->left_index,right_index);
	return a ;
}
int main(){
	clock_t t1,t2;
	t1=clock();
	int size;
	long int *A;
	int queries;
	int query_type;
	int left,right;
	long int result;
	ifstream in;
	in.open("data_sum.in");
	in>>size;
	A=new long int[size];
	for(int i=0;i<size;i++)
		in>>A[i];
	SegTree Tree(A,size);
	in>>queries;		//0 for printing the array,1  for printing the sum, 2 for updating the range.
	for( int i=0;i<queries;i++){
		in>>left>>right;
		result = Tree.get_sum(Tree.root,left,right);
		cout<<result<<endl;
	}
	t2=clock();
	cout<<"Time taken:"<<((float)t2-(float)t1)/1000000.0<<endl;
	return 0;
}

