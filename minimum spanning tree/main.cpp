//洛谷P3366最小生成树模板题
//链接：https://www.luogu.org/problem/P3366

//方法一：
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int N,M,sum=0;
struct Edge{
    int from;
    int to;
    int val;
};
vector<Edge>arr;

//将所有的边由值从小到大排序
bool cmp(Edge a,Edge b){
    return a.val<b.val;
}


//并查集
class Union_Find{
private:
    int *size;
    int *parent;

public:
    Union_Find(){
        size=new int[N+1];
        parent=new int[N+1];
        for(int i=0;i<=N;i++){
            size[i]=1;
            parent[i]=i;
        }
    }

    ~Union_Find(){
        delete []size;
        delete []parent;
    }

    int Find(int k){
        if(k==parent[k]){
            return k;
        }
        return Find(parent[k]);
    }

    //将p集合和q集合合并
    void Union(int p,int q){
        if(Find(p)==Find(q))
            return ;
        int PID=Find(p);
        int QID=Find(q);
        if(size[PID]>size[QID]){
            parent[QID]=PID;
            size[PID]+=size[QID];
        }
        else {
            parent[PID]=QID;
            size[QID]+=size[PID];
        }
    }

    //判断集合p是否与集合q相连
    bool isConnected(int p,int q){
        return Find(p)==Find(q);
    }
};

//kruskal算法
void kruskal(){
    int n=0;
    sort(arr.begin(),arr.end(),cmp);
    Union_Find F;
    //一共进行边数的循环
    for(int i=0;i<arr.size();i++){
        Edge e=arr[i];
        //如果两个点不在一个集合，说明sum可以添加val的值
        if(!F.isConnected(e.from,e.to)){
            sum+=e.val;
            n++;
            //sum添加后,这两个点就属于同一个连通子图了
            F.Union(e.from,e.to);
        }
        //最小生成树，当满足边的数量等于节点数减一就可以跳出循环
        if(n==N-1){
            cout<<sum<<endl;
            return ;
        }

    }
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
        arr.push_back(e1);
        arr.push_back(e2);
    }
    kruskal();
    return 0;
}



//方法二：
/*
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge{
    int from;
    int to;
    int weight;
};

int sum=0,n,m,k=0;
Edge arr[200001];
//将所有的边按val从小到大排序
bool cmp(Edge a,Edge b){
    return a.weight<b.weight;
}
int father[5001];

//k集合属于多少号
int Find(int k){
    if(father[k]==k)
        return k;
    return Find(father[k]);
}

void kruskal(){
    //最开始的时候每个节点都是属于单独的集合
    for(int i=0;i<=n;i++){
        father[i]=i;
    }
    //进行m条边的循环次数
    for(int i=0;i<m;i++){

        //如果sum加入的边数等于节点数减一，那么已经是最小生成树了
        if(k==n-1){
            cout<<sum<<endl;
            return ;
        }
        int from=arr[i].from;
        int to=arr[i].to;
        int weight=arr[i].weight;

        int a=Find(from);
        int b=Find(to);
        if(a!=b){
            sum+=weight;
            k++;
            //相加之后将a节点和b节点合并到一块
            father[a]=b;
        }
        else
            continue;
    }
    cout<<"orz"<<endl;
}


int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>arr[i].from>>arr[i].to>>arr[i].weight;
    }
    sort(arr,arr+m,cmp);
    kruskal();
    return 0;
}
 */




