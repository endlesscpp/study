
#include <stdio.h>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// [begin, end]
// return the last node pointer
ListNode* reverse22(ListNode* prev, ListNode* begin, ListNode* end)
{
    printf("end->val = %d\n", end->val);

    ListNode* pNew = end->next;
    end->next = NULL;
    ListNode* p = begin;

    while (p != NULL) {
        ListNode* t = p->next;
        p->next = pNew;
        pNew = p;
        p = t;
    }

    prev->next = end;
    return begin;
}

ListNode* reverse(ListNode* prev, ListNode* begin, ListNode* end)
{
    ListNode* end_next = end->next;

    for (ListNode *p = begin, *curr = p->next, *next = curr->next;
            curr != end_next;
        p = curr, curr = next, next = next ? next->next : NULL)
    {
        curr->next = p;
    }

    prev->next = end;
    begin->next = end_next;

    return begin;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    if (head == NULL || head->next == NULL || k < 2)
        return head;
    
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;

    while (true) {
        ListNode* curr = prev->next;
        ListNode* end = curr;

        for (int i = 1; i<k; i++)
            end = end ? end->next : NULL;

        if (end == NULL)
            break;

        prev = reverse(prev, curr, end);
    }

    return dummy.next;
}

int main()
{
    ListNode dummy(0);

    ListNode* p = &dummy;
    for (int i = 1; i<=4; i++) {
        p->next = new ListNode(i);
        p = p->next;
    }

    p = reverseKGroup(dummy.next, 2);

    printf("ret:\n");
    while (p != NULL) {
        printf("%d=>", p->val);
        p = p->next;
    }
    printf("\n");

    return 0;
}

