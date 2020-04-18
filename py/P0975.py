maxVal = 100001
import bisect
class Solution:
    def insertSortedIndex(self, A):
        s = [[maxVal,maxVal] for j in range(len(A))]
        a = [A[-1]]
        b = [len(A)-1]#index
        for i in range(len(A)-2, -1, -1):
            v = A[i]
            ind = bisect.bisect_left(a, v)
            if ind >= len(a):
                s[i] = [b[len(a)-1], maxVal]
            elif a[ind] == v:
                s[i] = [b[ind], b[ind]]
            elif ind == 0:
                s[i] = [maxVal, b[ind]]
            else:
                v0 = a[ind-1]
                ind0 = ind-1
                for j in range(ind-2, -1, -1):
                    if a[j] != v0:
                        break
                    ind0 = j
                s[i] = [b[ind0], b[ind]]
            a.insert(ind, v)
            b.insert(ind, i)
        return s
        
    def oddEvenJumps(self, A):
        indexSorted = self.insertSortedIndex(A)
        dp = [[0,0] for i in A]
        cnt = 0
        for i in range(0, len(A)):
            if dp[i][0] == 0:
                self.recur(A, i, dp, 0, indexSorted)
            if dp[i][0] == 1:
                cnt += 1
        return cnt
        
    def recur(self, A, start, dp, odd_even, indexSorted):
        if start == len(A)-1:
            dp[start][0] = dp[start][1] = 1
            return 1
        if dp[start][odd_even] != 0:
            return dp[start][odd_even]
        indexs = indexSorted[start]
        next_res = -1
        # odd jumper
        if odd_even == 0 and indexs[1] < maxVal:
            next_res = self.recur(A, indexs[1], dp, 1, indexSorted)
        # even jumper: to smaller
        elif odd_even == 1 and indexs[0] < maxVal:
            next_res = self.recur(A, indexs[0], dp, 0, indexSorted)
        dp[start][odd_even] = next_res
        return next_res
        

if __name__ == "__main__":
    so = Solution()
    #print(so.oddEvenJumps([2,3,1,1,4]))
    print(so.oddEvenJumps([5,1,3,4,2]))
    #so.insertSortedIndex([3,4,4,2])