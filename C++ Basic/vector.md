### Vector

Vectors are sequence containers representing arrays that can change in size.

#### Constructor:
```
include <vector>

vector<int> first;
vector<int> second (4,100);
vector<int> third (second.begin(),second.end());
vector<int> fourth (third);
vector<int> v;
```
#### Interators:  
```
v.begin();
v.end();
v.rbegin();
v.rend();
```
#### Capacity:  
Returns the number of elements in the vector.
```
v.size();
```
Resizes the container so that it contains n elements.
```
v.resize(5);  // resize the vector to 5
v.resize(8,100);  // resize the vector to 8 and fill the blank with 100
v.resize(12);  // resize the vector to 8 and fill the blank with 0
```
Test whether vector is empty.
```
v.empty();
```
#### Element Access:
Access element.
````
v[0].
v.at(0).  // the difference of [] and .at() is that .at() do the boundary test.
````
Access first element and last element.
```
v.front();
v.back();
```
#### Modifiers:
Add element at the end.
```
v.push_back(5);
```
Delete last element.
```
v.pop_back();
```

