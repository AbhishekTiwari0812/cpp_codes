#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#define ARRAY_SIZE 100000
#define QUERIES 10000
#define ELEMENT_RANGE 1000000
using namespace std;
int main(){
	srand(time(NULL));
	ofstream out;
	out.open("data_update.in");
	//size=(rand()%ARRAY_SIZE)+100;
	out<<ARRAY_SIZE<<endl;
	for(int i=0;i<ARRAY_SIZE;i++)
		out<<rand()%ELEMENT_RANGE<<" ";
	//queries=(rand()%ARRAY_SIZE)+100;
	out<<"\n"<<QUERIES<<endl;
	//case 1
	int query_type,left,right,increment;
	for(int i=0;i<QUERIES;i++){
		query_type= (rand()%17);		//0 for printing array.1 for updating the range. 2 for getting the sum.
		switch(query_type){
			case 0:
				left=rand()%ARRAY_SIZE;
				right=left+(rand()%(ARRAY_SIZE-left));
				out<<query_type<< " "<<left<<" "<<right<<endl;
				break;
			default:
				left=rand()%ARRAY_SIZE;
				right=left+(rand()%(ARRAY_SIZE-left));
				increment=rand()%(ELEMENT_RANGE/4);
				out<<query_type<< " "<<left<<" "<<right<<" "<<increment<<endl;
				break;
		}
	}
	return 0;
}
