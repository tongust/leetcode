import re
from enum import Enum

class MatchCase(Enum):
    NotUsed_Skip = 1
    Used_Skip = 2
    Match_One = 3
    Match_More = 4


class Solution:
    def isMatch(self, s, p):
        if s == "":
            if p == "":
                return True
            if len(p) % 2 == 1:
                return False
            for i in range(1, len(p), 2):
                if p[i] != '*':
                    return False
            return True
        if p == "":
            return s == ""
        x = s
        y = list()
        for i in range(len(p)):
            if p[i] == '*':
                continue
            if i == len(p) - 1 or (p[i+1] != '*'):
                y.append(p[i])
            else:
                y.append(p[i:i+2:])
        #dp = [[set()]*len(x)]**len(y)
        dp = [[set() for j in range(len(x))] for i in range(len(y))]
        for i in range(len(y)):
            for j in range(len(x)):
                y_equal_x = y[i] == x[j]
                if self.isValid1(dp, i, j, x, y):
                    dp[i][j].add(MatchCase.NotUsed_Skip)
                if self.isValid2(dp, i, j, x, y):
                    dp[i][j].add(MatchCase.Used_Skip)
                if self.isValid3(dp, i, j, x, y):
                    dp[i][j].add(MatchCase.Match_One)
                if self.isValid4(dp, i, j, x, y):
                    dp[i][j].add(MatchCase.Match_More)
        d = dp[len(y)-1][len(x)-1]
        return MatchCase.Used_Skip in d or MatchCase.Match_One in d or MatchCase.Match_More in d

    def isValid1(self, dp, i, j, x, y):
        """
        Not used and skip
        """
        if not y[i][-1] == '*':
            return False
        if i == 0 and j == 0:
            return True
        # case 1 check
        if i > 0:
            if MatchCase.NotUsed_Skip in dp[i-1][j]:
                return True
        if i > 0 and j > 0:
            d = dp[i-1][j-1]
            if MatchCase.Match_One in d or MatchCase.Match_More in d:
                return True
        return False
    def isValid2(self, dp, i, j, x, y):
        if i == 0 and j == 0:
            return False
        if i > 0:
            d = dp[i-1][j]
            if MatchCase.Used_Skip in d or MatchCase.Match_More in d or MatchCase.Match_One in d:
                return y[i][-1] == '*'
        return False
    
    def isValid3(self, dp, i, j, x, y):
        # if y[i] == '.' or y[i] == x[j]:
        check = y[i] == '.' or y[i] == x[j]
        if not check:
            return False
        if i == 0 and j == 0:
            return True
        if i > 0:
            d = dp[i-1][j]
            if MatchCase.NotUsed_Skip in d:
                return True
        if j > 0 and i > 0:
            d = dp[i-1][j-1]
            if MatchCase.Used_Skip in d or MatchCase.Match_One in d or MatchCase.Match_More in d:
                return True
        return False

    def isValid4(self, dp, i, j, x, y):
        if not (y[i][-1] == '*' and (y[i][0] == x[j] or y[i][0] == '.')):
            return False
        if i == 0 and j == 0:
            return True
        if i > 0:
            d = dp[i-1][j]
            if MatchCase.NotUsed_Skip in d:
                return True
        if j > 0:
            d = dp[i][j-1]
            if MatchCase.Match_More in d:
                return True
        if i > 0 and j > 0:
            d = dp[i-1][j-1]
            if MatchCase.Used_Skip in d or MatchCase.Match_More in d or MatchCase.Match_One in d:
                return True
        return False



if __name__ == "__main__":
    so = Solution()
    print(so.isMatch("ab", "a"))
    print(so.isMatch("aa", "a*"))
    print(so.isMatch("aab", "c*a*b"))
    print(so.isMatch("mississippi", "mis*is*p*."))
    print(so.isMatch("a", "aa"))
    print(so.isMatch("", ".*"))
    print(so.isMatch("", "c*d*.*"))