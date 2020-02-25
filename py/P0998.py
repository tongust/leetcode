# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def insertIntoMaxTree(self, root, val):
        a = self.in_order_traversing(root)
        a.append(val)
        return self.construct(a)

    def in_order_traversing(self, root):
        stack = []
        stack.append(root)

        traversing = list()
        visit_log = set()
        while stack:
            node = stack[-1]
            if node.left and node.left not in visit_log:
                stack.append(node.left)
            else:
                # visit in order
                node = stack.pop()
                traversing.append(node.val)
                visit_log.add(node)
                if node.right:
                    stack.append(node.right)
        return traversing
    
    def construct(self, array):
        if not array:
            return None
        m = max(array)
        m_i = array.index(m)
        node = TreeNode(m)
        node.left = self.construct(array[0:m_i:])
        node.right = self.construct(array[m_i+1::])
        return node



if __name__ == "__main__":

    so = Solution()

    a = so.construct([1,4,2,3])
    b = so.construct([1,4,2,3,5])
