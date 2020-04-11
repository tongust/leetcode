class Solution:
    def orangesRotting(self, grid):
        rottenSet = set()
        freshSet = set()
        count = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    freshSet.add((i,j))
                elif grid[i][j] == 2:
                    rottenSet.add((i,j))
        if len(freshSet) < 1:
            return 0
        elif len(rottenSet) < 1:
            return -1
        else:
            rottenSet = self.simplifyRotten(rottenSet, grid)
            # rotten
            while len(rottenSet) > 0 and len(freshSet) > 0:
                rottenAdd = set()
                for rot in rottenSet:
                    candi = self.couldBeRottenPos(grid, rot)
                    for can in candi:
                        grid[can[0]][can[1]] = 2
                        freshSet.remove(tuple(can))
                        rottenAdd.add(tuple(can))
                for add in rottenAdd:
                    rottenSet.add(add)
                rottenSet = self.simplifyRotten(rottenSet, grid)
                count += 1
        if len(freshSet) > 0:
            return -1
        else:
            return count
                    
    def couldBeRottenPos(self, grid, ij):
        ret = []
        i = ij[0]
        j = ij[1]
        for l in [-1, 0, 1]:
            for m in [-1, 0, 1]:
                if (l == 0 or m == 0) and self.couldBeRotten([i+l, j+m], grid):
                    ret.append([i+l, j+m])
        return ret
    def couldBeRotten(self, pos, grid):
        row = len(grid)
        col = len(grid[0])
        if (pos[0] > -1 and pos[0] < row) and (pos[1] > -1 and pos[1] < col):
            return grid[pos[0]][pos[1]] == 1
        else:
            return False
    def simplifyRotten(self, rottenSet, grid):
        retSet = set()
        for ij in rottenSet:
            i = ij[0]
            j = ij[1]
            if self.couldBeRotten([i+1,j], grid) or self.couldBeRotten([i-1, j], grid) or self.couldBeRotten([i, j-1], grid) or self.couldBeRotten([i, j+1], grid):
                retSet.add(tuple(ij))
        return retSet

if __name__ == "__main__":
    so = Solution()
    print(so.orangesRotting([[2,1,1],[1,1,0],[0,1,1]]))
    print(so.orangesRotting([[2,1,1],[0,1,1],[1,0,1]]))
    print(so.orangesRotting([[0,2]]))