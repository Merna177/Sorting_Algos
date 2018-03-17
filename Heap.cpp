#include <iostream>

using namespace std;

int heap[1005],len=0;
int getParentIndex(int index){
    return index/2;
}
int getParent(int index){
    return heap[index/2];
}
void heapifyup(){
    int index=len-1;
    while(index && getParent(index)<heap[index]){
            swap(heap[index],heap[getParentIndex(index)]);
            index = getParentIndex(index);
    }
}
void add(int value){
    if(len==0){
     heap[0]=value;
     len++;
    }
    else{
        heap[len]=value;
        len++;
        heapifyup();
    }


}
int getLeft(int i){
 return i*2+1;
}
int getRight(int i){
 return i*2+2;
}
void heapifydown(){
    int index=0,largest;
    while(1){
        int left=getLeft(index);
        int right=getRight(index);
        if(left >= len)
            break;
        if(heap[index]<heap[left])
            largest=left;
        else
            largest=index;
        if(right <len && heap[largest]<heap[right])
            largest=right;
        if(largest==index)
            break;
        swap(heap[index],heap[largest]);
        index=largest;
    }

}
int Remove(){
    int ret=heap[0];
    heap[0]=heap[len-1];
    len--;
    heapifydown();
    return ret;
}

int main()
{

  return 0;
}
