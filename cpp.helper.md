# Reference of c++

# Hash-set operator 
[**unordered_set**](http://www.cplusplus.com/reference/unordered_map/unordered_map)
```{cpp}
/*find*/
// define hash set
unordered_set<int> mset({1});
int val = 12;
auto resf = mset.find(val);
if (resf != mset.end()) {
    /* Not found */
} else {
    /* Found it */
}
```
