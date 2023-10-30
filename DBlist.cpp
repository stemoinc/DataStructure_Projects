#ifndef HEADER_DBLIST
#define HEADER_DBLIST
//Node
template<class Elemtype>
struct DBlistNode{
    //variable
    Elemtype data;
    DBlistNode<Elemtype> *back;
    DBlistNode<Elemtype> *next;

    //constructor 1
    DBlistNode(){
    next=nullptr;
}

    //constructor 2
    DBlistNode(const Elemtype &e,DBlistNode<Elemtype> *linkBack=nullptr,DBlistNode<Elemtype> *linkNext=nullptr){
    this->data=e;
    this->back=linkBack;
    this->next=linkNext;
}
};

//DBlist
template<class Elemtype>
class DBlist{
    private:
    //variable
    DBlistNode<Elemtype> *head;
    mutable int curposition;//position of current elem
    mutable DBlistNode<Elemtype> *curPtr;//pointer of current elem
    int count;//the number of current elems
    //helper function:GetElemPtr
    DBlistNode<Elemtype> *GetElemPtr(int position) const{
    if(position<1){
        return head;
    }else if(position>count){
        return nullptr;
    }else{
        if(curposition<position){
            for(;curposition<position;curposition++){
                curPtr=curPtr->next;
            }
        }else{
            for(;curposition>position;curposition--){
                curPtr=curPtr->back;
            }
        }
        return curPtr;
    }
}
    public:
    //constructor 1
    DBlist(){
    head=new DBlistNode<Elemtype>();
    curposition=0;
    curPtr=head;
    count=0;
}
    //constructor 2
    DBlist(const DBlist<Elemtype> &copy){
    head=new DBlistNode<Elemtype>();
    DBlistNode<Elemtype> *NowPtr=head;
    int NowPos=1;
    while(NowPos<=copy.Length()){
        Elemtype NowData;
        DBlistNode<Elemtype> *temp=NowPtr;
        copy.GetElem(NowPos,NowData);
        NowPtr=new DBlistNode<Elemtype>(NowData,temp);
        temp->next=NowPtr;
        NowPos++;
    }
    count=NowPos-1;
    curposition=1;
    curPtr=head->next;
}
    //destructor
    ~DBlist(){
    Clear();
    delete head;
}
    //other functon
    public:
    int Length() const{
    return count;
}
    bool Empty() const{
    return count?0:1;
}
    void Clear(){
        DBlistNode<Elemtype> *NowPtr=head->next;
        while(count--){
            DBlistNode<Elemtype> *temp=NowPtr->next;
            delete NowPtr;
            NowPtr=temp;
        }
        count=0;
        this->curposition=0;
        this->curPtr=nullptr;
}

    void Traverse(void(* visit)(const Elemtype &)) const{
    DBlistNode<Elemtype> *NowPtr=head->next;
    while(NowPtr==nullptr){
        visit(NowPtr->data);
        NowPtr=NowPtr->next;
    }
}
    bool GetElem(int position, Elemtype &e) const{
    if(position<1||position>this->count){
        return false;
    }
    else{
        DBlistNode<Elemtype> * TempPtr = this->GetElemPtr(position);
        e=TempPtr->data;
        return true;
    }
}
    bool SetElem(int position,const Elemtype &e){
    if(position<1||position>this->count){
        return false;
    }
    else{
        DBlistNode<Elemtype> * TempPtr = this->GetElemPtr(position);
        TempPtr->data=e;
        return true;
    }
}
    bool Delete(int position,Elemtype &e){
     if(position<1||position>this->count){
        return false;
    }else{
    DBlistNode<Elemtype> *TempPtr=this->GetElemPtr(position);
    DBlistNode<Elemtype> *Back=TempPtr->back;
    DBlistNode<Elemtype> *Next=TempPtr->next;
    Back->next=Next;
    if(position!=count){
        Next->back=Back;
    }
    e=TempPtr->data;
    if(position==count){
        curposition=0;
        curPtr=head;
    }else{
        curposition=position;
        curPtr=TempPtr->next;
    }
    count--;
    delete TempPtr;
    return true;
    }
}
    bool Insert(int position,const Elemtype &e){
     if(position<1||position>this->count+1){//insert the elem in front of the position
        return false;
    }else{
         DBlistNode<Elemtype> *TempPtr=this->GetElemPtr(position-1);
         DBlistNode<Elemtype> *InsertOne=new DBlistNode<Elemtype>(e,TempPtr,TempPtr->next);
         if(TempPtr->next==nullptr){
            TempPtr->next=InsertOne;
         }else{
            (TempPtr->next)->back=InsertOne;
            TempPtr->next=InsertOne;
         }
         count++;
         curposition=position;
         curPtr=InsertOne;
         return true;
    }
}
    DBlist<Elemtype> &operator= (const DBlist<Elemtype> &copy){
    this->Clear();
    /*head->next=new DBlistNode<Elemtype>(((copy.head)->next)->data,head);
    DBlistNode<Elemtype> *NowPtr=head->next;
    while(){
        NowPtr->next=new DBlistNode<Elemtype>((()))
    }*/
    DBlistNode<Elemtype> *NowPtr=head;
    int NowPos=1;
    while(NowPos<=copy.Length()){
        Elemtype NowData;
        DBlistNode<Elemtype> *temp=NowPtr;
        copy.GetElem(NowPos,NowData);
        NowPtr=new DBlistNode<Elemtype>(NowData,temp);
        temp->next=NowPtr;
        NowPos++;
    }
    count=NowPos-1;
    curposition=1;
    curPtr=GetElemPtr(curposition);
    return *(this);
}
};
#endif