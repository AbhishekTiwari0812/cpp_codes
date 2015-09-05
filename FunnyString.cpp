#include <cmath>
#include <iostream>
using namespace std;


int main() {
    int testcases;
    cin>>testcases;
    string s;
    int size;
    for(int i=0;i<testcases;i++){
        cin>>s;
        size=s.length();
        int j;
        for(j=1;j<size;j++){
            cout<<s[j]<<" "<<s[j-1]<<endl;
            cout<<  abs(s[j]-s[j-1])<<endl;
            cout<<s[size-j]<<" "<<s[size-1-j]<<endl;
            cout<<abs(s[size-j]-s[size-1-j]);
            if(abs(s[j]-s[j-1])!=(abs(s[size-1-j]-s[size-2-j]))){
             cout<<"";
                break;
            }
        }
        if(j==size)
            cout<<"FUNNY"<<endl;
        else cout<<"NOT FUNNY"<<endl;

    }
}
