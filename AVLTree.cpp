#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;




typedef struct node{
	int value;
	int weight;
	int is_left; //1 if left child, 0 is right
	struct node *left;
	struct node *right;
	struct node *parent;
}node;
class AVLTree{
	public:
		node *head;
		int height;
		AVLTree(node *root);					//while constructing,  add the root node!
		void insert_node(node *new_node);		//create a node, assign it some value, pass the pointer.
		void left_rotate(node *current);		//to balance the tree, if right side becomes more heavy
		void right_rotate(node *current);		//if left side becomes more heavy, rotating to right.
		void delete_node(node *del_node);		//pass the pointer of the node to be deleted.
		node *search(node *root,int key);		//to search the node, if exists otherwise the closest one.
		int compare(node &a,node &b);			//comparator. Returns 1 if a > b ; -1 if a < b; 0 if a=b;
		void balance_tree(node *current);		//after insertion or deletion, this must be called to balance the tree.
		void update_weight(node *current);
		void in_order_print(node *root);
};

void AVLTree::in_order_print(node *root){
	if(root!=NULL){
		in_order_print(root->left);
		cout<<root->value<<" ";
		in_order_print(root->right);
	}
}
AVLTree::AVLTree(node *root){
	head=root;
	head->parent=NULL;
	head->weight=0;
	head->left=NULL;
	head->right=NULL;
}


void AVLTree::update_weight(node *current){
	if(current->left!=NULL && current->right!=NULL)
		current->weight=abs(current->right->weight) - abs(current->left->weight);
	else if(current->left== NULL && current->right!=NULL)
		current->weight=current->right->weight+1;
	else if(current->left!=NULL && current->right==NULL )
		current->weight=current->left->weight-1;
	else current->weight=0;
}


void AVLTree::delete_node(node *del_node){}
void AVLTree::left_rotate(node *current){
	node *right_child=current->right;
	right_child->parent=current->parent;
	if(current->is_left){
		if(current->parent!=NULL)
		current->parent->left=right_child;
		right_child->is_left=1;
	}
	else
		if(current->parent!=NULL)
			current->parent->right=right_child;
	
	current->parent=right_child;
	current->is_left=1;
	current->right=right_child->left;
	right_child->left=current;

	if(current->right!=NULL){
		current->right->is_left=0;
		current->right->parent=current;
	}
	update_weight(current);
	update_weight(current->parent);
}

void AVLTree::right_rotate(node *current){
	node *left_child=current->left;
	left_child->parent=current->parent;
	if(current->is_left)
		if(current->parent!=NULL)
			current->parent->left=left_child;
	else{
		if(current->parent!=NULL)
			current->parent->right=left_child;
		left_child->is_left=0;
	}
	current->parent=left_child;
	current->is_left=0;
	current->left=left_child->right;
	left_child->right=current;
	if(current->left!=NULL){
		current->left->is_left=1;
		current->left->parent=current;
	}
	update_weight(current);
	update_weight(current->parent);

}

void AVLTree::balance_tree(node *current){
	if(current!=NULL){
		if(current->weight<=1 && current->weight >= -1)
			return balance_tree(current->parent);
		else if(current->weight > 1){
			current=current->right;
			if(current->weight==-1){
				right_rotate(current);		//always goes one level down
				balance_tree(current->parent);		//check here!
			}
			else{
				left_rotate(current->parent);
				balance_tree(current->parent);
			}
		}
		else if(current->weight < -1){
			if(current->weight==-1){
				right_rotate(current->parent);
				balance_tree(current->parent);
			}
			else{
				left_rotate(current);
				balance_tree(current->parent);
			}
		}
	}
	else return ;
}
int AVLTree::compare(node &a,node &b){
	if(a.value == b.value )
		return 0;
	else if(a.value > b.value )
		return 1;
	else return -1;
}
node *create_node(int value){
	node *new_node=(node *)malloc(sizeof(node));
	new_node->value=value;
	new_node->weight=0;
	new_node->left=NULL;
	new_node->right=NULL;
	new_node->parent=NULL;
	return new_node;
}
node *AVLTree::search(node *root,int value){
	if(root==NULL){
		cout<<"Some error.No root in the tree (or wrong pointer)."<<endl;
		return NULL;
	}
	if(root->value > value){
		if(root->left!=NULL)
			return search(root->left,value);
		else return root;		//node having slightly greater value is returned
	}
	else if(root->value <  value){
		if(root->right!=NULL)
			return search(root->right,value);
		else return root;		//node having slightly less value is returned
	}
	else return root;			//node is found
}
void AVLTree::insert_node(node *new_node){
	node *parent=search(head,new_node->value);
	int comp=compare(*new_node,*parent);
	if(comp==0){	//already in the tree
		//cout<<"Node "<<new_node->value<<" is already in the tree"<<endl;
		return;
	}
	else if(comp > 0){
		new_node->is_left=0;	//right child of the parent
		new_node->parent=parent;
		parent->right=new_node;
		parent->weight+=1;
		balance_tree(parent);
	}
	else {					
		new_node->is_left=1;	//left child of the parent
		new_node->parent=parent;
		parent->left=new_node;
		parent->weight-=1;
		balance_tree(parent);
	}
}
int main(){
	srand(time(NULL));
	node *root=create_node(69);
	AVLTree *new_tree=new AVLTree(root);
	int number_of_nodes=10000000;
	for(int i=0;i<number_of_nodes;i++){
		new_tree->insert_node(create_node(rand()%(1<<29)));
	}
	//new_tree->in_order_print(new_tree->head);
	cout<<endl;
	return 0;
}