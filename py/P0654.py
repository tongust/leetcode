# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> TreeNode:
        if not nums:
            return None
        m = max(nums)
        m_i = nums.index(m)
        node = TreeNode(m)
        node.left = self.constructMaximumBinaryTree(nums[0:m_i:])
        node.right = self.constructMaximumBinaryTree(nums[m_i+1::])
        return node