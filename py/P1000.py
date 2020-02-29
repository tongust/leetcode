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

    def emu(self, n, k):
        """
        """
        A0 = dict()
        for i in range(n):
            A0[(i,1)] = [[j] for j in range(0,i+1)]
        A1 = dict()
        for i in range(2, k+1):
            A1[(i-1,i)] = [list(range(0,i))]
            for j in range(i+1, n+1):
                v = j-1
                res = list()
                for a in A0[(v-1, i-1)]:
                    res.append(a+[v])
                res = res + A1[(v-1,i)]
                A1[(v,i)] = res
            A0 = A1
            A1 = dict()
        return A0
        
if __name__ == "__main__":
    so = Solution()
    A = so.mergeStones([6,4,4,6],2)
    print(A)
