#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;


void print_array(long int *A,int left,int right){
	for(int i=left;i<=right;i++)
		cout<<A[i]<<" ";
}
void update_range(long int *A,int left,int right,long int value){
	for(int i=left;i<=right;i++)
		A[i]+=value;
}

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
	in>>queries;		//0 for printing the array,1  for printing the sum, 2 for updating the range.
	for(int i=0;i<queries;i++){
		in>>query_type;
		switch (query_type){
			case 0:
				in>>left>>right;
				print_array(A,left,right);
				cout<<endl;
			break;
			case 1:
				in>>left>>right>>increment;
				update_range(A,left,right,increment);
			break;
		}
	}
	t2=clock();
	cout<<"Time taken:"<<((float)t2-(float)t1)/1000000.0<<endl;
	return 0;
}

