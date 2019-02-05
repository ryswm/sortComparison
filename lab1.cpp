#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

void printList(int arr[], int size);
void selectionSort(int test[], int size);
void mergeSort(int test[], int start, int end);
void mergeHelper(int test[], int start, int middle, int end);
//void mixedSort(int test[], int size);

int main(){
    const int LIMIT = 6; //Test size
    int arraySizes[6] = {6, 60, 240, 500, 10000, 36000};

    for(int i = 0; i < LIMIT; i++){                         // Loop over test 6 times; 6*3tests = 18 results printed
        srand(time(NULL)+i);                                // Reset rand()

        int caseSize = arraySizes[i];                    //setting size of array to value in range 6 - 10. = to n in assignment
        int *testCaseS = NULL, *testCaseM = NULL, *testCaseX = NULL;                //creating arrays of size caseSize = n
        testCaseS = new int[caseSize];
        testCaseM = new int[caseSize];
        testCaseX = new int[caseSize];

        for(int j = 0; j<caseSize; j++){                    // Setting array values to values in range 1 - 4n
            int x = rand() % (4*caseSize) + 1;
            testCaseS[j] = x;       
            testCaseM[j] = x;
            testCaseX[j] = x;
        }        
         
        /****** Start Sorting ******/
        printList(testCaseM, caseSize);


        auto startS = chrono::high_resolution_clock::now();  // start time for test
        selectionSort(testCaseS, caseSize);                 // Impliment selection sort
        auto endS = chrono::high_resolution_clock::now();  // Time node; end of selection sort
        chrono::duration<double> elapsed = endS - startS; 
        //printList(testCaseS, caseSize);  
        cout<<"Time to selection sort = "<<elapsed.count()<<endl;

        
        auto startM = chrono::high_resolution_clock::now();
        mergeSort(testCaseM, 0, caseSize-1);
        auto endM = chrono::high_resolution_clock::now();
        elapsed = endM - startM;
        printList(testCaseM, caseSize);
        cout<<"Time to merge sort = "<<elapsed.count()<<endl;

        
        auto startX = chrono::high_resolution_clock::now();
        //mixedSort();
        auto endX = chrono::high_resolution_clock::now();
        elapsed = endX - startX;
        cout<<"Time to merge/selection sort = "<<elapsed.count()<<endl;

        
        /****** End Sorting ******/

        cout<<endl;
        delete [] testCaseS;
        delete [] testCaseM;
        delete [] testCaseX;
        testCaseS = NULL;
        testCaseM = NULL;
        testCaseX = NULL;
    }

    return 0;
}





void printList(int arr[], int size){
    cout<<"Array: [";
    for(int i = 0; i < size; i++){
        if(i+1 < size){ 
            cout<<arr[i]<<", ";
        } else {
            cout<<arr[i];
        }
    }
    cout<<"]"<<endl;
}

                                    /********* Sorting Algorithms *********/

void selectionSort(int test[], int size){
    int minimum;

    for(int i = 0; i < size - 1; i++){          //Changing next minimum value;
        minimum = i;
        for(int j = i + 1; j < size; j++){      // Checking every unsorted value
            if(test[j] < test[minimum]){        // If a value is smaller, swap with minimum
                minimum = j;
            }
        }
        int temp = test[i];
        test[i] = test[minimum];
        test[minimum] = temp;
    }
}

void mergeSort(int test[], int start, int end){
    if(start < end){
        int middle = (end + start)/2;
        mergeSort(test, start, middle);
        mergeSort(test, middle+1, end);
        mergeHelper(test, start, middle, end);
    }
}

void mergeHelper(int test[], int start, int middle, int end){
    int x = start;
    int y = middle + 1;
    int z = 0;
    int *temp = NULL;
    temp = new int[end-start+1];

    for(int i = start ;i <= end ;i++) {
        if(x > middle) {                        //checks if first part comes to an end or not .
            temp[ z++ ] = test[ y++] ;
        } else if ( y > end) {               //checks if second part comes to an end or not
            temp[ z++ ] = test[ x++ ];
        } else if( test[ x ] < test[ y ]) {       //checks which part has smaller element.
            temp[ z++ ] = test[ x++ ];
        } else {
            temp[ z++ ] = test[ y++];
        }
    }

    for (int x = 0; x < z; x ++) {                   // Sorting actual array
        test[ start++ ] = temp[ x ] ;                          
    }

    delete [] temp;         // Cleaning up
    temp = NULL;
}

