#ifndef SLIST_HH
#define SLIST_HH

#include <iostream>
#include <list>
#include <iterator> // list iterator
#include <algorithm> // for std::find inPlaceQS

using namespace std;

class SList {
public:
    SList(){};
    SList(const SList &);
    ~SList(){Data.clear();};
    bool IsEmpty() const;
    int First() const;
    int Last() const;
    int addLast(const int Value);
    int RemoveFirst();
    int RemoveLast();
    // Add First one of S_2 as Last of S_1, and Remove from S_1
    void AddLastRemoveFirst(SList &S_2);
    void Display();

    void MergeSort();
    void HeapSort();
    void QuickSort();
    void Swap(list<int>::iterator left,list<int>::iterator right);
    void SwapX(int &left,int &right);

//    list<int>::iterator Pivot();
    int Pivot();

    void Merge(SList &S1, SList &S2);

private:
    list<int> Data;
};

#endif // SLIST_HH
