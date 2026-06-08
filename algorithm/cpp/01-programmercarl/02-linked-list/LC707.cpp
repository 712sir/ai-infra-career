/**
 * LC 707. Design Linked List
 *
 * 两种实现：单链表（虚拟头节点）/ 双链表（哨兵节点 + 双向遍历优化）
 *
 * 核心技巧：
 * - 单链表：_dummyHead 统一头节点操作
 * - 双链表：sentinelNode 循环哨兵 + size>>1 判断从头/尾遍历
 * - delete 后置 nullptr 防止野指针
 */

#include <iostream>
using namespace std;

// ============================================================
// 解法一：单链表
// ============================================================
class MyLinkedList_Singly {
public:
    struct LinkedNode {
        int val;
        LinkedNode* next;
        LinkedNode(int val) : val(val), next(nullptr) {}
    };

    MyLinkedList_Singly() {
        _dummyHead = new LinkedNode(0);
        _size = 0;
    }

    int get(int index) {
        if (index > (_size - 1) || index < 0) return -1;
        LinkedNode* cur = _dummyHead->next;
        while (index--) cur = cur->next;  // --index 会死循环：先减再判断
        return cur->val;
    }

    void addAtHead(int val) {
        LinkedNode* newNode = new LinkedNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size++;
    }

    void addAtTail(int val) {
        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while (cur->next != nullptr) cur = cur->next;
        cur->next = newNode;
        _size++;
    }

    void addAtIndex(int index, int val) {
        if (index > _size) return;
        if (index < 0) index = 0;
        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while (index--) cur = cur->next;
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }

    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) return;
        LinkedNode* cur = _dummyHead;
        while (index--) cur = cur->next;
        LinkedNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        tmp = nullptr;  // 防野指针：delete 后地址变随机值
        _size--;
    }

private:
    int _size;
    LinkedNode* _dummyHead;
};

// ============================================================
// 解法二：双链表（哨兵节点 + 双向遍历优化）
// ============================================================
class MyLinkedList_Doubly {
public:
    struct DList {
        int elem;
        DList* next;
        DList* pre;
        DList(int elem) : elem(elem), next(nullptr), pre(nullptr) {}
    };

    MyLinkedList_Doubly() {
        sentinelNode = new DList(0);
        sentinelNode->next = sentinelNode;
        sentinelNode->pre = sentinelNode;
        size = 0;
    }

    int get(int index) {
        if (index > size - 1 || index < 0) return -1;
        int mid = size >> 1;
        DList* curNode = sentinelNode;
        if (index < mid) {
            for (int i = 0; i < index + 1; i++)
                curNode = curNode->next;
        } else {
            for (int i = 0; i < size - index; i++)
                curNode = curNode->pre;
        }
        return curNode->elem;
    }

    void addAtHead(int val) {
        DList* newNode = new DList(val);
        DList* next = sentinelNode->next;
        newNode->pre = sentinelNode;
        newNode->next = next;
        size++;
        sentinelNode->next = newNode;
        next->pre = newNode;
    }

    void addAtTail(int val) {
        DList* newNode = new DList(val);
        DList* pre = sentinelNode->pre;
        newNode->next = sentinelNode;
        newNode->pre = pre;
        size++;
        sentinelNode->pre = newNode;
        pre->next = newNode;
    }

    void addAtIndex(int index, int val) {
        if (index > size) return;
        if (index <= 0) { addAtHead(val); return; }
        int mid = size >> 1;
        DList* curNode = sentinelNode;
        if (index < mid) {
            for (int i = 0; i < index; i++) curNode = curNode->next;
            DList* tmp = curNode->next;
            DList* newNode = new DList(val);
            curNode->next = newNode;
            tmp->pre = newNode;
            newNode->next = tmp;
            newNode->pre = curNode;
        } else {
            for (int i = 0; i < size - index; i++) curNode = curNode->pre;
            DList* tmp = curNode->pre;
            DList* newNode = new DList(val);
            curNode->pre = newNode;
            tmp->next = newNode;
            newNode->pre = tmp;
            newNode->next = curNode;
        }
        size++;
    }

    void deleteAtIndex(int index) {
        if (index > size - 1 || index < 0) return;
        int mid = size >> 1;
        DList* curNode = sentinelNode;
        if (index < mid) {
            for (int i = 0; i < index; i++) curNode = curNode->next;
            DList* next = curNode->next->next;
            curNode->next = next;
            next->pre = curNode;
        } else {
            for (int i = 0; i < size - index - 1; i++) curNode = curNode->pre;
            DList* pre = curNode->pre->pre;
            curNode->pre = pre;
            pre->next = curNode;
        }
        size--;
    }

private:
    int size;
    DList* sentinelNode;
};
