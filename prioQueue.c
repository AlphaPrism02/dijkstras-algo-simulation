#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct PriorityQueue{
    int item;
    struct PriorityQueue *next;
}PriorityQueue;

void addItem(int,PriorityQueue**);
int removeItem(int,PriorityQueue*);
int popItem(PriorityQueue**);
void displayQueue(PriorityQueue);

void main(){
    PriorityQueue *n1 = malloc(sizeof(PriorityQueue));
    PriorityQueue *n2 = malloc(sizeof(PriorityQueue));
    PriorityQueue *n3 = malloc(sizeof(PriorityQueue));
    PriorityQueue *n4 = malloc(sizeof(PriorityQueue));
    PriorityQueue *n5 = malloc(sizeof(PriorityQueue));

    n1->item = 1; n1->next = n2;
    n2->item = 2; n2->next = n3;
    n3->item = 6; n3->next = n4;
    n4->item = 7; n4->next = n5;
    n5->item = 8; n5->next = NULL;

    addItem(4,&n1);
    addItem(3,&n1);
    addItem(0,&n1);
    addItem(10,&n1);

    int del=removeItem(3,n1);
    //int popped=popItem(&n1);

    displayQueue(*n1);
}

void addItem(int item,PriorityQueue **prioQueue){
    if((*prioQueue)->item==INT_MIN){
        (*prioQueue)->item=item;
        (*prioQueue)->next=NULL;
    }
    else if((*prioQueue)->item>item){
        PriorityQueue *currItem=malloc(sizeof(PriorityQueue));
        currItem->item=item; 
        currItem->next=*prioQueue;
        *prioQueue=currItem;
    }
    else{
        PriorityQueue *currItem=*prioQueue;
        PriorityQueue *prev=NULL,*next=NULL;
        while(currItem->next!=NULL){
            if(currItem->next->item>item){
                prev=currItem;
                next=currItem->next;
                currItem->next=malloc(sizeof(PriorityQueue));
                currItem->next->item=item;
                currItem=currItem->next;
                currItem->next=next;
                return;
            }
            currItem=currItem->next;
        }
        currItem->next=malloc(sizeof(PriorityQueue));
        currItem->next->item=item;
        currItem->next->next=NULL;
    }
}

int removeItem(int item,PriorityQueue *prioQueue){
    if(prioQueue->item==INT_MIN){
        printf("empty");
        return INT_MIN;
    }

    PriorityQueue *currItem=prioQueue;
    PriorityQueue *prev=NULL,*next=NULL;

    if(currItem->item==item){
        currItem=currItem->next;
    }

    while(currItem->next!=NULL){
        prev=currItem;
        next=currItem->next->next;
        if(currItem->next->item==item){
            prev->next=next;
            return item;
        }
        currItem=currItem->next;
    }

    printf("not found");
    return INT_MAX;
}

int popItem(PriorityQueue **prioQueue){
    if((*prioQueue)->item==INT_MIN){
        printf("Queue is empty");
        return INT_MIN;
    }
    PriorityQueue *popped=*prioQueue;
    int item=popped->item;
    *prioQueue=popped->next;
    free(popped);
    return item;
}

void displayQueue(PriorityQueue prioQueue){
    if(prioQueue.item==INT_MIN){
        printf("Queue is empty\n");
        return;
    }
    
    while(prioQueue.next!=NULL){
        printf("%d ",prioQueue.item);
        prioQueue=*(prioQueue.next);
    }
    printf("%d\n",prioQueue.item);
}