"""
LC 707. Design Linked List

两种实现：单链表（虚拟头节点）/ 双链表（head+tail 双向遍历优化）

常见错误：
1. __init__ 拼成 _init_ → 构造方法不被调用
2. 缩进不一致 → IndentationError
3. self.size+=1 → PEP 8 要求运算符两侧空格
"""

# ============================================================
# 解法一：单链表
# ============================================================
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class MyLinkedList_Singly:
    def __init__(self):
        self.dummy_head = ListNode()
        self.size = 0

    def get(self, index):
        if index < 0 or index >= self.size:
            return -1
        cur = self.dummy_head.next
        for _ in range(index):
            cur = cur.next
        return cur.val

    def addAtHead(self, val):
        self.dummy_head.next = ListNode(val, self.dummy_head.next)
        self.size += 1

    def addAtTail(self, val):
        cur = self.dummy_head
        while cur.next:
            cur = cur.next
        cur.next = ListNode(val)
        self.size += 1

    def addAtIndex(self, index, val):
        if index < 0 or index > self.size:
            return
        cur = self.dummy_head
        for _ in range(index):
            cur = cur.next
        cur.next = ListNode(val, cur.next)
        self.size += 1

    def deleteAtIndex(self, index):
        if index < 0 or index >= self.size:
            return
        cur = self.dummy_head
        for _ in range(index):
            cur = cur.next
        cur.next = cur.next.next
        self.size -= 1


# ============================================================
# 解法二：双链表（head + tail，双向遍历优化 O(min(index, size-index))）
# ============================================================
class ListNode_Double:
    def __init__(self, val=0, pre=None, next=None):
        self.val = val
        self.pre = pre
        self.next = next


class MyLinkedList_Doubly:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def get(self, index):
        if index < 0 or index >= self.size:
            return -1
        if index < self.size // 2:
            cur = self.head
            for _ in range(index):
                cur = cur.next
        else:
            cur = self.tail
            for _ in range(self.size - index - 1):
                cur = cur.pre
        return cur.val

    def addAtHead(self, val):
        new_node = ListNode_Double(val, None, self.head)
        if self.head:
            self.head.pre = new_node
        else:
            self.tail = new_node
        self.head = new_node
        self.size += 1

    def addAtTail(self, val):
        new_node = ListNode_Double(val, self.tail, None)
        if self.tail:
            self.tail.next = new_node
        else:
            self.head = new_node
        self.tail = new_node
        self.size += 1

    def addAtIndex(self, index, val):
        if index < 0 or index > self.size:
            return
        if index == 0:
            self.addAtHead(val)
        elif index == self.size:
            self.addAtTail(val)
        else:
            if index < self.size // 2:
                cur = self.head
                for _ in range(index - 1):
                    cur = cur.next
            else:
                cur = self.tail
                for _ in range(self.size - index):
                    cur = cur.pre
            new_node = ListNode_Double(val, cur, cur.next)
            cur.next.pre = new_node
            cur.next = new_node
            self.size += 1

    def deleteAtIndex(self, index):
        if index < 0 or index >= self.size:
            return
        if index == 0:
            self.head = self.head.next
            if self.head:
                self.head.pre = None
            else:
                self.tail = None
        elif index == self.size - 1:
            self.tail = self.tail.pre
            if self.tail:
                self.tail.next = None
            else:
                self.head = None
        else:
            if index < self.size // 2:
                cur = self.head
                for _ in range(index):
                    cur = cur.next
            else:
                cur = self.tail
                for _ in range(self.size - index - 1):
                    cur = cur.pre
            cur.pre.next = cur.next
            cur.next.pre = cur.pre
        self.size -= 1
