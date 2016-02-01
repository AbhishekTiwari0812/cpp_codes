#include<iostream>
#include<cmath>
using namespace std;


class BitArray
{
public:
    int Value;
    int Size=11;
    int  A[11];
    int BitSize;
    //OpOver operator+(int *,int*)
    BitArray(int);
    int operator+(BitArray);
};

BitArray::BitArray(int B)
{
    if(B!=0)
    BitSize=(log2(B));
    else
        BitSize=0;
    BitSize+=1;
    Value=B;
    for (int i=0;i<Size-BitSize;i++)
        A[i]=0;
    int k=1;
    for(int i=Size-BitSize;i<Size;i++)
      {
      A[Size-k]=B%2;
        B/=2;
        k++;
      }
}

int BitArray::operator+(BitArray B)
{
int MaxSize=(BitSize>B.BitSize)?BitSize:B.BitSize;
int  XoredArray[11];
for(int i=0;i<MaxSize;i++)
    XoredArray[i]=0;
for(int i=MaxSize;i<Size;i++)
    XoredArray[i]=(A[i]==B.A[i])?0:1;
int XoredInt=0;
int pow=1;
for(int i=Size-1;i>=Size-MaxSize;i--){
    XoredInt+=pow*XoredArray[i];
    pow*=2;
}
return XoredInt;
}
int main(){
int T;
cin>>T;
for(int i=0;i<T;i++)
{

}

return 0;
}
