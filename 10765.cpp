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

class Graph
{
    int V;
    list<int> *adj;
    void APUtil(int v, bool visited[], int disc[], int low[],
                int parent[], bool ap[]);
public:
    bool *check;
    int countComponent;
    int *index;
    Graph(int V);
    void addEdge(int v, int w);
    int AP();
    int dfs(int val);
    void DFSSearch(int u,bool visited[]);
};

Graph::Graph(int V)
{
    check=new bool[V];
    index=new int[V];
    this->V = V;
    adj = new list<int>[V];
    for(int i=0;i<V;i++)
    {
        check[i]=false;
    }
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[])
{

    static int time = 0;

    int children = 0;

    visited[u] = true;

    disc[u] = low[u] = ++time;

    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        if (!visited[v])
        {
            children++;
            parent[v] = u;
            APUtil(v, visited, disc, low, parent, ap);
            low[u]  = min(low[u], low[v]);

            if (parent[u] == NIL && children > 1)
                ap[u] = true;

            if (parent[u] != NIL && low[v] >= disc[u])
                ap[u] = true;
        }
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}
void Graph::DFSSearch(int u,bool visited[])
{
    visited[u]=true;
    list<int>::iterator iter;
    for(iter=adj[u].begin(); iter!=adj[u].end(); iter++)
    {
        if(!visited[*iter])
        {
            DFSSearch(*iter,visited);
        }
    }
}

int Graph::dfs(int val)
{
    bool *visited=new bool[V];
    countComponent=0;
    for(int i=0; i<V; i++)
    {
        visited[i]=false;
    }
    visited[val]=true;
    for(int i=0; i<V; i++ )
    {
        if(!visited[i])
        {
            DFSSearch(i,visited);
            countComponent++;
        }

    }
    return countComponent;
}

int Graph::AP()
{
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V];
    int countAP=0;
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false)
            APUtil(i, visited, disc, low, parent, ap);
    }
    int k=0;
    for (int i = 0; i < V; i++)
    {
        if (ap[i] == true)
        {
            check[i]=true;
            index[k]=i;
            k++;
            countAP++;
        }
    }
    return countAP;
}
int main()
{
    int n,m;
    while(scanf("%d %d ",&n,&m) && (n!=0) && (m!=0))
    {
        int componentArray[n];
        int nodeArray[n];
        Graph g(n);
        int x,y;
        while(scanf("%d %d ",&x,&y) && x!=-1 && y!=-1)
        {
            g.addEdge(x,y);
        }
        int p=g.AP();
        for(int i=0;i<p;i++)
        {
           componentArray[i]=g.dfs(g.index[i]);
        }
        int q=p;
        int minimum=10000;
        for(int i=0; i<n;i++)
        {
            if(g.check[i]==true) continue;
            else
            {
                g.index[q]=i;
                componentArray[q]=1;
                q++;
            }

        }
        int temp1;
        int temp2;
        for(int i = 0; i <n; i++)
        {
            for(int j = 0; j < n-1; j++)
            {

                if(componentArray[j] < componentArray[j+1])
                {
                    temp1 = componentArray[j];
                    temp2 = g.index[j];
                    componentArray[j] = componentArray[j+1];
                    g.index[j]=g.index[j+1];
                    componentArray[j+1] = temp1;
                    g.index[j+1]=temp2;

                }
                else if(componentArray[j]==componentArray[j+1])
                {
                    if(g.index[j]>g.index[j+1])
                    {
                        temp1 = componentArray[j];
                        temp2 = nodeArray[j];
                        componentArray[j] = componentArray[j+1];
                        g.index[j] = g.index[j+1];
                        componentArray[j+1] = temp1;
                        g.index[j+1] = temp2;
                    }
                }
            }
        }
        for(int i=0;i<m;i++)
        {
           printf("%d %d\n",g.index[i],componentArray[i]);
        }
        printf("\n");
    }
    return 0;
}
