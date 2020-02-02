# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def mergeKLists(self, lists):
        if len(lists) < 1:
            if len(lists) == 1:
                return lists[0]
            return None
        size_list = len(lists)
        tmp_list = lists
        tmp_list1 = list()
        while len(tmp_list) > 1:
            for i in range(0, len(tmp_list)-1, 2):
                tmp_list1.append(self.mergeTwoLists(tmp_list[i], tmp_list[i+1]))
            if len(tmp_list) % 2 == 1:
                tmp_list1.append(tmp_list[-1])
            tmp_list = tmp_list1
            tmp_list1 = list()
        if not tmp_list[0]:
            return None
        return tmp_list[0]
    def mergeTwoLists(self, left, right):
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
