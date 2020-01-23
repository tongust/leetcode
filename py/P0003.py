class Solution:
    def lengthOfLongestSubstring(self, s):
        res = 0
        if len(s) < 2:
            return len(s)
        
        char_set = dict()
        for index, val in enumerate(s):
            if val in char_set:
                char_set[val].append(index)
            else:
                char_set[val] = [index]
        
        char_neigh = dict()
        for key,value in char_set.items():
            for index in range(len(value)):
                val = value[index]
                if index == 0:
                    char_neigh[(key, val)] = val
                else:
                    char_neigh[(key,val)] = value[index-1]
        res = 1
        cur = 1
        left_bound = 0
        left_same_char_index = -1

        while True:
            char = s[cur]
            left_same_char_index = char_neigh[(char, cur)]

            if left_same_char_index >= left_bound and left_same_char_index != cur:
                # invalid with repeating chars
                dist = cur - left_bound
                if dist > res:
                    res = dist
                left_bound = left_same_char_index + 1
            cur += 1
            if cur >= len(s):
                dist = cur - left_bound
                if dist > res:
                    res = dist
                break
        return res