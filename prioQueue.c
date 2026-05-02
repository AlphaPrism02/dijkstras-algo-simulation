#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node{
    int item;
    struct Node *next;
}Node;

typedef struct{
    Node *head;
    int len;
}PriorityQueue;

PriorityQueue* createPriorityQueue();
bool emptyQueue(PriorityQueue*);
void addItem(int,PriorityQueue*);
int removeItem(int,PriorityQueue*);
int popItem(PriorityQueue*);
int peekItem(PriorityQueue*);
bool containsItem(int,PriorityQueue*);
void displayQueue(PriorityQueue*);
void clearQueue(PriorityQueue*);

void main(){
    PriorityQueue *prioQueue=createPriorityQueue();
    
    printf("%s",emptyQueue(prioQueue) ? "true" : "false");

    addItem(4,prioQueue);
    addItem(3,prioQueue);
    addItem(0,prioQueue);
    addItem(10,prioQueue);
    addItem(1,prioQueue);
    addItem(6,prioQueue);
    addItem(2,prioQueue);
    addItem(5,prioQueue);
    addItem(8,prioQueue);

    displayQueue(prioQueue);
    
    int del=removeItem(4,prioQueue);
    int popped=popItem(prioQueue);

    printf("%d",peekItem(prioQueue));

    printf("%s",containsItem(10,prioQueue) ? "true" : "false");

    displayQueue(prioQueue);

    clearQueue(prioQueue);
    displayQueue(prioQueue);
}

PriorityQueue* createPriorityQueue(){
    PriorityQueue *prioQueue=malloc(sizeof(PriorityQueue));
    prioQueue->head=NULL;
    prioQueue->len=0;
    return prioQueue;
}

bool emptyQueue(PriorityQueue *prioQueue){
    if(prioQueue->head==NULL){
        return true;
    }
    return false;
}

void addItem(int item,PriorityQueue *prioQueue){
    if(emptyQueue(prioQueue)){
        prioQueue->head=malloc(sizeof(Node));
        prioQueue->head->item=item;
        prioQueue->head->next=NULL;

        prioQueue->len++;
        return;
    }
    if(prioQueue->head->item>item){
        Node *currNode=malloc(sizeof(Node));
        currNode->item=item; 
        currNode->next=prioQueue->head;
        prioQueue->head=currNode;

        prioQueue->len++;
        return;
    }

    Node *currNode=prioQueue->head;
    Node *next=NULL;
    while(currNode->next!=NULL){
        if(currNode->next->item>item){
            next=currNode->next;
            currNode->next=malloc(sizeof(Node));
            currNode->next->item=item;
            currNode=currNode->next;
            currNode->next=next;

            prioQueue->len++;
            return;
        }
        currNode=currNode->next;
    }
    currNode->next=malloc(sizeof(Node));
    currNode->next->item=item;
    currNode->next->next=NULL;
    prioQueue->len++;
}

int removeItem(int item,PriorityQueue *prioQueue){
    if(emptyQueue(prioQueue)){
        printf("empty");
        return INT_MIN;
    }

    Node *currNode=prioQueue->head;
    Node *next=NULL;

    if(currNode->item==item){
        prioQueue->head=currNode->next;
        prioQueue->len--;

        free(currNode);
        return item;
    }

    while(currNode->next!=NULL){
        next=currNode->next->next;
        if(currNode->next->item==item){
            Node *toFree=currNode->next;
            currNode->next=next;
            prioQueue->len--;

            free(toFree);
            return item;
        }
        currNode=currNode->next;
    }

    printf("not found");
    return INT_MAX;
}

int popItem(PriorityQueue *prioQueue){
    if(emptyQueue(prioQueue)){
        printf("Queue is empty");
        return INT_MIN;
    }

    Node *popped=prioQueue->head;
    int item=popped->item;
    prioQueue->head=popped->next;
    prioQueue->len--;

    free(popped);
    return item;
}

int peekItem(PriorityQueue *prioQueue){
    if(emptyQueue(prioQueue)){
        printf("Queue is empty\n");
        return INT_MIN;
    }

    return prioQueue->head->item;
}

bool containsItem(int item,PriorityQueue *prioQueue){
    if(emptyQueue(prioQueue)){
        return false;
    }

    Node node=*(prioQueue->head);
    while(node.next!=NULL){
        if(node.item==item){
            return true;
        }
        node=*(node.next);
    }
    if(node.item==item){
        return true;
    }

    return false;
}

void displayQueue(PriorityQueue *prioQueue){
    if(emptyQueue(prioQueue)){
        printf("Queue is empty\n");
        return;
    }

    Node node=*(prioQueue->head);
    
    while(node.next!=NULL){
        printf("%d ",node.item);
        node=*(node.next);
    }
    printf("%d\n",node.item);
}

void clearQueue(PriorityQueue *prioQueue){
    Node *curr = prioQueue->head;
    while(curr){
        Node *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    prioQueue->head = NULL;
    prioQueue->len  = 0;
}