#include<iostream>
#include<cmath>
#define GRID_X 6
#define GRID_Y 7
using namespace std;
class Node
{
public:
    int position;
    int Hvalue;
    int Gvalue;
    int Fvalue;
    int block;
    char ListName;		//'n' stands for none,'o' for open,'c' for closed list
    Node * parent;
};

//Node OpenList[GRID_X*GRID_Y];	//we can improve the data cost by using more sophisticated data structure here!
Node GRID[GRID_X*GRID_Y];
//Node ClosedList[GRID_X*GRID_Y];//we can improve the data cost by using more sophisticated data structure here!
void CalclulateHvalue(Node A[],int size,Node GoalNode){
    int i;
    int Xpos1,Xpos2;
    int Ypos1,Ypos2;
    Xpos1=(GoalNode.position)%GRID_X;
    Xpos1=(Xpos1!=0)?Xpos1:(GRID_X);
    Ypos1=ceil(float(GoalNode.position)/GRID_X);
    for(i=0; i<size; i++)
    {
        if (A[i].block!=1)
        {
            Xpos2=(A[i].position)%GRID_X;
            Xpos2=(Xpos2!=0)?Xpos2:(GRID_X);
            Ypos2=ceil(float(A[i].position)/GRID_X);
            A[i].Hvalue=abs(Xpos2-Xpos1)+abs(Ypos2-Ypos1);
        }
    }
}
void UpdateGvalueAndParent(Node* from,Node* to){
        int Xpos1,Xpos2;
        int Ypos1,Ypos2;
        Xpos1=((*from).position)%GRID_X;
        Xpos1=(Xpos1!=0)?Xpos1:(GRID_X);
        Ypos1=ceil(float((*from).position)/GRID_X);
        Xpos2=((*to).position)%GRID_X;
        Xpos2=(Xpos2!=0)?Xpos2:(GRID_X);
        Ypos2=ceil(float((*to).position)/GRID_X);
        int MovementCost;       //can also be defined by the user.
        if ( (Xpos1==Xpos2)||(Ypos1==Ypos2))
            MovementCost=10;
        else
            MovementCost=14;
        if ((*from).Gvalue+MovementCost<(*to).Gvalue)
        {
            (*to).Gvalue=(*from).Gvalue+MovementCost;
            (*to).Fvalue=(*to).Gvalue+(*to).Hvalue; //Fvalue also gets updated
            (*to).parent=from;
        }
    }

