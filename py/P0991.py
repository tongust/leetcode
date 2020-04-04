class Solution:
    def brokenCalc(self, X, Y):
        if X == Y:
            return 0
        if Y < X:
            return X - Y
        ret = 0
        y = Y
        while True:
            if y <= X:
                ret += X - y
                break
            if y % 2 == 1:
                y += 1
                ret += 1
            else:
                y = int(y / 2)
                ret += 1
        return ret

if __name__ == "__main__":
    so = Solution()
    print(so.brokenCalc(9411922,9702997))