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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            // Store the next node before we overwrite curr->next
            ListNode* next_node = curr->next;

            // Reverse the pointer
            curr->next = prev;

            // Move our pointers one step forward
            prev = curr;
            curr = next_node;
        }

        // prev will eventually end up at the original tail, which is our new head
        return prev;
    }
};