Node NeighborList[9];
void ExpandNode(Node* MainNode)
{
    int Xpos1,Xpos2;
    int Ypos1,Ypos2;
    Xpos1=((*MainNode).position)%GRID_X;
    Xpos1=(Xpos1!=0)?Xpos1:(GRID_X);
    Ypos1=ceil(float((*MainNode).position)/GRID_X);
    int k=0;
    //cout<<"\nXpos:"<<Xpos1<<" Ypos:"<<Ypos1<<endl;
    //cout<<"Main node:"<<(*MainNode).position<<"     "<<(*MainNode).block<<"    ";
    for(int i=-1; i<=1; i++)
        for(int j=-1; j<=1; j++)
        {
            if ( Xpos1+i > 0  &&  Xpos1+i <= GRID_X  &&  Ypos1+j > 0  &&  Ypos1+j <= GRID_Y )
            {
                NeighborList[k]=GRID[((*MainNode).position+i+j*GRID_X)-1];
                if (NeighborList[k].block!=1)
                    UpdateGvalueAndParent(MainNode,&NeighborList[k]);
            }
            else
            {
                NeighborList[k]=GRID[((*MainNode).position+j+i*GRID_X)-1];
                NeighborList[k].block=1;
            }
            //cout<<"here"<<((*MainNode).position+j+i*GRID_X)<<endl;
            k++;
        }
    NeighborList[4].block=1;     //replacing the MainNode with an invalid Node
    //cout<<"\nIn Expand Node"<<endl;
    //cout<<"Main node:"<<(*MainNode).position<<"\n";
    //for(int i =0; i<9; i++)
      //  cout<<NeighborList[i].position<<"     "<<NeighborList[i].block<<"    ";
    //cout<<'\n';
}
static bool Success;
void Astar(Node* Root,Node* Goal)
{
    static int counter=0;

    if (counter>2*GRID_X*GRID_Y)
    {
        cout<<"There doesn't exist any path";
        Success=true;
        return;
    }
    counter+=1;
    Success=false;
    if ((*Root).position==(*Goal).position)
    {
      Success=true;
        cout<<"The shortest path is: ";
        return;
    }
    else
    {
        (*Root).ListName='c';
        ExpandNode(Root);
        //cout<<"\nin A*"<<endl;
        //cout<<"Root node:"<<(*Root).position<<endl;
        //cout<<"Neighbors:"<<endl;
        //for(int i =0; i<9; i++){
          //  cout<<NeighborList[i].position<<"   "<<" block:"<<NeighborList[i].block<<" ";
       // if (NeighborList[i].block==0)
       // cout<<"parent"<<(*NeighborList[i].parent).position<<endl;
        }
        for(int i=0; i<9; i++)
            if (NeighborList[i].block==0)
            {
              //  cout<<"Neighbor"<<NeighborList[i].position<<endl;
                //cout<<"In the Grid"<<GRID[NeighborList[i].position-1].position<<endl;
                GRID[NeighborList[i].position-1]=NeighborList[i];
          //      cout<<"this should be parent:"<<(*NeighborList[i].parent).position<<endl;
            //    cout<<"parent of"<<GRID[NeighborList[i].position-1].position<<" is:"<<(*GRID[NeighborList[i].position-1].parent).position<<endl;
                if (GRID[NeighborList[i].position-1].ListName=='n')
                    if (GRID[NeighborList[i].position-1].block==0)
                    GRID[NeighborList[i].position-1].ListName='o';
            }
        static Node Min=GRID[15];       //MAKE SURE TO ASSIGN IT TO SOME IMPASSABLE BLOCK INITIALLY!!!!!!
        //for(int i=0;i<42;i++)
          //  cout<<"Position:"<<GRID[i].position<<" Listname:"<<GRID[i].ListName<<" Fvalue:"<<GRID[i].Fvalue<<"\n";
        //for(int i=0;i<42;i++)
           // cout<<GRID[i].position<<" "<<GRID[i].Fvalue<<" list name"<<GRID[i].ListName<<endl;
        for(int i=0; i<GRID_X*GRID_Y; i++)
            if ((GRID[i].ListName=='o')&&(GRID[i].Fvalue<Min.Fvalue))
            {
                Min=GRID[i];
                //cout<<GRID[i].position<<" ";
                //cout<<GRID[i].Fvalue<<" ";
            }
        //cout<<"Min position: "<<Min.position<<" "<<Min.Fvalue;
        Node *NextNode=&GRID[Min.position-1];
        //if (Min.position==16)
          //      return;

//        for (long i=0;i<100000000;i++)
  //      {
        //cout<<"Busy here";
    //    i+=i+i-(2*i);
      //  }

        while (Success!=true)
            Astar(NextNode,Goal);		//this point may cause error.Put a while loop here!
    }

void printPath(Node* ToReach,Node* startingFrom)
{
    if ((*ToReach).position!=(*startingFrom).position)
        printPath(ToReach,(*startingFrom).parent);
    cout<<(*startingFrom).position<<" ";
}
int main()
{
    int x=0;
    while(x!=-1)
    {


    for(int i=0; i<GRID_X*GRID_Y; i++)
    {
        GRID[i].position=i+1;
        GRID[i].Gvalue=100000;          // ideally must be infinite
        GRID[i].Fvalue=100000;          // ideally must be infinite
        GRID[i].Hvalue=100000;
        GRID[i].block=0;
        GRID[i].ListName='n';
    }
    Node* StartNode,*GoalNode;
    int StartPoint;
    int EndPoint;
    cout<<"\nEnter Start Point and End point:";
    cin>>StartPoint;
    cin>>EndPoint;
    StartPoint-=1;
    EndPoint-=1;
    GRID[15].block=1;
    GRID[25].block=1;
    GRID[27].block=1;
    GRID[33].block=1;
    GoalNode=&GRID[EndPoint];
    CalclulateHvalue(GRID,42,*GoalNode);

    GRID[StartPoint].Gvalue=0;
    StartNode=&GRID[StartPoint];
    if((*StartNode).block==true||((*GoalNode).block==true))
    {
        cout<<"Sorry,Either the goal node or the starting node is a block\n";
        return -1;
    }
    (*StartNode).parent=&GRID[StartPoint];
    Astar(StartNode,GoalNode);
    cout<<endl;

    printPath(StartNode,GoalNode);/*while ((*GoalNode).position!=(*StartNode).position)
        {
            cout<<((*GoalNode).position)<<" ";
        GoalNode=(*GoalNode).parent;
                }*/
}
}
