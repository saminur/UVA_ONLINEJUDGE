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

#define INF 99999
using namespace std;
#define nodesize 101

int floyd(int FinalMatrix[][nodesize],int costMatrix[][nodesize])
{
    int i,j,k;
    for(i=0; i<nodesize; i++)
    {
        for(j=0; j<nodesize; j++)
        {
            FinalMatrix[i][j]=costMatrix[i][j];
        }
    }
    for(i=0; i<nodesize; i++)
    {
        FinalMatrix[i][i]=0;
    }
    for(k=0; k<nodesize; k++)
    {
        for(i=0; i<nodesize; i++)
        {
            for(j=0; j<nodesize; j++)
            {
                if(FinalMatrix[i][k]+FinalMatrix[k][j]<FinalMatrix[i][j])
                {
                    FinalMatrix[i][j]=FinalMatrix[i][k]+FinalMatrix[k][j];
                }
            }
        }
    }
    int sum=0;
    for(int i=0; i<nodesize; i++)
    {
        for(int j=0; j<nodesize; j++)
        {
            if(FinalMatrix[i][j]==INF) continue;
            sum=sum+FinalMatrix[i][j];
        }
    }
    return sum;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int u,v,iu,iv;
    int FinalMatrix[nodesize][nodesize];
    int costMatrix[nodesize][nodesize];
    int fallen[nodesize];
    int maxNode;
    int cases=0;
    while(scanf("%d %d",&u,&v) && u!=0 && v!=0)
    {
        for(int i=0; i<nodesize; i++)
        {
            fallen[i]=0;
            for(int j=0; j<nodesize; j++)
            {

                costMatrix[i][j]=INF;

            }
        }
        costMatrix[u-1][v-1]=1;
        fallen[u-1]=1;
        fallen[v-1]=1;
        while(scanf("%d %d",&iu,&iv) && iu!=0 && iv!=0)
        {
            costMatrix[iu-1][iv-1]=1;
            fallen[iu-1]=1;
            fallen[iv-1]=1;
        }
        int totalPage=floyd(FinalMatrix,costMatrix);
        maxNode=0;
        for(int i=0;i<nodesize;i++)
        {
            if(fallen[i]) maxNode++;
        }
        int countValue=maxNode*(maxNode-1);
        float res=totalPage*1.00/countValue;
        printf("Case %d: average length between pages = %.3lf clicks\n",++cases,res);
    }
    return 0;
}
