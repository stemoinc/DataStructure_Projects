#include"Editor.h"
bool testIsNum(const String& s){
    if(s.Empty()){
        return false;
    }else{
        char *str=s.getStringValue();
        int lenth=s.Length();
        for(int i=0;i<lenth;i++){
            if(str[i]>='0'&&str[i]<='9'){
                //
            }else{
                return false;
            }
        }
        return true;
    }
}
int convertStringToNum(const String&s){
    char *str=s.getStringValue();
    int lenth=s.Length();
    int num=0;
    for(int i=0;i<lenth;i++){
        int temp;
        temp=int(str[i]-'0');
        num*=10;
        num+=temp;
    }
    return num;
}
void TextEditorUserInterface(){
    Editor TextEditor;
    TextEditor.getFilename();
    //
    String help("h(help),r(read),w(write),v(view),s(to start),l(to last),b(backline),n(nextline),t(to some line),i(insert),d(delete),f(find),"
                "S(substitute:you can choose in now line or in text),g(getnum:you can choose linenum or wordnum),"
                "c:(change the filename.You can choose it is in or out),e(exit system).");
    
    std::cout<<"Welcome to our text editor!\n";
    std::cout<<"Now the buffer is empty.You can enter r to read the input file or enter h to get help.\n";
	while (1){
        if(TextEditor.showNowLine()){
            //
        }else{
            std::cout<<"~:Now the buffer is empty."<<std::endl;
        }
        char choice;
        String num;
        String temp;
        choice=std::cin.get();
        char c;
        while ((c = getchar()) !='\n');
		switch (choice){
        case 'h':
            std::cout<<help<<std::endl;
            break;
		case 'r':
            if(TextEditor.read()){
                std::cout<<"Read successfully!"<<std::endl;
            }else{
                std::cout<<"Error:can't find file. You can enter c to change the filename."<<std::endl;
            }
			break;
		case 'w':
            if(TextEditor.write()){
                std::cout<<"Write successfully!"<<std::endl;
            }else{
                std::cout<<"Error:can't find file. You can enter c to change the filename."<<std::endl;
            }
			break;
		case 'c':
            TextEditor.getFilename();
			break;
		case 'v':
            if(TextEditor.showAll()){
                //
            }else{
                std::cout<<"Error:buffer is empty!"<<std::endl;
            }
			break;
		case 's':
            if(TextEditor.toFirstLine()){
                //
            }else{
                std::cout<<"Error:no first line!"<<std::endl;
            }
			break;
		case 'l':
            if(TextEditor.toLastLine()){
                //
            }else{
                std::cout<<"Error:no last line!"<<std::endl;
            }
			break;
		case 'b':	
			if(TextEditor.toBackLine()){
                //
            }else{
                std::cout<<"Error:no back line!"<<std::endl;
            }
			break;
        case 'n':
            if(TextEditor.toNextLine()){
                //
            }else{
                std::cout<<"Error:no next line!"<<std::endl;
            }
            break;
        case 't':
            std::cout<<"Please enter the line number:"<<std::endl;
            std::cin>>num;
            if(testIsNum(num)){
                int lineNum=convertStringToNum(num);
                if(TextEditor.toLine(lineNum)){
                //
                }else{
                    std::cout<<"Error:wrong line number!"<<std::endl;
                }
            }else{
                std::cout<<"Not a line number!"<<std::endl;
            }
            break;
        case 'i':
            std::cout<<"Please enter the line number:";            
            std::cin>>num;
            if(testIsNum(num)){
                int lineNum=convertStringToNum(num);
                std::cout<<"Please enter your stirng:";
                std::cin>>temp;
                if(TextEditor.insertLine(lineNum,temp)){
                //
                }else{
                    std::cout<<"Error:wrong line number!"<<std::endl;
                }
            }else{
                std::cout<<"Not a line number!"<<std::endl;
            }
            break;
        case 'd':
            std::cout<<"Please enter the line number:"<<std::endl;
            
            std::cin>>num;
            if(testIsNum(num)){
                int lineNum=convertStringToNum(num);
                if(TextEditor.deleteLine(lineNum)){
                //
                }else{
                    std::cout<<"Error:wrong line number!"<<std::endl;
                }
            }else{
                std::cout<<"Not a line number!"<<std::endl;
            }
            break;
        case 'f':
            {
                std::cout<<"Please enter the string:"<<std::endl;
                String s;
                std::cin>>s;
                if(TextEditor.searchInAllText(s)){
                    //
                }else{
                   std::cout<<"Do not find."<<std::endl;
                }
            }
            break;
        case 'S':
            std::cout<<"Enter 1 to substitude for nowline and enter 2 to substitude for string in text:"<<std::endl;
            std::cin>>num;
            if(testIsNum(num)){
                int Num=convertStringToNum(num);
                if(Num==1){
                    std::cout<<"Please enter your string:"<<std::endl;
                    String s;
                    std::cin>>s;
                    if(TextEditor.replaceNowLine(s)){
                        //
                    }else{
                        std::cout<<"Error:buffer is empty!"<<std::endl;
                    }
                }else if(Num==2){
                    std::cout<<"Please enter the string you want to substitude:"<<std::endl;
                    String toSub;
                    std::cin>>toSub;
                    std::cout<<"Please enter the string which will be substituded:"<<std::endl;
                    String beSubed;
                    std::cin>>beSubed;
                    if(TextEditor.replaceInAllText(toSub,beSubed)){
                        //
                    }else{
                        std::cout<<"Did not find the string."<<std::endl;
                    }
                }else{
                    std::cout<<"Error:wrong number!"<<std::endl;
                }

            }else{
                std::cout<<"Not a line number!"<<std::endl;
            }
            break;
        case 'g':
            {
                String num;
                std::cout<<"Enter 1 to get the line count in the buffer and enter 2 to get total word count:";
                std::cin>>num;
                if(!testIsNum(num)){
                    std::cout<<"Not a line number!"<<std::endl;
                }else{
                    int Num=convertStringToNum(num);
                    if(Num==1){
                        std::cout<<"The current line word count is "<<TextEditor.getLineNum()<<std::endl;
                    }else if(Num==2){
                        std::cout<<"The total word count is "<<TextEditor.getWordNum()<<std::endl;
                    }else{
                        std::cout<<"Error:wrong number!"<<std::endl;
                    }
                }
            }
        break;
        case 'e':
            return;
            break;
		default:
			std::cout <<"Not a command!"<<std::endl;
		}
	} 
}
int main(){
    TextEditorUserInterface();
}