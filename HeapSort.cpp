#include <iostream>

using namespace std;

int heap[1005],n,len;
int getLeft(int i){
 return i*2+1;
}
int getRight(int i){
 return i*2+2;
}
void heapify(int i){
   int l=getLeft(i);
   int r=getRight(i);
   int largest=i;
   if(l<n&&heap[l]>heap[i])
    largest=l;
   if(r<n&&heap[r]>heap[largest])
    largest=r;
   if(largest!=i){
      swap(heap[largest],heap[i]);
      heapify(largest);
   }
}
void build(){
   for(int i=n/2-1;i>=0;i--)
     heapify(i);

}
void HeapSort(){
    for(int i=n-1;i>=0;i--){
        swap(heap[0],heap[i]);
        n--;
        heapify(0);
    }
}
int main()
{
 n=7;
 len=n;
 heap[0]=8;
 heap[1]=-2;
 heap[2]=10;
 heap[3]=7;
 heap[4]=-10;
 heap[5]=11;
 heap[6]=2610;
 build();
  HeapSort();
  for(int i=0;i<len;i++){
    cout<<heap[i]<<" ";
  }
  return 0;
}
