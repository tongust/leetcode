import math
class Solution:
    def numSquarefulPerms(self, A):
        if (len(A) < 2):
            return len(A)
        return self.recur(A)

    def isSquareful(self, a, b):
        c = int(a+b)
        d = int(math.sqrt(c))
        d = d**2
        return c == d

    def recur(self, A):
        C = dict()
        for a in A:
            if a in C:
                C[a] += 1
            else:
                C[a] = 1
        B = dict()
        for i in range(len(A)):
            a = A[i]
            for j in range(i+1, len(A)):
                b = A[j]
                if self.isSquareful(a, b):
                    if a in B:
                        B[a].add(b)
                    else:
                        B[a] = set([b])
                    if b in B:
                        B[b].add(a)
                    else:
                        B[b] = set([a])
        ret = 0
        if not B:
            return 0
        for a in C:
            C[a] -= 1
            res = self._recur(a, B, C, len(A)-1)
            C[a] += 1
            ret += len(res)
        return ret

    def _recur(self, val, B, C, n):
        if n == 0:
            return list([[val]])
        if val not in B:
            return []
        cands = B[val]
        res = list()


        for can in cands:
            if C[can] > 0:
                C[can] -= 1
                res_list = self._recur(can, B, C, n-1)
                for r in res_list:
                    res.append([val]+r)
                # recover
                C[can] += 1
        return res

if __name__ == "__main__":
    so = Solution()
    print(so.numSquarefulPerms([3,1,2]))
