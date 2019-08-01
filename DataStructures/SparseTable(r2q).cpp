/*Дано число N и последовательность из N целых чисел.
 *Найти вторую порядковую статистику на заданных диапазонах.
 *Для решения задачи используйте структуру данных Sparse Table.
 *Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных O(NlogN)
*/
/*Алоритм решения:
 *Строим SparseTable следующим образом:
 *   ST[k][i] - пара индексов(min1, min2) минимальных элементов на отрезке [array[i], array[i+2^k]]
 *   причем min1<min2
 *   При k > 0 построение происходит по формуле: ST[k][i] = min_pair(ST[k-1][i], ST[k-1][i + 2^(k)])
 *   min_pair(pair1, pair2) - возвращает пару индексов мин эл-ов из отрезка образованного парами pair1, pair2
 *
 * Кол-во уровней в таблице = log2(n),
 * на каждом уровне O(n) элементов =>
 * Всего О(nlogn) элементов в таблице, каждое значение вычисляется за О(1) =>
 * Время препроцессинга = O(nlogn)
 *
 * Получение 2 порядковой статистики на диапазоне:
 * Если right - left = 1: ans = ST[0][l].second
 * Если k = log(right - left + 1):
 * ans = min_pair(ST[k-1][l], ST[k-1][right - 2^k + 1]).second
 **/

#include <iostream>
#include <vector>
#include <algorithm>


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;


class R2Q {
public:
    R2Q(vector<int>& _array);
    void SparseTable();
    int RecLog(int x);
    void Log();
    void Pow();
    pair <int, int> GetMinPair(pair <int, int> &pair1, pair <int, int> &pair2) const;
    int GetValue(int left, int right) const;

private:
    vector <vector<pair<int, int>>> st;
    vector <int> log;
    vector <int> pow;
    vector <int> array;
};

R2Q::R2Q(vector<int>& _array): array(_array){}

int R2Q::RecLog(int x) {
    if( x == 1 ) {
        return 0;
    } else {
        return RecLog(x / 2) + 1;
    }
}

void R2Q::Log() {
    log.emplace_back(-1); //log[0] = -1
    for( int i = 1; i < array.size() + 1; i++ ) {
        log.emplace_back(RecLog(i));
    }
}

void R2Q::Pow() {
    //pow[i] = 2^i
    pow.emplace_back(1);
    for(int i = 1; i < log[array.size()] + 1; i++) {
        pow.emplace_back(pow[i - 1] * 2);
    }
}

pair <int, int> R2Q::GetMinPair(pair<int, int> &pair1, pair<int, int> &pair2) const{
    vector <int> section;
    section.emplace_back(array[pair1.first]);
    section.emplace_back(array[pair1.second]);
    if( pair2.first != pair1.first && pair2.first != pair1.second) {
        section.emplace_back(array[pair2.first]);
    }
    if( pair2.second != pair1.first && pair2.second != pair1.second) {
        section.emplace_back(array[pair2.second]);
    }

    sort(section.begin(), section.end());

    int min1, min2;

    //Поиск индексов min1, min2
    if( section[0] == array[pair1.first] ) {
        min1 = pair1.first;
        if( section[1] == array[pair1.second] ) {
            min2 = pair1.second;
        }
        else {
            if( section[1] == array[pair2.first] && pair2.first != pair1.first) {
                min2 = pair2.first;
            } else {
                min2 = pair2.second;
            }
        }
    }

    if( section[0] == array[pair2.first] ) {
        min1 = pair2.first;
        if( section[1] == array[pair2.second] ) {
            min2 = pair2.second;
        } else {
            if( section[1] == array[pair1.first] && pair1.first != pair2.first) {
                min2 = pair1.first;
            } else {
                min2 = pair1.second;
            }
        }
    }

    pair <int, int> result = make_pair(min1, min2);
    return result;
}

void R2Q::SparseTable() {
    int n = array.size();
    st.assign(log[n], vector <pair <int, int>>(n, {-1, -1})); //(min1_index, min2_index)

    //Заполняем ST[0]
    for( int i = 0; i < n - 1; i++ ) {
        if( array[i] < array[i + 1] ) {
            st[0][i] = make_pair(i, i + 1);
        } else {
            st[0][i] = make_pair(i + 1, i);
        }
    }

    //Заполняем ST[1],...,ST[log[n]-1]
    for( int i = 1; i < log[n]; i++) {
        for( int j = 0; j < n; j++) {
            if( j + pow[i] < n ) { //j + 2^(i)<n
                st[i][j] = GetMinPair(st[i - 1][j], st[i - 1][j + pow[i]]);
            }
        }
    }
}

int R2Q::GetValue(int left, int right) const {
    if( right - left == 1 ) {
        return array[st[0][left].second];
    }

    int k = log[right - left + 1];

    pair <int, int> ans = GetMinPair(st[k-1][left], st[k-1][right - pow[k] + 1]);
    return array[ans.second];
}

void Solve(int n, int m){
    vector<int> array;
    for( int i = 0; i < n; i++ ) {
        int x;
        cin >> x;
        array.emplace_back(x);
    }

    R2Q r2q(array);

    r2q.Log();
    r2q.Pow();
    r2q.SparseTable();

    for( int i = 0; i < m; i++ ) {
        int l, r;
        cin >> l >> r;
        cout << r2q.GetValue(l - 1, r - 1) << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    Solve(n, m);
}