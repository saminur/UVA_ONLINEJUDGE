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

#define INF 100000
using namespace std;
int main()
{
    //freopen("in.txt","r",stdin);
    int testCase,nodeNum,edgeNum;
    int u,v,iu,iv;
    cin>>testCase;

    for(int tc=1; tc<=testCase; tc++)
    {
        int sum=0;
        cin>>nodeNum;
        cin>>edgeNum;
        int FinalMatrix[nodeNum][nodeNum];
        int costMatrix[nodeNum][nodeNum];
        int fallen[nodeNum];
        for(int i=0; i<nodeNum; i++)
        {
            fallen[i]=0;
            for(int j=0; j<nodeNum; j++)
            {
                costMatrix[i][j]=INF;
            }
        }
        for(int i=0; i<edgeNum; i++)
        {
            cin>>u>>v;
            costMatrix[u][v]=1;
            costMatrix[v][u]=1;
            fallen[u]=1;
            fallen[v]=1;
        }
        for(int i=0; i<nodeNum; i++)
        {
            for(int j=0; j<nodeNum; j++)
            {
                FinalMatrix[i][j]=costMatrix[i][j];
            }
        }
        for(int i=0; i<nodeNum; i++)
        {
            FinalMatrix[i][i]=0;
        }
        for(int k=0; k<nodeNum; k++)
        {
            for(int i=0; i<nodeNum; i++)
            {
                for(int j=0; j<nodeNum; j++)
                {
                    if(FinalMatrix[i][k]+FinalMatrix[k][j]<FinalMatrix[i][j])
                    {
                        FinalMatrix[i][j]=FinalMatrix[i][k]+FinalMatrix[k][j];
                    }
                }
            }
        }
        int maxValue=-222;
        cin>>iu>>iv;
        for(int i=0; i<nodeNum; i++)
        {
            if(FinalMatrix[iu][i]==INF) continue;
            if(maxValue<(FinalMatrix[iu][i]+FinalMatrix[i][iv]))
            {
                maxValue=FinalMatrix[iu][i]+FinalMatrix[i][iv];
            }
        }
        printf("Case %d: %d\n",tc,maxValue);
    }
    return 0;
}
