# Definition for a binary tree node.

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def minCameraCover(self, root):
        dp = dict()
        if not root:
            return 0
        elif not root.left and not root.right:
            return 1
        return self.recur(root, dp, False, False)

    def recur(self, root, dp, parentInstall, mustInstall):
        if not root:
            return 0    
        if (root, parentInstall, mustInstall) in dp:
            return dp[(root, parentInstall, mustInstall)]
        if parentInstall:
            # install
            ret0 = 1
            ret0 += self.recur(root.left, dp, True, False)
            ret0 += self.recur(root.right, dp, True, False)
            # not install
            ret1 = 0
            ret1 += self.recur(root.left, dp, False, False)
            ret1 += self.recur(root.right, dp, False, False)
            retVal = min([ret0, ret1])
            
        else:
            # intall
            ret0 = 1
            ret0 += self.recur(root.left, dp, True, False)
            ret0 += self.recur(root.right, dp, True, False)
            retVal = ret0
            # depend on children
            if not mustInstall:
                # case0
                if root.left and not root.right:
                    case0 = self.recur(root.left, dp, False, True)
                    if retVal > case0:
                        retVal = case0
                elif not root.left and root.right:
                    case1 = self.recur(root.right, dp, False, True)
                    if retVal > case1:
                        retVal = case1
                elif root.left and root.right:
                    # case2
                    case2 = self.recur(root.left, dp, False, True) + self.recur(root.right, dp, False, True)
                    case3 = self.recur(root.left, dp, False, True) + self.recur(root.right, dp, False, False)
                    case4 = self.recur(root.left, dp, False, False) + self.recur(root.right, dp, False, True)
                    retVal = min([case2, case3, case4, retVal])

        dp[(root, parentInstall, mustInstall)] = retVal
        return retVal
        

if __name__ == "__main__":
    so = Solution()
    root = TreeNode(0)
    root.left = TreeNode(1)
    root.left.right = TreeNode(2)
    root.left.right.left = TreeNode(3)
    root.left.right.left.right = TreeNode(4)
    root.left.right.left.right.left = TreeNode(5)

    print(so.minCameraCover(root))
        