#include "SList.hh"

#define MEAN_COEFFICIENT 6 // used to set how long will be mean in QuickSort

using namespace std;

bool SList::IsEmpty() const{
    return SList::Data.empty();
}

int SList::First() const{
    return SList::Data.front();
}

int SList::Last() const{
    return SList::Data.back();
}

int SList::addLast(const int Value){
    SList::Data.push_back(Value);
    return SList::Data.back();
}

int SList::RemoveFirst(){
    int buffer = SList::Data.front();
    SList::Data.pop_front();
    return buffer;
}

int SList::RemoveLast(){
    int buffer = SList::Data.back();
    SList::Data.pop_back();
    return buffer;
}

// Add First one of S_2 as Last of this list, and Remove from S_2
void SList::AddLastRemoveFirst(SList &S_2){
    SList::addLast(S_2.RemoveFirst());
}

void SList::Display(){
    cout << "Displaying all elements: " << endl;
    // Iterating over list elements and display them
    list<int>::iterator it = Data.begin();
    while(it != Data.end()){
        cout<< *it <<" ";
        it++;

    }
    cout << endl << "Done with Displaying." << endl;
}

void SList::Merge(SList &S1, SList &S2){
    while(!S1.IsEmpty() && !S2.IsEmpty()){
        if(S1.First() <= S2.First()){
            // move the first element of S1 at the end of S}
            SList::AddLastRemoveFirst(S1);
        } else {
            // same, but with S2
            SList::AddLastRemoveFirst(S2);
        }
    }  // while

    // move the remaining elements of S1 to S
    while(!S1.IsEmpty()){
        SList::AddLastRemoveFirst(S1);
    }

    // move the remaining elements of S1 to S
    while(!S2.IsEmpty()){
        SList::AddLastRemoveFirst(S2);
    }
}   // Merge

void SList::SwapX(int &left,int &right){
    std::swap(left, right);
}

//list<int>::iterator SList::Pivot(){
int SList::Pivot(){
    list<int>::iterator it_b = Data.begin();
    list<int>::iterator mid = it_b;
    int Size = Data.size();

    for(int i = 0; i < (Size/2); i++){
        mid++;
    }
    list<int>::iterator it_e = Data.end();
    --it_e; // it_e at first points to value of Data.size()

    if(Data.size() > 3){   // Median of three
        int begX = *it_b;
        int midX = *mid;
        int finX = *it_e;
        if(begX > midX){
            SwapX(begX, midX);
        }
        if(begX > finX){
            SwapX(begX, finX);
        }
        if(midX > finX){
            SwapX(finX, midX);
        }

        if(!((begX<=midX)&&(midX<=finX))){
            cout << endl << "FALSE: " << begX <<" "<< midX <<" "<< finX << endl;
        }
        return midX;

    } else {        // Just choose beginning
        return *it_b;
    }
}   // Pivot

void SList::MergeSort(){
    int List_Size = Data.size();
    if(List_Size <= 1){
        return;
    }

    list<int>::iterator it = Data.begin();
    SList S_1, S_2;

    for(int i=0; i < List_Size/2; i++){
        S_1.addLast(*it++);
    }
    for(int i=List_Size/2; i < List_Size; i++){
        S_2.addLast(*it++);
    }
    Data.clear();
    S_1.MergeSort();
    S_2.MergeSort();
    Merge(S_1,S_2);
} // MergeSort

void SList::QuickSort(){
    if(Data.size() <= 1){
        return;
    }
    int* p;
    int xp = Pivot();
    p = &xp;

    SList L,E,G;

    while(!IsEmpty()){
        if(Last() < *p){
            L.addLast(RemoveLast());
        } else if(Last() == *p){
            E.addLast(RemoveLast());
        } else {    // Last one is Greater
            G.addLast(RemoveLast());
        }
    }

    // Recur on those lists
    L.QuickSort();
    G.QuickSort();


    while(!L.IsEmpty()){
        AddLastRemoveFirst(L);
    }
    while(!E.IsEmpty()){
        AddLastRemoveFirst(E);
    }
    while(!G.IsEmpty()){
        AddLastRemoveFirst(G);
    }
    return;
}   // QuickSort

void HeapSort(){

}
