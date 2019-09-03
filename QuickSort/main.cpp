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


////方法一
//int quicksort(int arr[],int l,int r){
//
//    //以l这个位置的元素作为参考数
//    int j=l;
//    for(int i=l+1;i<=r;i++){
//        //arr[i]只要比arr[l]这个数小的都交换元素值
//        if(arr[i]<arr[l]){
//            j++;
//            swap(arr[i],arr[j]);
//        }
//    }
//
//    // 最后：arr[j],arr[j+1]...arr[l]...arr[r] 其中arr[j+1]...arr[l-1]都是比arr[l]小的数;
//    // arr[l+1]...ar[r]都是比arr[l]大的数
//    // 交换arr[j]和arr[l]的值
//    swap(arr[j],arr[l]);
//    //返回这个子数组的中间位置的下标
//    return j;
//}

//方法二
//传统的快速排序
int quicksort(int arr[],int l,int r){
    int tem=arr[l];
    while(l<r){
        //先从数组的右边开始找，找到一个比tem要小的数,将这个数赋值给arr[l];
        while(l<r&&arr[r]>tem){
            r--;
        }
        arr[l]=arr[r];
        //从数组的左边开始找，找到一个比tem要大的数，将这个数赋值给arr[r];
        while(l<r&&arr[l]<tem){
            l++;
        }
        arr[r]=arr[l];
    }
    arr[l]=tem;      //arr[r]=tem;
    return l;
}


void Quicksort(int arr[],int l,int r){
    if(l>=r)
        return ;
    //经过一次排序后得到:
    //arr[l]到arr[mid-1]的数都小于arr[mid];
    //arr[mid+1]到arr[r]的数都大于arr[mid];
    int mid=quicksort(arr,l,r);

    //对小于arr[mid]部分的元素再进行排序
    Quicksort(arr,l,mid-1);
    //对大于arr[mid]部分的元素再进行排序
    Quicksort(arr,mid+1,r);
}

//传入一个arr数组，数组中一共有n个元素
void QuickSort(int arr[],int n){
    //对arr数组下标为0到n-1之间的数进行排序
    Quicksort(arr,0,n-1);
}



//以上排序为普通的快速排序，下面这种方式采用的是三路快排
//三路快排
void Quicksort3(int *arr,int l,int r)
{
    if(l>=r)
        return ;
    int v=arr[l];
    int lt=l;
    int gt=r+1;
    int i=l+1;
    while(i<gt)
    {
        if(arr[i]<v)           //比v小的移到左边位置
        {
            swap(arr[i],arr[lt+1]);
            i++;
            lt++;
        }
        else if(arr[i]>v)   //比v大的移到右边位置
        {
            swap(arr[i],arr[gt-1]);
            gt--;
        }
        else                  //和v相等的不用移动，放在中间位置
        {
            i++;
        }
    }
    swap(arr[l],arr[lt]); //这里不要写swap(v,arr[lt]);因为v和arr[l]地址不同，我们要做的是交换数组中两个元素的位置；
    Quicksort3(arr,l,lt-1);
    Quicksort3(arr,gt,r);
}

void QuickSort3(int *arr,int n)
{
    Quicksort3(arr,0,n-1);
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
    //调用三路快速排序
    QuickSort3(arr,n);
    //打印出arr数组排序后的元素序列(这里的排序方式是按照从小到大进行排序的)
    Print(arr,n);
    return 0;
}