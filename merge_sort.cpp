#include <iostream>
#include <cstdlib>
#define INF 2147482647
//Infinity is supposed to be the biggest of all the numbers which are being compared!
//change this value if data type changes from int to something else!!


using namespace std;


	void merge(int *A,int start,int mid,int end){
		int left[mid-start+1+1];
		int right[end-mid+1];
		for(int i=start;i<=mid;i++)
			left[i-start]=A[i];
		for(int i=mid+1;i<=end;i++)
			right[i-mid-1]=A[i];
		left[mid-start+1]=INF;
		right[end-mid]=INF;
		int left_cursor=0;
		int right_cursor=0;
		for(int i=start;i<=end;i++)
				if( left[left_cursor] <= right[right_cursor])
					A[i]=left[left_cursor++];
				else A[i]=right[right_cursor++];

	}

	void merge_sort(int *input_array,int start,int end){		
		if(start==end)
			return ;
		else{
			int mid=(start+end)/2;
			merge_sort(input_array,start,mid);
			merge_sort(input_array,mid+1,end);
			merge(input_array,start,mid,end);
		}

	}



int main(){
	int size=10;
	int A[size];
	cout<<"input array"<<endl;
	for(int i=0;i<size;i++){
		A[i]=rand()%10000;
		cout<<A[i]<<" ";
	}
	cout<<"\n\n\nOutput array:"<<endl;
	merge_sort(A,0,size-1);
	for(int i=0;i<size;i++)
		cout<<A[i]<<" ";
	cout<<endl;
	return 0;

}