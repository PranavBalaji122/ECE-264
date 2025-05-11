#include "hw14.h"

#include <stdlib.h>


void compute_layout(struct DOMNode *node, float x1, float y1, float x2, float y2, FILE *target) {
    fprintf(target, "%d %0.2f %0.2f %0.2f %0.2f\n", node->id, x1, y1, x2, y2);

    int numChildren = 0;
    for (struct DOMNodeList *p = node->children; p; p = p->next){
        numChildren +=1;
    }  
    if(numChildren == 0){
        return;
    }
    float x1New = x1;
    float x2New = x2;
    float y1New = y1; 
    float y2New = y2;
    int counter = 0;
    for(struct DOMNodeList *helper = node->children; helper; helper = helper->next){
        float width = (x2-x1) * (1-node->margin)  / numChildren;
        float length = (y2 - y1) * (1-node->margin) / numChildren;

        if(node->layout_direction == LAYOUT_HORIZ){ // horiz means that all children have the same width
            x1New = x1 + ((x2 - x1) * node->margin * 0.5) + counter * width;
            x2New = x1New + width;
            y1New = y1 + (node->margin * (y2-y1) * 0.5);
            y2New = y2 - (node->margin * (y2-y1) * 0.5);
        }else if (node->layout_direction == LAYOUT_VERT){ // vertical means that all children have the same length ex same y
            x1New = x1 + ((x2 - x1) * node->margin * 0.5);
            x2New = x2 - (node->margin * (x2 - x1) * 0.5);
            y1New = y1 + ((y2 - y1) * node->margin * 0.5) + (counter * length);
            y2New = y1New + length;

        }else{ // there is no layout
            x1New = x1 + ((x2-x1) * node->margin * 0.5);
            x2New = x2 - ((x2-x1) * node->margin * 0.5);
            y1New = y1 + ((y2-y1) * node->margin * 0.5);
            y2New = y2 - ((y2-y1) * node->margin * 0.5);
        }
        compute_layout(helper->node, x1New, y1New, x2New, y2New, target);
        counter ++;
    }
}


void layout(struct DOMNode *root, float width, float height, FILE *target) {
    fprintf(target, "%.2f %.2f\n", width, height); 
    compute_layout(root, 0.0, 0.0, width, height, target);
}


void free_DOMTree(struct DOMNode *root) {
    // Base Case: checking if the root is null 

    if(root == NULL){

        return; // if it is then return nothing  

    }
    // creating a DOMNode list to free the dom tree recursively 
    struct DOMNodeList *helper = root->children;
    
    while (helper!=NULL) {
        // creating another DomNodeList to save the next node after the current domnodelist is freed
        struct DOMNodeList *helper1 = helper->next;  
        // calling the method recursively
        free_DOMTree(helper->node);        
        // freeing the DomNodeList       
        free(helper);                             
        helper = helper1;              
    }

    // freeing the root
    free(root);   


}
