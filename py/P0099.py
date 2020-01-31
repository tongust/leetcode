# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
import queue
class Solution:
    def recoverTree(self, root):
        """
        Do not return anything, modify root in-place instead.
        """
        if root is None:
            return root

        invalidList = list()
        visitCan = queue.Queue()
        visitCan.put(root)

        ids_invalid_set = set()
        while visitCan.qsize() > 0:
            node = visitCan.get()
            ids = self.invalidIdList(node)
            ids_invalid_set = ids_invalid_set.union(set(ids))
            if node.left is not None:
                visitCan.put(node.left)
            if node.right is not None:
                visitCan.put(node.right)
        # inorder traversing
        visitCan = queue.deque()
        visitCan.appendleft(root)
        invalid_node_list = list()
        visit_flag = set()
        while len(visitCan) > 0:
            node = visitCan[-1]
            if node.left is None or node.left in visit_flag:
                # visit medium
                node = visitCan.pop()
                visit_flag.add(node)
                if node.val in ids_invalid_set:
                    invalid_node_list.append(node)
                # visit right
                if node.right is not None:
                    visitCan.append(node.right)

            else:
                # left fist
                visitCan.append(node.left)
        first = invalid_node_list[0]
        last = invalid_node_list[-1]
        self.swapNodes(first, last)

    def swapNodes(self, node1, node2):
        if node2 is None or node1 is None:
            return

        tmpVal = node1.val
        node1.val = node2.val
        node2.val = tmpVal
        

    def isValid(self, root):
        if root is None:
            return True
        return self.isValidSingleNode(root) and self.isValidSingleNode(root.left) and self.isValidSingleNode(root.right)
    
    def invalidIdList(self,root):
        ids = set()
        # verify left
        if root.left is not None:
            pred = self.predecessor(root)
            if pred.val > root.val:
                ids.add(pred.val)
                ids.add(root.val)
            if root.left.val > root.val:
                ids.add(root.val)
                ids.add(root.left.val)
        # verify right
        if root.right is not None:
            succ = self.successor(root)
            if succ.val < root.val:
                ids.add(succ.val)
                ids.add(root.val)
            if root.right.val < root.val:
                ids.add(root.right.val)
                ids.add(root.val)
        return list(ids)

    def isValidSingleNode(self, root):
        if root is None:
            return True
        # verify left
        if root.left is not None:
            pred = self.predecessor(root)
            if pred.val >= root.val or root.val <= root.left.val:
                return False
        # verify right
        if root.right is not None:
            succ = self.successor(root)
            if succ.val <= root.val or root.right.val <= root.val:
                return False
        return True
    
    def successor(self, root):
        if root is None or root.right is None:
            return None
        
        child = root.right
        while child.left is not None:
            child = child.left
        return child

    def predecessor(self, root):
        if root is None or root.left is None:
            return None
        
        pred = root.left
        while pred.right is not None:
            pred = pred.right
        return pred 