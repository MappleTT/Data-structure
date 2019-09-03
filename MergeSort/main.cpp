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


void Merge(int arr[],int l,int mid,int r){
    //开辟新的空间，把arr[r-l]元素放进去，归并排序就是拿空间换时间
    int aux[r-l+1];
    for(int i=l;i<=r;i++){
        aux[i-l]=arr[i];
    }

    int i=l,j=mid+1;
    for(int k=l;k<=r;k++){

        //如果i下标已经越界，则只考虑下标j
        if(i>mid){
            arr[k]=aux[j-l];
            j++;
        }
            //如果j下标已经越界,则只考虑下标i
        else if(j>r){
            arr[k]=aux[i-l];
            i++;
        }
        else if(aux[i-l]<=aux[j-l]){
            arr[k]=aux[i-l];
            i++;
        }
        else {
            arr[k]=aux[j-l];
            j++;
        }
    }
}

//递归
void Mergesort(int arr[],int l,int r){
    if(l>=r)
        return ;
    //找到数组中间位置的下标
    int mid=(r-l)/2+l;
    //对下标为l到mid之间的元素进行归并排序
    Mergesort(arr,l,mid);
    //对下标为mid+1到r之间的元素进行归并排序
    Mergesort(arr,mid+1,r);
    //排序后arr[mid]的值是arr[l...mid]中最大的，arr[mid+1]的值是arr[mid+1...r]最小的
    //如果arr[mid]>arr[mid+1]，那么要对这两个数组进行归并
    if(arr[mid]>arr[mid+1]){
        Merge(arr,l,mid,r);
    }
}


//这里的n是数组的元素个数
void MergeSort(int arr[],int n){
    Mergesort(arr,0,n-1);
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
    MergeSort(arr,n);
    //打印出arr数组排序后的元素序列(这里的排序方式是按照从小到大进行排序的)
    Print(arr,n);
    return 0;
}