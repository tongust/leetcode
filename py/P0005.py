class Solution:
    def longestPalindrome(self, s):
        """
        Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

        Example 1:

        Input: "babad"
        Output: "bab"
        Note: "aba" is also a valid answer.
        Example 2:

        Input: "cbbd"
        Output: "bb"
        """
        # duplicated sequence
        if len(s) < 2:
            return s
        
        # special case

        char_prev = s[0]
        res = 1
        cur_res = 1
        cur_char = char_prev
        for index,char in enumerate(s):
            if index == 0:
                continue
            
            if char == char_prev:
                cur_res += 1
                if res < cur_res:
                    res = cur_res
                    cur_char = char
            else:
                char_prev = char
                cur_res = 1
        
        res_str = cur_char*res
        
        for index in range(1, len(s)-1):
            if s[index-1] == s[index+1]:
                index1 = 1
                size_pali = 1
                while index - index1 > -1 and index + index1 < len(s) and s[index - index1] == s[index + index1]:
                    index1 += 1
                    size_pali += 2
                    if size_pali > res:
                        res_str = s[index-int((size_pali-1)/2) : index + int((size_pali-1)/2) + 1:1]
                        res = size_pali
        
        for index in range(0, len(s)-1):
            if s[index] == s[index+1]:

                index1 = 1
                size_pali = 2
                while index - index1 > -1 and index + 1 + index1 < len(s) and s[index - index1] == s[index + 1 + index1]:
                    size_pali += 2
                    if size_pali > res:
                        res_str = s[index-index1:index+index1+2:1]
                        res = size_pali
                    index1 += 1
        
        return res_str