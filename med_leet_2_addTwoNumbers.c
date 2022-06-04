/*Success
Details 
Runtime: 13 ms, faster than 81.46% of C online submissions for Add Two Numbers.
Memory Usage: 7.6 MB, less than 87.79% of C online submissions for Add Two Numbers.

*
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int add(struct ListNode** rs, int val1, int val2) {
    struct ListNode* tmp = *rs;
    struct ListNode* item  = malloc(sizeof(struct ListNode));
    item->val = (val1 + val2) % 10;
    item->next = NULL;
    
    if (!tmp) {
        *rs = item;
    }
    else {
        while (tmp && tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = item;
    }
    return (val1 + val2) / 10;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode* rs = NULL;
    struct ListNode* list1 = l1;
    struct ListNode* list2 = l2;
    int leftOver = 0;
    
    // while (list1 && list2) {
    //     leftOver = add(&rs, list1->val + leftOver, list2->val);
    //     list1 = list1->next;       
    //     list2 = list2->next;
    // }
    // list1 = list1 ? list1 : list2;
    // while (list1) {
    //     leftOver = add(&rs, list1->val, leftOver);
    //     list1 = list1->next; 
    // }
    // if (leftOver) add(&rs, 0, leftOver);
    
    
    while (list1 || list2 || leftOver) {
         leftOver = add(&rs, (list1 ? list1->val : 0) + leftOver, list2 ? list2->val : 0);
         list1 = list1 ? list1->next : NULL;
         list2 = list2 ? list2->next : NULL;
    }
    return rs;
}
