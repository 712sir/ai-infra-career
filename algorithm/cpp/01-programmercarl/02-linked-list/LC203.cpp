/**
 * LC 203. Remove Linked List Elements
 *
 * 三种解法：直接删除 / 虚拟头节点 / 递归
 * 核心技巧：虚拟头节点（dummy head）统一处理删除逻辑
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // ============================================================
    // 解法一：直接使用原链表删除
    // 头节点需要单独处理（while 不是 if）
    // ============================================================
    ListNode* removeElements_v1(ListNode* head, int val) {
        // 删除值是 val 的头节点（可能有连续多个）
        while (head != NULL && head->val == val) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        // 删除非头节点
        ListNode* cur = head;
        while (cur != NULL && cur->next != NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        return head;
    }

    // ============================================================
    // 解法二：虚拟头节点（推荐面试写法）
    // 统一所有节点的删除逻辑，不需要特判头节点
    // ============================================================
    ListNode* removeElements_v2(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* cur = dummyHead;

        while (cur->next != NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }

        head = dummyHead->next;
        delete dummyHead;
        return head;
    }

    // ============================================================
    // 解法三：递归
    // 递归处理剩余链表，根据当前节点值决定返回什么
    // ============================================================
    ListNode* removeElements_v3(ListNode* head, int val) {
        if (head == nullptr) return nullptr;

        if (head->val == val) {
            ListNode* newHead = removeElements_v3(head->next, val);
            delete head;
            return newHead;
        } else {
            head->next = removeElements_v3(head->next, val);
            return head;
        }
    }
};
