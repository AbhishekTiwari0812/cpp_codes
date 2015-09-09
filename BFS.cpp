#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class node{
    public:
        int cost_of_reach=-1;
        vector<node *> Neighbours;    
};

queue<node *> my_queue;

void BFS(){
    node *current;
    while(!my_queue.empty()){
        current=my_queue.front();
        my_queue.pop();
        for(int i=0;i<current->Neighbours.size();i++){
            if(current->Neighbours[i]->cost_of_reach==-1){
                current->Neighbours[i]->cost_of_reach=(current->cost_of_reach)+6;
                
                my_queue.push(current->Neighbours[i]);
            }
        }
    }
}

int main() {
    int test_cases;
    int number_of_nodes;
    int node1,node2;
    int number_of_edges;
    cin>>test_cases;
    for(int something=0;something<test_cases;something++){
        cin>>number_of_nodes;
        cin>>number_of_edges;

        node * Nodes[number_of_nodes];
        for(int i=0;i<number_of_nodes;i++)
            Nodes[i]=new node;
        for(int i=0;i<number_of_edges;i++){
            cin>>node1;
            node1-=1;
            cin>>node2;
            node2-=1;
            Nodes[node1]->Neighbours.push_back(Nodes[node2]);
            Nodes[node2]->Neighbours.push_back(Nodes[node1]);
        }
        
        int temp;
        cin>>temp;
        temp-=1;
        Nodes[temp]->cost_of_reach=0;
        my_queue.push(Nodes[temp]);
        BFS();
        for(int i=0;i<number_of_nodes;i++){
            if(i==temp)
                continue;
            cout<< Nodes[i]->cost_of_reach<< " ";
        }
    }
    return 0;
}
