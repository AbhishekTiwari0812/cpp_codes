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
	out.open("data_sum.in");
	int size;		//array size.
	int queries;	//number of queries
	//size=(rand()%ARRAY_SIZE)+100;
	out<<ARRAY_SIZE<<endl;
	for(int i=0;i<ARRAY_SIZE;i++)
		out<<rand()%ELEMENT_RANGE<<" ";		//array elements
	//queries=(rand()%ARRAY_SIZE)+100;
	out<<"\n"<<QUERIES<<endl;
	int left,right,increment;
	for(int i=0;i<QUERIES;i++){
		left=rand()%ARRAY_SIZE;
		right=left+(rand()%(ARRAY_SIZE-left));
		out<<left<<" "<<right<<endl;		//query ranges
	}
	out.close();
	return 0;
}
