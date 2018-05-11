#include <iostream>
#include <regex>
#include <set>
#include <string>
using namespace std;

#define pb push_back
#define F first
#define S second
typedef pair<int,string>ii;
vector<string>keywords;
bool flag=0,flag2=0;
void addKeywords()
{
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
int isToken(string s)
{
    for(int i=0; i<keywords.size(); i++)
    {
        if(keywords[i]==s)
        {
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
    if(s==",")return 19;
    if(s=="==")return 20;
    if(s==">=")return 21;
    if(s=="<=")return 22;
    if(s=="<")return 23;
    if(s==">")return 24;
    return 0;
}
vector<string>spaceDivide(string s)
{
    vector<string>ret;
    string cur="";
    for(int i=0; i<s.length(); i++)
    {
        if(s[i]==' ')
        {
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
void divideIntoTokens(string s)
{
    int len=s.size();
    int start=0;
    while(len !=0)
    {
        string x=s.substr(start,len);
        int type=isToken(x);
        if(type)
        {
            tokens.push_back(make_pair(type,x));
            start+= x.size();
            len=s.size()-start;
        }
        else
        {
            len--;
        }
        if(len==0 && start !=s.size() )
        {
            cout<<"SYNTAX ERROR";
            exit(0);
        }
    }
}
int idx=0;
int get() /// returns next token 0 if vector 5ls
{
    if(idx==tokens.size())return 0;
    return tokens[idx].F;
}
void incr()
{
    idx++;
}
bool isNumber(int idx)  /// whether token 17 is a number wala l2
{
    string s=tokens[idx].S;
    if(regex_match(s,regex("-|[[:digit:]]+|\\-|[[:digit:]]+.[[:digit:]]+")))return 1;
    return 0;
}
void ERROR()
{
    cout<<"Syntax Error";
    exit(0);
}
void expression()  /// id |   factor + factor | factor * factor
{
    if(get()!=17)ERROR();
    incr();
    while(get()==13||get()==18)
    {
        incr();
        if(get()!=17)ERROR();
        incr();
    }
}
vector<string>scanning;
///
void generateMyWRITE(){
    int    index=0;
    while(index<scanning.size()){
    if(flag2==1){
        cout<<"LDA "<<scanning[index]<<endl;
        cout<<"JSUB WRITE"<<endl;
        index++;
    }
    else{
        flag2=1;
    cout<<"WRITE  LDX #0"<<endl;
    cout<<"STA SCAN"<<endl;
    cout<<"LDT #3"<<endl;
    cout<<"JLOOP LDCH SCAN,X"<<endl;
    cout<<"TD INDEV"<<endl;
    cout<<"JEQ TLOOP"<<endl;
    cout<<"WD INDEV"<<endl;
    cout<<"TIXR T"<<endl;
    cout<<"JLLT TLOOP"<<endl;
    cout<<"RSUB"<<endl;
    }

    }
}
void generateMyREAD(){
int    index=0;
    while(index<scanning.size()){
    if(flag==1){
        cout<<"JSUB READ"<<endl;
        cout<<"STA "<<scanning[index]<<endl;
        index++;
    }
    else{
        flag=1;
    cout<<"READ  LDX #0"<<endl;
    cout<<"LDT #3"<<endl;
    cout<<"TLOOP TD INDEV"<<endl;
    cout<<"JEQ TLOOP"<<endl;
    cout<<"RD INDEV"<<endl;
    cout<<"STCH SCAN,X"<<endl;
    cout<<"TIXR T"<<endl;
    cout<<"JLLT TLOOP"<<endl;
    cout<<"LDA SCAN"<<endl;
    cout<<"RSUB"<<endl;
    }

    }
}
///
void READ()
{
    incr();
    if(get()!=15)ERROR();
    incr();
    if(get()!=17||isNumber(idx))ERROR();
    scanning.pb(tokens[idx].S);
    incr();
    while(get()==19)
    {
        incr();
        if(get()!=17||isNumber(idx))ERROR();
        scanning.pb(tokens[idx].S);
        incr();
    }
    generateMyREAD();
    if(get()!=16)ERROR();
    incr();
}
void WRITE()
{
    scanning.clear();
    incr();
    if(get()!=15)ERROR();
    incr();
    if(get()!=17||isNumber(idx))ERROR();
    scanning.pb(tokens[idx].S);
    incr();
    while(get()==19)
    {
        incr();
        if(get()!=17||isNumber(idx))ERROR();
        scanning.pb(tokens[idx].S);
        incr();
    }
    if(get()!=16)ERROR();
    incr();
}
void varAssembly(){

}
int statements();
void FOR(){
    /// FOR id := expr to expr
    /// DO
    /// statement wa7da or begin statements end
    incr();
    if(get()!=17 || isNumber(idx))ERROR();
    incr();
    if(get()!=12)ERROR();
    incr();
    expression();
    if(get()!=9)ERROR();
    incr();
    expression();
    if(get()!=10)ERROR();
    incr();
    bool more=0;
    if(get()==3)incr(),more=1;
    int k=statements();
    if(k>1&&more==0)ERROR();
    if(get()!=4&&more==1)ERROR();
    if(more)incr();
}
void IF()
{
    incr();
    if(get()!=15)ERROR();
    incr();
    while(get()!=17)ERROR();
    incr();
    while(get()==13 || get()==18)
    {
        incr();
        if(get() !=17)ERROR();
        incr();
    }
    if(get()!=20 && get()!=21 && get()!=22 && get()!=23 && get()!=24)ERROR();
    incr();
    if(get()!=17)ERROR();
    incr();
    while(get()==13 || get()==18){
        incr();
        if(get()!=17)ERROR();
        incr();
    }
    if(get()!=16)ERROR();
}
vector<int>v;
int neededVar=0;
vector<string>operations;
string intToString(int a){
  string ret="",z="0123456789";
  while(a){
    ret+=z[a%10];
    a/=10;
  }
  reverse(ret.begin(),ret.end());
  return ret;
}
void assignAssembley(){
   /// v[0] is the index to save data into
   /// skip v[0]+1
   vector<vector<int> >all;
   vector<int>var;
   vector<string>add;
   set<int>st;
   for(int i=v[0]+2;i<=v[1];i++){
        if(tokens[i].F==18){ /// *
             if(var.empty()||var.back()!=i-1){
                 if(var.size()){
                    all.pb(var);
                    var.clear();
                 }
                 var.pb(i-1);
                 st.insert(i-1);
             }
             var.pb(i+1);
             st.insert(i+1);
        }
   }
   for(int i=v[0]+2;i<=v[1];i++){
       if(tokens[i].F==17){
          if(!st.count(i))
           if(isNumber(i))
             add.pb("#"+tokens[i].S);
           else
             add.pb(tokens[i].S);
       }
   }
   if(var.size())all.pb(var);
   int cur=0;
   for(int i=0;i<all.size();i++){
       for(int j=0;j<all[i].size();j++){
           int pos=all[i][j];
           if(j==0){
               operations.pb("LDA "+tokens[pos].S);
           }
           else{
              if(isNumber(pos))
               operations.pb("MUL #"+tokens[pos].S);
              else
               operations.pb("MUL "+tokens[pos].S);
           }
       }
      if(i+1<all.size()){ /// keep last result in the
       cur++;
       operations.pb("STA savedVariables"+intToString(cur));
      }
      else{
         for(int j=1;j<=cur;j++){
            operations.pb("ADD savedVariables"+intToString(j));
         }
      }
   }
   neededVar=max(neededVar,cur);
   if(all.empty()){
      operations.pb("STA "+add.back());
      add.pop_back();
   }
   for(int i=0;i<add.size();i++){
      operations.pb("ADD "+add[i]);
   }
   operations.pb("STA "+tokens[v[0]].S);
}
void ASSIGN()
{
    v.clear();
    v.pb(idx);
    if(get()==17&&isNumber(idx)==0)incr();
    else ERROR();
    if(get()==12)incr();
    else ERROR();
    ///expression
    expression();
    v.pb(idx-1);
    if(get()!=11)ERROR();
    incr();
    assignAssembley();
}
vector<string>allvar;
int statements()
{
    int ret=0;
    while(get()==7||get()==8||get()==14||(get()==17&&isNumber(idx)==0))
    {
        if(get()==7)READ();
        if(get()==8)WRITE();
        if(get()==14)FOR();
        if(get()==17)ASSIGN();/// call each of them and let them check
        ret++;
    }
    return ret;
}
void parse()
{
    /// Program name
    if(get()==1)
    {
        incr();
        if(isNumber(idx)==0&&get()==17)
            incr();
        else ERROR();
    }
    else
        ERROR();
    /// VAR
    if(get()==2)
    {
        incr();
        if(isNumber(idx)==0&&get()==17)/// at least 1 id
            allvar.pb(tokens[idx].S),incr();
        else
            ERROR();
        while(get()==19)
        {
            incr();
            if(get()!=17||isNumber(idx))ERROR();
            allvar.pb(tokens[idx].S);
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
    freopen("test.out","w",stdout);
    string s;
    addKeywords();
    for(int i=0; i<11; i++)
    {
        getline(cin,s);
        vector<string>z=spaceDivide(s);
        for(int j=0; j<z.size(); j++)
            divideIntoTokens(z[j]);
    }
    parse();
    for(int i=0;i<operations.size();i++)cout<<operations[i]<<endl;
    generateMyWRITE();
    for(int i=0;i<allvar.size();i++)cout<<allvar[i]<<" RESW 1\n";
    if(flag==1 || flag2==1){
        cout<<"INDEV BYTE \"F2\" \n";
        cout<<"SCAN RESW 1\n";
    }
    return 0;
}
/*
PROGRAM BICS
VAR
X,Y,A,B,C,Z
BEGIN
X := X+5;
A := Y*5+11*Z+9.5;
END.
*/

