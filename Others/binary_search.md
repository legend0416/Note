### Binary Search

Compare the value we seached **s** with the middle value **m** of an sorted array, if **s** = **m** then we find the value. 
If **s** < **m**, then we don't need to search the value listed after m; on the contary, if If **s** > **m**, then we don't need to search the value listed before m.
#### c++:
```cpp
#include <iostream>
#include <vector>

using namespace std;


void binarySearch(vector<int > v, int svalue){
    int l = 0, h = v.size()-1;
    while(l <= h){
        int m = (l + h) / 2;
        if(svalue == v[m]){
            cout << "find the value" << endl;
            return;
        }
        else if(svalue < v[m]){
            h = m - 1;
        }
        else{
            l = m + 1;
        }
    }
}

int main(){

    vector<int> v;
    for(int i = 1; i < 6; i++){
        v.push_back(i);
    }
    binarySearch(v,2);

    return 0;
}
```

### python:
```python
def binarySearch(a, svalue):
    l, h = 0, len(a) - 1
    while l <= h:
        m = (l + h) / 2
        if svalue == a[m]:
            print "find the value"
            return
        elif svalue < a[m]:
            h = m - 1
        else:
            l = m + 1

a = [i for i in range(5)]
binarySearch(a, 4)
```