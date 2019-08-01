/*Во входном файле содержится начальная конфигурация головоломки – 3 строки по 3 числа в каждой.
Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек,
которое нужно сделать, чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую последовательность ходов:
L означает, что в результате перемещения костяшки пустая ячейка сдвинулась влево, R – вправо, U – вверх, D – вниз.
 Если таких последовательностей несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно число −1.
*/
/*Алгоритм решения:
 *Будем рассматривать всевозможные состояния, достяжимые из начального состояния, пока не встретим нужное состояние или не рассмотрим все состояния
 *1) Создаем очередь состояний и добавляем туда начальное состояние
 *2) Пока эта очередь не пуста и конечное состояние не найдено:
      -проверяем не является ли текщее состояние конечным
      -находим все состояния, в которые мы можем попасть из текущего состояния за один ход
      -рассматриваем каждое найденное состояние
      -если в рассматриваемом состоянии мы еще не были, добавляем его в очередь и находим длину пути и путь до него от начального состояния
*/
#include <iostream>
#include<vector>
#include<queue>
#include<map>
#include <string>
#include <set>

using std::set;
using std::cin;
using std::endl;
using std::cout;
using std::vector;
using std::queue;
using std::map;
using std::string;

void FindNextStages(vector<int> &cur, vector<std::pair<vector<int>, char>> &nextStages){
    int index_0 = 0; 
    for(int i = 0; i < 9; ++i)
        if (cur[i] == 0){
            index_0 = i;
            break;
        }

    //Находим всевозможные состояния досяжимые из текущего
    if( index_0 != 0 && index_0 != 1 && index_0 != 2 ) { 
        vector <int> tmp = cur;
        std::swap(tmp[index_0], tmp[index_0 - 3]);
        nextStages.emplace_back(std::make_pair(tmp, 'U'));
    }

    if( index_0 != 6 && index_0 != 7 && index_0 != 8 ) {
        vector <int> tmp = cur;
        std::swap(tmp[index_0], tmp[index_0 + 3]);
        nextStages.emplace_back(std::make_pair(tmp, 'D'));
    }

    if( index_0 != 2 && index_0 != 5 && index_0 != 8 ) { 
        vector <int> tmp = cur;
        std::swap(tmp[index_0], tmp[index_0 + 1]);
        nextStages.emplace_back(std::make_pair(tmp, 'R'));
    }

    if( index_0 != 0 && index_0 != 3 && index_0 != 6 ) {
        vector <int> tmp = cur;
        std::swap(tmp[index_0], tmp[index_0 - 1]);
        nextStages.emplace_back(std::make_pair(tmp, 'L'));
    }
}

void bfs(vector<int> &beginStages){
    vector<int> endStages = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    map <vector <int>, int> Dist; //словарь, сопоставляющий состоянию длину пути до него из beginCondition
    map <vector <int>, string> Way; // словарь, сопоставляющий состоянию путь до него из beginCondition
    set<vector<int>> visited; //уже пройденые состояния
    queue<vector<int>> queue; //очередь состояний

    Dist.insert(std::pair <vector <int>, int>(beginStages, 0));
    Way.insert(std::pair <vector <int>, string>(beginStages, ""));
    visited.insert(beginStages);
    queue.push(beginStages);

    bool found = false;

    while( !queue.empty() && !found ) {
        vector <int> cur = queue.front();
        queue.pop();
        if(cur == endStages) {
            found = true;
            break;
        }

        vector <std::pair<vector <int>, char>> nextStages; //вектор хранящий следующие состояния
        FindNextStages(cur, nextStages);
        for( int i = 0; i < nextStages.size(); ++i ) { //рассматриваем найденные состояния
            vector <int> x = nextStages[i].first;
            if( visited.count(x) == 0 ) { //если в этом состоянии мы еще не были, добавляем его в очередь
                visited.insert(x);
                queue.push(x);

                char way = nextStages[i].second;
                string path = Way[cur] + way;
                Way.insert( std::pair <vector <int>, string>(x, path));

                int dist = Dist[cur] + 1;
                Dist.insert( std::pair <vector <int>, int>(x, dist));
            }
        }
    }

    if( found == false ) {
        cout << -1;
    } else {
        cout << Dist[endStages] << endl;
        cout << Way[endStages] << endl;
    }
}

int main() {
    vector<int> beginCondition;
    for(int i = 0; i < 9; ++i){
        int x;
        cin >> x;
        beginCondition.push_back(x);
    }

    bfs(beginCondition);
    return 0;
}