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
    if(regex_match(s,regex("-|[[:digit:]]+|\\-|[[:digit:]]+.[[:digit:]]+"))){return 17;}
    if(regex_match(s,regex("(([a-z]|[A-Z])([[:digit:]]|[a-z]|[A-Z])*)")))return 17;
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
    int open=0;
    if(get()==15){
        open++;
        incr();
    }
    if(get()!=17)ERROR();
    incr();
    bool next=1;
    while(get()==13||get()==18||get()==15||get()==16)
    {
        if(get()==15)open++;
        if(get()==16)open--;
        if(open<0)ERROR();
        if(get()==16&&(tokens[idx+1].F!=13&&tokens[idx+1].F!=18)){
            incr();
            break;
        }
        if(get()==16){
            incr();
            continue;
        }
        incr();
        if(get()!=17)ERROR();
        incr();
    }
    if(open)ERROR();
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
   /// 13 + 18 * 17 id 15 ( 16 )
   stack<ii>st;
   bool empty=1;
   int used=0;
   for(int i=v[0]+2;i<=v[1];i++){
        if(tokens[i].F==15){
            st.push(tokens[i]);
        }
        if(tokens[i].F==16){
            empty=1;
            while(st.size()&&st.top().F!=15){
                ii cur=st.top();
                st.pop();
                if(cur.F==13)continue;
                if(empty){
                   cout<<"LDA "<<cur.S<<endl;
                   empty=0;
                }
                else{
                    cout<<"ADD "<<cur.S<<endl;
                }
            }
            st.pop();
            used++;
            while(tokens[i+1].F==18){
                i++;
                i++;
                cout<<"MUL "<<tokens[i].S<<endl;
                i++;
            }
            cout<<"STA "<<"USEDVAR"<<used<<endl;
            st.push(ii(17,"USEDVAR"+intToString(used)));
            empty=1;
        }
        if(tokens[i].F==13){
            st.push(tokens[i]);
        }
        if(tokens[i].F==18){
            st.push(tokens[i]);
        }
        if(tokens[i].F==17){
           bool in=0;
           while(st.size()&&st.top().F==18){
               in=1;
               st.pop();
               if(empty){
                  cout<<"LDA "<<st.top().S<<endl;
                  st.pop();
                  empty=0;
               }
               else{
                 cout<<"MUL "<<st.top().S;
                 st.pop();
               }
           }
           if(in){
            cout<<"MUL "<<tokens[i].S<<endl;
            while(tokens[i+1].F==18){
                 i++;
                 i++;
                 cout<<"MUL "<<tokens[i].S<<endl;
                 i++;
            }
            used++;
            cout<<"STA "<<"USEDVAR"<<used<<endl;
            st.push(ii(17,"USEDVAR"+intToString(used)));
           }
           else{
            st.push(tokens[i]);
           }
           empty=1;
        }
   }
   cout<<"LDA "<<st.top().S<<endl;
   st.pop();
   while(st.size()){
       if(st.top().F==13){st.pop();continue;}
       if(st.top().F==17)cout<<"ADD "<<st.top().S<<endl;
       st.pop();
   }
   cout<<"STA "<<tokens[v[0]].S<<endl;
   neededVar=max(neededVar,used);
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
    freopen("exp22.txt","r",stdin);
    //freopen("test.out","w",stdout);
    string s;
    addKeywords();
    for(int i=0; i<6; i++)
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
    for(int i=1;i<=neededVar;i++)cout<<"USEDVAR"<<i<<" RESW 1\n";
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

