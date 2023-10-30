#ifndef HEADER_STRING
#define HEADER_STRING
#include<fstream>
#include<iostream>
int KMP(char *a,char *b,int lenthA,int lenthB);//a is the text,b is the line
int *GetPrefix(char *a,int lenth);
class String{
    private:
    char* stringValue;
    int lenth;
    public:
    String();
    String(char *,int);
    String(const String& s);
    String(const char*);
    ~String();
    public:
    void Show();//will exchange line
    int Length() const;
    char *getStringValue() const;
    bool Empty() const;
    int match(const String &s)const;
    String subString(int begin,int end)const;
    String operator+(const String &s);
    String &operator=(const String &s);
    friend std::ostream &operator <<(std::ostream &out,String &s);
    friend bool operator >>(std::istream &in,String &s);
};
#endif