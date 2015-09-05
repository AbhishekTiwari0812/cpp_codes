#include <vector>
#include <string>
#include<iostream>
#include <sstream>

using namespace std;
int FindMaxRepLetter(string input)
{
int A[26];
for(int i=0;i<26;i++)
    A[i]=0;
for(int i=0;i<26;i++)
    A[input[i]-'a']++;
int max=0;
for(int i=0;i<26;i++)
    if(A[i]>max)
        max=A[i];
return max;
}

main()
{

    string str("hello girl");  //input string
    //first split the string.
    string buf;
    stringstream ss(str);
    vector<string> tokens;
    while (ss >> buf)
        tokens.push_back(buf);
    //now....
    //Main part.......
    int Result=-1;      //index of the word which has maximum repeated letters will be stored in this.
    int max=0;              //count of repetition of the letter in the result word.
     for(int i=0;i<tokens.size();i++)
        if(FindMaxRepLetter(tokens.at(i))>max){
            max=FindMaxRepLetter(tokens.at(i));
            Result =i;
    }

    cout<<tokens.at(Result);
}
