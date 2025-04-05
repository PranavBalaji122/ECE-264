#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node *node = malloc(sizeof(struct list_node));
  node->next = NULL;
  node->value = value;
  return node;
  }

void insert_at_head(struct linked_list *list, size_t value) {

    struct list_node *node = new_node(value);
    node->next = list->head;
    list->head = node;



}

void insert_at_tail(struct linked_list *list, size_t value) {
  if(list->head != NULL){
    struct list_node *node = new_node(value);
    struct list_node *ch = list->head;
    while((ch->next) != NULL){
      ch = ch->next;
    }
    ch->next = node;
  }else{
    struct list_node *node = new_node(value);
    list->head = node;
  }
  


}

size_t remove_from_head(struct linked_list *list) { 
  if(list->head == NULL){
    return 0;
  }
  size_t returnVal = list->head->value;
  struct list_node *temp_val = list->head;
  list->head = temp_val->next;
  free(temp_val);

  return returnVal; 
  }

size_t remove_from_tail(struct linked_list *list) { 

  if(list->head == NULL){
    return 0;
  }
  struct list_node *cur = list->head;
  struct list_node *node_beforeLast = list->head;
  while(cur->next != NULL){
    cur = cur->next;
    node_beforeLast = cur;
  }
  size_t returnVal = cur->value;
  node_beforeLast->next = NULL;
  free(cur);
  return returnVal;

  }

void free_list(struct linked_list list) {
  struct list_node *ch = list.head;
  struct list_node *next = list.head;
  while(ch != NULL){
    next = ch->next;
    free(ch);
    ch = next;
  }

}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
