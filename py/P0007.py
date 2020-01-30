import math
class Solution:
    def reverse(self, x):
        signed = False
        if x < 0:
            signed = True
            x = 0 - x
        res = str(x)[::-1]
        if signed:
            res = "-"+res
        res = int(res)
        if (res > (2**31) + 1) or (res < -2**31):
            res = 0
        return int(res)