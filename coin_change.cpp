#include <iostream>
#include <cstdlib>
#include <vector>
#define MAX_CHANGE 250
#define MAX_POS_COIN_TYPE 50
using namespace std;

int DP[MAX_CHANGE][MAX_POS_COIN_TYPE];


int *list_of_coins;
int size;

long long int count_ways(int change , int max_index){
	long long int a,b;
	if (max_index < 0){
		//DP[change][max_index]=0;
		return 0;
	}
	if(change < 0 ){
		//DP[change][max_index]=0;
		return 0;
	}
	else if (change == 0 ){
		DP[change][max_index]=1;
		return 1;
	}
	if ( change-list_of_coins[max_index] >= 0 && DP[change-list_of_coins[max_index]][max_index]==-1){
		a = count_ways(change-list_of_coins[max_index],max_index );
		DP[change-list_of_coins[max_index]][max_index]=a;
	}
	else if (change-list_of_coins[max_index]>= 0)
		a =DP[change-list_of_coins[max_index]][max_index];
	else a=0;
	if ( max_index>=0 &&  DP[change][max_index-1]==-1){
		b = count_ways(change,max_index -1);
		DP[change][max_index-1]=b;
	}
	else if ( max_index>=0)
		b =DP[change][max_index-1];
	else b=0;
	return a+b;
}



int main(int argc ,char * argv[]){
	int change;
	cin>>change;
	int size;
	cin>>size;
	for(int i = 0;i<MAX_CHANGE;i++)
		for(int j=0;j<MAX_POS_COIN_TYPE;j++)
			DP[i][j]=-1;

	list_of_coins=(int *)malloc(sizeof(int)*size);
	for(int i=0;i<size;i++)	
		cin>>list_of_coins[i];
	long long number_of_ways;
	number_of_ways=count_ways(change,size-1);
	cout<<number_of_ways<<endl;

	return 0;


}