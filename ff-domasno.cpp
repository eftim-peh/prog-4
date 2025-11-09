#include <bits/stdc++.h>
using namespace std;
vector<vector<int>>adj;
vector<int>parent;
int n,start,finish;
int dfs(int a)
{
    if(a==finish)return INT_MAX;
    for(int i=0;i<n;i++)
    {
        if(adj[a][i]!=0&&parent[i]==-1)
        {
            parent[i]=a;
            int t=dfs(i);
            if(t>0)return min(t,adj[a][i]);
        }
    }
    return 0;
}
int main()
{

    int m,a,b,c;
    cin>>n>>m;
    cin>>start>>finish;
    adj.resize(n,vector<int>(n));
    parent.resize(n,-1);
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        adj[a][b]=c;
    }
    int flow=0;
    int min_flow;
    while(true)
    {
        for(int i=0;i<n;i++)parent[i]=-1;
        parent[start]=-2;
        min_flow=dfs(start);
        if(min_flow==0)break;
        int k=finish;
        cout<<finish<<" ";
        while(k!=start)
        {
            adj[parent[k]][k]-=min_flow;
            adj[k][parent[k]]+=min_flow;
            k=parent[k];
            cout<<k<<" ";
        }
        cout<<endl;
        flow+=min_flow;
    }
    cout<<flow;
}