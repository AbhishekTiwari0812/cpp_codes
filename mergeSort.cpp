#include<iostream>
#define INF 10000       //inf must be bigger than all the other objects to be compared
using namespace std;
template<class t>
void merge(t a[],int left_start,int right_end){
int middle=(left_start+right_end)/2;
t left_array[middle-left_start+1+1];
t right_array[right_end-middle+1];
for(int i=left_start;i<=middle;i++)
    left_array[i-left_start]=a[i];
left_array[middle-left_start+1]=INF;
for(int i=middle+1;i<=right_end;i++)
    right_array[i-middle-1]=a[i];
right_array[right_end-middle]=INF;
int left_cursor=0;
int right_cursor=0;
for(int i =left_start;i<=right_end;i++)
{
    if(right_array[right_cursor]>=left_array[left_cursor])
        a[i]=left_array[left_cursor++];
    else
        a[i]=right_array[right_cursor++];
}
}
template<class t>
void merge_sort(t a[],int start ,int end){
    if(start<end)
    {
        int middle=(start+end)/2;
        merge_sort(a,start,middle);
        merge_sort(a,middle+1,end);
        merge(a,start,end);

    }
}
//first algorihtm will be to sort the whole array by merge sort algorithm and find out the k-th element
int main()
{
int to_sort[]={4,230,43,2,43};
int size=5;
merge_sort(to_sort,0,size-1);
for(int i=0;i<size;i++)
    cout<<to_sort[i]<<" ";
cout<<endl;

}
