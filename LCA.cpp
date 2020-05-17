#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1e3+3;
const int lg=log2(MAXN);

vector<int> graph[MAXN];
int n;

int level[MAXN];
int parent[MAXN];
int LCA[MAXN][lg+1];



void dfs(int u,int parent)
{
    level[u]=level[parent]+1;
    LCA[u][0]=parent;

    for(auto v:graph[u])
    {
        if(v==parent) continue;
        dfs(v,u);
    }

}

int lca(int u,int v)
{
    if(level[u]<level[v]) swap(u,v);

    int diff=level[u]-level[v];

    for(int i=0;i<=lg;i++)
    {
        if((1<<i) & diff) u=LCA[u][i];
    }

    if(u==v) return u;

    for(int i=lg;i>=0;i--)
    {
        if(LCA[u][i]!=LCA[v][i])
        {
            u=LCA[u][i];
            v=LCA[v][i];
        }
    }
    return LCA[u][0];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin>>t;
	int tc=1;
	while(t--)
    {

        cin>>n;

        for(int i=1;i<=n;i++)
        {
            graph[i].clear();
            level[i]=0;
        }

        for(int i=1;i<=n;i++)
        {
            int child_cnt; cin>>child_cnt;

            for(int j=0;j<child_cnt;j++)
            {
                int child; cin>>child;
                graph[i].push_back(child);
                graph[child].push_back(i);
            }
        }


        memset(LCA,-1,sizeof(LCA));
        level[0]=-1;
        dfs(1,0);

        // table construction

        for(int j=1;j<=lg;j++)
        {
            for(int i=1;i<=n;i++)
            {
                if(LCA[i][j-1]!=-1)
                {
                    int par=LCA[i][j-1];
                    LCA[i][j]=LCA[par][j-1];
                }
            }
        }


        int q;cin>>q;
        cout << "Case " << tc << ":" << endl;
        while(q--)
        {
            int a,b; cin>>a>>b;
            cout<<lca(a,b)<<endl;
        }


     tc++;

    }

	return  0;
}
