﻿/*Шаг 1. Строится минимальное остовное дерево (алгоритм Прима или Краскала).
Шаг 2. На множестве вершин дерева, имеющих нечетную степень, находится паросочетание минимального веса. Таких вершин в любом графе - четное число.
Шаг 3. Каркас преобразуется в эйлеров граф путем присоединения ребер, соответствующих найденному паросочетанию.
Шаг 4. В построенном графе находится эйлеров маршрут.
Шаг 5. Эйлеров маршрут преобразуется в маршрут коммивояжера*/ 

#include "include/TSP.h"
#include "include/Generator.h"
#include "include/TSP_2.h"
#include "include/test.h"

int main(){
    cout<<"Results for N = 8"<<endl;
    test(8, 10);

    cout<<"Results for N = {2,...,10}"<<endl;
    test(2, 10, 1);
}
