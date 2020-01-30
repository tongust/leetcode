class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        # if target is even
        res = [-1,-1]
        if (target % 2) == 0:
            count = 0
            target_half = target / 2
            for index,val in enumerate(nums):
                if val == target_half:
                    res[count] = index
                    count += 1
                    if count >= 2:
                        return res

        # dedup
        nums0 = list(set(nums))
        if len(nums0) < 2:
            return [0,1]

        nums0 = [target - val for index,val in enumerate(nums0)] + [val for index,val in enumerate(nums0)]
        nums0 = sorted(nums0, reverse=False)

        first = 0
        prev = nums0[0]
        for i in range(1, len(nums0)):
            current = nums0[i]
            if current == prev:
                first = current
                break
            prev = current
        second = target - first
        count = 0
        for index,val in enumerate(nums):
            if second == val or first == val:
                res[count] = index
                count += 1