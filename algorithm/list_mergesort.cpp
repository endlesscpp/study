/**
 * merge sort the list
 */




/**
 * Definition for singly-linked list.
 */
#define NULL 0
#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* merge(ListNode* h1, ListNode* h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;

    ListNode merged(0);
    ListNode* p = &merged;

    while (true)
    {
        if (h1 == NULL)
        {
            p->next = h2;
            break;
        }
        else if (h2 == NULL)
        {
            p->next = h1;
            break;
        }

        if (h1->val < h2->val )
        {
            p->next = h1;
            p = p->next;
            h1 = h1->next;
        }
        else
        {
            p->next = h2;
            p = p->next;
            h2 = h2->next;
        }
    }

    return merged.next;
}

ListNode* mergeSortListWithStep( ListNode* p, int step )
{
    ListNode* ret = NULL;
    ListNode* tail = NULL;

    while (p != NULL )
    {
        ListNode* h1 = p;
        ListNode* h2 = p;

        for (int i = 0; i < step-1 && h2 != NULL; i++)
            h2 = h2->next;

        if (h2 )
        {
            ListNode* temp = h2->next;
            h2->next = NULL;
            h2 = temp;
        }

        // get the next header to sort
        p = h2;
        for (int i = 0; i < step-1 && p != NULL; i++ )
            p = p->next;

        if ( p )
        {
            ListNode* temp = p->next;
            p->next = NULL;
            p = temp;
        }

        ListNode* pNewHead = merge(h1, h2);
        if (ret == NULL)
            ret = pNewHead;

        if (tail != NULL)
            tail->next = pNewHead;
        else
            tail = pNewHead;

        while (tail->next != NULL)
            tail = tail->next;    
    }

    return ret;
}

class Solution {
public:
    ListNode *sortList(ListNode *head) {

        if (head == NULL)
            return head;

        int len = 0;
        for (ListNode* p = head; p != NULL; p = p->next)
            len = len + 1;
        
        for (int step = 1; step < len; step = step * 2)
            head = mergeSortListWithStep(head, step);

        return head;
    }
};


int main()
{
    ListNode node(0);
    ListNode* p = &node;
    for (int i = 20; i>0; i--)
    {
        p->next = new ListNode(i);
        p = p->next;
    }

    for (p = node.next; p != NULL; p = p->next)
        printf("%d ", p->val);
    printf("\n");

    Solution s;
    node.next = s.sortList( node.next );

    for (p = node.next; p != NULL; p = p->next)
        printf("%d ", p->val);
    printf("\n");


    return 0;
}
