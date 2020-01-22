class Solution:
    def addTwoNumbers(self, l1, l2):
        l3 = ListNode(0)
        cur1 = l1
        cur2 = l2
        cur3 = l3
        cur3.next = None
        aggr_prev = 0
        first = True
        while True:
            if cur1 is None and cur2 is None:
                if aggr_prev > 0:
                    cur3.next = ListNode(0)
                    cur3 = cur3.next
                    cur3.val = aggr_prev
                    cur3.next = None
                else:
                    cur3.next = None
                break
            else:
                if not first:
                    cur3.next = ListNode(0)
                    cur3 = cur3.next
                    cur3.next = None
                else:
                    first = False
            if cur1 is None:
                val = cur2.val + aggr_prev
            elif cur2 is None:
                val = cur1.val + aggr_prev
            else:
                val = cur1.val + cur2.val + aggr_prev
            aggr = 0
            if val > 9:
                aggr = int(val/10)
            cur3.val = val - 10*aggr

            aggr_prev = aggr

            if cur1 is not None:
                cur1 = cur1.next
            if cur2 is not None:
                cur2 = cur2.next
        return l3