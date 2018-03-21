#include <iostream>
#include <bits/stdc++.h>
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

int main()
{
   freopen("cases.out","w",stdout);
   /// test case
   /// size of each case
   /// integers in this case
   cout<<8<<endl;
   int n[]={5,10,50,100,500,1000,5000,10000};
   for(int i=0;i<8;i++){
      cout<<n[i]<<' ';
      for(int j=0;j<n[i];j++){
        int r=rand()%1000000000;
        cout<<r<<' ';
      }
      cout<<endl;
   }
   return 0;
}
