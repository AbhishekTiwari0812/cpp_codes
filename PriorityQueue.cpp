#include<iostream>
#include<math.h>
#define MAX_HEAP_SIZE 10000

using namespace std;
class node{
    int value;
    vector<node> neighbours;
public:
    node(int i){
    value=i;
    for(int j=i+1;j<=i+6;i++)
    neighbours.add(j);
    }
    addNeighbour(node &a){
    neighbours.push(a);
    }
    getNeighbour(int i){

    }
    };



template<typename T>
class Heap{
T mHeap[MAX_HEAP_SIZE];
int HeapSize=0;
public:
    void MinHeapify(int);
    T HeapMin();
    Heap(T *,int);
    T ExtractMin();
    void increaseKey(int,int);
    void decreaseKey(int,int);
    void insert(T);
    void swap(T *a,T *b){
    int temp=(*a).value;
    (*a).value=(*b).value;
    (*b).value=temp;
    }
    int parent(int i){
        return ceil(float(i)/2);
    }
    int left(int i){
        return 2*i+1;
    }
    int right(int i){
        return 2*i+2;
    }

};
template<typename T>
void Heap<T>::MinHeapify(int index){        //comparing downwards
int l=left(index);
int r=right(index);
int smallest =index;
if(l<HeapSize-1 && mHeap[l].value<mHeap[index].value ){         //change sign for changing Heap type
smallest=l;
}
if(r<HeapSize-1 && mHeap[r].value<mHeap[smallest].value){        //change sign for changing Heap type
    smallest=r;
}
if(smallest!=index){
    swap(&smallest,&index);            //only swap the sentential data,not the complete element..!
    MinHeapify(smallest);
}
}
template<typename T>
Heap<T>::Heap(T *ConvToHeap,int Size){
    HeapSize=Size;
    for(int i=HeapSize-1;i>=0;i--){
        mHeap[i]=ConvToHeap[i];
    }
    for(int i=HeapSize/2-1;i>=0;i--){
        MinHeapify(i);
    }
}
template<typename T>
T Heap<T>::HeapMin(){
return mHeap[0];
}
template<typename T>
T Heap<T>::ExtractMin(){
    if (HeapSize<1){
     cout<<"heap underflow";
     return NULL;
    }
     T max =mHeap[0];
     mHeap[0]=mHeap[HeapSize-1];
     HeapSize-=1;
     MinHeapify(0);
     return max;
}
template<typename T>
void Heap<T>::increaseKey(int index,int newValue){      //this is also to be modified if you want change the type of heap
  if(newValue>mHeap[index].value){
        cout<<"Value is being decreased while increaseKey was called"<<endl;
        return ;
    }
    mHeap[index].value=newValue;
    MinHeapify(index);
}
template<typename T>
void Heap<T>::decreaseKey(int index,int newValue){      //this is also to be modified if you want change the type of heap
    if(newValue>mHeap[index].value){
        cout<<"Value is being increased while decreaseKey was called"<<endl;
        return ;
    }
    mHeap[index].value=newValue;
    while(index>0 && mHeap[parent(index)].value<mHeap[index].value){
        swap(&mHeap[parent(index)],&mHeap[index]);
        index=parent(index);
    }
}
template<typename T>
void Heap<T>::insert(T newNode){
HeapSize+=1;
mHeap[HeapSize-1]=newNode;
mHeap[HeapSize-1].value=INFINITY;
decreaseKey(HeapSize-1,newNode.value);
}












