#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct{
    int *arr;
    int front;
    int cap;  //total capacity
    int size; //current amount of items
}Queue;

Queue* createQueue(int);
bool nullQueue(Queue*);
bool emptyQueue(Queue*);
bool fullQueue(Queue*);
void sizeup(Queue*);
void sizedown(Queue*);
void enqueue(int,Queue*);
int dequeue(Queue*);
int peek(Queue*);
void display(Queue*);
void clearQueue(Queue*);


int main(){
    Queue *queue=createQueue(15);

    printf("%s",emptyQueue(queue) ? "true" : "false");

    for(int i=0;i<30;i++){
        enqueue(i,queue);
    }

    display(queue);
    printf("%d\n",peek(queue));

    for(int i=0;i<20;){
        i=dequeue(queue);
    }
    display(queue);

    for(int i=0;i<10;i++){
        enqueue(i,queue);
    }

    display(queue);

    clearQueue(queue);
    display(queue);

    return 1;
}

Queue* createQueue(int capacity){
    Queue *queue=malloc(sizeof(Queue));

    queue->arr=malloc(capacity * sizeof(int));
    queue->cap=capacity;
    queue->front=0;
    queue->size=0;

    return queue;
}

bool nullQueue(Queue *queue){
    if(queue->arr==NULL){
        return true;
    }
    return false;
}

bool emptyQueue(Queue *queue){
    if(nullQueue(queue)){
        return true;
    }
    if(queue->size==0){
        return true;
    }
    return false;
}

bool fullQueue(Queue *queue){
    if(queue->size==queue->cap){
        return true;
    }
    return false;
}

void sizeup(Queue *queue){
    int newcap=queue->cap*2;
    int *newArr=malloc(newcap*sizeof(int));

    for (int i=0; i<queue->size;i++){
        newArr[i]=queue->arr[(queue->front+i)%queue->cap];
    }

    free(queue->arr);
    queue->arr=newArr;
    queue->cap=newcap;
    queue->front=0;
}

void sizedown(Queue *queue){
    int newcap=queue->size+2;
    int *newArr=malloc(newcap*sizeof(int));

    for(int i=0;i<queue->size;i++){
        newArr[i]=queue->arr[(queue->front+i)%queue->cap];
    }

    free(queue->arr);
    queue->arr=newArr;
    queue->cap=newcap;
    queue->front=0;
}

void enqueue(int item,Queue *queue){
    if(nullQueue(queue)){
        queue=createQueue(2);
    }

    if(fullQueue(queue)){
        sizeup(queue);
    }

    int rear=(queue->front+queue->size)%queue->cap;
    queue->arr[rear]=item;
    queue->size++;
}

int dequeue(Queue *queue){
    if(emptyQueue(queue) || nullQueue(queue)){
        return INT_MIN;
    }
    if(queue->size<=queue->cap/3){
        sizedown(queue);
    }

    int item=queue->arr[queue->front];
    queue->front=(queue->front + 1)%queue->cap;
    queue->size--;

    return item;
}

int peek(Queue *queue){
    if(emptyQueue(queue) || nullQueue(queue)){
        return INT_MIN;
    }
    return queue->arr[queue->front];
}

void display(Queue *queue){
    if(emptyQueue(queue) || nullQueue(queue)){
        printf("empty queue\n");
        return;
    }

    for(int i=queue->front,counter=0;counter<queue->size;i=(i+1)%queue->cap,counter++){
        printf("%d ",queue->arr[i]);
    }

}

void clearQueue(Queue *queue){
    free(queue->arr);
    queue->arr=NULL;
}