#include <iostream>
#include <bits/stdc++.h>
#include <time.h>
#include <chrono>

using namespace std;

#define pb push_back
#define ll long long
#define F first
#define S second
#define PI acos(-1)
#define EPS 1e-8
#define BASE 53ll
#define mod 1000000007ll
#define ld long double
#define MAX 900001
#define NIL 0
#define INF (1<<28)

#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER  start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            std::chrono::high_resolution_clock::now()-start \
    ).count() << " ms " << std::endl;
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#endif
typedef pair<int,int>ii;
typedef pair<ii,int>state;
typedef pair<int,ii>edge;
typedef pair<vector<int>,int>vii;
const int N=100005;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }
ll fact(ll n){ll ret=1;for(int i=1;i<=n;i++)ret*=i;return ret;}
bool is_vowel(char c){if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y')return 1;return 0;}
ld getDistance(ld x1,ld y1,ld x2,ld y2){return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

int arr[N],n;
void bubbleSort(){
   for(int i=0;i<n;i++){
      for(int j=0;j<n-1;j++){
        if(arr[j]>arr[j+1])
            swap(arr[j],arr[j+1]);
      }
   }
}
///
int quickArr[N];
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
///
int main()
{
   //freopen("cases.out","w",stdout);
   cin>>n;
   for(int i=0;i<n;i++){
        arr[i]=rand()%1000000000;
        quickArr[i]=arr[i];
   }
   INIT_TIMER;
   START_TIMER;
   bubbleSort();
   STOP_TIMER("bubble sort -> ");
   START_TIMER;
   quickSort(0,n-1);
   STOP_TIMER("quick sort -> ");
   return 0;
}
