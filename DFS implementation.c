#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int pathfinder(int[11][11],int,int,int);
bool pathLeft(int[11][11],int,int);

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

    printf("%d",pathfinder(grid,0,0,0));

    return 0;
}

int pathfinder(int grid[11][11],int depth,int x,int y)
{
    static int bestPath;
    if(x==0 && y==0 && grid[x][y]==0){bestPath=INT_MAX;}

    grid[x][y]=2;
    do
    {
        if(x==10 && y==10) //reached end
        {
            bestPath=(depth<bestPath)?depth:bestPath;
            return --depth;
        }

        if(y+1 < 11 && grid[x][y+1] == 0){depth=pathfinder(grid,depth+1,x,y+1);}
        if(y-1 >= 0 && grid[x][y-1] == 0){depth=pathfinder(grid,depth+1,x,y-1);}
        if(x+1 < 11 && grid[x+1][y] == 0){depth=pathfinder(grid,depth+1,x+1,y);}
        if(x-1 >= 0 && grid[x-1][y] == 0){depth=pathfinder(grid,depth+1,x-1,y);}
    }while(pathLeft(grid,x,y));

    if(x==0 && y==0 && grid[x][y]==2){return bestPath;} //if start is 0, then all paths are covered
    return --depth;
}

bool pathLeft(int grid[11][11], int x, int y)
{
    if ((y+1 < 11 && grid[x][y+1] == 0) ||
        (y-1 >= 0 && grid[x][y-1] == 0) ||
        (x+1 < 11 && grid[x+1][y] == 0) ||
        (x-1 >= 0 && grid[x-1][y] == 0))
    {
        return true;
    }
    return false;
}