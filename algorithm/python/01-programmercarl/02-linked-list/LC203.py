"""
LC 203. Remove Linked List Elements

三种解法：直接删除 / 虚拟头节点 / 递归
核心技巧：虚拟头节点（dummy head）统一处理删除逻辑
Python 注意点：无 NULL，用 None；类方法调用必须加 self.
"""

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    # ============================================================
    # 解法一：直接使用原链表删除
    # 头节点需要单独处理（while 不是 if）
    # ============================================================
    def removeElements_v1(self, head, val):
        # 删除值是 val 的头节点（可能有连续多个）
        while head and head.val == val:
            head = head.next

        cur = head
        while cur and cur.next:
            if cur.next.val == val:
                cur.next = cur.next.next
            else:
                cur = cur.next

        return head

    # ============================================================
    # 解法二：虚拟头节点（推荐面试写法）
    # 统一所有节点的删除逻辑，不需要特判头节点
    # ============================================================
    def removeElements_v2(self, head, val):
        dummy_head = ListNode(0, head)

        cur = dummy_head
        while cur.next:
            if cur.next.val == val:
                cur.next = cur.next.next
            else:
                cur = cur.next

        return dummy_head.next

    # ============================================================
    # 解法三：递归
    # 递归处理剩余链表，根据当前节点值决定返回什么
    # 注意：类方法调用必须加 self.
    # ============================================================
    def removeElements_v3(self, head, val):
        if not head:
            return head

        if head.val == val:
            return self.removeElements_v3(head.next, val)
        else:
            head.next = self.removeElements_v3(head.next, val)
            return head
