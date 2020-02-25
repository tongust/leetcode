# Ordered Dict
An OrderedDict is a dictionary subclass that remembers the order that keys were first inserted. The only difference between dict() and OrderedDict() is that:

OrderedDict preserves the order in which the keys are inserted. A regular dict doesn’t track the insertion order, and iterating it gives the values in an arbitrary order. By contrast, the order the items are inserted is remembered by OrderedDict.

## Utils
```python
import collections
d = collections.OrderedDict()
# insert
d['a'] = 1
d['b'] = 2
d['c'] = 3
for key, value in od.items(): 
    print(key, value)
```
out put:
```
('a', 1)
('b', 2)
('c', 3)
```
