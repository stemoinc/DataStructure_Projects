#include"String.h"
int *GetPrefix(char *a,int lenth){
    int *prefix=new int[lenth];
    prefix[0]=0;
    for(int i=1;i<lenth;i++){
        int j=prefix[i-1];
        while(j>0&&a[j]!=a[i]) j=prefix[j-1];
        if(a[j]==a[i]) j++;
        prefix[i]=j;
    }
    return prefix;
}
int KMP(char *a,char *b,int lenthA,int lenthB){
    int ptrA=0;
    int ptrB=0;
    int *prefixB=GetPrefix(b,lenthB);
    while(1){
        if(a[ptrA]==b[ptrB]){
            if((ptrB+1)==lenthB){
                delete prefixB;
                return ptrA-lenthB+1;
            }else{
                if((ptrA+1)==lenthA){
                    delete prefixB;
                    return -1;
                }else{
                    ptrA++;
                    ptrB++;
                }
            }
        }else{
            if((ptrA+1)==lenthA){
                delete prefixB;
                return -1;
            }else{
                if(ptrB==0){
                ptrA++;
            }else{
                ptrB=prefixB[ptrB-1];
            }
            }
        }
    }
}
String::String(){
    stringValue=nullptr;
    lenth=0;
}
String::String(char *s,int len){
    stringValue=s;
    lenth=len;
}
String::String(const String&s){
    int sLenth=s.Length();
    char *sPtr=s.getStringValue();
    stringValue=new char[sLenth];
    for(int i=0;i<sLenth;i++){
        stringValue[i]=sPtr[i];
    }
    lenth=sLenth;
}
String::String(const char* s){
    int i=0;
    for(;s[i]!='\0';i++);
    stringValue=new char[i];
    for(int j=0;s[j]!='\0';j++){
        stringValue[j]=s[j];
    }
    lenth=i;
}
String::~String(){
    delete stringValue;
}
void String::Show(){
    for(int i=0;i<lenth;i++){
        std::cout<<stringValue[i];
    }
    std::cout<<std::endl;
}
int String::Length() const{
    return lenth;
}
char* String::getStringValue()const{
    return stringValue;
}
bool String::Empty()const{
    if(lenth)
    return false;
    else
    return true;
}
int String::match(const String &s)const{
    return KMP(s.getStringValue(),this->stringValue,s.Length(),lenth);
}
String String::subString(int begin,int end)const{
    char *str=new char[end-begin+1];
    int len=end-begin+1;
    for(int i=0;i<len;i++){
        str[i]=stringValue[begin+i];
    }
    String s(str,len);
    return s;
}
String String::operator+(const String &s){
    int sLenth=s.Length();
    char *sPtr=s.getStringValue();
    char *newStrPtr=new char[sLenth+lenth];
    for(int i=0;i<lenth;i++){
        newStrPtr[i]=stringValue[i];
    }
    for(int i=lenth;i<sLenth+lenth;i++){
        newStrPtr[i]=sPtr[i-lenth];
    }
    String news(newStrPtr,sLenth+lenth);
    return news;
}
String& String::operator=(const String &s){
    int sLenth=s.Length();
    char *sPtr=s.getStringValue();
    char *newStrPtr=new char[sLenth];
    for(int i=0;i<sLenth;i++){
        newStrPtr[i]=sPtr[i];
    }
    delete stringValue;
    stringValue=newStrPtr;
    lenth=sLenth;
    return *this;
}
std::ostream& operator <<(std::ostream &out,String &s){
    char *sOut=s.stringValue;
    for(int i=0;i<s.lenth;i++){
        out<<sOut[i];
    }
    return out;
}
bool operator >>(std::istream &in,String &s){
    if(in.eof()){
        return false;
    }else{
    int Len=500;
    char *newString=new char[Len];
    char ch;
    ch=in.get();
    int i;//i is the lenth of the changed string
    for(i=0;ch!='\n';i++){
        if(i==Len){
            return false;
        }else{
            newString[i]=ch;
            if(in.eof()){
                break;
            }
            ch=in.get();
        }
    }
    delete s.stringValue;
    s.stringValue=newString;
    s.lenth=i;
    return true;
    }
}