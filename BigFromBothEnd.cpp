#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int A[n];
    int B[n];
    long long int MAX=0;
    for(int i=0;i<n;i++){
            cin>>A[i];
            B[n-1-i]=A[i];
    }

    for(int i=0;i<n;i++){
        long long int maxFromLeft=-1,maxFromRight=-1;
        for(int j=i-1;j>=0;j--)
        if(A[j]>A[i]){
            maxFromLeft=j;
            break;
            }
        for(int j=i+1;j<n;j++)
            if(A[j]>A[i]){
                maxFromRight=j;
                break;
                }
        if(A[i]!=A[maxFromLeft] &&A[i]!=A[maxFromLeft])
            if(MAX<(maxFromLeft+1)*(maxFromRight+1))
                MAX=(maxFromLeft+1)*(maxFromRight+1);

       // cout<<"A[i]="<<A[i]<<"Max from Left:"<<maxFromLeft<<" And max from Right:"<<maxFromRight<<" and max is:"<<MAX<<endl;
    }

    cout<<MAX<<endl;
    return 0;
}
