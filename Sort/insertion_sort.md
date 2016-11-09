### Insertion Sort

The elements before the pointer __i__ are already sorted. What we do is to insert the element pointed by __i__ in the sorted array iteratively. To achieve this the insertion step, we do the comparison and replacement in the sorted array from right to left until we meet an element smaller than the element pointed by  __i__.

Complexity: O(n^2)  

```cpp
void insertionSort(int a[], int n){
    int tmp = 0, i, j;
    for(i = 0; i < n; i++) {
        tmp = a[i];
        for(j = i; j > 0 && a[j-1] > tmp; j--) {
                a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

```