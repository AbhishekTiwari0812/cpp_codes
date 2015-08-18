#include<iostream>
using namespace std;
int main(){
	int test,N;
	int *A;
	long sum;
	int input;
	cin>>test;
	for(int i=0;i<test;i++){
		cin>>N;
		sum=0;
		for(int j=0;j<N;j++){
			cin>>input;
			sum+=(2*j+1-N)*input;
		}
		cout<<sum<<endl;
	}
	return 0;
}
