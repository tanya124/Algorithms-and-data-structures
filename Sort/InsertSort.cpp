/*Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
Предполагается, что никакие три точки не лежат на одной прямой.
Стройте ломаную от точки, имеющей наименьшую координату x.
Если таких точек несколько, то используйте точку с наименьшей координатой y. 
Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
Для сортировки точек реализуйте алгоритм сортировки вставками.*/


#include <iostream>

using std::cout;
using std::cin;


struct Dot{
    int x;
    int y;
    double tg; 
	
    Dot() : x(0), y(0), tg(0) { }
};


void InsertionSort( Dot* a, int n){
    for(int i = 1; i < n; ++i){
        double t = a[i].tg;
        int x_coord = a[i].x;
        int y_coord = a[i].y;
        int j = i - 1;
		
        for( ; j >= 0 && (t >= a[j].tg) ; --j){
            if (t > a[j].tg){
                a[j + 1].tg = a[j].tg;
                a[j + 1].x = a[j].x;
                a[j + 1].y = a[j].y;
            }
        }
		
        a[j + 1].tg = t;
        a[j + 1].x = x_coord;
        a[j + 1].y = y_coord;
    }
}

int main()
{
    int n, x, y;
    int min_x = 100001, min_y = 100001; 
    Dot tmp;
    cin >> n;
	
    Dot arr[n];
	
    for (int i = 0; i < n; ++i){
        cin >> x >> y;
        tmp.x = x;
        tmp.y = y;
        
        if (x < min_x) {
            min_x = x;
            min_y = y;
        }
        if (x == min_x){
            if (min_y > y)
                min_y = y;
        }
        arr[i] = tmp;
    }
	
    for (int i = 0; i < n; ++i){
        if (arr[i].x != min_x)
            arr[i].tg = (double)(arr[i].y - min_y)/(double)(arr[i].x - min_x);
        else
            (arr[i].y == min_y ? arr[i].tg = 100001.0 :  arr[i].tg = 100000.0);
    }

    InsertionSort(arr, n);

    for (int i = 0; i < n; ++i)
        cout << arr[i].x <<" "<< arr[i].y <<endl;

    return 0;
}
