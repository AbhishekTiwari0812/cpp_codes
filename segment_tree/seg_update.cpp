#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
typedef struct node{
	int value;
	int left_index;
	int right_index;
	struct node* left_child;
	struct node* right_child;
	long int increment;
	long int height;
}node;
class SegTree{
public:
	node *root;
	SegTree(long int *A,int size);
	void update_range(node *root,int left_index,int right_index,long int value);
	void print_array(node *root,int left,int right,long int increment);
};
node *create_parent(node *a,node *b){
	node *new_node=new node;
	if(b!=NULL){
		new_node->left_child=a;
		new_node->right_child=b;
		new_node->left_index=a->left_index;
		new_node->right_index=b->right_index;
		//for debugging
		new_node->increment=a->increment+b->increment;
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
		new_node->value=A[i];
		new_node->left_index=i;
		new_node->right_index=i;
		new_node->left_child=NULL;
		new_node->right_child=NULL;
		new_node->height=0;
		new_node->increment=0;
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

void SegTree::update_range(node *root,int left_index,int right_index,long int value){
	if(root->left_index==left_index && root->right_index==right_index)
		root->increment+=value;
	else if(right_index<=root->left_child->right_index)
		 update_range(root->left_child,left_index,right_index,value);
	else if(left_index >= root->right_child->left_index)
		update_range(root->right_child,left_index,right_index,value);
	else {
		update_range(root->left_child,left_index,root->left_child->right_index,value);
		update_range(root->right_child,root->right_child->left_index,right_index,value);
	}
}
void SegTree::print_array(node *root,int left ,int right,long int increment=0){
	if(root==NULL)
		return ;
	if(root->left_index!=root->right_index){
		if(root->left_index<=left && root->right_index>=right){
			print_array(root->left_child,left,root->left_child->right_index,increment+root->increment);
			print_array(root->right_child,root->right_child->left_index,right,increment+root->increment);
		}
		else if(right<=root->left_child->right_index){
			print_array(root->left_child,left,right,increment+root->increment);
		}
		else if(left >= root->right_child->left_index){
			print_array(root->right_child,left,right,increment+root->increment);
		}
	}
	else cout<<root->value+increment+root->increment<<" ";}

int main(){
	clock_t t1,t2;
	t1=clock();
	int size;
	long int *A;
	int queries;
	int query_type;
	int left,right,increment;
	long int result;
	ifstream in;
	in.open("data_update.in");
	in>>size;
	A=new long int[size];
	for(int i=0;i<size;i++)
		in>>A[i];
	SegTree Tree(A,size);
	in>>queries;		//0 for printing the array,1  for printing the sum, 2 for updating the range.
	for( int i=0;i<queries;i++){
		in>>query_type;
		switch (query_type){
			case 0:
				in>>left>>right;
				Tree.print_array(Tree.root,left,right);
				cout<<endl;
			break;
			case 1:
				in>>left>>right>>increment;
				Tree.update_range(Tree.root,left,right,increment);
			break;
		}
	}
	t2=clock();
	cout<<"Time taken:"<<((float)t2-(float)t1)/1000000.0<<endl;
	return 0;
}

