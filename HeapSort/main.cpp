//时间复杂度O(nlogn)
#include<iostream>
#include<ctime>
#include<cmath>
using namespace std;

//打印数组元素
void Print(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


//本函数用来处理逐渐加入元素的数组进行操作，维护最大/最小堆
void shiftUp(int arr[],int k){
    while(k>0&&arr[k]<arr[(k-1)/2]){
        swap(arr[k],arr[(k-1)/2]);
        k=(k-1)/2;
    }
}


//arr数组，对下边k的元素进行操作，目前arr数组中进行操作的总数为n个
void shiftDown(int arr[],int k,int n){
    while(2*k+1<n){
        int j=2*k+1;
        //如果右节点存在，并且右节点的值大于左节点的值，选最大的
        if(j+1<n&&arr[j+1]>arr[j]){
            j+=1;
        }
        //如果根节点最大，那么不需要交换
        if(arr[k]>arr[j])
            break;
        //否则交换两个元素的值
        swap(arr[k],arr[j]);
        //继续向下进行操作
        k=j;
    }
}


//原地堆排序
void HeapSort(int arr[],int n){
    //可以将数组看成是以arr[0]为根节点的二叉树，从第一个非叶子节点开始进行shiftDown
    //经过此次循环，变成了最大堆
    for(int i=(n-1)/2;i>=0;i--){
        shiftDown(arr,i,n);
    }

    //此时，arr[0]是arr数组中最大的元素，将它和arr[i]互换位置，再对arr[0]进行shiftDown操作
    //循环结束后，arr数组的元素从小到大排序
    for(int i=n-1;i>=0;i--){
        swap(arr[0],arr[i]);
        shiftDown(arr,0,i);
    }
}

int main(){

    //给arr数组随机值
    int n;
    cin>>n;
    int arr[n];
    srand(time(NULL));
    for(int i=0;i<n;i++){
        arr[i]=rand()%100;//随机产生[0,100)的数
    }

    //打印出arr数组排序前的元素序列
    Print(arr,n);
    //调用归并排序
    HeapSort(arr,n);
    //打印出arr数组排序后的元素序列(这里的排序方式是按照从小到大进行排序的)
    Print(arr,n);
    return 0;
}