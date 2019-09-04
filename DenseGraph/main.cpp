#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<cassert>
using namespace std;

//稠密图
class DenseGraph{
private:
    int n,m;
    vector<vector<bool> >arr;
    bool directed;



public:
    DenseGraph(int n,bool directed){
        this->m=0;
        this->n=n;
        this->directed=directed;
        arr=vector<vector<bool> >(n,vector<bool>(n,false));
    }


    ~DenseGraph(){}

    int V(){
        return n;
    }

    int E(){
        return m;
    }

    //判断是否存在从v到w的边
    bool hasEdge(int v,int w){
        assert(v>=0&&v<n);
        assert(w>=0&&w<n);
        return arr[v][w];
    }

    //添加从v到w的边
    void addEdge(int v,int w){
        assert(w>=0&&w<n);
        assert(v>=0&&v<n);

        if(hasEdge(v,w)){
            return ;
        }
        arr[v][w]=true;
        //如果是无向图
        if(!directed){
            arr[w][v]=true;
        }
        m++;
    }


    //打印与v节点相邻的所有边
    void Print(int v){
        for(int i=0;i<arr[v].size();i++){
            if(arr[v][i]){
                cout<<i<<" ";
            }
        }
        cout<<endl;
    }

    //稠密图的迭代器
    class adjIterator{
    private:
        int index;
        DenseGraph &G;
        int v;
    public:
        adjIterator(DenseGraph &g,int v):G(g){
            this->v=v;
            this->index=0;
        }

        //这样就实现了封装性，用户修改不了图中的数据
        int  begin(){
            int index=-1;
            return next();
        }

        int next(){
            for(index+=1;index<G.arr[v].size();index++){
                if(G.arr[v][index]){
                    return index;
                }
            }
            return -1;
        }

        bool end(){
            return index>=G.arr[v].size();
        }
    };


    //连通分量，深度优先遍历
    class Component{
    private:
        DenseGraph &G;
        bool *visited;   //给某个节点是否被访问了做个标记
        int *id;        //这个数组来存储某个节点是属于几号连通分量
        int ccount;    //表示最大连通分量的个数

        void dfs(int k){
            visited[k]=true;
            id[k]=ccount;
            adjIterator adj(G,k);
            for(int i=adj.begin();!adj.end();i=adj.next()){
                if(!visited[i])
                    dfs(i);
            }
        }

    public:
        Component(DenseGraph &g):G(g){
            visited=new bool [G.V()];
            id=new int [G.V()];
            this->ccount=0;
            for(int i=0;i<G.V();i++){
                visited[i]=false;
                id[i]=-1;
            }

            //访问图中的每个节点
            for(int i=0;i<G.V();i++){
                //如果这个节点没有被访问
                if(!visited[i]){
                    //进行深度优先遍历，凡是与i这个节点相邻的节点都被访问了，
                    // 如果不与i这个节点相邻的节点，说明一定是在另一个连通分量里面
                    dfs(i);

                    ccount++;
                }
            }
        }

        ~Component(){
            delete []visited;
            delete []id;
        }

        int count(){
            return ccount;
        };
    };


    //寻路算法
    class Path{
    private:
        bool *visited;
        int *from;
        int s;
        DenseGraph &G;

        void dfs(int k){
            visited[k]=true;
            adjIterator adj(G,k);
            for(int i=adj.begin();!adj.end();i=adj.next()){
                if(!visited[i]){
                    dfs(i);
                    from[i]=k;
                }
            }
        }

        //查询从s到w的路径，将它们存放在vec数组中
        void path(int w,vector<int> &vec){
            assert(hasPath(w));
            stack<int>s;
            int p=w;
            while(p!=-1){
                s.push(p);
                p=from[p];
            }
            vec.clear();
            while(!s.empty()){
                vec.push_back(s.top());
                s.pop();
            }
        }

    public:
        Path(DenseGraph &g,int s):G(g){
            assert(s>=0&&s<G.n);
            visited=new bool [G.V()];
            from=new int[G.V()];
            this->s=s;
            for(int i=0;i<G.n;i++){
                visited[i]=false;
                from[i]=-1;
            }
            dfs(s);
        }


        ~Path(){
            delete []visited;
            delete []from;
        }

        //查询从s点到w点是否存在路径
        bool hasPath(int w){
            assert(w>=0&&w<G.n);
            return visited[w];
        }


        //打印出从s到w的路径
        void showPath(int w){
            assert(hasPath(w));
            vector<int>vec;
            path(w,vec);
            for(int i=0;i<vec.size();i++){
                cout<<vec[i];
                if(i!=vec.size()-1){
                    cout<<"->";
                }
            }
            cout<<endl;
        }

    };

};
int main()
{



    return 0;
}