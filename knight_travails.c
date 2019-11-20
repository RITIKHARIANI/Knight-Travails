//Program to find the shortest sequence of paths taken by a knight from source to destination vertex
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define N 8
typedef struct Node
{
    int x;
    int y;
    int distance;
}Node;

//valid movement of the knight
int row[] = {-2, -1, 1, 2, -2, -1, 1, 2}; 
int col[] = {-1, -2, -2, -1, 1, 2, 2, 1}; 

int visit[N+1][N+1] = {{0}};
Node q[1000];
int front = -1;
int rear = -1;
int top = -1;

int mapCoordsToIndex(int x, int y) //hash code conversion
{
    return y*8 + x;
}

int isValid(int x, int y) 
{
    //checking if the coordinate given doesnt go out of the chess board
    if(x >= 1 && x <= N && y >= 1 && y <= N)
        return 1; 
    return 0;
}

void enqueue(int x, int y, int distance)
{
    if(front==-1)    
        front=0;            
    rear++;
    q[rear].x=x;
    q[rear].y=y;
    q[rear].distance=distance;
}
void dequeue()
{
    if(front == rear)
        front = rear = -1;
    else    
        front++;
}

int qisempty()
{
    if(rear==-1 && front ==-1)    
        return 1;    
    return 0;
}

void push(int index,  int *stack)
{
    top++;
    stack[top] = index;
}

void pop()
{
    top--;
}

int getX(int index) //extracts and returns the X coordinate
{
    return (index % 8) + 1;
}
int getY(int index) //extracts and returns the Y coordinate
{    
    return (index / 8) + 1;
}

void bfs(int sx, int sy, int dx, int dy)
{
    Node t;
    int x, y;
    enqueue(sx, sy, 0); //adding starting position of knight to the queue with 0 distance travelled
    //visited starting position
    visit[sx][sy] = 1;
    int map[64] = {0}; 
    //using array of size 64 to simulate map, using the encoding i*8+j to store the respective pairs
    //looping until queue is empty
    while(!qisempty())
    {   
        t = q[front];
        dequeue();     
        if(t.x == dx && t.y == dy)
        {
            // to do when the index is found
            printf("Total moves needed to be taken : %d \n", t.distance);
            int stack[1000];
            push(mapCoordsToIndex(t.x-1, t.y-1),stack);            
            if(t.distance != 0) //when source and destination are not the same
            {                
                for(int i = mapCoordsToIndex(t.x-1, t.y-1);  ; i = mapCoordsToIndex(t.x-1, t.y-1)) 
                {
                    if(!(getX(map[i]) == sx && getY(map[i]) == sy)) //if not equal to source , then continue
                    {                        
                        t.x = getX(map[i]);
                        t.y = getY(map[i]);                        
                        push(mapCoordsToIndex(t.x-1, t.y-1),stack);
                    }
                    else
                        break;
                }
            }
            printf("path : (%d,%d) ",sx,sy);
            for (; top != -1; pop())            
                printf("-> (%d,%d) ",getX(stack[top]) ,getY(stack[top]));                            
            printf("\n\n");
            return;        
        }
        
        for(int i=0;i<8;i++) //knights movements
        {               
            x = t.x + row[i];
            y = t.y + col[i];            
            if(isValid(x,y) && !visit[x][y])
            {
                visit[x][y] = 1;                
                enqueue(x, y, t.distance + 1);
                map[mapCoordsToIndex(x-1, y-1)] = mapCoordsToIndex(t.x-1, t.y-1);
                //maps each next coordinate with next coordinate
            }
        }
    }
}

int main()
{
    //Destination coordinates
    int dx,dy;
    //Source coordinates
    int sx,sy;
    printf("Enter the Source Coordinates (x,y), where x and y are numbers between 1 and 8: \n");
    scanf("%d%d",&sx,&sy);
    printf("Enter the Destiation Coordinates (x,y), where x and y are numbers between 1 and 8: \n");
    scanf("%d%d",&dx,&dy);
    if((isValid(sx,sy) && isValid(dx,dy)))
        bfs(sx,sy,dx,dy);
    else
        printf("Wrong input!\n");

    return 0;
}