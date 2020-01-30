class Solution:
    def convert(self, s, numRows):
        if numRows < 2 or numRows == len(s):
            return s
        period = numRows*2 - 2
        mod = len(s) % period

        res = list()
        for i in range(numRows):
            if i == 0 or i == numRows - 1:
                res = res + list(s[i::period])
            else:
                s0 = s[i::period]
                s1 = s[i+(period - 2*i)::period]
                j = 0
                while j < len(s0) and j < len(s1):
                    res += [s0[j], s1[j]]
                    j += 1
                if j < len(s0):
                    res.append(s0[j])
                if j < len(s1):
                    res.append(s1[j])
        
        return ''.join(res)