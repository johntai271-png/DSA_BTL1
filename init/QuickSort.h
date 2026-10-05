#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "ISort.h"
#include <stdexcept>
using namespace std;

template<class T>
class QuickSort : public ISort<T> {
private:
    int (*pivotSelection)(T*, int);
    void swap(T&a,T&b){
        T temp=a;
        a=b;
        b=temp;
    }

public:
    QuickSort(int (*pivotSelection)(T*, int) = 0)
        : pivotSelection(pivotSelection) {}

    void sort(T array[], int size, int (*comparator)(T&, T&) = 0) override {
        // TODO Q4
        if(size<=1) return;
        if(comparator==0){
            comparator=SortSimpleOrder<T>::compare4Ascending;
        }
        quickSort(array,0,size-1,comparator);
    }

private:
    void quickSort(T array[], int left, int right,
                   int (*comparator)(T&, T&) = 0) {
        // TODO Q4
        if(left>=right) return;
        int q=partition(array,left,right,comparator);
        quickSort(array,0,q-1,comparator);
        quickSort(array,q+1,right,comparator);
    }

    int partition(T array[], int left, int right,
                  int (*comparator)(T&, T&) = 0) {
        // TODO Q4
        int pivotIndex=right;
        if(pivotSelection!=0){
            pivotIndex=left+ pivotSelection(array+left,right-left+1);      
        }
      swap(array[pivotIndex],array[right]);
      T pivot=array[right];
      int j=left;
      for(int i=left;i<right;i++){
            if(comparator(array[i],pivot)<0){
                swap(array[i],array[j]);
                j++;
            }
        }
        swap(array[right],array[j]);
        return j;  
    }
};

#endif
