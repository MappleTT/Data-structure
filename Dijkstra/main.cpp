//洛谷P3371单源最短路径模板题
//链接：https://www.luogu.org/problem/P3371
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define  MAX 2147483647
int N,M,S;
bool marked[10001];  //用来标记节点是否被访问了
int dis[10001];     //到达每个节点的最小距离
struct Edge {
    int from;
    int to;
    int val;

    bool operator <(const Edge &a)const{
        return a.val<val;
    }
};

vector<vector<Edge> >arr(10001,vector<Edge>());
priority_queue <Edge> q;


void visited(int k){
    marked[k]=true;
    Edge e;
    //访问k节点的所有边
    for(int i=0;i<arr[k].size();i++){
        //如果到达i节点的前一个节点k的dis值加上k节点到i节点的权值比dis[i]这个要小，那么就说找到了一条到达i节点更小的路
        if(dis[k]+arr[k][i].val<dis[arr[k][i].to]) {
            //更新这条路
            dis[arr[k][i].to] = dis[k] + arr[k][i].val;
            //将更新的这个Edge放入到最小堆中
            e.from=k;
            e.to=arr[k][i].to;
            e.val=dis[arr[k][i].to];
            q.push(e);
        }
    }
}


void Dijkstra(){
    for(int i=0;i<=N;i++){
        marked[i]=false;
        dis[i]=MAX;
    }
    dis[S]=0;
    visited(S);
    while(!q.empty()){
        Edge e=q.top();
        q.pop();
        //如果这个点已经被访问过了，说明已经是最小的了，不需要继续访问了，忽略这个点，继续下一个点
        if(marked[e.to]){
            continue;
        }
        visited(e.to);
    }

    for(int i=1;i<=N;i++){
        cout<<dis[i];
        if(i!=N){
            cout<<" ";
        }
    }
    cout<<endl;
}
int main()
{
    cin>>N>>M>>S;
    Edge e;
    for(int i=0;i<M;i++){
        cin>>e.from>>e.to>>e.val;
        arr[e.from].push_back(e);
    }
    Dijkstra();
    return 0;
}