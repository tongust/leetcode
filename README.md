# **LEETCODE JUST FOR FUN**
|---| Title| Type | Complexity| Difficulty |Time Cost|  Performence  |
|---|------|------|-----------|------------|---------|----------------|
|[0001](https://leetcode.com/problems/two-sum/) |[Two sum](./py/P001.py) | Sort and scan. No hashing is used here.| O(nlogn) time and O(n) space | Easy| 1h |  Runtime: faster than 32.26%. Usage:less than 66.05%.|
|0002|||||||
|0003|||||||
|[0004](https://leetcode.com/problems/median-of-two-sorted-arrays)|[Median of two sorted arrays](./py/P0004.py)|Bisect the each array to get the smallest list whose length is fixed. For example, if the length of arrays (A, B) is same, equal to n. In the initial step, we want to get n/2 elements, which are all smaller than the rest. and we can always get the answer with complexity as O(1). The A[n/2] and B[n/2] are compared, if A[n/2] is not greater than B[n/2], then we will say A[0:n/2:] will the array that are the smallest numbers with fixed length n/2. Some of the submissions justed use the sort of pyathon, I think it is not the intention of this algorithm question.|O(log(m+n)) and space O(1)|Hard|2.5h|Runtime: faster than 5.38%. Memory Usage: less than 100.00%|