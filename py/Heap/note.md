# Heap structure in Python
The complexity of *insert* and *maintenance* of Heap is O(log(n)). The value of parent node is always greater than the ones of the children.

## Element

The element can be defined as below. Here we re-define the comparator \_\_lt\_\_.
```python
class KeyValue:
    def __init__(self, key, value, time):
        self.key = key
        self.value = value
        self.frequency = 0
        self.time = time
    def __lt__(self, other):
        if self.frequency < other.frequency:
            return True
        elif self.frequency == other.frequency:
            return self.time < other.time
        return False
```

## heapify
```python
heap = [ele1,ele2]
heapq.heapify(heap)
```
## push and pop
```python
# pop up the element which is always the latest one.
evict = heapq.heappop(heap)
# will re-heapify the heap
heapq.heappush(heap, kv)
```
