# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        left = l1
        right = l2
        if not left:
            return right
        if not right:
            return left
        head = None
        cur = None
        l = left
        r = right
        while l and r:
            l,r = self.min_max(l,r)
            if not head:
                head = l
            else:
                cur.next = l
            cur = l
            l = l.next
        if r:
            cur.next = r
        return head

    def min_max(self, left, right):
        if left.val < right.val:
            return (left, right)
        else:
            return (right, left)