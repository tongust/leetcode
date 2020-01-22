import math
class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        m = len(nums1)
        n = len(nums2)
        if (n == 0 or m == 0):
            nums3 = nums1 + nums2
            if (m+n) % 2 == 0:
                return float(nums3[int((m+n)/2)] + nums3[int((m+n)/2) - 1] ) / 2.0
            else:
                return float(nums3[int((m+n)/2)])
        mid = [0,0]
        p0 = 0
        p1 = 0
        if (m+n)%2 == 0:
            # even
            half = int((m+n)/2)
            while True:
                can_len = int(half/2)
                e0 = p0 + can_len
                e1 = p1 + can_len

                if e0 > m:
                    e0 = m
                if e1 > n:
                    e1 = n

                if nums1[int((p0+e0)/2)] <= nums2[int((p1+e1)/2)]:
                    delta = int(((p0+e0)/2) + 1 - p0)
                    p0 = int(((p0+e0)/2) + 1)
                    half = int(half - delta)
                else:
                    delta = int(((p1+e1)/2) + 1 - p1)
                    p1 = int(((p1+e1)/2) + 1)
                    half = int(half - delta)
                
                # check
                if p0 >= m:
                    if half == 0 and m > 0:
                        if p1 == 0:
                            mid[0] = nums1[-1]
                        else:
                            mid[0] = max(nums1[-1], nums2[int(p1 - 1)])
                    else:
                        mid[0] = nums2[int(p1 + half - 1)]
                    mid[1] = nums2[int(p1 + half)]
                    break
                elif p1 >= n:
                    if half == 0 and n > 0:
                        if p0 == 0:
                            mid[0] = nums2[-1]
                        else:
                            mid[0] = max(nums2[-1], nums1[int(p0 - 1)])
                    else:
                        mid[0] = nums1[int(p0 + half - 1)]
                    mid[1] = nums1[int(p0 + half)]
                    break
                elif half == 0:
                    mid[0] = min(nums1[p0], nums2[p1])
                    if p0 == 0:
                        mid[1] = nums2[p1-1]
                    elif p1 == 0:
                        mid[1] = nums1[p0-1]
                    else:
                        mid[1] = max(nums1[p0-1], nums2[p1-1])
                    break
        else:
            half = int((m+n)/2)
            while True:
                can_len = int(half / 2)
                e0 = p0 + can_len
                e1 = p1 + can_len

                if e0 > m:
                    e0 = m
                if e1 > n:
                    e1 = n

                if nums1[int((p0+e0)/2)] <= nums2[int((p1+e1)/2)]:
                    delta = int(((p0+e0)/2) + 1 - p0)
                    p0 = int(((p0+e0)/2) + 1)
                    half = int(half - delta)
                else:
                    delta = int(((p1+e1)/2) + 1 - p1)
                    p1 = int(((p1+e1)/2) + 1)
                    half = int(half - delta)
                
                # check
                if p0 >= m:
                    mid[1] = nums2[int(p1 + half)]
                    mid[0] = mid[1]
                    break
                elif p1 >= n:
                    mid[1] = nums1[int(p0 + half)]
                    mid[0] = mid[1]
                    break
                elif half == 0:
                    mid[1] = min(nums1[p0], nums2[p1])
                    mid[0] = mid[1]
                    break
        return float(sum(mid)/2)