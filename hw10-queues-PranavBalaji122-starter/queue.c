#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    
    size_t sterlized_game = serialize(state);
    insert_at_tail(&q->data,sterlized_game);

}

struct game_state dequeue(struct queue *q) { 
    size_t value_removed = remove_from_head(&q->data);
    return(deserialize(value_removed));
}


int number_of_moves(struct game_state start) { 
    struct queue q;
    q.data.head = NULL;
    struct linked_list visited;
    visited.head = NULL;

    enqueue(&q,start);
    while(q.data.head != NULL){
        struct game_state cur = dequeue(&q);
        size_t cur_id = serialize(cur);
        // printf("%d ", cur.empty_row);
        // printf("%d\n", cur.empty_col);
        
        int skip_node = 0;
        for(struct list_node *node = visited.head; node != NULL; node = node->next){
            if(node->value == cur_id){
                skip_node = 1;
                break;
            }
        }
        if(skip_node != 1){ 
            insert_at_head(&visited, cur_id); 
            int finished = 1;
            int counter = 1;
            for (int i = 0; i < 4 && finished; i++) {
                for (int j = 0; j < 4 && finished; j++) {
                    if (i == 3 && j == 3) {
                        if (cur.tiles[i][j] != 0) {
                            finished = 0;
                        }
                    } else {
                        if (cur.tiles[i][j] != counter) {
                            
                            finished = 0;
                        }
                        counter++;
                    }
                }
            }
            if (finished) {
                free_list(visited);
                free_list(q.data);
                return cur.num_steps; 
            }


            struct game_state new_state;
            if(cur.empty_row > 0){
                    new_state = cur;
                    move_down(&new_state);
                    enqueue(&q,new_state);
            }
            if(cur.empty_row < 3){
                    new_state = cur;
                    move_up(&new_state);
                    enqueue(&q,new_state);
            }
            if(cur.empty_col > 0){
                    new_state = cur;
                    move_right(&new_state);

                    enqueue(&q,new_state);
            }
            if(cur.empty_col < 3){
                    new_state = cur;
                    move_left(&new_state);

                    enqueue(&q,new_state);
            }
            }
        }
    free_list(q.data);
    free_list(visited);
    return -1; 

}
