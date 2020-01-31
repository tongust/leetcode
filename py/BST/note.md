# Binary Search Tree
There are 3 method to traverse/walk through the BST:
pre-order, in-order, post-order. Here we only show the implementations of pre-order and in-order in non-recursively method.
## Non-recursively: in-order traversing
```python
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

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
                traversing.append(node)
                visit_log.add(node)
                if node.right:
                    stack.append(node.right)
        return traversing
```

## Non-recursively: pre-order traversing
```python
    def pre_order_traversing(self, root):
        stack = []
        stack.append(root)

        traversing = list()

        while stack:
            node = stack.pop()
            traversing.append(node)
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
        return traversing
```