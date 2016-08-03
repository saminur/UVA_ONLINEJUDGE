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

#define NIL -1
using namespace std;
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}
class Graph
{
    int V;
    list<int> *adj;
    void DFS_Search(bool visited[],map<int,string>map2,vector<string> &ss)
    {
        for(int i=0;i<V;i++)
        {
            if(indegree[i]==0 && !visited[i])
            {
                list<int>::iterator it;
                for(it=adj[i].begin();it!=adj[i].end();it++)
                {
                    indegree[*it]--;
                }
                ss.push_back(map2[i]);
                visited[i]=true;
                DFS_Search(visited,map2,ss);
            }
        }
    }
public:
    map<int, int> indegree;
    Graph(int V)
    {
        this->V=V;
        adj=new list<int>[V];
        for(int i=0;i<V;i++)
        {
            indegree[i]=0;
        }
    }
    void addEdge(int v,int w)
    {
        indegree[w]++;
        adj[v].push_back(w);
    }
    void dfs(map<int,string>map2,int testCase)
    {
        vector<string> ss;
        bool *visited=new bool[V];
        for(int i=0; i<V; i++)
        {
            visited[i]=false;
        }


        DFS_Search(visited,map2,ss);
        cout<<"Case #"<<testCase<<": Dilbert should drink beverages in this order: ";
        int stackSize=ss.size();
        for(int j=0;j<stackSize-1;j++)
        {
            cout<<ss[j]<<" ";
        }
        cout<<ss[ss.size()-1]<<"."<<endl<<endl;
    }
};

int main()
{
    freopen("in.txt","r",stdin);
    int N,E;
    string line;
    int testCase=1;
    while(cin>>N)
    {
        map<string,int> map1;
        map<int,string> map2;
        vector<string>sortArray;
        string str;
        Graph g(N);
        for(int i=0; i<N; i++)
        {
            cin>>str;
            map1[str]=i;
            map2[i]=str;
        }
        cin>>E;
        for(int i=0;i<E; i++)
        {
            string s,s2;
            cin>>s>>s2;
            g.addEdge(map1[s],map1[s2]);

        }
        g.dfs(map2,testCase);
        testCase++;
        getline(cin,line);
    }
    return 0;
}
