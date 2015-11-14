#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;


long int get_sum(long int *A,int left,int right){
	long int sum=0;
	for(int i=left;i<=right;i++)
		sum+=A[i];
	return sum;
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
	in>>queries;		//0 for printing the array,1  for printing the sum, 2 for updating the range.
	for( int i=0;i<queries;i++){
		in>>left>>right;
		result = get_sum(A,left,right);
		cout<<result<<endl;
	}
	t2=clock();
	cout<<"Time taken:"<<((float)t2-(float)t1)/1000000.0<<endl;
	return 0;
}
