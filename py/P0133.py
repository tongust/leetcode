class Node:
    def __init__(self, val = 0, neighbors = []):
        self.val = val
        self.neighbors = neighbors

class Solution:
    def cloneGraph(self, node):
        if node is None:
            return None
        visited = [None]*101
        res = self._cloneGraph(node, visited)
        return res

    def _cloneGraph(self, node, visited):
        if node is None:
            return None
        nodeNew = Node(node.val, [])
        visited[nodeNew.val] = nodeNew
        if node.neighbors is not None:
            nodeNew.neighbors = []
            for child in node.neighbors:
                # make sure child is not visited
                if visited[child.val] is not None:
                    nodeNew.neighbors.append(visited[child.val])
                else:
                    nodeNew.neighbors.append(self._cloneGraph(child, visited))
        return nodeNew