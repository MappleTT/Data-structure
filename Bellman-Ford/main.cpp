//用来处理负权边，不能有负权环
bool Bellmanford(){
    for(int i=0;i<=N;i++){
        //一共有N个顶点，每个距离初始化Max,Max是个很大的值，可以自己定义
        dis[i]=Max;
    }
    //从S点出发
    dis[S]=0;
    //考虑极端的情况，一个点到达另一个点的最短路径在N个节点里面，最多走过N-1条边完成更新
            //可以有只经过一条边更新到最小，只经过两条边更新到最小...
    for(int i=1;i<N;i++){
        //从节点1开始
        for(int j=1;j<=N;j++){
            //从顶点j遍历与j顶点相邻的每一条边
            for(int k=0;k<arr[j].size();k++){
                //采用邻接表存储
                int val=arr[j][k].val;  //顶点j到达arr[j][k]位置点的权值
                int to=arr[j][k].to;    //顶点j到达arr[j][k]位置点是多少，比如从j点到k点，这里的to点就是k点
                if(dis[j]+val<dis[to])  //如果能更新，就更新
                    dis[to]=dis[j]+val;
            }
        }
    }

    //如果经过上面的循环还能更新更短的边，则必存在负权环，使得每再进行一次操作，距离变得更小
    for(int i=1;i<=N;i++){
        for(int j=0;j<arr[i].size();j++){
            int val=arr[i][j].val;
            int to=arr[i][j].to;
            if(dis[j]+val<dis[to])
                //存在负权环
                return true;
        }
    }
    //不存在负权环
    return false;
}
