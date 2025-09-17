#include <bits/stdc++.h>
using namespace std;
int vfind(int a,vector<int>&dsu)
{
    if(dsu[a]==a)return a;
    return dsu[a]=vfind(dsu[a],dsu);
}
void generiraj(int n,int edges,vector<vector<pair<int,int>>>&g)
{
    cout<<n<<" "<<edges<<" "<<endl;
    cout<<"1"<<endl;
    vector<int>dsu(n);
    for(int i=0;i<n;i++)dsu[i]=i;
    int cnt=0,cnt1=0;
    while(cnt<edges)
    {
        int a=rand()%n,b=rand()%n;
        while(vfind(a,dsu)==vfind(b,dsu)&&cnt1<n-1)
        {
            a=rand()%n;b=rand()%n;
        }
        cnt1++;
        cnt++;
        int c=rand();
        if(rand()%10==0)c=-c;
        cout<<a<<" "<<b<<" "<<c<<endl;
        g[a].push_back({b,c});
        dsu[vfind(b,dsu)]=vfind(a,dsu);
    }
}
vector<int> bellmanford(int n,int start,vector<vector<pair<int,int>>>g)
{
    vector<int>res(n,INT_MAX);
    res[start]=0;
    bool updated;
    for(int i=0;i<n;i++)
    {
        updated=false;
        for(int a=0;a<n;a++)
        {
            if(res[a]==INT_MAX)continue;
            for(auto j:g[a])
            {
                if(res[j.first]>res[a]+j.second)
                {
                    res[j.first]=res[a]+j.second;
                    updated=true;
                }
            }
        }
    }
    if(!updated)return res;
    for(int i=0;i<n;i++)
    {
        for(int a=0;a<n;a++)
        {
            if(res[a]==INT_MAX)continue;
            for(auto j:g[a])
            {
                if(res[a]==-INT_MAX)
                {
                    res[j.first]=-INT_MAX;
                }
                else if(res[j.first]>res[a]+j.second)
                {
                    res[j.first]=-INT_MAX;
                }
            }
        }
    }
    return res;
}
int main()
{
    //freopen("input9.txt","w",stdout);
    int n,edges,a,b,c,start;
    bool check;
    //cout<<"Vnesi broj na teminja i rabovi:";
    cin>>n>>edges;
    vector<vector<pair<int,int>>>g(n);
    //cout<<"Dali bi sakal ti da generiras graf?Odgovori binarno:";
    cin>>check;
    if(check)
    {
        for(int i=0;i<edges;i++)
        {
            cin>>a>>b>>c;
            g[a].push_back({b,c});
        }
    }
    else generiraj(n,edges,g);
    //cout<<"Vnesi pocetno teme:";
    cin>>start;
    //freopen("output9.txt","w",stdout);
    vector<int>res=bellmanford(n,start,g);
    for(auto i:res)
    {
        if(i==INT_MAX)cout<<"inf";
        else if(i==-INT_MAX)cout<<"-inf";
        else cout<<i;
        cout<<endl;
    }
    return 0;
}