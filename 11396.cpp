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

    void DFS_Search(int v,bool Visited[]);
    public:
        list<int> *adj;
        bool bipartite;
        bool *color;
        Graph(int V);
        void addEdge(int w,int v);
        void dfs();

};
Graph::Graph(int V)
{
    this->V=V;
    adj=new list<int>[V];
    color=new bool[V];
    bipartite=true;
}
void Graph::addEdge(int w, int v)
{
    adj[w].push_back(v);
    adj[v].push_back(w);
}
void Graph::DFS_Search(int v,bool visited[])
{
    visited[v]=true;
    list<int>::iterator it;
    for(it=adj[v].begin();it!=adj[v].end();it++)
    {
        if(!visited[*it])
        {
            color[*it]=!color[v];
            DFS_Search(*it,visited);
        }
        else if(color[*it]==color[v])
        {
            bipartite=false;
        }
    }
}
void Graph::dfs()
{
    bool *visited=new bool[V];
    for(int i=0; i<V; i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<V;i++)
    {
        if(!visited[i])
        {
            color[i]=false;
            DFS_Search(i,visited);
        }
    }
}

int main()
{

    int n;
    while(scanf("%d",&n) && (n!=0))
    {
        Graph g(n);
        int x,y;
        while(scanf("%d %d ",&x,&y) && x!=0 && y!=0)
        {
            g.addEdge(x-1,y-1);
        }
        g.dfs();
        if(g.bipartite==true)
        {
            cout<<"YES"<<endl;
        }
        else{
                cout<<"NO"<<endl;
        }
    }
    return 0;
}
