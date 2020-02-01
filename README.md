# **LEETCODE JUST FOR FUN**
## Data structure in Python
- [Binary Search Tree](./py/BST/note.md)
[0099](https://leetcode.com/problems/recover-binary-search-tree/), [0493](https://leetcode.com/problems/reverse-pairs/)


## Problems
|#| Title| Type | Complexity| Difficulty |Time Cost|  Performence  |
|---|------|------|-----------|------------|---------|----------------|
|[0001](https://leetcode.com/problems/two-sum/) |[Two sum](./py/P0001.py) | Sort and scan. No hashing is used here.| O(nlogn) time and O(n) space | Easy| 1h |  Runtime: faster than 32.26%. Usage:less than 66.05%.|
|[0002](https://leetcode.com/problems/add-two-numbers)|[Add Two Numbers](./py/P0002.py)|Scan and list|O(n), O(1)|Medium|0.5h|Runtime: 108 ms, faster than 7.89%. Memory Usage: 12.7 MB, less than 100.00%|
|[0003](https://leetcode.com/problems/longest-substring-without-repeating-characters)|[Longest Substring Without Repeating Characters](./py/P0003.py)|Trick. Data structure: dictionary|O(n), O(2n)|Medium|1.5h|Runtime: 140 ms, faster than 22.55%; Memory Usage: 17.2 MB, less than 5.10%|
|[0004](https://leetcode.com/problems/median-of-two-sorted-arrays)|[Median of two sorted arrays](./py/P0004.py)|Bisect the each array to get the smallest list whose length is fixed. For example, if the length of arrays (A, B) is same, equal to n. In the initial step, we want to get n/2 elements, which are all smaller than the rest. and we can always get the answer with complexity as O(1). The A[n/2] and B[n/2] are compared, if A[n/2] is not greater than B[n/2], then we will say A[0:n/2:] will the array that are the smallest numbers with fixed length n/2. Some of the submissions justed use the sort of pyathon, I think it is not the intention of this algorithm question.|O(log(m+n)) and space O(1)|Hard|2.5h|Runtime: faster than 5.38%. Memory Usage: less than 100.00%|
|[0005](https://leetcode.com/problems/longest-palindromic-substring)|[Longest palindromic substring](./py/P0005.py)|This is one of classical computer algorithm problems. And the state of the art algorithm is called [Manacher's algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring). There are several alternatives. For example, **dynamic programming**. We define P(i,j)as following:$$P(i,j) = \begin{cases} \text{true,} &\quad\text{if the substring } S_i \dots S_j \text{ is a palindrome}\\ \text{false,} &\quad\text{otherwise.} \end{cases} $$Therefore, $$P(i, j) = ( P(i+1, j-1) \text{ and } S_i == S_j )$$ [see more](https://leetcode.com/articles/longest-palindromic-substring/).| $$O(n^2) \text{ and } O(1)$$| Medium| 1.5h |Runtime: 1536 ms, faster than 50.13%; Memory Usage: 12.8 MB, less than 100.00%|
|[0006](https://leetcode.com/problems/zigzag-conversion/)|[zigzag conversion](./py/P0006.py)|There exist the **pattern** in this problem|O(n) and O(n)|Medium|0.5h|faster than 20.56%; less than 100.00%|
|[0007](https://leetcode.com/problems/reverse-integer/submissions/)|[reverse integer](./py/P0007.py)||O(1)|Easy|20m| faster than 51.04%;less than 100.00%|
|[0133](./py/P0133.py)|[Clone graph](https://leetcode.com/problems/clone-graph/)| **Graph** | O(n), O(n)| Medium|40m|faster than 72.21%; less than 100.00%|
|[0099](./py/P0099.py)|[Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/)|**BST**, **Stack**, **In Order Traversing** Firstly all the invalid nodes are collectd, whose relationship is inconsistent with the rule in BST (such the value of current node is smaller than the one of left child or the one of its predecessor). Secondly, all the invalid nodes are re-sequenced by in-order traversing. Thirdly, the first and last nodes from the sequences are the target nodes.|O(nlogn), O(n)| Hard | 3h | faster than 5.18%; less than 100.00%|
|[0493](./py/P0099.py)|[Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)| Binary Tree, Sort | O(nlogn), O(n) | Medium | 30m |faster than 17.22%;less than 33.33%|
|0???|
