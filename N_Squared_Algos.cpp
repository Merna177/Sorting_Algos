#include <iostream>

using namespace std;

int n,arr[100];
void bubbleSort(){
   for(int i=0;i<n;i++){
      for(int j=0;j<n-1;j++){
        if(arr[j]>arr[j+1])
            swap(arr[j],arr[j+1]);
      }
   }
}
void insertionSort(){
   for(int i=0;i<n;i++){
      int mnIdx=i;
      for(int j=i;j<n;j++){
        if(arr[mnIdx]>arr[j])
            mnIdx=j;
      }
      swap(arr[mnIdx],arr[i]);
   }
}
int main()
{
        n=7;
     arr[0]=8;
 arr[1]=-2;
 arr[2]=10;
 arr[3]=7;
 arr[4]=-10;
 arr[5]=11;
 arr[6]=2610;
 //bubbleSort();
 insertionSort();
 for(int i=0;i<n;i++)
    cout<<arr[i]<<' ';

    return 0;
}
