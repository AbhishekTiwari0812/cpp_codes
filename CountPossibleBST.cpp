//not done yet.

#include <iostream>
using namespace std;

int CountBST(int n){
	if(n==0||n==1)
		return 1;
	else if(n==2)
		return 2;
	else if(n==3)
		return 5;
	else {
		int mid=n/2;
		int left_count=CountBST(mid-1);
		int right_count=CountBST(n-mid);
		return 5*left_count*right_count;
	}
}
int main(){

	cout<<CountBST(4)<<endl;
	return 0;
}