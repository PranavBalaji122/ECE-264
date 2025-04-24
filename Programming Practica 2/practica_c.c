// MODIFY ONLY THIS FILE
// Fill in the function following the instructions in the README

#include "practica_c.h"

static ListNode *reverse_list(ListNode* head);



ListNode *reverse_range(ListNode *head, int left, int right){
    ListNode helper = {.idx = 0, .next = head};
    ListNode *before = &helper;
    int counter = 0;

    while (counter < left) {
        before = before->next;
        ++counter;
    }

    //now i need to get the part of the list to after the reverse
    ListNode *after = head;
    for(int i =0; i< right; i++){
        after = after->next;
    }

    //now creating the correct list to flip
    for(int i =0; i< left; i++){
        head = head->next;
    }
    ListNode *subhelper = head;
    while(subhelper->next != after){
        subhelper = subhelper->next;
    }
    subhelper->next = NULL;

    head = reverse_list(head);
    before->next = head;
    while(head->next != NULL){
        head = head->next;
    }
    head->next = after;

    return(helper.next);
}


static ListNode * reverse_list(ListNode* head){

    if (head == NULL || head->next == NULL) {
        return head;
    }

    ListNode *new_head = reverse_list(head->next);
    head->next->next   = head;
    head->next         = NULL;
    return new_head;
}
