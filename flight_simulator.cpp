#include <string>
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>

using namespace std;

int CITIES;
typedef struct aeroplane{
	int ID;
	int start_city;
	int end_city;
	int dep_time;
	int arr_time;
}plane;


typedef struct city{
	int ID;
	vector<struct city *> nbd;		//here, we can improve.Redundant storage!
	vector<plane> connection;
	struct city *parent;
	//struct city *next;
	int value;		//should be initialized to infinity
}city;

city **G;



int time_to_minute(string t){
	if(t.size()<4||t.size()>4){
		cout<<"time format error"<<endl;
		return -1;
	}
	int h=(10*(t[0]-'0')+(t[1]-'0'))*60;
	int m=(10*(t[2]-'0')+(t[3]-'0'));
	return h+m;
}


int duration(int from,int to){
	if(to<from){
		to+=time_to_minute("2400");
	}
	return to-from;
}

typedef struct city_plane_pair{
	city c;
	plane p;
}cpp;

//returns the arrival time at the neighbourhood station
int get_value(city *a,int b_index){
	//equality may not hold
	if(a->connection[b_index].dep_time >= a->value+30)
		return a->connection[b_index].arr_time;
	else return a->connection[b_index].arr_time+time_to_minute("2400");
}

//first fill the priority queue with all the elements

city **MyQueue;
int START;	//should be initialized to 0
int ELEMENTS_LEFT;
bool is_empty(){return (ELEMENTS_LEFT==0);}
city *pop(){
	START++;
	ELEMENTS_LEFT--;
	return MyQueue[START-1];
} 
//check this sorting function
bool comp(city *a,city *b){
	return (a->value <= b->value);
}
void update_queue(){
	sort(MyQueue+START,MyQueue+CITIES-START,comp);
}

void initialize_queue(city *start){
 	ELEMENTS_LEFT=CITIES;
 	MyQueue=new city*[CITIES];
 	START=0;
 	for(int i=0;i<CITIES;i++){
 		if(G[i]!=start)
 			G[i]->value=INT_MAX;
 		MyQueue[i]=G[i];

 	}
 	update_queue();
 }

 

city* find_path(city *start,city *end){
	//start time should already be assigned
	//cout<<"start point"<<start->ID<<endl;
	//cout<<"End point"<<end->ID<<endl;
	initialize_queue(start);
	city *temp;
	while(is_empty()!=true){
		temp=pop();
		if(temp==end){
	//		cout<<"Destination reached:"<<temp->ID<<endl;
			return temp;		//here maybe some problem
		}
		for(int i=0;i<temp->nbd.size();i++){
			if(temp->nbd[i]->value >  get_value(temp,i)){
				temp->nbd[i]->parent=temp;
				temp->nbd[i]->value=get_value(temp,i);
				//update this in the priorit queue
			}
		}
		//very time consuming. Can be better.
		update_queue();
	}
	//no path found
	return NULL;
}

void print_answer(city *last,city *start){
		
	cout<<last->ID;
	if(last!=start){
		cout<<" <-- ";
		print_answer(last->parent,start);
	}
	
}

int main(){
	ifstream in;
	ofstream out;
	int edges;
	in.open("Input.txt");
	in>>CITIES;
	G=new city*[CITIES];
	for(int i=0;i<CITIES;i++){
		G[i]=new city;
		G[i]->ID=i+1;
	}

	in>>edges;
	int plane_id,start_city,end_city;
	string dep_time,arr_time;
	for(int i=0;i<edges;i++){
		plane p;
		in>>plane_id>>start_city>>end_city;
		in>>dep_time>>arr_time;
		start_city-=1;
		end_city-=1;
		p.ID=plane_id;
		p.start_city=start_city;
		p.end_city=end_city;
		p.dep_time=time_to_minute(dep_time);
		p.arr_time=time_to_minute(arr_time);
		G[start_city]->nbd.push_back(G[end_city]);
		G[start_city]->connection.push_back(p);		
	}
	int query;
	in>>query;
	for(int i=0;i<query;i++){
		in>>start_city>>end_city;
		in>>dep_time>>arr_time;
		start_city-=1;
		end_city-=1;
		G[start_city]->value=time_to_minute(dep_time);
		city *answer=find_path(G[start_city],G[end_city]);
		if(answer->value <=time_to_minute(arr_time)){
			print_answer(answer,G[start_city]);
			cout<<"\nfinal time:"<<answer->value;
			
		}
		else cout<<"No path possible";
		cout<<endl;
	}


}