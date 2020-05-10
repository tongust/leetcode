class Solution:
    def maxArea(self, height):
        n = len(height)
        left = 0
        right = n - 1
        id = sorted(range(len(height)), key=lambda k: height[k])
        res = 0
        k = 0
        while k < n-1:
            i = id[k]
            h = height[i]
            while h > height[left]:
                left += 1
            while h > height[right]:
                right -= 1
            res0 = h * (right - left)
            if res0 > res:
                res =res0
            k += 1
        return res

        
if __name__ == "__main__":
    so = Solution()
    print(so.maxArea([1,8,6,2,5,4,8,3,7]))