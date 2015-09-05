#include<iostream>
using namespace std;

long long f(int a)
{
    long long product;
    for(int i=0; i<a; i++)
        product*=i;
    return product;
}
class Union
{
public:
    bool head;
    bool isInitialized;
    int value;
    Union* parent;
    int cardinality;
    Union(int i)
    {
        value=i;
        isInitialized=false;
        cardinality=1;
        head=true;
    }
};
void(Union* a,Union* b)
{
    if ((*a).isInitialized==false && (*b).isInitialized==false)
    {
        (*a).parent=a;
        (*b).parent=a;
        (*a).head=true;
        (*a).cardinality+=1;

    }
    else if ((*a).isInitialized==true && (*b).isInitialized==false)
    {
        Union *k=(*a).parent;
        while ((*k).isInitialized!=true)
            k=(*k).parent;
        (*b).parent=k;
        (*b).isInitialized=true;
        (*k).cardinality+=1;
    }
    else if ((*b).isInitialized==true && (*a).isInitialized==false)
    {
        Union *k=(*b).parent;
        while ((*k).isInitialized!=true)
            k=(*k).parent;
        (*a).parent=k;
        (*a).isInitialized=true;
        (*k).cardinality+=1;

    }
    else
    {
    Union *k1=(*a).parent;
    Union *k2=(*b).parent;

}
int main()

{
    int N,K;
    cin>>N;
    cin>>K;
    Union A[N];

    return 0;
}
