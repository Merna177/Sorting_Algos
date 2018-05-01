#include <iostream>
#include <regex>
using namespace std;

#define pb push_back
#define F first
#define S second
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
    if(regex_match(s,regex("([a-z]|[A-Z])([[:digit:]]|[a-z]|[A-Z])*")))return 17;
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
   return ret;
}
vector<ii>tokens;
void divideIntoTokens(string s){
   int len=s.size();
   int start=0;
   while(len !=0){
       string x=s.substr(start,len);
        int type=isToken(x);
    if(type){
        tokens.push_back(make_pair(type,x));
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
}
int idx=0;
int get(){/// returns next token 0 if vector 5ls
  if(idx==tokens.size())return 0;
  return tokens[idx].F;
}
void incr(){
   idx++;
}
bool isNumber(int idx){ /// whether token 17 is a number wala l2
   string s=tokens[idx].S;
  if(regex_match(s,regex("-|[[:digit:]]+|\\-|[[:digit:]]+.[[:digit:]]+")))return 1;
  return 0;
}
void ERROR(){
        cout<<"Syntax Error";
        exit(0);
}
void expression(){ /// id |   factor + factor | factor * factor
   if(get()!=17)ERROR();
   incr();
   while(get()==13||get()==18){
      incr();
      if(get()!=17)ERROR();
   }
}
void READ(){

}
void WRITE(){

}
void FOR(){

}
void ASSIGN(){
    if(get()==17&&isNumber(idx)==0)incr();
    else ERROR();
    if(get()==12)incr();
    else ERROR();
    ///expression
    expression();
    if(get()!=11)ERROR();
    incr();
}
void statements(){
   while(get()==7||get()==8||get()==14||(get()==17&&isNumber(idx)==0)){
         if(get()==7)READ();
         if(get()==8)WRITE();
         if(get()==14)FOR();
         if(get()==17)ASSIGN();/// call each of them and let them check
   }
}
void parse(){
   /// Program name
   if(get()==1){
      incr();
      if(isNumber(idx)==0&&get()==17)
         incr();
      else ERROR();
   }
   else
      ERROR();
   /// VAR
   if(get()==2){
       incr();
       if(isNumber(idx)==0&&get()==17)/// at least 1 id
          incr();
       else
         ERROR();
       while(get()==17){
             if(isNumber(idx))ERROR();
             incr();
       }
   }
   /// BEGIN
   if(get()!=3)ERROR();
   incr();
   statements();
   ///
   if(get()!=5)ERROR();///END.
}
int main()
{
    freopen("test.in","r",stdin);
    string s;
    addKeywords();
    for(int i=0;i<5;i++){
         getline(cin,s);
         vector<string>z=spaceDivide(s);
         for(int j=0;j<z.size();j++)
            divideIntoTokens(z[j]);
    }
    parse();
    return 0;
}

