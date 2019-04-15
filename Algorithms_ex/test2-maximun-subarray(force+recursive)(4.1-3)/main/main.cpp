#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define MAX_B 100   //数字范围
#define MAX_IN 8000  //数组大小(4字节)
int A[MAX_IN];
class Max_subarray
{
    public:
        int sum_max;  //和
        int left;     //起点
        int right;    //终点
        Max_subarray(int sum_max_, int left_, int right_)
        {
            sum_max = sum_max_;
            left = left_;
            right = right_;
        }

};

void rand_issue(int* a, int left, int right)
{
    srand((unsigned)time(NULL));
    for(int i = 0; i < MAX_IN; i++)
    {
        a[i] = rand()%(right - left) + left;  //产生从left到right的随机数
    }
}
void print_list(int* lista, int num)      //打印数组
{
    for(int i=0; i<num; i++)
        cout<<lista[i]<<" ";
}
Max_subarray subarray_find_force(int a[], int left, int right)  //暴力方法O(n)
{
    Max_subarray f_sub(INT_MIN, -1, -1);
    for(int i = left; i < right; i++)
    {
        int sum = 0;
        for(int j = i; j < right; j++)
        {
            sum += a[j];
            if(sum > f_sub.sum_max)
            {
                f_sub.sum_max = sum;
                f_sub.left = i;
                f_sub.right = j;
            }
        }
    }
    return f_sub;
}

Max_subarray sub_cross_find(int a[], int left, int mid, int right)   //从分治算法关键：中间往两边搜索
{
    Max_subarray f_sub(INT_MAX, -1, -1);
    int low_max = INT_MIN;
    int right_max = INT_MIN;
    int sum = 0;
    for(int i = mid; i >= left; i--)
    {
        sum += a[i];
        if(sum > low_max)
        {
            low_max = sum;
            f_sub.left = i;
        }
    }
    sum = 0;
    for(int i = mid+1; i <= right; i++)
    {
        sum += a[i];
        if(sum > right_max)
        {
            right_max = sum;
            f_sub.right = i;
        }
    }
    f_sub.sum_max = low_max + right_max;
    return f_sub;
}

Max_subarray subarray_find_recursion(int a[], int left, int right)  //分治递归方法O(nlogn)
{
    Max_subarray f_sub(INT_MIN, -1, -1);
    if(left == right)
    {
        f_sub.left = f_sub.right = left;
        f_sub.sum_max = a[right];
        return f_sub;
    }
    else
    {
        int mid = (left + right)/2;
        Max_subarray tem = subarray_find_recursion(a, left, mid);
        Max_subarray tem2 = subarray_find_recursion(a, mid+1, right);
        Max_subarray tem3 = sub_cross_find(a, left, mid, right);
        if(tem.sum_max >= tem2.sum_max && tem.sum_max >= tem3.sum_max)
            return tem;
        else if(tem2.sum_max >= tem.sum_max && tem2.sum_max >= tem3.sum_max)
            return tem2;
        else
            return tem3;
    }
}

Max_subarray linear_find(int a[], int high)     //线性搜索时间复杂符O(n)
{
    Max_subarray* suf[high];          //suf[x]是array中以x结尾的有最大和的subarray
    for(int i = 0; i < high; i++)
        suf[i] = new Max_subarray(INT_MIN, -1, -1);
    suf[0]->left = 0;
    suf[0]->right = 0;
    suf[0]->sum_max = a[0];
    for(int i = 1; i<high; i++)
    {
        if(suf[i-1]->sum_max <= 0)
        {
            suf[i]->left = i;
            suf[i]->right = i;
            suf[i]->sum_max = a[i];
        }
        else
        {
            suf[i]->left = suf[i-1]->left;
            suf[i]->right = i;
            suf[i]->sum_max = suf[i-1]->sum_max + a[i];

        }
    }
    int sum = suf[0]->sum_max;
    int index = 0;
    for(int i = 1; i<high; i++)
    {
        if(sum < suf[i]->sum_max)
        {
            sum = suf[i]->sum_max;
            index = i;
        }
    }
    return *suf[index];

}
int main()
{
    clock_t t1,t2,t3,t4;
    rand_issue(A, -(MAX_B/2), MAX_B/2);
    print_list(A, MAX_IN);
    t1 = clock();
    cout<<endl<<"start!"<<endl;
    Max_subarray out = subarray_find_force(A, 0, MAX_IN);    //暴力搜索方法
    t2 = clock();
    cout<<"force: "<<out.left<<" "<<out.right<<" "<<out.sum_max<<" ms: "<<(t2 - t1)<<endl;
    Max_subarray out2 = subarray_find_recursion(A, 0, MAX_IN);   //分治递归方法
    t3 = clock();
    cout<<"recursion: "<<out2.left<<" "<<out2.right<<" "<<out2.sum_max<<" ms: "<<(t3 - t2)<<endl;
    Max_subarray out3 = linear_find(A, MAX_IN);   // 线性方法
    t4 = clock();
    cout<<"linear: "<<out3.left<<" "<<out3.right<<" "<<out3.sum_max<<" ms: "<<(t4 - t3)<<endl;
    return 0;
}
