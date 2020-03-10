# Binary Search
 binary search, also known as half-interval search, is a search algorithm that finds the position of a target value within a sorted array.

 Given a array of sections whose length is equal to K, and they are sorted by the begining value. For any value V, how to count the number of sections where the value can lies.

  For example, A = {[2,12], [3,13], [5,15], [7,19]}, V = 5, and the answer is 3, those sections satisfy the requirements: [2,12],[3,13],[5,15].

  This problem can be solved using **binary search**.

  ```python
      def count(self, begs, ends, v):
        if not begs:
            return 0
        e_i = self._flipCount0(ends, v, 0, len(ends))
        if e_i < len(ends):
            b_i = self._flipCount1(begs, v, e_i, len(ends))
            diff = b_i - e_i + 1
            return diff
        return 0
      def _flipCount0(self, ends, v, s, e):
        mid = int((s+e)/2)
        if mid == s:
            if v <= ends[mid]:
                return mid
            else:
                return mid+1
        if ends[mid] == v:
            return mid
        elif v < ends[mid]:
            return self._flipCount0(ends, v, s, mid)
        else:
            return self._flipCount0(ends, v, mid, e)
    
    def _flipCount1(self, ends, v, s, e):
        mid = int((s+e)/2)
        if mid == s:
            if v >= ends[mid]:
                return mid
            else:
                return mid-1
        if ends[mid] == v:
            return mid
        elif v < ends[mid]:
            return self._flipCount1(ends, v, s, mid)
        else:
            return self._flipCount1(ends, v, mid, e)
  ```