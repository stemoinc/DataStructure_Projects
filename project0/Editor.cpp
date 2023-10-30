#include"Editor.h"
Editor::Editor(){
    lineNum=0;
    inputFileName=new char[100];
    outputFileName=new char[100];
}
Editor::~Editor(){
    delete inputFileName;
    delete outputFileName;
}
//Functions
int Editor::getNowLine(){
    return lineNum;
}
bool Editor::showAll(){
    if(buffer.Empty()){
        return false;
    }else{
        String temp;
        for(int i=1;i<=buffer.Length();i++){
            buffer.GetElem(i,temp);
            std::cout<<i<<":"<<temp<<std::endl;
        }
    return true;
    }
}
bool Editor::showNowLine(){
    if(buffer.Empty()){
        return false;
    }else{
        String temp;
        buffer.GetElem(lineNum,temp);
        std::cout<<"~"<<lineNum<<":"<<temp<<std::endl;
        return true;
    }

}
bool Editor::toFirstLine(){
    if(buffer.Empty()){
        return false;
    }else{
        String temp;
        lineNum=1;
        return true;
    }
}
bool Editor::toLastLine(){
    if(buffer.Empty()){
        return false;
    }else{
        String temp;
        lineNum=buffer.Length();
        return true;
    }
}
bool Editor::toBackLine(){
    if(lineNum<=1){
        return false;
    }else{
        String temp;
        lineNum=lineNum-1;
        return true;
    }
}
bool Editor::toNextLine(){
    if(lineNum==buffer.Length()||buffer.Empty()){
        return false;
    }else{
        String temp;
        lineNum=lineNum+1;
        return true;
    }
}
bool Editor::toLine(int linePos){
    if(linePos<1||linePos>buffer.Length()){
        return false;
    }else{
        String temp;
        lineNum=linePos;
        return true;
    }
}
bool Editor::insertLine(int linePos,const String &s){
    if(linePos<1||linePos>buffer.Length()+1){
        return false;
    }else{
        buffer.Insert(linePos,s);
        lineNum=linePos;
        return true;
    }
}
bool Editor::deleteLine(int linePos){
    if(linePos<1||linePos>buffer.Length()+1){
        return false;
    }else{
        String temp;
        buffer.Delete(linePos,temp);
        return true;
    }
}
bool Editor::replaceNowLine(const String &s){
    if(buffer.Empty()){
        return false;
    }else{
        String temp;
        buffer.Delete(lineNum,temp);
        buffer.Insert(lineNum,s);
        return true;
    }
}
bool Editor::replaceInAllText(const String &toSub,const String &beSubed){
    String text;
    String temp;
    int *positionOfString=new int[buffer.Length()+1];
    int nowPos=-1;
    for(int i=1;i<=buffer.Length();i++){
        buffer.GetElem(i,temp);
        text=text+temp;
        nowPos=nowPos+temp.Length();
        positionOfString[i-1]=nowPos;
    }
    positionOfString[buffer.Length()]=-1;
    int Pos=beSubed.match(text);
    if(Pos==-1){
        delete positionOfString;
        return false;
    }else{
        int i;
        for(i=0;;i++){
            int end=positionOfString[i];
            if(Pos<=end){
                break;
            }
        }
        positionOfString[i]=Pos+beSubed.Length()-1;
        int j;
        for(j=i+1;;j++){
            int end=positionOfString[j];
            if(positionOfString[i]<end){
                break;
            }
        }
        int i_copy=i;
        int newlenth=buffer.Length()+(j-i-1);
        int oldlenth=buffer.Length();
        for(int k=oldlenth;k>=i+1;k--){
            String temp;
            buffer.Delete(k,temp);
        }
        int begin;
        int end;
        for(int k=0;k<newlenth;k++){
            if(k==0){
                begin=0;
            }else{
                begin=positionOfString[k-1]+1;
            }
            end=positionOfString[k];
            if(k==i+1){
                k=j;
            }
            if(k>=i){
                if(k==i){
                    String temp;
                    temp=text.subString(begin,Pos-1)+toSub;
                    buffer.Insert(i+1,temp);
                }else{
                    String temp;
                    temp=text.subString(begin,end);
                    buffer.Insert(i_copy+2,temp);
                    i_copy++;
                }              
            }
        }
        lineNum=i+1;
        delete positionOfString;
        return true;
    }
}
bool Editor::searchInAllText(const String &s){
    String text;
    String temp;
    int *positionOfString=new int[buffer.Length()+1];
    int nowPos=-1;
    for(int i=1;i<=buffer.Length();i++){
        buffer.GetElem(i,temp);
        text=text+temp;
        nowPos=nowPos+temp.Length();
        positionOfString[i-1]=nowPos;
    }
    positionOfString[buffer.Length()]=-1;
    int Pos=s.match(text);
    if(Pos==-1){
        delete positionOfString;
        return false;
    }else{
        int i;
        for(i=0;;i++){
            int end=positionOfString[i];
            if(Pos<=end){
                break;
            }
        }
        int posOfSEnd=Pos+s.Length()-1;
        int j;
        for(j=i;;j++){
            int end=positionOfString[j];
            if(posOfSEnd<end){
                break;
            }
        }
        for(int k=0;k<buffer.Length();k++){
            buffer.GetElem(k+1,temp);
            std::cout<<temp<<std::endl;
            if(k>=i&&k<=j){
                if(i==j){
                    if(k==0){
                        for(int kk=0;kk<=positionOfString[0];kk++){
                            if(kk>=Pos&&kk<=posOfSEnd){
                                std::cout<<"^";
                            }else{
                                std::cout<<" ";
                            }
                        }
                        std::cout<<std::endl;
                    }else{
                        for(int kk=positionOfString[k-1]+1;kk<=positionOfString[k];kk++){
                            if(kk>=Pos&&kk<=posOfSEnd){
                                std::cout<<"^";
                            }else{
                                std::cout<<" ";
                            }
                        }
                        std::cout<<std::endl;
                    }
                }else{
                    if(k==i){
                        if(k==0){
                            for(int kk=0;kk<=positionOfString[0];kk++){
                                if(kk>=Pos){
                                    std::cout<<"^";
                                }else{
                                    std::cout<<" ";
                                }
                            }
                            std::cout<<std::endl;                            
                        }else{
                            for(int kk=positionOfString[k-1]+1;kk<=positionOfString[k];kk++){
                                if(kk>=Pos){
                                    std::cout<<"^";
                                }else{
                                    std::cout<<" ";
                                }
                            }
                            std::cout<<std::endl;
                        }
                    }else if(k==j){
                        for(int kk=positionOfString[k-1]+1;kk<=positionOfString[k];kk++){
                            if(kk<=posOfSEnd){
                                std::cout<<"^";
                            }else{
                                std::cout<<" ";
                            }
                        }
                        std::cout<<std::endl;
                    }else{
                        for(int kk=positionOfString[k-1]+1;kk<=positionOfString[k];kk++){
                            std::cout<<"^";
                        }
                        std::cout<<std::endl;
                    }
                }
            }
        }
        delete positionOfString;
        return true;
    }
}
int Editor::getLineNum(){
    return buffer.Length();
}
int Editor::getWordNum(){
    int WordNum=0;
    String temp;
    for(int i=1;i<=buffer.Length();i++){
        buffer.GetElem(i,temp);
        WordNum+=temp.Length();
    }
    return WordNum;
}
bool Editor::read(){
    std::ifstream inFile(inputFileName);
    if(inFile.fail()){
        return false;
    }else{
        buffer.Clear();
        String temp;
        for(int i=1;1;i++){
            if(inFile>>temp){
                //
            }else{
                break;
            }
            if(buffer.Insert(i,temp)){
                //
            }else{
                std::cout<<"insert error!"<<std::endl;
            }
        }
        lineNum=1;
        return true;
    }

}
bool Editor::write(){
    std::ofstream outFile(outputFileName);
    if(outFile.fail()){
        return false;
    }
    String temp;
    for(int i=1;i<=buffer.Length();i++){
        buffer.GetElem(i,temp);
        outFile<<temp;
        if(i!=buffer.Length()){
            outFile<<'\n';
        }
    }
    return true;
}
void Editor::getFilename(){
    char ch;
    int i=0;
    std::cout<<"Please enter the input file name:"<<std::endl;
    while((ch=std::cin.get())!='\n'){
        inputFileName[i]=ch;
        i++;
    }
    inputFileName[i]='\0';
    i=0;
    std::cout<<"Please enter the output file name:"<<std::endl;
    while((ch=std::cin.get())!='\n'){
        outputFileName[i]=ch;
        i++;
    }
    outputFileName[i]='\0';
}