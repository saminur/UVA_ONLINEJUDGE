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
#define NIL -1
using namespace std;
#define M 26
int** floyd(int* resultMatrix[M],int* costMatrix[M])
{
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<M; j++)
        {
            resultMatrix[i][j]=costMatrix[i][j];
        }
    }
    for(int i=0; i<M; i++)
    {
        resultMatrix[i][i]=0;
    }
    for(int k=0; k<M; k++)
    {
        for(int i=0; i<M; i++)
        {
            for(int j=0; j<M; j++)
            {
                if(resultMatrix[i][k]+resultMatrix[k][j]<resultMatrix[i][j])
                {
                    resultMatrix[i][j]=resultMatrix[i][k]+resultMatrix[k][j];

                }
            }
        }
    }
    return resultMatrix;
}
class Graph
{
public:
    char person;
    char direction;
    char a;
    char b;
    int cost;
};
int main()
{
    freopen("in.txt","r",stdin);
    int edge;
    while(1)
    {
        cin>>edge;
        if(edge==0) break;
        int index=0;
        char person;
        char direction;
        char a,b;
        int cost;
        Graph g[edge];
        map<char,int> node;
        map<int,char> node2;
        for(int i=0; i<edge; i++)
        {
            cin>>person>>direction>>a>>b>>cost;
            node[a]=a-'A';
            node[b]=b-'A';
            node2[a-'A']=a;
            node2[b-'A']=b;
            g[i].person=person;
            g[i].direction=direction;
            g[i].a=a;
            g[i].b=b;
            g[i].cost=cost;
        }
        int sizeArray=node.size();
        int** costArray = new int*[M];
        int** costArray2 = new int*[M];
        int** resultArray = new int*[M];
        int** resultArray2 = new int*[M];
        for (int i = 0; i < M; ++i)
        {
            costArray[i] = new int[M];
            costArray2[i] = new int[M];
            resultArray[i]= new int[M];
            resultArray2[i]= new int[M];
        }
        for(int i=0; i<M ; i++)
        {
            for(int j=0; j<M; j++)
            {
                costArray[i][j]=INF;
                costArray2[i][j]=INF;
            }
        }
        for(int i=0; i<edge; i++)
        {
            //cout<<g[i].person<<endl;
            //cout<<g[i].direction<<endl;
            if(g[i].person=='Y')
            {

                if(g[i].direction=='U')
                {
                    //cout<<"inner if:"<<endl;
                    if(costArray[node[g[i].a]][node[g[i].b]]!=INF
                            && costArray[node[g[i].a]][node[g[i].b]]<g[i].cost)
                    {
                        //cout<<"inner inner if:"<<endl;
                        continue;
                    }
                    costArray[node[g[i].a]][node[g[i].b]]=g[i].cost;
                }
                else
                {
                    //cout<<"inner else:"<<endl;
                    if(costArray[node[g[i].a]][node[g[i].b]]!=INF
                            && costArray[node[g[i].a]][node[g[i].b]]<g[i].cost)
                    {
                        //cout<<"inner inner if:"<<endl;
                        costArray2[node[g[i].a]][node[g[i].b]]=g[i].cost;
                        continue;
                    }
                    costArray[node[g[i].a]][node[g[i].b]]=g[i].cost;
                    costArray[node[g[i].b]][node[g[i].a]]=g[i].cost;
                }
            }
            else
            {
                if(g[i].direction=='U')
                {
                    if(costArray2[node[g[i].a]][node[g[i].b]]!=INF
                            && costArray2[node[g[i].a]][node[g[i].b]]<g[i].cost)
                    {
                        //cout<<"inner inner if:"<<endl;
                        continue;
                    }

                    costArray2[node[g[i].a]][node[g[i].b]]=g[i].cost;
                }
                else
                {
                    //cout<<"inner else:"<<endl;
                    if(costArray2[node[g[i].a]][node[g[i].b]]!=INF
                            && costArray2[node[g[i].a]][node[g[i].b]]<g[i].cost)
                    {
                        //cout<<"inner inner if:"<<endl;
                        costArray2[node[g[i].a]][node[g[i].b]]=g[i].cost;
                        continue;
                    }
                    costArray2[node[g[i].a]][node[g[i].b]]=g[i].cost;
                    costArray2[node[g[i].b]][node[g[i].a]]=g[i].cost;
                }
            }
        }
        resultArray=floyd(resultArray,costArray);
        resultArray2=floyd(resultArray2,costArray2);

        char src,src2;
        cin>>src>>src2;
        bool flag=false;
        int sum=0;
        for(int i=0; i<M; i++)
        {
            if(resultArray[node[src]][i]==INF ||resultArray2[node[src2]][i]==INF) continue;
            else
            {
                flag=true;
                sum=sum+resultArray[node[src]][i]+resultArray2[node[src2]][i];
                cout<<sum<<' '<<node2[i];
            }
        }
        if(flag==true) cout<<endl;
        if(flag==false)
        {
            cout<<"You will never meet."<<endl;
        }

    }
    return 0;
}

