# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def swapNode(self, left, right):
        if not left:
            return right
        if not right:
            return left
        if left.val > right.val:
            return left
        else:
            return right
    def proceedNodes(self, head, k):
        res = head
        while k > 0 and res:
            res = res.next
            k -= 1
        return res
    def sortList(self, head, k):
        head = self.sortListWithoutAlter(head, k, None)
        tail = self.proceedNodes(head, k-1)
        tail.next = None
        return head
    def sortListWithoutAlter(self, head, k, head_pre):
        if k < 2:
            return head
        if k == 2:
            if head.val > head.next.val:
                return head
            else:
                head1 = head.next
                if head_pre:
                    head_pre.next = head1
                tail = head1.next
                head1.next = head
                head.next = tail
                return head1
        k_left = int(k / 2)
        k_right = k - k_left
        right_pre = self.proceedNodes(head, k_left-1)
        right = right_pre.next
        right = self.sortListWithoutAlter(right, k_right, right_pre)
        left = self.sortListWithoutAlter(head, k_left, head_pre)
        head = self.swapNode(left, right)
        if head_pre:
            head_pre.next = head
        node = None
        while k_left > 0 and k_right > 0:
            if left.val > right.val:
                if node:
                    node.next = left
                node = left
                left = left.next
                k_left -= 1
            else:
                if node:
                    node.next = right
                node = right
                right = right.next
                k_right -= 1
        if k_left == 0:
            node.next = right
        else:
            node.next = left
        return head

    def initialNodeList(self, l):
        if not l:
            return None
        r = list()
        for i in l:
            r.append(ListNode(i))
        head = r[0]
        for i in range(0, len(l)-1):
            r[i].next = r[i+1]
        return head
    def print11(self, l, n):
        s = ""
        while l:
            s += str(l.val) + " --> "
            l = l.next
            n -= 1
        print(s)
    def size(self, head):
        s = 0
        while head:
            s += 1
            head = head.next
        return s
    def reverse(self, head, k, head_pre):
        if not head or k == 1:
            return head
        i = 0
        e = int(k / 2)
        left = head
        left_pre = head_pre
        tail = self.proceedNodes(head, k)
        res = None
        while i < e:
            right_pre = self.proceedNodes(left, k-1-i-i-1)
            right = right_pre.next
            if left_pre:
                left_pre.next = right
            right_pre.next = left
            tmp = right.next
            right.next = left.next
            left.next = tmp
            if not res:
                res = right
            left_pre = right
            left = right.next
            i += 1
        return res
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        if k < 2:
            return head
        head_pre = None
        res = None
        size = self.size(head)
        if k > size:
            return head
        if size == 0:
            return head
        while True:
            end = self.proceedNodes(head, k-1)
            if not end:
                break
            end = end.next
            head = self.reverse(head, k, head_pre)
            #head = self.sortListWithoutAlter(head, k, head_pre)
            if not res:
                res = head
            head_pre = self.proceedNodes(head, k-1)
            head = end
        if size % k != 0:
            head_pre.next = head
        if not res:
            res = head
        tail = self.proceedNodes(res,size-1)
        tail.next = None
        return res

if __name__ == "__main__":
    so = Solution()
    head = so.initialNodeList([1,2,3,4,5])
    head = so.reverseKGroup(head, 8)
    so.print11(head, 5)