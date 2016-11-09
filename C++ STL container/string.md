### String

Strings are objects that represent sequences of characters.

#### Constructor:
```cpp
include <string>

string s("She believed she could.");
string s1;
string s2(s);
string s3(s, 4, 8);    // s0[4] = 'b', s3 = "believed"
string s4("Another character sequence", 12);    // s4 = "Another char"
string s5(s.begin(), s.begin()+7);
```
#### Interators:  
```cpp
s.begin();
s.end();
s.rbegin();
s.rend();
```
#### Capacity:
Returns length of string.
```
s.size();
s.length();
```
Clear string.
```
s.clear();
```
Test if string is empty.
```
s.empty();
```
####Modifier:
Append to string.
```
operator +=
```
```
string str;
string str2 = "XOXO";
str.append(str2);
```