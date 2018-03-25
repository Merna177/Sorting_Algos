#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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

map<string,int>SYMTAB;
map<string,bool>isDir;
map<string,string>OPTAB;
string s,label,operand,dir;
int startingAddress,locationCounter,progLength;
bool ERROR=0;

vector<string>divide(string s){/// divides the string into fields label , operand, dir
  vector<string>ret;
  string cur="";
  for(int i=0;i<s.length();i++){
      if(s[i]==' '){
        if(cur.length()!=0){
            ret.push_back(cur);
            cur="";
        }
      }
      else{
        cur+=s[i];
      }
  }
  if(cur.length()!=0)
    ret.push_back(cur);
  return ret;
}
bool isAssemblerDirective(string s){/// returns true if the string is an assemblre directive or RESW RESB
  return isDir.count(s)|OPTAB.count(s);
}
void getInput(){///reads line from file divides it into fields
        getline(cin,s);
        if(s.length()==0)
            getline(cin,s);
        vector<string>cur=divide(s);
        label="",dir="",operand="";
        for(int i=0;i<cur.size();i++){
            if(isAssemblerDirective(cur[i])){
                dir=cur[i];
                if(i)
                    label=cur[i-1];
                if(i+1<cur.size())
                    operand=cur[i+1];
            }
        }
        if(operand.length()>2){
            int sz=operand.length();
            if(operand[sz-1]=='X'&&operand[sz-2]==',')
                operand.erase(operand.end()-2,operand.end());
        }
}
int toInt(string a){/// converts hexa to int
   int cur=0;
   for(int i=0;i<a.length();i++){
        cur*=16;
        if(a[i]>='0'&&a[i]<='9')cur+=a[i]-'0';
        else cur+=10+(a[i]-'A');
   }
   return cur;
}
FILE *f;
void getInput2(){///reads line from file divides it into fields intermediate file
        char c=fgetc(f);
        s="";
        while(c!='\n'){
            s+=c;
            c=fgetc(f);
        }
        vector<string>cur=divide(s);
        label="",dir="",operand="";
        for(int i=0;i<cur.size();i++){
            if(isAssemblerDirective(cur[i])){
                dir=cur[i];
                if(i-1>0)
                    label=cur[i-1];
                if(i+1<cur.size())
                    operand=cur[i+1];
            }
        }
        if(operand.length()>2){
            int sz=operand.length();
            if(operand[sz-1]=='X'&&operand[sz-2]==',')
                operand.erase(operand.end()-2,operand.end());
        }
        locationCounter=toInt(cur[0]);
}
int getSize(string s){/// returns size of the operand in case of BYTE
    int sum=0;
    if(s[0]=='X'){
       sum=int(s.length())-3;
       sum+=sum%2;
       sum/=2;
    }
    else{
         sum=int(s.length())-3;
    }
    return sum;
}
string val="FEDCBA9876543210";
string toHexa(int a){/// converts decimal to hexa
  string ret="";
  if(s.length()>2){
    if(s[s.length()-1]=='X'&&s[s.length()-2]==',')
        a+=(1<<15);
  }
  int power=16*16*16;
  for(int i=3;i>=0;i--){
      for(int j=15;j>=0;j--){
        if(j*power<=a){
            ret+=val[15-j];
            a-=j*power;
            break;
        }
      }
      power/=16;
  }
  return ret;
}
string toHexaOneByte(int a){/// converts decimal to hexa
  string ret="";
  int power=16;
  for(int i=1;i>=0;i--){
      for(int j=15;j>=0;j--){
        if(j*power<=a){
            ret+=val[15-j];
            a-=j*power;
            break;
        }
      }
      power/=16;
  }
  return ret;
}
void printIntermediate(int tmp){
  FILE *f = fopen("intermediate.out","a");
  string loc=toHexa(tmp);
  for(int i=0;i<loc.length();i++)
    fprintf(f,"%c",loc[i]);
  fprintf(f," ");
  for(int i=0;i<s.length();i++){
      fprintf(f,"%c",s[i]);
  }
  fprintf(f,"\n");
  fclose(f);
}
void Pass1(){
    getInput();
    int tmp=0;
    if(dir=="START"){
             startingAddress=toInt(operand);
             locationCounter=startingAddress;
             tmp=locationCounter;
             printIntermediate(tmp);
             getInput();
    }
    else{
        startingAddress=0;
        locationCounter=0;
    }
    while(1){
         /// if comment skip it
         tmp=locationCounter;
         bool flag=0;/// to not print in intermediate file if the line is wrong
         if(label.length()!=0){
            if(SYMTAB.count(label)){
                printf("ERROR : duplicate labels\n");
                ERROR=1;
                flag=1;
            }
            else{
                SYMTAB[label]=locationCounter;
            }
         }
         if(dir=="END"){
             printIntermediate(tmp);
             break;
         }
         if(dir=="START"){
                printf("ERROR : START exists more that once\n");
                ERROR=1;
                flag=1;
         }
         else{
            if(OPTAB.count(dir)){
                locationCounter+=3;
            }
            else if(dir=="WORD"){
                locationCounter+=3;
            }
            else if(dir=="RESW"){
                locationCounter+=3*toInt(operand);
            }
            else if(dir=="RESB"){
                locationCounter+=toInt(operand);
            }
            else if(dir=="BYTE"){
                locationCounter+=getSize(operand);
            }
            else{
                printf("ERROR : not defined opCode\n");
                ERROR=1;
                flag=1;
            }
         }
         if(!flag)
            printIntermediate(tmp);
         getInput();
    }
    progLength=locationCounter-startingAddress;
}
string objectCode;
void printListing(string code){/// prints into listing file after PASS 2
  FILE *f = fopen("listing.out","a");
  objectCode=code;
  for(int i=0;i<s.length();i++){
      fprintf(f,"%c",s[i]);
  }
  fprintf(f," ");
  for(int i=0;i<code.length();i++){
      fprintf(f,"%c",code[i]);
  }
  fprintf(f,"\n");
  fclose(f);
}
string toAscii(string a){/// converts operand to ascii
  string ret="";
  for(int i=0;i<a.length();i++){
     int convert=a[i];
     ret+=toHexaOneByte(convert);
  }
  return ret;
}
int fromStringtoInt(string a){
   int ret=0;
   for(int i=0;i<a.length();i++)
    ret*=10,ret+=(a[i]-'0');
  return ret;
}
int recordStart=-1,len=0;
string record;
void printObj(char c,string code){/// prints into listing file after PASS 2
  FILE *f = fopen("Obj.out","a");
  fprintf(f,"%c ",c);
  for(int i=0;i<code.length();i++){
        fprintf(f,"%c",code[i]);
  }
  fprintf(f,"\n");
  fclose(f);
}
string makeSizeSix(string s){
    if(s.length()>=6)return s;
    for(int i=0;i+s.length()<=6;i++){
        s="0"+s;
    }
    return s;
}
void Pass2(){
    int operandAddress,tmp;
    string opcodeValue;
    getInput2();
    if(dir=="START"){
             locationCounter=startingAddress;
             printListing("");
             string send=label;
             send+=" ";
             send+=makeSizeSix(operand);
             send+=" ";
             send+=makeSizeSix(toHexa(progLength));
             printObj('H',send);
             getInput2();
    }
    else{
        locationCounter=0;
             string send="000000";
             send+=" ";
             send+="000000";
             send+=" ";
             send+=makeSizeSix(toHexa(progLength));
        printObj('H',send);
    }
    while(1){
         if(dir=="END"){
            if(record.length()){
                string send=makeSizeSix(toHexa(recordStart));
                send+=" ";
                string z=toHexa((len+1)/2);
                z.erase(z.begin(),z.begin()+2);
                send+=z;
                send+=" ";
                send+=record;
                printObj('T',send);
            }
            if(SYMTAB.count(operand)){
                operand=toHexa(SYMTAB[operand]);
                s.erase(s.end()-operand.length()-2,s.end());
                printListing(operand);
            }
            else
              printListing("");
            printObj('E',operand);
            break;
         }
         if(dir=="START"){
                printf("ERROR : START exists more that once\n");
                ERROR=1;
         }
         else{
                tmp=locationCounter;
                if(recordStart==-1){
                    recordStart=locationCounter;
                }
               if(OPTAB.count(dir)){
                    opcodeValue=OPTAB[dir];
                    if(operand.length()!=0)
                        if(SYMTAB.count(operand))
                          operandAddress=SYMTAB[operand];
                        else{
                          operandAddress=0;
                          ERROR=1;
                          printf("ERROR : SYMBOL NOT FOUND\n");
                        }
                    else{
                        operandAddress=0;
                    }
                   printListing(opcodeValue+toHexa(operandAddress));
                }
                else{
                    if(dir=="BYTE"||dir=="WORD"){
                        string tmp="";
                        opcodeValue="";
                        for(int i=0;i<s.length();i++){
                            if((s[i]=='X'||s[i]=='C')&&s[i+1]=='’'){/// gowa X hexa
                                i+=2;
                                while(s[i]!='’')
                                    opcodeValue+=s[i++];
                                break;
                            }
                            tmp+=s[i];
                        }/// tmp ta2reban mlosh lzma
                        s=tmp;
                        if(dir=="WORD"){
                            if(opcodeValue.length()==0){
                                   if(operand[operand.length()-1]=='H'){
                                       operand.erase(operand.end()-1,operand.end());
                                       printListing(operand);
                                   }
                                   else
                                    printListing(makeSizeSix(toHexa(fromStringtoInt(operand))));
                            }
                            else if(operand[0]=='X')
                               printListing(makeSizeSix(opcodeValue));
                            else if(operand[0]=='C')
                               printListing(makeSizeSix(toAscii(opcodeValue)));
                        }
                        else{
                          if(opcodeValue.length()==0){
                             if(operand[operand.length()-1]=='H'){
                                    operand.erase(operand.end()-1,operand.end());
                                    printListing(operand);
                             }
                            else
                                printListing(toHexa(fromStringtoInt(operand)));
                          }
                          else if(operand[0]=='X')
                            printListing(opcodeValue);
                          else if(operand[0]=='C'){
                            printListing(toAscii(opcodeValue));
                          }
                        }
                    }
                    else{
                           ///RESW RESB
                           printListing("");
                    }
                }
         }
         if(objectCode.length()+len>60||((dir=="RESW"||dir=="RESB")&&record.length()!=0)){
            string send=makeSizeSix(toHexa(recordStart));
            send+=" ";
            string z=toHexa((len+1)/2);
            z.erase(z.begin(),z.begin()+2);
            send+=z;
            send+=" ";
            send+=record;
            printObj('T',send);
            if(dir!="RESW"&&dir!="RESB"){
              recordStart=tmp;
              record=objectCode;
              len=objectCode.length();
            }
            else{
                recordStart=-1;
                record="";
                len=0;
            }
         }
         else{
            record+=" ";
            len+=objectCode.length();
            record+=objectCode;
         }
         getInput2();
    }
}
int main()
{
    INIT_TIMER;
    START_TIMER;
    freopen("test.in","r",stdin);
    isDir["START"];
    isDir["BYTE"];
    isDir["RESW"];
    isDir["RESB"];
    isDir["WORD"];
    isDir["END"];
    OPTAB["JLT"]="38";
    OPTAB["TIX"]="2C";
    OPTAB["ADD"]="18";
    OPTAB["STA"]="0C";
    OPTAB["LDA"]="00";
    OPTAB["LDX"]="04";
    OPTAB["STL"]="14";
    OPTAB["JSUB"]="48";
    OPTAB["COMP"]="28";
    OPTAB["LDCH"]="50";
    OPTAB["STCH"]="54";
    OPTAB["SUB"]="1C";
    OPTAB["TD"]="E0";
    OPTAB["RD"]="D8";
    OPTAB["WD"]="DC";
    OPTAB["JEQ"]="30";
    OPTAB["MUL"]="20";
    Pass1();
    f = fopen("intermediate.out","r");
    Pass2();
    STOP_TIMER("Time taken by the program : ");
    return 0;
}
