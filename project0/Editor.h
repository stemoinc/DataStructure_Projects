#ifndef HEADER_EDITOR
#define HEADER_EDITOR
#include"String.h"
#include"DBlist.cpp"
#include<stdio.h>
class Editor{
    private:
    DBlist<String> buffer;
    int lineNum;
    char *inputFileName;
    char *outputFileName;
    public:
    //constructor
    Editor();
    //destructor
    ~Editor();
    public:
    int getNowLine();
    bool showAll();
    bool showNowLine();
    bool toFirstLine();
    bool toLastLine();
    bool toBackLine();
    bool toNextLine();
    bool toLine(int linePos);
    bool insertLine(int linePos,const String &s);
    bool deleteLine(int linePos);
    bool replaceNowLine(const String &s);
    bool replaceInAllText(const String &toSub,const String &beSubed);
    bool searchInAllText(const String &s);
    int getLineNum();
    int getWordNum();
    bool read();
    bool write();
    void getFilename();
};
#endif