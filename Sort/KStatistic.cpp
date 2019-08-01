/*Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.*/

#include <iostream>

using std::cin;
using std::cout;
using std::swap;

int pivot(int* array, int left, int right){
    int midlle = (left + right) / 2;
    int tmp;
	
    if (array[right] > array[left])
        (array[left] > array[midlle] ? tmp = left : tmp = midlle);
    else
        (array[right] > array[midlle] ? tmp = right : tmp = midlle);
	
    return tmp;
}


int Partition(int* array, int left, int right){
    swap(array[right], array[pivot(array, left, right)]);
    int j = left;
	
    for(int i = left; i < right; i++)
        if(array[i] < array[right]){
            swap(array[i], array[j]);
            j++;
        }
		
    swap(array[j], array[right]);
    return j;
}

int KStat(int* array, int n, int k){
    int left = 0;
    int right = n - 1;
	
    while (true){
        int p = Partition(array, left, right);
        if (p < k){
            left = p +1;
        }
        else{
            if(p > k)
                right = p - 1;
            else
                return array[k];
        }
    }
}

int main(){
    int n, k;
    cin >> n >> k;
    int * arr = new int[n];
	
    for(int i = 0; i < n; ++i)
        cin >> arr[i];
	
    cout << KStat(arr, n, k);
	
    delete[] arr;
    return 0;
}
