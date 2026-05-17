/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextLargerNodes(struct ListNode* head, int* returnSize) {
    
    int numsNos = 0;
    int firstNo = 0;
    struct ListNode* nos = head;
    struct ListNode* nextNo; 

    while (nos != NULL) {
        nos = nos->next;
        numsNos++;
    }

    nos = head;
    *returnSize = numsNos;

    int* answer = (int*)malloc(numsNos * sizeof(int));
    numsNos = 0;
    
    while (nos != NULL) {
        firstNo = nos->val;
        nextNo = nos->next;

        while (nextNo != NULL) {

            if (firstNo < nextNo->val) {
                firstNo = nextNo->val;
                break;
            }
            nextNo = nextNo->next;
        }

        if (firstNo == nos->val) {
            firstNo = 0;
        }

        nos = nos->next;
        answer[numsNos] = firstNo;
        numsNos++;
        
    }
    return answer;  
}
