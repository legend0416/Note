### Bubble Sort

5 1 4 2 8 -> 1 5 4 2 8  
1 5 4 2 8 -> 1 4 5 2 8  
1 4 5 2 8 -> 1 4 2 5 8 

There are two pointers **i** & **j**. Pointer **i** seperates the sorted area from the unsorted area.
Pointer **j** successively swaps two adjacent elements and push the biggest (or smallest) element into the sorted area.

Complexity: O(n^2)
```cpp
void bubbleSort1(int a[],int n){
    for(int i = n-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}
```
```cpp
include <algotithm >

void bubbleSort3(int a[],int n){
    for(int i = n-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(a[j] > a[j+1]){
                swap(a[j], a[j+1]);
            }
        }
    }
}
```