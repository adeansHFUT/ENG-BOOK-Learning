#include <iostream>

using namespace std;

int inversion = 0;
int A[5] = {2, 3, 8, 6, 1};

void my_merge(int a[], int p, int q, int r)
{
    int i, j, k;
    int n1 = q - p + 1 ;
    int n2 = r - q;
    int L[n1];
    int R[n2];
    for(i = 0; i < n1; i++)
        L[i] = a[p+i];
    for(i = 0; i < n2; i++)
        R[i] = a[q+1+i];
//    for(int i = 0; i < n1; i++)
//        cout<<L[i];
//    cout<<endl;
//    for(int i = 0; i < n2; i++)
//        cout<<R[i];
    for(i = 0, j = 0, k = p; k <= r; k++)
    {
        if (i == n1)
            A[k] = R[j++];
        else if(j == n2)
            A[k] = L[i++];
        else if(L[i] < R[j])
            A[k] = L[i++];
        else
        {
            A[k] = R[j++];
            inversion += n1-i;      //有n1-i个L[]元素在R[j]后面
        }
    }


}

void merge_sort(int a[], int p, int r)
{
    if(p < r)
    {
        int q = (p+r)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        my_merge(a, p, q, r);
    }
}

int main()
{
    merge_sort(A, 0, 4);
    for(int i = 0; i < 5; i++)
        cout<<A[i];
    cout<<endl<<inversion<<endl;
    return 0;
}


