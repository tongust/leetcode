from math import log
import math
class Solution:
    def leastOpsExpressTarget(self, x, target):
        ts = {target:0}
        while True:
            ts1 = dict()
            for t in ts:
                base, rest0, rest1 = self.decom(t, x)
                if rest0 == 0:
                    if base == 0:
                        return ts[t] + 1
                    else:
                        return ts[t] + base - 1
                base0 = base
                if base0 == 0:
                    base0 = 2
                count0 = ts[t] + base0
                # +
                if rest0 in ts1:
                    if ts1[rest0] > count0:
                        ts1[rest0] = count0
                else:
                    ts1[rest0] = count0
                # -
                base1 = base + 1
                count1 = ts[t] + base1
                if rest1 in ts1:
                    if ts1[rest1] > count1:
                        ts1[rest1] = count1
                else:
                    ts1[rest1] = count1
            ts = ts1

    def decom(self, value, x):
        a = int(log(value, x))
        b = x**a
        return (a, value - b, b*x - value)
        
if __name__ == "__main__":

    so = Solution()
    dp = {1:{}, 2:{}, 0:{}}
    #so.isExpressTarget(3, 1, 1, dp)
    print(so.leastOpsExpressTarget(3, 365))
    print(so.leastOpsExpressTarget(3, 19))
    print(so.leastOpsExpressTarget(2, 125046))
    print(so.leastOpsExpressTarget(100, 100000000))