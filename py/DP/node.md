Here, we take leetcode problem [Minimum Cost to Merge Stones](https://leetcode.com/problems/minimum-cost-to-merge-stones/) for an example.
```
There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.

A move consists of merging exactly K consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these K piles.

Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1.
```
Below is my solution:
```python
class Solution:
    def __init__(self):
        self._max = 2**32

    def mergeStones(self, stones, K):
        if (len(stones) - 1) % (K-1) != 0 or K < 1 or not stones:
            return -1
        if K == len(stones):
            return sum(stones)
        if K > len(stones):
            return 0
        N = len(stones)
        A = dict()
        for i in range(len(stones)):
            A[(i,i)] = 0

        E = self.enum1(N,K)
        return self.dp(stones, A, 0, N-1, K, E)
    
    def isSplitable(self, N, K):
        return (N-1) % (K-1) == 0

    def dp(self, stones, A, start, end, K, E):
        if (start, end) in A:
            return A[(start, end)]
        n = end - start + 1
        cost = sum(stones[start:end+1])
        if n == K:
            A[(start, end)] = cost
            return A[(start, end)]
        if not self.isSplitable(n, K):
            return -1
        
        min_cost = self._max
        for e in E[n]:
            s0 = start
            s1 = start - 1
            cost = 0
            for j in range(len(e)):
                s0 = s1 + 1
                s1 = s0 + e[j] - 1
                tmp = self.dp(stones, A, s0, s1, K, E)
                cost += tmp
            if cost < min_cost:
                min_cost = cost
        cost0 = sum(stones[start:end+1])
        A[(start, end)] = min_cost + cost0
        return min_cost + cost0

    def enum1(self, n, k):
        if not self.isSplitable(n, k):
            return E
        if n == k:
            E[n] = [1]*k
        iter_count = int((n-k) / (k-1))
        E = dict()
        E[k] = [[1]*k]
        for i in range(iter_count):
            v = k + (k-1) * (1+i)
            E[v] = list()
            for e in E[v-k+1]:
                g = self.genEnu(e, k-1)
                E[v] += g
            E[v] = self.dedup(E[v])
        return E

    def dedup(self, g):
        f = set([tuple(i) for i in g])
        g = [list(i) for i in f]
        return g

    def genEnu(self, e, k):
        index = next((ind for ind,val in enumerate(e) if val > 1), 0)
        res = []
        for i in range(index, len(e)):
            e0 = e.copy()
            e0[i] += k
            res.append(e0)
        
        return res
```
The formula of this dp is:

$dp(i,j) = argmin(dp(i, m_1)+dp(m_1+1,m_2)+dp(m_2+1, m_3)+...+dp(m_{k-1}+1, m_k)+...+dp(m_K, j))$

Where $\{m_1,m_2,...m_k,...m_K\}$ is listed exhaustively, and it is to split the (j-i+1) elements to $K$ parts. And at last the $K$ parts can be merged successfully. So how to split the large pile ({i,...,j}) to meet the requirements that its children parts ($\{m_{k-1}, m_k\}$) also can be concatenated into one pile?

The py function $enum1$ is to enumerate the solutions. For example, if $K=3, N = 7$, we can find the spliting-solutions exhaustively as below:

```
n = 3
1,1,1
_______________
n = 3 + 2
1+2 ,1,  1
1   ,1+2,1
1   ,1  ,1+2
_______________
n = 3 + 2 + 2
Here it is depended on n = 3+2
----------
3,  1,  1
----------
3+2, 1,   1
3,   1+2, 1 
3,   1,   1+2

----------
1,  3,  1
----------
1,   3+2, 1 
1,   3,   1+2

----------
1,  1,  3
----------
1,   1,   3+2
```
So we get the matrix $M$:

```
M[3,3] = [[1,1,1]]
M[5,3] = [[3,1,1],[1,3,1],[1,1,3]]
M[7,3] = [
          [5,1,1],[3,3,1],[3,1,3],
          [1,5,1],[1,3,3],
          [1,1,5]
         ]
```