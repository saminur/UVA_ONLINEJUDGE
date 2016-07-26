#include<iostream>
#include<cstdio>
#include<list>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

#define NIL -1

using namespace std;

class Graph{
    int V;
    list<int> *adj;


    void BridgeUtil(int v, bool visited[], int disc[], int low[],int parent[]);
    public:
        int countCritical;
        int *start;
        int *endArray;
        Graph(int V);
        void AddEdge(int v,int w);
        void Bridge();

};

Graph::Graph(int V)
{
    this->V=V;
    countCritical=0;
    start=new int[V];
    endArray=new int[V];
    adj=new list<int>[V];

}
void Graph::AddEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
void Graph::BridgeUtil(int v, bool visited[], int disc[], int low[],int parent[])
{
    static int time=0;

    visited[v]=true;
    disc[v]=low[v]= ++time;
    list<int>::iterator i;
    for(i=adj[v].begin();i!=adj[v].end();++i)
    {
        int u=*i;
        if(!visited[u])
        {
            parent[u]=v;
            BridgeUtil(u, visited, disc, low, parent);
            low[v]=min(low[v],low[u]);
            if(low[u]>disc[v])
            {
                if(v<u)
                {
                    start[countCritical]=v;
                    endArray[countCritical]=u;
                }
                else{
                    start[countCritical]=u;
                    endArray[countCritical]=v;
                }
                countCritical++;
            }
        }
        else if(u !=parent[v])
        {
            low[v]=min(low[v],disc[u]);
        }
    }
}
void Graph:: Bridge()
{
        bool *visited=new bool[V];
        int *parent=new int[V];
        int *disc=new int[V];
        int *low=new int[V];
        for(int j=0;j<V;j++)
        {
            visited[j]=false;
            parent[j]=NIL;
        }
        for(int i=0;i<V;i++)
        {
            if(visited[i]==false)
            {
                BridgeUtil(i,visited,disc,low,parent);
            }
        }
}
int main()
{
    freopen("in.txt","r",stdin);
    int nodeNumber;
    int n,tmp,edge;
    while(scanf("%d",&nodeNumber)==1)
    {

        Graph g1(nodeNumber);
        for(int i=0;i<nodeNumber;i++)
        {
            scanf("%d (%d)",&n,&edge);
            while(edge--)
            {
                scanf("%d",&tmp);
                g1.AddEdge(n,tmp);
            }
        }
        g1.Bridge();
        int temp1;
        int temp2;
        for(int i = 0; i <g1.countCritical; i++)
        {
            for(int j = 0; j < g1.countCritical-1; j++)
            {

                if(g1.start[j] > g1.start[j+1])
                {
                    temp1 = g1.start[j];
                    temp2 = g1.endArray[j];
                    g1.start[j] = g1.start[j+1];
                    g1.endArray[j] = g1.endArray[j+1];
                    g1.start[j+1] = temp1;
                    g1.endArray[j+1] = temp2;
                }
                else if(g1.start[j]==g1.start[j+1])
                {
                    if(g1.endArray[j]>g1.endArray[j+1])
                    {
                        temp1 = g1.start[j];
                        temp2 = g1.endArray[j];
                        g1.start[j] = g1.start[j+1];
                        g1.endArray[j] = g1.endArray[j+1];
                        g1.start[j+1] = temp1;
                        g1.endArray[j+1] = temp2;
                    }
                }
            }
        }
        printf("%d critical links\n",g1.countCritical);
        for(int i=0;i<g1.countCritical;i++)
        {
            printf("%d - %d\n",g1.start[i],g1.endArray[i]);
        }
        printf("\n");
    }
    return 0;
}
