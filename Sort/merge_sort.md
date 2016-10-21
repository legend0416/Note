### Merge Sort

We divide an array into a left subarray and a right subarray and recursively do this action until there is only one element in the subarray. 
Sort the two subarrarys and then merge them together.

Time Complexity: O(nlog n)  
Space Complexity: O(n)

```cpp
void merge(int*, int*, int, int, int);
void mergeSort(int*, int);

void merge(int *arr1, int *arr2, int l1, int l2, int n) {
    int i = 0, j = 0, idx = 0;
    int *res = (int*) malloc(sizeof(int) * n);
    while(i < l1 && j < l2 ) {
        res[idx++] = (arr1[i] <= arr2[j]) ? arr1[i++] : arr2[j++];
    }
    while(i < l1) {
        res[idx++] = arr1[i++];
    }
    while(j < l2) {
        res[idx++] = arr2[j++];
    }
    idx = 0;
    for(i = 0; i < l1; i++) {
        arr1[i] = res[idx++];
    }
    for(j = 0; j < l2; j++) {
        arr2[j] = res[idx++];
    }
    free(res);
}

void mergeSort(int *arr, int n) {
    int m;
    if(n > 1) {
        m = n/2;
        mergeSort(arr, m);
        mergeSort(arr + m, n-m);
        merge(arr, arr + m, m, n-m, n);
    }
}
```