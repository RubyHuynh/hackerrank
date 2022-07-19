
// 23. Merge k Sorted Lists
//https://leetcode.com/problems/merge-k-sorted-lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    /*Solution 1: Brute Force*/
//     ListNode* merge(ListNode* a,ListNode* b) {
//         if(!a) return b;
//         if(!b) return a;
//         ListNode* temp=NULL;
//         if(a->val<=b->val) 
//         {
//             temp =a;
//             temp->next = merge(a->next,b);
//         }
//         else 
//         {
//             temp = b;
//             temp->next = merge(a,b->next);
//         }
//         return temp;        
//     }
    
//     ListNode* mergeKLists(vector<ListNode*>& lists) {
//         if(lists.size()==0) return NULL;
//         if(lists.size()==1) return lists[0];
//         ListNode* ans=NULL;
//         for(auto l : lists) 
//         {
//             ans = merge(ans,l);
//         }
//         return ans;
//     }
  
    /*Solution 2:Priority queue*/
     ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0) return NULL;
        priority_queue<int,vector<int>,greater<int>> pq;
        
        for(int i=0;i<lists.size();i++)
        {
            ListNode* head = lists[i];
            while(head!=NULL)
            {
                pq.push(head->val);
                head = head->next;
            }
        }
        ListNode* start = NULL;
        ListNode* end = NULL;
        while(!pq.empty()) {
            if(start==NULL)
            {
                start = new ListNode(pq.top());
                end = start;
                pq.pop();
            }
            else{
                end->next = new ListNode(pq.top());
                pq.pop();
                end = end->next;
            }
        }
            return start;
    }
    /*Solution 3: Divide and Conquer*/
//     ListNode* mergesort(ListNode* a  , ListNode* b) {
//         if(!a) 
//             return b;
//         if(!b)
//             return a;
//         ListNode* ans=NULL;
//         if(a->val<=b->val)
//         {
//             ans=a;
//             ans->next = mergesort(a->next,b);
//         }
//         else
//         {
//             ans=b;
//             ans->next = mergesort(a,b->next);
//         }
//         return ans;
//     }
    
//     ListNode* mergeK(vector<ListNode*>& lists,int k) {
//         while(k!=0) {
//             int i = 0,j = k;
//             while(i<j) {
//                 lists[i]=mergesort(lists[i],lists[j]);
//                 i++;
//                 j--;
//                 if(i>=j) 
//                     k=j;
//             }
//         }
//         return lists[0];
//     }
    
//     ListNode* mergeKLists(vector<ListNode*>& lists) {
//         if(lists.size()==1)
//             return lists[0];
//         if(lists.size()==0) 
//             return NULL;
//         ListNode*newhead = mergeK(lists,lists.size()-1);
//         return newhead;
//     }
};
