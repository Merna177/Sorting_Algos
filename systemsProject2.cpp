#include <iostream>
#include <regex>
using namespace std;

#define pb push_back
typedef pair<int,string>ii;
vector<string>keywords;
void addKeywords(){
    keywords.pb("PROGRAM");
    keywords.pb(("VAR"));
    keywords.pb(("BEGIN"));
    keywords.pb(("END"));
    keywords.pb(("END."));
    keywords.pb(("FOR"));
    keywords.pb(("READ"));
    keywords.pb(("WRITE"));
    keywords.pb(("TO"));
    keywords.pb(("DO"));
    keywords.pb(("FOR"));
}
int isToken(string s){
    for(int i=0;i<keywords.size();i++){
        if(keywords[i]==s){
            if(s=="FOR")return 14;
            return i+1;
        }
    }
    if(regex_match(s,regex("-|[[:digit:]]+|\\-|[[:digit:]]+.[[:digit:]]+")))return 17;
    if(regex_match(s,regex("([a-z]|[A-Z])([[:digit:]]|[a-z]|[A-Z])*")))return 1;
    if(s==";")return 11;
    if(s==":=")return 12;
    if(s=="+")return 13;
    if(s=="(")return 15;
    if(s==")")return 16;
    if(s=="*")return 18;
    return 0;
}
vector<string>spaceDivide(string s){
   vector<string>ret;
   string cur="";
   for(int i=0;i<s.length();i++){
        if(s[i]==' '){
            if(cur.length())
                ret.pb(cur);
            cur="";
        }
        else
           cur+=s[i];
   }
   if(cur.length())
    ret.pb(cur);
}
vector<vector<ii> >tokens;
void divideIntoTokens(string s){
   vector<ii>cur;
   int len=s.size();
   int start=0;
   while(len !=0){
       string x=s.substr(start,len);
        int type=isToken(x);
    if(type){
        cur.push_back(make_pair(type,x));cout<<x<<endl;
        start+= x.size();
        len=s.size()-start;
    }
    else{
        len--;
    }
    if(len==0 && start !=s.size() ){
        if(x==","){
            start++;
            len=s.size()-start;

        }
       else{
            cout<<"SYNTAX ERROR";
            exit(0);
        }
    }

   }
  tokens.pb(cur);
}
int main()
{
    divideIntoTokens("READ(Y,Z,B,1a)");
    return 0;
}
