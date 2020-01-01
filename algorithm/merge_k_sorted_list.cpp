#include <vector>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next( NULL )
    {
    }
};

struct compareFunc
{
    bool operator() ( ListNode* const & lhs, ListNode* const & rhs) {
        return lhs->val > rhs->val;
    }
};
    
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.size() == 0)
            return NULL;
            
        ListNode header(0);
        ListNode* lastNode = &header;
        
        priority_queue<ListNode*, vector<ListNode*>, compareFunc> heap;
        
        for (int i = 0; i<lists.size(); i++) {
            if (lists[i])
                heap.push( lists[i] );
        }
        
        while (true) {
            if (heap.empty())
                break;
                
            if (heap.size() == 1) {
                lastNode->next = heap.top();
                break;
            }
            
            ListNode* curr = heap.top();

            heap.pop();
            ListNode* p = curr->next;
            curr->next = NULL;
            
            if (p)
                heap.push(p);
            
            lastNode->next = curr;
            lastNode = lastNode->next;
        }
        
        return header.next;
    }

int main()
{
    vector<ListNode*> v;
    v.push_back(new ListNode(2));
    v.push_back(new ListNode(1));
    v.push_back(new ListNode(3));
    v.push_back(new ListNode(5));
    v.push_back(new ListNode(4));

    ListNode* ans = mergeKLists(v);

    while (ans != NULL) {
        printf("%d->", ans->val);
        ans = ans->next;
    }
    printf("\n");

    return 0;
}
