#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Node{
	int value;
	struct Node *left;
	struct Node *right;
}node;

template<class T>
class Tree{
	T *root_node;
	public:
		Tree(int val){
			root_node=new T();
			root_node->value=val;
		}
		T *get_root(){
			return root_node;
		}
		T *bin_search_num(int num,T *root);
		void insert_num(int num);
		T *create_tree_from_array(int *root,int size);		//returns the pointer to the head of the tree
		void delete_num(int num);
		void in_order_traversal(T *root);
		void pre_order_traversal(T *root);
		void post_order_traversal(T *root);

};

template<typename T>
T *Tree<T>::create_tree_from_array(int *input_array,int size){
	//root node must already be assigned !
	for(int i=1;i<size;i++)
		Tree::insert_num(input_array[i]);
}

template<typename T>
T *Tree<T>::bin_search_num(int num,T *root){	//searches for the number closest to it in the tree.  
	if(root->value==num)
		return root;
	else if(num < root->value)
		 if(root->left!=NULL)
		 	return bin_search_num(num,root->left);
		 else return root;			//finds the first number greater than num in the tree.
	else 
		if(root->right!=NULL)
			return bin_search_num(num,root->right);
		else return root;			//returns the first number smaller than num in the tree.
	}

template<typename T>
void Tree<T>::insert_num(int num){
	T *parent_node=bin_search_num(num,root_node);
	if(parent_node->value == num)
		cout<<"Number:"<<num<<" is already in the tree"<<endl;
	else if(num > parent_node->value){
		parent_node->right=(T *)malloc(sizeof(T));
		parent_node->right->value=num;
		//just to avoid garbage allocation.
		parent_node->right->left=NULL;
		parent_node->right->right=NULL;
	}
	else if(num < parent_node->value){
		parent_node->left=(T *)malloc(sizeof(T));
		parent_node->left->value=num;
		//just to avoid garbage allocation.
		parent_node->left->left=NULL;
		parent_node->left->right=NULL;
	}
}

template<typename T>
void Tree<T>::delete_num(int num){

}

template<typename T>
void Tree<T>::in_order_traversal(T *root){
	if(root->left!=NULL)
		in_order_traversal(root->left);
	cout<<root->value<<" ";
	if(root->right!=NULL)
		in_order_traversal(root->right);
}

template<typename T>
void Tree<T>::pre_order_traversal(T *root){
	cout<<root->value<<" ";
	if(root->left!=NULL)
		in_order_traversal(root->left);
	if(root->right!=NULL)
		in_order_traversal(root->right);
}
template<typename T>
void Tree<T>::post_order_traversal(T *root){
	cout<<root->value<<" ";
	if(root->left!=NULL)
		in_order_traversal(root->left);
	if(root->right!=NULL)
		in_order_traversal(root->right);
}


int main(){
	int size=10;
	int A[size];
	cout<<"Input array:"<<endl;
	for(int i=0;i<size;i++){
		A[i]=rand()%10000;		//numbers range from 0 to 9999.
		cout<<A[i]<<" ";
	}
	cout<<endl;
	Tree<node> *m_tree=new Tree<node>(A[0]);		//allocated in the heap.
	//root node must to added while calling the constructor!
	m_tree->create_tree_from_array(A,size);
	cout<<"\nIn order:"<<endl;
	m_tree->in_order_traversal(m_tree->get_root());
	cout<<"\nPre order:"<<endl;
	m_tree->pre_order_traversal(m_tree->get_root());
	cout<<"\nPost order:"<<endl;
	m_tree->post_order_traversal(m_tree->get_root());
	cout<<endl;
	return 0;

}