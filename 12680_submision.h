#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;

Node* ReadOneList(){

    //allocate a handler
    Node *tmp;
    tmp = (Node *)malloc(sizeof(Node));

    //read the amount of data
    int size = 0;
    scanf("%d: ", &size);
    
    //allocate array (as a piece contiguous memory) for all data
    int *data;
    data = (int *)malloc(size * sizeof(int));

    //read and write through data to "data[]" one by one
    int t;
    for (int i = 0; i < size; i++){
        scanf("%d", &t);
        data[i] = t;
    }

    //update info.
    tmp->size = size;
    tmp->data = data;
    tmp->next = NULL;

    return tmp;
}


void PrintList(Node* head){

    //use curnode and prev to record progress
    Node *curnode = head->next;
    Node *prev = head;

    //print one by one
    while (curnode != NULL)
    {
        //due to presentation request, have to seperate first data from the folllowing
        printf("%d", curnode->data[0]);
        for (int i = 1; i < curnode->size; i++){
            printf(" %d", curnode->data[i]);
        }
        printf("\n");
        free(prev);
        prev = curnode;
        curnode = curnode->next;
    }
    
    //release memory space
    free(curnode);
    free(head);
}

void Merge(Node* head, int x, int y){

    //case1: x==y
    if(x==y)
        return;

    Node *prev_x, *cur_x;
    Node *prev_y, *cur_y;
    prev_x = prev_y = head;
    cur_x = cur_y = head->next;

    //move to the target list x
    x--;
    while(x-- && cur_x->next != NULL){
        prev_x = prev_x->next;
        cur_x = cur_x->next;
    }

    //move to the target list y
    y--;
    while (y-- && cur_y->next != NULL)
    {
        prev_y = prev_y->next;
        cur_y = cur_y->next;
    }

    //if cur_x or cur_y is not arrive the target node however stop by end of the list
    if ( (cur_x->next==NULL && x>0) || (cur_y->next==NULL && y>0) )
        return;

    //dont name it "new" because it is reserved word
    Node *tmp;
    tmp = (Node *)malloc(sizeof(Node));

    //allocate space for data for merged node
    int *new_data;
    new_data = (int *)malloc( ((cur_x->size)+(cur_y->size)) * sizeof(int));
    
    //copy from old list to new list
    //must y first since we add x to y
    for (int i = 0; i < cur_y->size; i++){
        new_data[i] = cur_y->data[i];
        //printf("merge new data from y: %d ", new_data[i]); //debug
    }
    //printf("\n"); //debug
    for (int j = 0; j < cur_x->size; j++)
    {
        new_data[cur_y->size + j] = cur_x->data[j];  //notice: is 'y' not 'x'!!
        //printf("merge new data from x: %d", new_data[new_data[cur_x->size + j]]); //debug
    }
    //printf("\n"); //debug

    //update info.
    int new_size = cur_x->size + cur_y->size;

    tmp->data = new_data;
    tmp->size = new_size;

    //update links
    //case2: distance(x,y)=1 && x<y
    if (cur_x == prev_y){
        tmp->next = cur_y->next;
        prev_x->next = tmp;
    }

    //case3: distance(x,y)=1 && x>y
    else if (cur_y == prev_x){
        tmp->next = cur_x->next;
        prev_y->next = tmp;
    }

    //case4: distance(x,y)>0
    else{
        tmp->next = cur_y->next;
        prev_y->next = tmp;
        prev_x->next = cur_x->next;
    }

    free(cur_x->data);
    free(cur_y->data);
    free(cur_x);
    free(cur_y);
}

void Cut(Node* head, int x, int y){
    Node *cur = head; //dummy_head
    Node *prev;

    //go to the target node
    while (x--)
    {
        prev = cur;
        cur = cur->next;
    }

    //allocate for 2 new node for cutted node
    Node *new1;
    Node *new2;
    new1 = (Node *)malloc(sizeof(Node));
    new1->data = (int *)malloc(sizeof(int) * y);
    
    new2 = (Node *)malloc(sizeof(Node));
    new2->data = (int *)malloc(sizeof(int) * (cur->size - y));

    //copy to new1
    for (int i = 0; i < y; i++){        
        new1->data[i] = cur->data[i];
        //printf("cut to new1: %d\n", new1->data[i]); //debug
    }
    //printf("\n"); //debug
    new1->size = y;

    //copy to new2
    for (int j = 0; j < (cur->size- y); j++){        
        new2->data[j] = cur->data[j+y];
        //printf("cut to new1: %d\n", new2->data[j]); //debug
    }
    //printf("\n"); //debug
    new2->size = (cur->size - y);

    //update info.
    prev->next = new1;
    new1->next = new2;
    new2->next = cur->next;

    free(cur->data);
    free(cur);
}

#endif