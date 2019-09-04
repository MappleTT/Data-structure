//洛谷P3366最小生成树模板题
//链接：https://www.luogu.org/problem/P3366

//方法一：
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int N,M,sum=0;
bool marked[5001];
struct Edge{
    int from;   //边的起始点
    int to;     //边的到达点
    int val;    //权值

    //将所有的边在优先队列中按权值构造小顶堆
    bool operator <(const Edge &a)const{
        return a.val<val;
    }
};

vector<vector<Edge> >arr(5001,vector<Edge>());
priority_queue<Edge> q;

//访问k这个节点的所有边，并把这些边全部存入优先队列中
void visited(int k){
    marked[k]=true;
    for(int i=0;i<arr[k].size();i++){
        if(!marked[arr[k][i].to]){
            q.push(arr[k][i]);
        }
    }
}

void Prime(){
    int n=0;
    //开始时，全部的点都是没有被访问的
    for(int i=0;i<=N;i++){
        marked[i]=false;
    }
    //从第一个节点开始
    visited(1);
    while(!q.empty()){
        Edge e=q.top();
        q.pop();
        //如果两个点存在于同一个阵营，那么此边就不是横切边,那么就抛出这条边，继续寻找权值次小的边
        if(marked[e.to]==marked[e.from]){
            continue;
        }
        sum+=e.val;
        n++;
        //然后访问一条边中没有被标记的那个顶点
        if(!marked[e.to]){
            visited(e.to);
        }
        else{
            visited(e.from);
        }
    }
    if(n==N-1)
        cout<<sum<<endl;
    else
        cout<<"orz"<<endl;
}

int main()
{
    cin>>N>>M;
    Edge e1,e2;
    for(int i=0;i<M;i++){
        cin>>e1.from>>e1.to>>e1.val;
        e2.from=e1.to;
        e2.to=e1.from;
        e2.val=e1.val;
        arr[e1.from].push_back(e1);
        arr[e2.from].push_back(e2);
    }
    Prime();
    return 0;
}


//方法二：
/*
#include<iostream>
#include<vector>
using namespace std;

#define MAX 9999999
int N,M,sum=0;
bool marked[5001];
int dis[5001];   //用来存储节点的最短距离
struct Edge{
    int from;
    int to;
    int val;
};
vector<vector<Edge> >arr (5001,vector<Edge>());


void visited(int k){
    marked[k]=true;
    for(int i=0;i<arr[k].size();i++){
        //如果这个点没有被访问
        if(!marked[arr[k][i].to]){
            if(arr[k][i].val<dis[arr[k][i].to]){
                //找到某条边的权值还有被更新的可能，更新dis[arr[k][i].to]这个点的距离
                dis[arr[k][i].to]=arr[k][i].val;
            }
        }
    }
}

void Prime(){
    for(int i=0;i<=N;i++){
        marked[i]=false;
        dis[i]=MAX;
    }

    visited(1);
    int k=1;
    //每一轮都会找到dis[i]没有被访问的节点距离最小的那个
    for(int i=2;i<=N;i++){
        int min=MAX;
        for(int j=0;j<=N;j++){
            if(!marked[j]&&dis[j]<min){
                min=dis[j]; //此时的最小距离
                k=j;      //几号节点
            }
        }
        sum+=min;
        //以这个最小的节点再次visited
        visited(k);
    }

    for(int i=1;i<=N;i++){
        if(!marked[i]){
            cout<<"orz"<<endl;
            return ;
        }
    }
    cout<<sum<<endl;
}


int main()
{
    cin>>N>>M;
    Edge e1;
    Edge e2;
    for(int i=0;i<M;i++){
        cin>>e1.from>>e1.to>>e1.val;
        e2.from=e1.to;
        e2.to=e1.from;
        e2.val=e1.val;
        arr[e1.from].push_back(e1);
        arr[e2.from].push_back(e2);
    }
    Prime();
    return 0;
}
 */


//方法三：
/*
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MAX 9999999
int N,M,sum=0;
bool marked[5001];
int dis[5001];
struct Edge{
    int from;
    int to;
    int val;
};
vector<vector<Edge> >arr (5001,vector<Edge>());

struct Minval{
    int k;
    int val;

    bool operator <(const Minval &a)const{
        return a.val<val;
    }
};

priority_queue<Minval> q;
void visited(int k){
    marked[k]=true;
    Minval minval;
    for(int i=0;i<arr[k].size();i++){
        if(!marked[arr[k][i].to]){
            if(arr[k][i].val<dis[arr[k][i].to]){
                dis[arr[k][i].to]=arr[k][i].val;

                //这里用了最小堆，和方法二一个思路，就是缩短了时间复杂度，方法二中每次查找最小的dis[i]的值，都需要一遍for循环
                minval.k=arr[k][i].to;
                minval.val=arr[k][i].val;
                q.push(minval);
            }
        }
    }


}

void Prime(){
    for(int i=0;i<=N;i++){
        marked[i]=false;
        dis[i]=MAX;
    }

    visited(1);
    //假设所有的边都进入了堆中，那么肯定很多边不是横切边，那么我们就可以把它抛出来，当堆中为空的时候，循环结束
    while(!q.empty()){
        Minval minval=q.top();
        q.pop();
        if(marked[minval.k])
            continue;
        sum+=minval.val;
        visited(minval.k);
    }

    //如果有一个节点没有被访问到，也就是说遍历了所有的边都没有访问到这个节点，那么这个节点肯定属于另一个连通子图，即这个图不连通
    for(int i=1;i<=N;i++){
        if(!marked[i]){
            cout<<"orz"<<endl;
            return ;
        }
    }
    cout<<sum<<endl;
}


int main()
{
    cin>>N>>M;
    Edge e1;
    Edge e2;
    for(int i=0;i<M;i++){
        cin>>e1.from>>e1.to>>e1.val;
        e2.from=e1.to;
        e2.to=e1.from;
        e2.val=e1.val;
        arr[e1.from].push_back(e1);
        arr[e2.from].push_back(e2);
    }
    Prime();
    return 0;
}
*/


