keywords = [];
tokens = [[]];#lists of lists each list will have 2 items , string and token ID
def addKeywords():
    keywords.append("PROGRAM");
    keywords.append("VAR");
    keywords.append(("BEGIN"));
    keywords.append(("END"));
    keywords.append(("END."));
    keywords.append(("FOR"));
    keywords.append(("READ"));
    keywords.append(("WRITE"));
    keywords.append(("TO"));
    keywords.append(("DO"));
    keywords.append(("FOR"));

def isToken(s):
    for i in range(0,len(keywords)):
       if(keywords[i]==s):
           if(s=="FOR"):
              return 14;
           return i+1;
    #na2s regex isa
    return 0;            

def divideIntoTokens(s):
    cur =[];
    length=len(s);
    start=0;
    while(length!=0):
        x=s[start:length];
        type=isToken(x);
               
def main():
    string =raw_input("enter a string\n");
    words = string.split();#divide after spaces
    addKeywords();
    print(isToken(words[0]));
    #divideIntoTokens(string);
  
main();    
