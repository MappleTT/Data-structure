#include<iostream>
#include<stack>
#include<cassert>
#include<vector>
using namespace std;

//稀疏图
class SparaGraph{
private:
    int n,m;
    vector<vector<int> >arr;
    bool directed;


public:
    SparaGraph(int n,bool directed){
        this->n=n;
        this->m=0;
        this->directed=directed;
        arr=vector<vector<int> >(n,vector<int>());
    }

    ~SparaGraph(){};

    int V(){
        return n;
    }

    int M(){
        return m;
    }

    //添加从v到w的边
    void addEdge(int v,int w){
        assert(v>=0&&v<n);
        assert(w>=0&&w<n);

        //通常使用邻接表存储不考虑重边情况，一旦考虑重边情况，那么时间复杂度就会增大
//        if(hasEdge(v,w)){
//            return ;
//        }
        arr[v].push_back(w);
        if(!directed){
            arr[w].push_back(v);
        }
        m++;
    }

    //判断从点v到点w是否已经有边
    bool hasEdge(int v,int w){
        assert(v>=0&&v<n);
        assert(w>=0&&w<n);
        for(int i=0;i<arr[v].size();i++){
            if(arr[v][i]==w)
                return true;
        }
        return false;
    }

    //打印出与点v相邻的所有边
    void Print(int v){
        for(int i=0;i<arr[v].size();i++){
            cout<<arr[v][i]<<" ";
        }
        cout<<endl;
    }


    //稀疏图的邻接迭代器
    class adjIterator{
    private:
        int index;
        SparaGraph &G;
        int v;

    public:
        adjIterator(SparaGraph &g,int v):G(g){
            this->v=v;
            this->index=0;
        }

        ~adjIterator(){}

        int begin(){
            index=0;
            if(G.arr[v].size()>0){
                return G.arr[v][index];
            }
            return -1;
        }

        int next(){
            index++;
            if(index<G.arr[v].size()){
                return G.arr[v][index];
            }
            return -1;
        }

        bool end(){
            return index>=G.arr[v].size();
        }
    };

    //连通分量
    class Componet{
    private:
        bool *visited;    //用来标记节点是否被访问
        int ccount;       //最大连通分量
        int *id;          //id[k] k这个节点属于哪个连通分量
        SparaGraph &G;

        void dfs(int k){
            visited[k]=true;
            id[k]=ccount;
            adjIterator adj(G,k);
            for(int i=adj.begin();!adj.end();i=adj.next()){
                if(!visited[i]){
                    //与k节点相连的节点进行深度优先遍历
                    dfs(i);
                }
            }
        }

    public:
        Componet(SparaGraph &g):G(g){
            visited=new bool [G.n];
            this->ccount=0;
            id=new int[G.n];
            for(int i=0;i<G.n;i++){
                visited[i]=false;
                id[i]=-1;
            }

            for(int i=0;i<G.n;i++){
                if(!visited[i]){
                    dfs(i);
                    //没有与i这个节点相连的点必然属于另一个连通分量，ccount++;
                    ccount++;
                }
            }
        }

        ~Componet(){
            delete []visited;
            delete []id;
        }

        //返回最大连通分量
        int count(){
            return ccount;
        };

    };


    //寻路
    class Path{
    private:
        int s;
        int *from;
        bool *visited;
        SparaGraph &G;

        void dfs(int k){
            visited[k]=true;
            adjIterator adj(G,k);
            for(int i=adj.begin();!adj.end();i=adj.next()){
                if(!visited[i]){
                    dfs(i);
                    //i节点是通过k节点寻来的
                    from[i]=k;
                }
            }
        }

        //将s到w的路径存在vec这个数组中
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
        Path(SparaGraph &g,int s):G(g){
            assert(s>=0&&s<n);
            this->s=s;
            from=new int[G.n];
            visited=new bool[G.n];
            for(int i=0;i<G.n;i++){
                from[i]=-1;
                visited[i]=false;
            }
            dfs(s);
        }


        ~Path(){
            delete []visited;
            delete []from;
        }

        //是否有从s到w的边
        bool hasPath(int w){
            assert(w>=0&&w<G.n);
            return visited[w];
        }


        //打印出s到w的路径
        void showPath(int w){
            assert(hasPath(w));
            vector<int>vec;
            path(w,vec);
            for(int i=0;i<vec.size();i++){
                cout<<vec[i];
                if(i!=vec.size()-1){
                    cout<<"->";
                }
                else
                    cout<<endl;
            }
        }
    };


};

int main()
{

    return 0;
}