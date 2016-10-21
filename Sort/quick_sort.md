### Quick Sort

We select an element as the pivot first, shift the elements smaller than the pivot to the left and the elements greater than the pivot to the right. Then we treat the left side of the array and the right side of the array as two arrays. Do the same job described above to arrays recursively until one or no element remained in the array.

Complexity: O(nlog n)

####In-place version

We set the first element as pivot and have two poiter **i** and **j**. Let **i** and **j** start from the left, **j** starts off first. If **j** meets an element smaller than the pivot, then **j** swaps it with the element pointed by **i** and **i** moves forward. After this action, the elements behind **i** will >= the pivot.


```cpp
void qsort(int a[], int l, int h) {
    if(l < h) {
        int m = partition(a, l, h);
        qsort(a, l, m);
        qsort(a, m + 1, h);
    }
}

int partition(int *a, int l, int h) {
    int pivot = a[h - 1];
    int i = l, j;
    for(j = l; j < h - 1; j++) {
        if(a[j] <= pivot) {
            int tmp = a[i];
            a[i++] = a[j];
            a[j] = tmp;
        }
    }
    int tmp = a[i];
    a[i] = a[h - 1];
    a[h - 1] = tmp;
    return i;
}
```