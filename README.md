# **LEETCODE JUST FOR FUN**
## Data structure in Python
- [Binary Search Tree](./py/BST/note.md)

[0099](https://leetcode.com/problems/recover-binary-search-tree/), [0493](https://leetcode.com/problems/reverse-pairs/),
[0654](https://leetcode.com/problems/maximum-binary-tree/),
[0998](https://leetcode.com/problems/maximum-binary-tree-ii/)

- [Heap](./py/Heap/note.md)

- [Binary Search](./py/BinarySearch/note.md)

[0995](https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/)

- List

[0021](https://leetcode.com/problems/merge-two-sorted-lists/)
[0023](https://leetcode.com/problems/merge-k-sorted-lists/)

- DC

[0021](https://leetcode.com/problems/merge-two-sorted-lists/)
[0023](https://leetcode.com/problems/merge-k-sorted-lists/)

- [DP - 1d]

[0975](https://leetcode.com/problems/odd-even-jump/submissions/)

- [DP - 2d](./py/DP/node.md)

[0010](https://leetcode.com/problems/regular-expression-matching/)
[1000](https://leetcode.com/problems/minimum-cost-to-merge-stones/)


- [Ordered Dict](./py/Others/OrderedDict.md)

[0460](https://leetcode.com/problems/lfu-cache/)


- Deep first search

[0996](https://leetcode.com/problems/number-of-squareful-arrays/solution/)

- Classical problems

[0952](./py/BST/note.md)

- Bread first search



## Problems
|#| Title| Type | Complexity| Difficulty |Time Cost|  Performence (runtime and memory beats) |
|---|------|------|-----------|------------|---------|----------------|
|[0001](https://leetcode.com/problems/two-sum/) |[Two sum](./py/P0001.py) | Sort and scan. No hashing is used here.| O(nlogn) time and O(n) space | Easy| 1h |Runtime: faster than 32.26%. Usage:less than 66.05%.|
|[0002](https://leetcode.com/problems/add-two-numbers)|[Add Two Numbers](./py/P0002.py)|Scan and list|O(n), O(1)|Medium|0.5h|7.89%;100.00%|
|[0003](https://leetcode.com/problems/longest-substring-without-repeating-characters)|[Longest Substring Without Repeating Characters](./py/P0003.py)|Trick. Data structure: dictionary|O(n), O(2n)|Medium|1.5h|22.55%;5.10%|
|[0004](https://leetcode.com/problems/median-of-two-sorted-arrays)|[Median of two sorted arrays](./py/P0004.py)|Bisect the each array to get the smallest list whose length is fixed. For example, if the length of arrays (A, B) is same, equal to n. In the initial step, we want to get n/2 elements, which are all smaller than the rest. and we can always get the answer with complexity as O(1). The A[n/2] and B[n/2] are compared, if A[n/2] is not greater than B[n/2], then we will say A[0:n/2:] will the array that are the smallest numbers with fixed length n/2. Some of the submissions justed use the sort of pyathon, I think it is not the intention of this algorithm question.|O(log(m+n)) and space O(1)|Hard|2.5h|5.38%;100.00%|
|[0005](https://leetcode.com/problems/longest-palindromic-substring)|[Longest palindromic substring](./py/P0005.py)|This is one of classical computer algorithm problems. And the state of the art algorithm is called [Manacher's algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring). There are several alternatives. For example, **dynamic programming**. We define P(i,j)as following:$$P(i,j) = \begin{cases} \text{true,} &\quad\text{if the substring } S_i \dots S_j \text{ is a palindrome}\\ \text{false,} &\quad\text{otherwise.} \end{cases} $$Therefore, $$P(i, j) = ( P(i+1, j-1) \text{ and } S_i == S_j )$$ [see more](https://leetcode.com/articles/longest-palindromic-substring/).| $$O(n^2) \text{ and } O(1)$$| Medium| 1.5h |50.13%;100.00%|
|[0006](https://leetcode.com/problems/zigzag-conversion/)|[zigzag conversion](./py/P0006.py)|There exist the **pattern** in this problem|O(n) and O(n)|Medium|0.5h|20.56%;100.00%|
|[0007](https://leetcode.com/problems/reverse-integer/submissions/)|[reverse integer](./py/P0007.py)||O(1)|Easy|20m|51.04%;100.00%|
|[0010](./py/P0010.py)| [regular expression matching](https://leetcode.com/problems/regular-expression-matching/) | This is one of classic ***Dynamic Programming*** problems. The formula of is: $d[i][j]=argmax(cal(i-1,j),cal(i,j-1), cal(i-1,j-1))$. Here the *argmax* is not to optimization, if there exist one solution or path, the path will be added to d[i][j]. | O(n\*n), O(n\*n) | Hard | 3+h |30.40%;100.00%|
|[0011](./py/P0011.py)|[Container With Most Water](https://leetcode.com/problems/container-with-most-water/)|Sort, one by one|O(nlog(n))|Medium|1h|16.67%;5.26%|
|[0021](./py/P0021.py)|[Merge two sorted lists](https://leetcode.com/problems/merge-two-sorted-lists/)|Sort, list| O(logn), O(1)| Easy | 10m |96.01%;100.00%|
|[0023](./py/P0021.py)|[Merge k Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)|Sort, list| O(nlogn), O(1)|Easy | 10m| 36.57%;100.00%|
|[0025](./py/P0025.py)|[Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)|List|O(n\*n), O(1)| Hard| 3+h | 5.03%;100.00%|
|[0099](./py/P0099.py)|[Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/)|**BST**, **Stack**, **In Order Traversing** Firstly all the invalid nodes are collectd, whose relationship is inconsistent with the rule in BST (such the value of current node is smaller than the one of left child or the one of its predecessor). Secondly, all the invalid nodes are re-sequenced by in-order traversing. Thirdly, the first and last nodes from the sequences are the target nodes.|O(nlogn), O(n)| Hard | 3h |5.18%;100.00%|
|[0133](./py/P0133.py)|[Clone graph](https://leetcode.com/problems/clone-graph/)| **Graph** | O(n), O(n)| Medium|40m|72.21%;100.00%|
|[0218]((./py/P0218.py))|[The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)| Strategy. Binary search. [0281](./py/Others/SkylineProblems.md)| O(n) | Hard | 3d+ |93.40%;10.00%|
|[0460](./py/P0460.py)|[LFU Cache](https://leetcode.com/problems/lfu-cache/)| Least Frequently Used cache | O(1), O(n)| Hard | 2h |80.66%;100.00%|
|[0493](./py/P0099.py)|[Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)| Binary Tree, Sort | O(nlogn), O(n) | Medium | 30m |17.22%;33.33%|
|[0654](./py/P0654.py)| [Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree-ii/) | Binary Search Tree, Non-recursively: in-order traversing | O(n),O(n) | Median | 24m | 83.06%%;100.00%|
|[0863](./py/P0863.py)|[All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/)| Binary Tree. Tree walk| O(ln(n)*ln(n))| Median | 30m |26.87%;100.00%|
|[0952](./py/P0952.py)| [Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/)|Prime, BFS| O(n) | hard |1d+|100%;100%|
|[0975](./py/P0975.py)| [Odd Even Jump](https://leetcode.com/problems/odd-even-jump/submissions/) | dp and bisect | O(nlogn) | Hard | 2h47m |11.09%;14.29%|
|[0980](./py/P0980.py)| [Unique Paths III](https://leetcode.com/problems/unique-paths-iii/) | Deep first search | O(n*n?) | Hard | 1h |96.85%;7.69%|
|[0994](./py/P0994.py)|[Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)||O(n^2)|Median|1h|11.05%;16.67%|
|[0995](./py/P0995.py)| [Minimum Number of K Consecutive Bit Flips](https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/)|Binary Search| O(nlogk) | hard |3h+|5.88%;50.00%|
|[0996](./py/P0996.py)| [Number of Squareful Arrays](https://leetcode.com/problems/number-of-squareful-arrays/) | Deep first search | O(N^N) | Hard | 70m | 65.18%;100.00% |
|[0998](./py/P0998.py)| [Maximum Binary Tree II](https://leetcode.com/problems/maximum-binary-tree-ii/) | Binary Search Tree, Non-recursively: in-order traversing | O(n),O(n) | Median | 24m | 21.36%;100.00%|
|[1000](./py/P1000.py)|[Minimum Cost to Merge Stones](https://leetcode.com/problems/minimum-cost-to-merge-stones/)|Dynamic Programming. [See detail]()|O(n^3)| Hard | 3h+|15.54%;100.00%|
|[1001](./py/P1001.py)| [Grid Illumination](https://leetcode.com/problems/grid-illumination/) | dictionary | O(m,n) | Hard | 1h | 59.52%;25.00%|
