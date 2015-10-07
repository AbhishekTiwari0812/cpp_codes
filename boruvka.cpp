//assuming nodes have values from 0 to n-1.
//may need a hash table if this is not the case
#include <iostream>
#include <vector>
#define INFINITE 1<<30
#define QUEUE_SIZE 1000		// should be sufficient enough for BFS
using namespace std;

typedef struct edge{
	int u;
	int v;
	int cost;
}edge;

vector<edge *> MST;

typedef struct node{
	int value;
	vector<int> edge_cost;
	int visited;
	int level;
	struct node* parent;
	vector<struct node*> neighbours;
}node;



//Error can occur if the Queue is full!!!
//i.e. if the Graph is highly connected and 
//TODO: initialize this
node *MyQueue[QUEUE_SIZE];		
int elements_in_the_queue;

node *dequeue(){
	static int i=0;
	elements_in_the_queue--;
	if(elements_in_the_queue<=0){
		cout<<"queue is empty."<<endl;
		return NULL;
	}
	node *temp=MyQueue[i];
	i+=1;
	i%=QUEUE_SIZE;
	return temp;
}

void enqueue(node *new_node){
	elements_in_the_queue++;
	if(elements_in_the_queue > QUEUE_SIZE){
		cout<<"Can not insert.Queue is full.Increase Queue capacity."<<endl;
		return ;
	}
	static int i=0;
	MyQueue[i]=new_node;
	i++;
}


class Graph{
public:
	Graph(int n);
	vector<node *> V;
	int num_of_meta_nodes;
	node *start;
	void contract_edge(node *a,node *b,int cost);
	void BFS(node *);
	int compress_graph();
	void start_contracting(node *);
};

Graph::Graph(int num_of_vertices){
	this->num_of_meta_nodes=num_of_vertices;
}
Graph *G;


int get_min_cost_edge_index(node *current_node){
	int min=1<<30;
	int index=-1;
	for(int i=0;i < current_node->edge_cost.size();i++)
		if(current_node->edge_cost[i] < min ){
			index=i;
			min=current_node->edge_cost[i];
		}
	if(index==-1){
		cout<<"No neighbours"<<endl;
		return index;
	}
	
	current_node->edge_cost[index]=INFINITE;
	for(int i=0;i<G->V[index]->neighbours.size();i++){
		if(G->V[index]->neighbours[i]->value == current_node->value){
			G->V[index]->edge_cost[i]=INFINITE;
			break;
		}
	}
	return index;
}
//no need here though :P
void Graph::BFS(node *root){
	if(root->visited==1)
		return;
	root->visited=1;
	enqueue(root);
	root->level=0;
	while(elements_in_the_queue > 0){
		root=dequeue();
		for(int i=0;i<root->neighbours.size();i++){
			if(root->neighbours[i]->visited!=1){
				root->neighbours[i]->visited=1;
				root->neighbours[i]->level=root->level+1;
				enqueue(root->neighbours[i]);
			}
		}
	}
}


void Graph::contract_edge(node *a,node *b,int cost){
	//must be added to the MST
	edge *new_edge=new edge;
	node *temp1;
	node *temp2;
	if(a->value <= b->value){
		temp1=a;
		temp2=b;
	}
	else {
		temp2=a;
		temp1=b;
	}

	new_edge->u=temp1->value;
	new_edge->v=temp2->value;
	new_edge->cost=cost;
	MST.push_back(new_edge);
	int index1;
	cout<<"Nodes:"<<temp1->value<<" "<<temp2->value<<endl;
	for(int i=0;i<temp1->neighbours.size();i++)
		if(temp1->neighbours[i]->value==temp2->value){
			temp1->neighbours.erase(temp1->neighbours.begin()+i);
			cout<<"Deleting "<<temp1->neighbours[i]->value <<" from neighbour of "<<temp1->value<<endl;
			break;
		}
	for(int i=0;i<temp2->neighbours.size();i++)
		if(temp2->neighbours[i]->value==temp1->value){
			temp2->neighbours.erase(temp2->neighbours.begin()+i);
			cout<<"Deleting "<<temp2->neighbours[i]->value <<" from neighbour of "<<temp2->value<<endl;
			break;
		}
	//memory can be saved here!
	//temp2->value=temp1->value;
	//is this step necessary??????????

	temp1->neighbours.insert(temp1->neighbours.end(),temp2->neighbours.begin(),temp2->neighbours.end());

}


void Graph::start_contracting(node *current_node){
	current_node->visited=1;
	int index=get_min_cost_edge_index(current_node);
	for(int i=1;i<10000000;i++);
	cout<<"current_node:"<<current_node->value<<" and neighbour:"<<current_node->neighbours[index]->value<<endl;
	if(index!=-1 && (G->V[index]->visited!=1)){
		cout<<"NEVER COMES HERE\n";
		G->V[index]->parent=current_node->parent;
		contract_edge(current_node->parent,G->V[index],current_node->edge_cost[index]);
		start_contracting(G->V[index]);
	}
	return;
}

int Graph::compress_graph(){
	if(this->num_of_meta_nodes<=1){
		cout<<"Your fresh MST is ready,monsieur :)"<<endl;
		return 1;
	}
	//cout<<"Here ";
	int index;
	int temp=0;
	for(int i=0;i<this->num_of_meta_nodes;i++){
		if(G->V[i]->visited!=1){
			G->V[i]->parent=NULL;
			start_contracting(G->V[i]);
			temp++;
		}
	}
	//cout<<"Here "<<temp<<" ";
	//this->num_of_meta_nodes=temp;
	for(int i=0;i<this->num_of_meta_nodes;i++){
		if(G->V[i]->parent==NULL)
			G->V[i]->visited=0;
		else G->V[i]->visited=1;
	}
	return -1;
}

void initialize(int n){
	//G->num_of_meta_nodes=n;
	node *temp;
	for(int i=0;i<n;i++){
		temp = new node;
		temp->value=i;
		temp->visited=-1;
		temp->level=0;
		temp->parent=NULL;
		G->V.push_back(temp);
	}
	int j,k;
	int cost;
	for(int i=0;i<G->V.size();i++){
		cout<<"Enter number of neighbours for node "<<i<<endl;
		cin>>k;
		cout<<"Enter neighbours with costs for node "<<i<<endl;
		for(int something=0;something<k;something++){
			cin>>j>>cost;
			G->V[i]->neighbours.push_back(G->V[j]);
			G->V[i]->edge_cost.push_back(cost);
		}
	}
}

void print_my_mst(){
	int sum=0;
	cout<<"\n";
	for(int i=0;i<MST.size();i++){
		cout<<"("<<MST[i]->u<<","<<MST[i]->v<<") ";
		sum+=MST[i]->cost;
	}
	cout<<"Total cost:"<<sum<<endl;

}



int main(){
	int n;
	cout<<"Enter number of nodes"<<endl;
	cin>>n;
	G=new Graph(n);
	elements_in_the_queue=0;
	initialize(n);
	while(true){
		//cout<<"here";
		if(G->compress_graph()==1)
			break;
	}
	print_my_mst();
	return 0;
}