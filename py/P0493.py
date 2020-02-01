# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def findBottomLeftValue(self, root):
        leaf_list = []
        self.getLeaf(root, "1", leaf_list)
        leaf_list = sorted(leaf_list, key=lambda x: (len(x[1]), x[1]), reverse=True)
        return leaf_list[0][0]
    
    def getLeaf(self, root, depth, leaf_list):
        if not root:
            return
        if self.isLeaf(root):
            leaf_list.append([root.val, depth])
        if root.left:
            self.getLeaf(root.left, depth+"1", leaf_list)
        if root.right:
            self.getLeaf(root.right, depth+"0", leaf_list)

    def isLeaf(self, root):
        return root and not root.left and not root.right