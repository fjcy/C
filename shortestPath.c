#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct vertex
{
    int x;
    int y;
}Vertex;

int main()
{
    Vertex v[11], v_copy[11];
    int i, j, d, temp, next=0, total=0, min=0;

    v[0].x=0; v[0].y=0;
    srand((unsigned)time(NULL));
    for(i=1; i<11; i++)
    {
        v[i].x=rand()%101;
        v[i].y=rand()%101;
    }

    for(i=1; i<11; i++)
    {
        for(j=i+1; j<11; j++)
        {
            if((v[i].x==v[j].x)&&(v[i].y==v[j].y))
                v[j].x=rand()%101;
                v[j].y=rand()%101;
        }
    }

    for(i = 0; i < 11; i++)
    {
        v_copy[i].x=v[i].x;
        v_copy[i].y=v[i].y;
    }
    printf("10个点为: \n");
    for(i = 1; i < 11; i++)
    {
        printf("   %2d     (%2d, %2d)\n", i, v[i].x, v[i].y);
    }

    printf("\n最短路径为:0");
    next=0;
    for(i=0; i<11; i++)
    {
        min=999;
        for(j=1; j<11; j++)
        {
            d=distance(v[next], v_copy[j]);
            if(d<min)
            {
                    min=d;
                    temp=j;
            }
        }
        if(min<999)
        {
            total+=min;
            printf(" -> %d",temp);
        }
        v_copy[temp].x=999;
        v_copy[temp].y=999;
        next=temp;
    }
    printf(" -> 0\n");
    total+=distance(v[0],v[temp]);
    printf("\n总路程为:%d\n",total);
    return 0;
}

int distance(Vertex v, Vertex w)
{
    int delta_x,delta_y,result;
    delta_x=w.x-v.x;
    delta_y=w.y-v.y;
    result=sqrt(delta_x*delta_x + delta_y*delta_y);
    return result;
}
