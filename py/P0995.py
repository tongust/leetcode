class Solution:
    def minKBitFlips(self, A, K):
        if K == len(A):
            if sum(A) == K:
                return 0
            elif sum(A) == 0:
                return 1
            else:
                return -1

        n = len(A)
        ret = 0
        ends = list()
        begs = list()
        for i in range(0, n-K+1):
            if not ends:
                if A[i] != 1:
                    begs.append(i)
                    ends.append(i+K-1)
                    ret += 1
                continue
            fc = self.flipCount(begs, ends, i)
            if (fc == 0 and A[i] == 0) or (fc == 1 and A[i] == 1):
                begs.append(i)
                ends.append(i+K-1)
                ret += 1
        for i in range(n-K+1, n):
            fc = self.flipCount(begs, ends, i)
            if fc == A[i]:
                return -1
        return ret

    def flipCount(self, begs, ends, v):
        if not begs:
            return 0
        e_i = self._flipCount0(ends, v, 0, len(ends))
        if e_i < len(ends):
            b_i = self._flipCount1(begs, v, e_i, len(ends))
            diff = b_i - e_i + 1
            return diff % 2
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
    
    

if __name__ == "__main__":
    so = Solution()
    so.minKBitFlips([1,1,0],2)