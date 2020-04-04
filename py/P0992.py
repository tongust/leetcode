import collections
class Solution:

    def subarraysWithKDistinct(self, A, K):
        B = list()
        for a in A:
            if not B:
                B.append([a, 1])
                continue
            if B[-1][0] == a:
                B[-1][1] += 1
            else:
                B.append([a, 1])
        ret = 0
        if K == 1:
            for i in range(len(B)):
                ret += self.add(B[i][1])
            return ret
        return self.recur(B, K)
    def add(self, n):
        return int((n+1)*n/2)
    def addDict(self, d, v):
        if v in d:
            d[v] += 1
        else:
            d[v] = 1
    def delDict(self, d, v):
        if v in d:
            if d[v] == 1:
                del d[v]
            else:
                d[v] -= 1
    def recur(self, B, K):
        b = dict()
        n = len(B)
        ret = 0
        i = 0
        e0 = -1
        while i < n:
            if e0 < 0:
                e0 = i
            for j in range(e0, n):
                if len(b) == K:
                    e0 = j - 1
                    break
                else:
                    self.addDict(b, B[j][0])
                    e0 = j

            if len(b) < K:
                break
            e1 = e0
            e_c = B[e0][1]
            for j in range(e0+1, n):
                v = B[j][0]
                if v not in b:
                    e1 = j - 1
                    break
                else:
                    e_c += B[j][1]
                    e1 = j
            b_c = 0
            b0 = i
            b1 = i
            for j in range(i, n):
                v = B[j][0]
                b1 = j
                b_c += B[j][1]
                if b[v] == 1:
                    break
                else:
                    self.delDict(b, v)
            ret += b_c * e_c
            self.delDict(b, B[b1][0])
            i = b1 + 1
            e0 += 1
        return ret

class Window:
    def __init__(self):
        self.count = collections.Counter()
        self.nonzero = 0

    def add(self, x):
        self.count[x] += 1
        if self.count[x] == 1:
            self.nonzero += 1

    def remove(self, x):
        self.count[x] -= 1
        if self.count[x] == 0:
            self.nonzero -= 1

class Solution1(object):
    def subarraysWithKDistinct(self, A, K):
        window1 = Window()
        window2 = Window()
        ans = left1 = left2 = 0

        for right, x in enumerate(A):
            window1.add(x)
            window2.add(x)

            while window1.nonzero > K:
                window1.remove(A[left1])
                left1 += 1

            while window2.nonzero >= K:
                window2.remove(A[left2])
                left2 += 1

            ans += left2 - left1

        return ans

if __name__ == "__main__":
    so = Solution1()
    print(so.subarraysWithKDistinct([1,2,1,2,3,1,2,4],3))
