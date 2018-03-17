#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int quickArr[100];
int Partition(int i,int j){
    int len=j-i+1;
    int pivot=rand()%len+i;
    int pointer1=i-1;
    swap(quickArr[j],quickArr[pivot]);
    for(int k=i;k<j;k++){
        if(quickArr[k]<=quickArr[j]){
            pointer1++;
            swap(quickArr[k],quickArr[pointer1]);
        }
    }
    swap(quickArr[pointer1+1],quickArr[j]);
    return pointer1+1;
}
void quickSort(int i,int j){
if(i>=j)
    return;
int dest = Partition(i,j);
quickSort(i,dest-1);
quickSort(dest+1,j);
}
int main()
{
 int n=7;
  quickArr[0]=8;
 quickArr[1]=-2;
 quickArr[2]=10;
 quickArr[3]=7;
 quickArr[4]=-10;
 quickArr[5]=11;
 quickArr[6]=2610;
 quickSort(0,n-1);
 for(int i=0;i<n;i++){
    cout<<quickArr[i]<<" ";
 }
    return 0;
}
