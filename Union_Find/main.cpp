//  此题是洛谷模板题
//  链接为：https://www.luogu.org/problem/P3367
#include<iostream>
#include<cassert>
using namespace std;
class Union_Find{
private:
    int n;
    int *size;
    int *parent;


public:
    Union_Find(int n){
        parent=new int[n+1];
        size=new int[n+1];
        for(int i=0;i<=n;i++){
            parent[i]=i;
            size[i]=1;
        }
        this->n=n;
    }


    ~Union_Find(){
        delete []size;
        delete []parent;
    }

    //得到当前的并查集中一共有多少个元素
    int getSize(){
        return n;
    }

    int Find(int k){
        //这里是从下标为1开始存储的，如果是从下标为0开始的assert(k>=0&&k<n);
        assert(k>=0&&k<=n);
        if(k==parent[k]){
            return k;
        }
        return Find(parent[k]);
    }


    bool isConnected(int p,int q){

        return Find(p)==Find(q);
    }


    void Union(int p,int q){
        assert(p>=0&&p<=n&&q>=0&&q<=n);
        int PID=Find(p);
        int QID=Find(q);
        if(PID==QID)
            return ;
        //如果size[PID]这个集合的元素个数大于size[QID]的个数，那么把元素少的集合合并到元素多的集合
        if(size[PID]>size[QID]){
            size[PID]+=size[QID];
            parent[QID]=PID;
        }
        else {
            size[QID]+=size[PID];
            parent[PID]=QID;
        }
    }

};

int main()
{

    int n,m;
    cin>>n>>m;
    Union_Find arr(n);
    int a,b,c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        if(a==1){
            arr.Union(b,c);
        } else {
            if(arr.isConnected(b, c)){
                cout<<'Y'<<endl;
            }
            else
                cout<<'N'<<endl;
        }
    }
    return 0;
}