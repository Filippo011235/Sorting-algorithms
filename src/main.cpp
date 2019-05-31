#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>  // for rand
#include <cmath>     // pow()
#include <ctime>    // for time
#include "SList.hh"

#define NoOfADT 10

using namespace std;

void ShellSort(std::vector<int> &Array);
void Sort(const int Size, const double AlreadySorted, bool TrialDisplay);
void Display(vector<int> &v){
    cout << "Displaying all elements: " << endl;
    for(int n : v) {
        cout << n << " ";
    }
    cout << endl << "Done with Displaying." << endl;
}

int main(){

srand(time(NULL));  // sets starting point for randomization

// Trial run
cout << "Example sorting for 10 elem. and 50 % of ADT already sorted: " << endl << endl;
Sort(10, 50, true);
cout << "----------------------------------" << endl << endl;

int NoS = 5;    // Number of Sizes values
int NoAS = 2;   // Number of AlreadySorted

int Size[NoS] = {10000, 50000, 100000, 500000, 1000000};
double AlreadySorted[NoAS] = {0,25,50,75,95,99,99.7};

cout << "Actual tests: " << endl << endl;

for(int n = 0; n < NoAS; n++){  // for all pre sorted values
    cout << "---------------" << AlreadySorted[n] << "%-----------------" << endl;
    for(int i = 0; i < NoS; i++){     // for different Sizes
        Sort(Size[i], AlreadySorted[n], false);
    }
}

return 0;
}


void ShellSort(std::vector<int> &Array){
    int Interval = 1;   // Interval has to be at least 1
    int TempValue, Inner, Outer;
    int Size = Array.size();

   // Initial Interval based on Knuth's formula
   while(Interval < Size/3){
      Interval = Interval*3 + 1;
    }

   while(Interval > 0){
    // Do Insertion sort on given Interval until entire Array is sorted
      for(Outer = Interval; Outer < Size; Outer++){
          TempValue = Array[Outer]; // Store temporary TempValue
        // shift elements until correct location is found
        Inner = Outer;
         while(Inner>Interval-1 && Array[Inner-Interval]>=TempValue){
            Array[Inner] = Array[Inner-Interval];
            Inner -= Interval;
         }
          // put back TempValue at correct location
          Array[Inner] = TempValue;
      } // for
   // reduce the Interval
   Interval = (Interval-1)/3;
   }    // while
}   // ShellSort

// AlreadySorted -> How many elements have been sorted before time test. -1 is inverted.
void Sort(const int Size, const double AlreadySorted, bool TrialDisplay){
    SList MLists[NoOfADT], QLists[NoOfADT]; // Merge and Quick
    std::vector<int> SArrays[NoOfADT];   // for ShellSort
    int Range = Size + 1;
    double PartOfADT = (double)Size*(AlreadySorted/100);
    double StorageOfTimes[3][NoOfADT];
    double AverageTime[3];
    double sum[3] = {};    // for AverageTime
    double SumInDevation[3] = {};
    double Deviation[3]; // Standard Devation
    clock_t Start, Finish;

    for(int i = 0; i < NoOfADT; i++){
        if(AlreadySorted > 0){
            for(int j = 0; j < PartOfADT; j++){
                int Value = rand() % Range;
                MLists[i].addLast(Value);
                QLists[i].addLast(Value);
                SArrays[i].push_back(Value);
            }

            // Initially sort AlreadySorted part of the ADT
            MLists[i].MergeSort();
            QLists[i].QuickSort();
            ShellSort(SArrays[i]);
            // Add (unsorted)rest of the ADT

            for(int j = PartOfADT; j < Size; j++){
                int Value = rand() % Range;
                MLists[i].addLast(Value);
                QLists[i].addLast(Value);
                SArrays[i].push_back(Value);
            }

        } else if(AlreadySorted == 0){
            for(int j = 0; j < Size; j++){
                int Value = rand() % Range;
                MLists[i].addLast(Value);
                QLists[i].addLast(Value);
                SArrays[i].push_back(Value);
            }
        }  else if(AlreadySorted == -1){
            cout << "Invert";
        } // else if

        // Display unsorted ADTs
        if(TrialDisplay == true && i == 1){
            cout << "Before(Respectively Merge, Quick, Shell): " << endl;
            MLists[1].Display();
            QLists[1].Display();
            Display(SArrays[1]);
        }

        // Sort and save time of operation

        // MERGE
        Start = clock();
        MLists[i].MergeSort();
        Finish = clock();
        StorageOfTimes[0][i] = (Finish - Start)/(double)CLOCKS_PER_SEC;
        sum[0] += StorageOfTimes[0][i];

        // QUICK
        Start = clock();
        QLists[i].QuickSort();
        Finish = clock();
        StorageOfTimes[1][i] = (Finish - Start)/(double)CLOCKS_PER_SEC;
        sum[1] += StorageOfTimes[1][i];

        // SHELL
        Start = clock();
        ShellSort(SArrays[i]);
        Finish = clock();
        StorageOfTimes[2][i] = (Finish - Start)/(double)CLOCKS_PER_SEC;
        sum[2] += StorageOfTimes[2][i];

    }   // for

    // AverageTimes
    for(int n = 0; n < 3; n++){
        AverageTime[n] = sum[n]/NoOfADT;
    }
    // Standard Deviation
    for(int i = 0; i < NoOfADT; i++){
        for(int n = 0; n < 3; n++){
            SumInDevation[n] += pow((StorageOfTimes[n][i] - AverageTime[n]), 2);
            Deviation[n] = sqrt(SumInDevation[n]/NoOfADT);
        }
    }

    // Display sorted ADTs
    if(TrialDisplay == true){
        cout << endl << "After(M,Q,S) : " << endl;
        MLists[1].Display();
        QLists[1].Display();
        Display(SArrays[1]);
    }

    cout << endl << "Average Time of sorts for " << Size << " and " << AlreadySorted << " %"<< endl;
    cout << "M, Q, S: " << endl;
    cout << "AverageTimes: " << endl;
    for(int n = 0; n < 3; n++){
        cout << AverageTime[n] << endl;
    }
    cout << "Deviations: " << endl;
    for(int n = 0; n < 3; n++){
        cout << Deviation[n] << endl;
    }
}   // Sort function
