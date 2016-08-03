#include<iostream>
#include<cstdio>
#include<list>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include<map>
#include<stack>

#define INF 1000000
#define NIL -1
using namespace std;
#define M 26
int costArray [26][26];
int costArray2[26][26];

int main()
{
    //freopen("in.txt","r",stdin);
    int edge;
    while(1)
    {
        cin>>edge;
        int sum=INF;
        if(edge==0) break;
        char person,direction,a,b;
        int cost;
        for(int i=0; i<M ; i++)
        {
            for(int j=0; j<M; j++)
            {
                costArray[i][j]=INF;
                costArray2[i][j]=INF;
            }
        }
        for(int i=0; i<M; i++)
        {
            costArray[i][i]=costArray2[i][i]=0;
        }
        for(int i=0; i<edge; i++)
        {
            cin>>person>>direction>>a>>b>>cost;
            if(person=='Y')
            {

                if(direction=='U')
                {
                    //cout<<"inner if:"<<endl;
                    if(cost<costArray[a-'A'][b-'A'])
                    {
                        costArray[a-'A'][b-'A']=cost;
                    }
                }
                else
                {
                    //cout<<"inner else:"<<endl;
                    if(cost<costArray[a-'A'][b-'A'])
                    {
                        costArray[a-'A'][b-'A']=cost;
                    }
                    if(cost<costArray[b-'A'][a-'A'])
                    {
                        costArray[b-'A'][a-'A']=cost;
                    }
                }
            }
            else
            {
                if(direction=='U')
                {
                    //cout<<"inner if:"<<endl;
                    if(cost<costArray2[a-'A'][b-'A'])
                    {
                        costArray2[a-'A'][b-'A']=cost;
                    }
                }
                else
                {
                    //cout<<"inner else:"<<endl;
                    if(cost<costArray2[a-'A'][b-'A'])
                    {
                        costArray2[a-'A'][b-'A']=cost;
                    }
                    if(cost<costArray2[b-'A'][a-'A'])
                    {
                        costArray2[b-'A'][a-'A']=cost;
                    }
                }
            }
        }
        for(int k=0; k<M; k++)
        {
            for(int i=0; i<M; i++)
            {
                for(int j=0; j<M; j++)
                {
                    if(costArray[i][k]+costArray[k][j]<costArray[i][j])
                    {
                        costArray[i][j]=costArray[i][k]+costArray[k][j];

                    }
                    if(costArray2[i][k]+costArray2[k][j]<costArray2[i][j])
                    {
                        costArray2[i][j]=costArray2[i][k]+costArray2[k][j];

                    }
                }
            }
        }
        char src,src2;
        cin>>src>>src2;
        for(int i=0; i<M; i++)
        {
            if(costArray[src-'A'][i]+costArray2[src2-'A'][i]<sum)
            {
                sum=costArray[src-'A'][i]+costArray2[src2-'A'][i];
            }
        }
        if(sum<INF)
        {
            printf("%d",sum);

            for (int i=0; i<M; ++i)
                if (costArray[src-'A'][i]+costArray2[src2-'A'][i]==sum)
                    printf(" %c",i+'A');
            printf("\n");
        }
        else
            printf("You will never meet.\n");

    }
    return 0;
}

