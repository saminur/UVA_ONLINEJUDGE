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

#define NIL -1

using namespace std;

class Graph
{
    int V;
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *recStack);
    void DFS_Search(bool visited[],map<int,char>Map2,vector<int>res)
    {
        bool flag=false;
        for(int i=0; i<V; i++)
        {
            if(indegree[i]==0 && !visited[i])
            {
                list<int>::iterator it;
                for(it=adj[i].begin(); it!=adj[i].end(); it++)
                {
                    indegree[*it]--;
                }
                res.push_back(i);
                visited[i]=true;
                DFS_Search(visited,Map2,res);

                visited[i]=false;
                res.erase(res.end()-1);
                for(it=adj[i].begin(); it!=adj[i].end(); it++)
                {
                    indegree[*it]++;
                }
                flag=true;


            }
        }
        if(!flag)
        {
            for(int j=0; j<res.size()-1; j++)
            {
                char a=Map2[res[j]];
                cout<<a<<" ";
            }
            char b=Map2[res[res.size()-1]];
            cout<<b<<endl;
        }
    }
public:
    vector<int> indegree;
    bool isCyclic();
    Graph(int V)
    {
        this->V=V;
        adj=new list<int>[V];
        for(int i=0; i<V; i++)
        {
            indegree.push_back(0);
        }
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        indegree[w]++;
    }
    void dfs(map<int,char>Map2)
    {
        bool *visited=new bool[V];
        for(int i=0; i<V; i++)
        {
            visited[i]=false;

        }
        vector<int> res;
        DFS_Search(visited,Map2,res);

    }
};
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }

    }
    recStack[v] = false;
    return false;
}
bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;

    return false;
}
int main()
{

    int n;
    cin>>n;
    string s;
    getline(cin,s);
    char sortArray[20];
    for(int i=1; i<=n; i++)
    {
        getline(cin,s);
        int j,k;
        map<char,int> graphMap;
        map<int,char> Map2;
        string str,constraints;

        getline(cin,str);
        getline(cin,constraints);
        for(j=0,k=0; j<str.size(); j++)
        {
            if(str[j]==' ') continue;
            else
            {
                sortArray[k]=str[j];
                k++;
            }
        }
        sort(sortArray,sortArray+k);
        for(int m=0;sortArray[m]!='\0';m++)
        {
            graphMap[sortArray[m]]=m;
            Map2[m]=sortArray[m];
        }
        Graph g(k);

        for(j=0; j<constraints.size();)
        {
            if(constraints[j]==' ')
            {
                j++;
                continue;
            }
            else
            {
                char a=constraints[j];
                char b=constraints[j+2];
                j=j+3;
                int n1=graphMap[a];
                int n2=graphMap[b];
                g.addEdge(n1,n2);
            }
        }
        if(g.isCyclic())
        {
            cout<<"NO"<<endl;
            if(i<n) puts("");
            continue;
        }
        g.dfs(Map2);
        if(i<n) puts("");
    }
    return 0;
}

