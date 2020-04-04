# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def distanceK(self, root, target, K):
        if not root or not target:
            return []
        if K == 0:
            return [target.val]
        trace = list()
        self.findK(root, target, trace)
        ret = list()
        for ind, tra in enumerate(trace):
            if ind == 0:
                ret = self.childDistK(tra, K)
            else:
                child = trace[ind - 1]
                if K - ind == 0:
                        ret.append(tra.val)
                        break
                if child is tra.left:
                    ret += self.childDistK(tra.right, K - 1 - ind)
                else:
                    ret += self.childDistK(tra.left, K - 1 - ind)
        return ret

    def findK(self, root, target, trace):
        if not root:
            return False
        if root.val == target.val:
            trace.append(root)
            return True
        l = r = False
        l = self.findK(root.left, target, trace)
        if not l:
            r = self.findK(root.right, target, trace)
        if l or r:
            trace.append(root)
            return True
        else:
            return False
    def childDistK(self, root, K):
        ret = list()
        if K == 0:
            if root:
                ret.append(root.val)
            return ret
        
        elif not root:
            return ret
        
        ret = self.childDistK(root.left, K-1) + self.childDistK(root.right, K-1)
        return ret
        