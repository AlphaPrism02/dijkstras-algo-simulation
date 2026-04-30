#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct PriorityQueue{
    int item;
    struct PriorityQueue *next;
}PriorityQueue;

PriorityQueue** createPriorityQueue();
void addItem(int,PriorityQueue**);
int removeItem(int,PriorityQueue**);
int popItem(PriorityQueue**);
int peekItem(PriorityQueue);
void displayQueue(PriorityQueue);

void main(){
    PriorityQueue **prioQueue=createPriorityQueue();

    addItem(4,prioQueue);
    addItem(3,prioQueue);
    addItem(0,prioQueue);
    addItem(10,prioQueue);

    int del=removeItem(0,prioQueue);
    //int popped=popItem(prioQueue);

    displayQueue(**prioQueue);
}

PriorityQueue** createPriorityQueue(){
    PriorityQueue **prioQueue=malloc(sizeof(PriorityQueue*));
    PriorityQueue *n1=malloc(sizeof(PriorityQueue));
    n1->item=INT_MIN;
    n1->next=NULL;
    *prioQueue=n1;
    return prioQueue;
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

int removeItem(int item,PriorityQueue **prioQueue){
    if((*prioQueue)->item==INT_MIN){
        printf("empty");
        return INT_MIN;
    }

    PriorityQueue *currItem=*prioQueue;
    PriorityQueue *prev=NULL,*next=NULL;

    if(currItem->item==item){
        *prioQueue=currItem->next;
        return item;
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

int peekItem(PriorityQueue prioQueue){
    return prioQueue.item;
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