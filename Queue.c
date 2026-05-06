#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct{
    int x;
    int y;
}Position;

typedef struct{
    Position *pos;
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
void enqueue(Position,Queue*);
Position dequeue(Queue*);
Position peek(Queue*);
void display(Queue*);
void clearQueue(Queue*);


int main(){
    Queue *queue=createQueue(2);

    printf("%s",emptyQueue(queue) ? "true" : "false");

    int dx[]={0,0,1,-1};
    int dy[]={-1,1,0,0};

    for(int i=0;i<4;i++){
        enqueue((Position){dx[i],dy[i]},queue);
    }

    display(queue);
    printf("x:%d\ny:%d\n",peek(queue).x,peek(queue).y);

    for(int i=0;i<3;i++){
        Position pos=dequeue(queue);
    }
    display(queue);

    for(int i=0;i<4;i++){
        enqueue((Position){dx[i],dy[i]},queue);
    }

    display(queue);

    clearQueue(queue);
    display(queue);

    return 1;
}

Queue* createQueue(int capacity){
    Queue *queue=malloc(sizeof(Queue));

    queue->pos=malloc(capacity * sizeof(Position));
    queue->cap=capacity;
    queue->front=0;
    queue->size=0;

    return queue;
}

bool nullQueue(Queue *queue){
    if(queue->pos==NULL){
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
    Position *newpos=malloc(newcap*sizeof(Position));

    for (int i=0; i<queue->size;i++){
        newpos[i]=queue->pos[(queue->front+i)%queue->cap];
    }

    free(queue->pos);
    queue->pos=newpos;
    queue->cap=newcap;
    queue->front=0;
}

void sizedown(Queue *queue){
    int newcap=queue->size+2;
    Position *newpos=malloc(newcap*sizeof(Position));

    for(int i=0;i<queue->size;i++){
        newpos[i]=queue->pos[(queue->front+i)%queue->cap];
    }

    free(queue->pos);
    queue->pos=newpos;
    queue->cap=newcap;
    queue->front=0;
}

void enqueue(Position pos,Queue *queue){
    if(nullQueue(queue)){
        queue=createQueue(2);
    }

    if(fullQueue(queue)){
        sizeup(queue);
    }

    int rear=(queue->front+queue->size)%queue->cap;
    queue->pos[rear].x=pos.x;
    queue->pos[rear].y=pos.y;
    queue->size++;
}

Position dequeue(Queue *queue){
    if(emptyQueue(queue) || nullQueue(queue)){
        return (Position){INT_MIN,INT_MIN};
    }
    if(queue->size<=queue->cap/3){
        sizedown(queue);
    }

    Position pos=queue->pos[queue->front];
    queue->front=(queue->front + 1)%queue->cap;
    queue->size--;

    return pos;
}

Position peek(Queue *queue){
    if(emptyQueue(queue) || nullQueue(queue)){
        return (Position){INT_MIN,INT_MIN};
    }
    return queue->pos[queue->front];
}

void display(Queue *queue){
    if(emptyQueue(queue) || nullQueue(queue)){
        printf("empty queue\n");
        return;
    }

    printf("[");
    for(int i=queue->front,counter=0;counter<queue->size-1;i=(i+1)%queue->cap,counter++){
        printf("%d ",queue->pos[i].x);
    }
    printf("%d]\n",queue->pos[(queue->front+queue->size-1)%queue->cap].x); //prints last element

    printf("[");
    for(int i=queue->front,counter=0;counter<queue->size-1;i=(i+1)%queue->cap,counter++){
        printf("%d ",queue->pos[i].y);
    }
    printf("%d]",queue->pos[(queue->front+queue->size-1)%queue->cap].y); //prints last element

}

void clearQueue(Queue *queue){
    free(queue->pos);
    queue->pos=NULL;
}