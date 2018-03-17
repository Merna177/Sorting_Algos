#include <iostream>

using namespace std;

int arr[1000],tmp[1000],n;
void MergeSort(int l,int r){
  if(l==r)return;
  int mid=(l+r)/2;
  MergeSort(l,mid);
  MergeSort(mid+1,r);
  int pointer2=(l+r)/2 +1,pointer1=l,i=0;
  while(pointer1<=(l+r)/2 &&pointer2<=r){
    if(arr[pointer2]<arr[pointer1]){
        tmp[i]=arr[pointer2];
        pointer2++;
    }
    else{
        tmp[i]=arr[pointer1];
        pointer1++;
    }
    i++;
  }
  while(pointer2<=r)tmp[i++]=arr[pointer2++];
  while(pointer1<=(l+r)/2+1)tmp[i++]=arr[pointer1++];
  for(int i=l;i<=r;i++)
    arr[i]=tmp[i-l];
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


    MergeSort(0,n-1);
    for(int i=0;i<n;i++)cout<<arr[i]<<' ';
    return 0;
}
