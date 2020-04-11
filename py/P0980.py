class Solution:
    def uniquePathsIII(self, grid):
        emptyCnt = 0
        start = []
        for ind_i, val_i in enumerate(grid):
            for ind_j, val_j in enumerate(val_i):
                if val_j == 1:
                    start = [ind_i, ind_j]
                elif val_j == 0:
                    emptyCnt += 1
        return self.recur(grid, start, emptyCnt)
    def recur(self, grid, start, emptyCnt):
        # up
        row = len(grid)
        col = len(grid[0])
        i = start[0]
        j = start[1]
        retCnt = 0
        if emptyCnt == 0:
            if ( (i-1>-1 and grid[i-1][j] == 2) or (i+1<row and grid[i+1][j] == 2) or (j-1>-1 and grid[i][j-1] == 2) or (j+1<col and grid[i][j+1] == 2) ):
                return 1
            else:
                return 0
        val = grid[i][j]
        grid[i][j] = -1
        if i-1>-1 and grid[i-1][j] == 0:
            retCnt += self.recur(grid, [i-1,j], emptyCnt-1)
        if i+1<row and grid[i+1][j] == 0:
            retCnt += self.recur(grid, [i+1,j], emptyCnt-1)
        if j-1>-1 and grid[i][j-1] == 0:
            retCnt += self.recur(grid, [i,j-1], emptyCnt-1)
        if j+1<col and grid[i][j+1] == 0:
            retCnt += self.recur(grid, [i,j+1], emptyCnt-1)
        grid[i][j] = val
        return retCnt

if __name__ == "__main__":

    so = Solution()
    so.uniquePathsIII([[1,0,0,0],[0,0,0,0],[0,0,0,2]])