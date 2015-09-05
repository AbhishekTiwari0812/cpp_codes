#include<iostream>
#include<fstream>

using namespace std;


char ConvertToByte(string str){
    int sum=0;
    if(str.length()!=8){
        cout<<"We have a problem here"<<endl;
    }
    int pow_2=1;
    for(int i=7;i>=0;i--){
        sum+=pow_2*(str[i]-'0');
        pow_2*=2;
    }
    if(sum>=256){
        cout<<"there's something wrong"<<endl;
    }
    return (char    )sum;
}

int main(){
string mByte="";
ifstream  in("output.txt");
ofstream out("compressed.txt");
char c;          //the bits

while(in>>c){
    if(mByte.length()!=8){
        mByte+=c;
    }
    else{
        out<<ConvertToByte(mByte);
        mByte="";
    }
    }

out<<ConvertToByte(mByte);      //last few characters


}
