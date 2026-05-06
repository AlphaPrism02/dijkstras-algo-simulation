#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include </workspaces/dijkstras-algo-simulation/Queue.c>

int bfs(int grid[11][11],Position endPos,Queue *queue);
void fillQueue(int grid[11][11],bool visited[11][11],Position currPos,Queue *queue);
bool moveAvailable(Position newPos,int grid[11][11],bool visited[11][11]);

int main()
{
    int grid[11][11] = {
        {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
    };

    Queue *queue=createQueue(1);
    Position startpos={0,0};
    enqueue(startpos,queue);
    Position endpos={10,10};
    printf("path length:%d",bfs(grid,endpos,queue));

    return 0;
}

int bfs(int grid[11][11],Position endPos,Queue *queue){
    bool visited[11][11]={false};
    int depth=0;
    visited[0][0] = true;
    
    while(!emptyQueue(queue)){
        int noOfNodes=queue->size;

        for(int i=0;i<noOfNodes;i++){
            if(peek(queue).x==endPos.x && peek(queue).y==endPos.y){
                return depth;
            }

            Position pos=dequeue(queue);
            fillQueue(grid,visited,pos,queue);
        }
        depth++;
    }
    
    return INT_MIN;
}

void fillQueue(int grid[11][11],bool visited[11][11],Position currPos,Queue *queue){
    int dx[]={0,0,1,-1};
    int dy[]={-1,1,0,0};

    for(int i=0;i<4;i++){
        Position newPos=(Position){currPos.x+dx[i],currPos.y+dy[i]};
        if(moveAvailable(newPos,grid,visited)){
            enqueue(newPos,queue);
            visited[newPos.x][newPos.y]=true;
        }
    }
}

bool moveAvailable(Position newPos,int grid[11][11],bool visited[11][11]){
    if( newPos.x >= 0 && newPos.x < 11 &&
        newPos.y >= 0 && newPos.y < 11 &&
        visited[newPos.x][newPos.y]==false && grid[newPos.x][newPos.y]!=1){
        return true;
    }
    return false;
}