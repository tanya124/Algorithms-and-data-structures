#include <iostream>

using std::cout;
using std::cin;

void Merge(int* a, int size_a, int* b, int size_b, int* c ){
    int i = 0, j = 0;
    while(i < size_a && j < size_b){
        if(a[i] <= b[j]){
            c[i + j] = a[i];
            ++i;
        }
        else {
            c[i + j] = b[j];
            ++j;
        }
    }

    if( i == size_a ) {
        for( ; j < size_b; ++j )
            c[i + j] = b[j];

    }
    else {
        for( ; i < size_a; ++i )
            c[i + j] = a[i];

    }
}

void QuickSort(int *arr, int left, int right){
    int pivot;
    int l_hold = left;
    int r_hold = right;

    pivot = arr[left];

    while(left < right){
        while ((arr[right] >= pivot) && (left < right))
            right--;

        if(left != right){
            arr[left] = arr[right];
            left++;
        }

        while((arr[left] <= pivot) && (left < right))
            left++;

        if (left != right){
            arr[right] = arr[left];
            right--;
        }
    }

    arr[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;

    if(left < pivot)
        QuickSort(arr, left, pivot - 1);

    if(right > pivot)
        QuickSort(arr, pivot + 1, right);
}

void MergeSort(int* array, int n, int k){
    for (int i = 0; i < n; i += k)
        if(i != n - n % k)
            QuickSort(array, i, i + k - 1);
        else
            QuickSort(array, i, i + (n % k) - 1);

    int c[2 * k];
    int tmp1[k];
    int tmp2[k];

    for(int i = 0; i < k; i++)
        tmp1[i] = array[i];

    for(int j = k; j < n; j++){
        tmp2[j % k] = array[j];

        if(j % k == k - 1){
            Merge(tmp1, k, tmp2, k, c);
            for(int i = 0; i < 2*k; i++){
                array[j - (2*k - 1) + i] = c[i];
                if(i >= k)
                    tmp1[i % k] = c[i];
            }
        }

        if (n%k!=0 && j == n - 1){
            Merge(tmp1, k, tmp2, n % k, c);
            for(int i = 0; i < k + n % k; i++){
                array[j - (k + n % k - 1) + i] = c[i];
            }
        }
    }
}

int main(){
    int n, k;
    cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    MergeSort(arr, n, k);

    for(int i = 0; i<n;i++)
        cout << arr[i] << " ";

    return 0;
}