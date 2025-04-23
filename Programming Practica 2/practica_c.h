#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "assert.h"
#include "string.h"

typedef struct _list_node
{
    const int idx;
    struct _list_node *next;
} ListNode;

ListNode *reverse_range(ListNode *head, int left, int right);

#endif