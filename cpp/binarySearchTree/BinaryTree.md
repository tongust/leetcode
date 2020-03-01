# use the STL data struct

## set and multiset
*set* and *multiset* is implemented by ***red black tree***
```cpp
template<typename T>
int countRange(multiset<T> &mset, const T& val_lower, const T& val_upper)
{
        //for (auto it : mset) cout << it << " ";
        // [)
        if (val_lower > val_upper)return -1;
        auto lower = std::lower_bound(mset.begin(), mset.end(), val_lower);
        auto upper = std::upper_bound(mset.begin(), mset.end(), val_upper);
        return std::distance(lower, upper);
        // return std::distance(upper, lower); // WRONG!
}
int main()
{
        multiset<int> mset = {2,4,1,7,3,9,3,1,11};
        for (auto it : mset)
                cout << it << " ";
        cout << countRange(mset, 3, 7) << endl;
```
>1 1 2 3 3 4 7 9 11
>4  


