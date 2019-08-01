/*Задано дерево с корнем, содержащее (1 ≤ n ≤ 100 000) вершин, пронумерованных от 0 до n-1.
Требуется ответить на m (1 ≤ m ≤ 10 000 000) запросов о наименьшем общем предке для пары вершин.
Запросы генерируются следующим образом. Заданы числа a1, a2 и числа x, y и z.
Числа a3, ..., a2m генерируются следующим образом: ai = (x ⋅ ai-2 + y ⋅ ai-1 + z) mod n.
Первый запрос имеет вид (a1, a2). Если ответ на i-1-й запрос равен v, то i-й запрос имеет вид ((a2i-1 + v) mod n, a2i).
Для решения задачи можно использовать метод двоичного подъёма.*/

/*Алгоритм решения:
 *Делаем dfs обход по дереву и запоминаем вермя входа и выхода для каждой вершины.(чтобы потом посмотреть является ли одна вершина предком другой)
 *Зпоминаем массив из l = log(N) предков для каждой вершины(если вершина выше уровня l, то в конце корень повторяется несколько раз)
 *Даны вершины А и Б. Сначала проверяем не является ли одна из них предком другой,
 * если да, то задача решена,
 * если нет, то берем самого старшего предка вершины А, смотрим является ли он предком Б,
 * если да, то переходим к менее старшему, смотрим является ли он, и так далее, когда находим того, который не является предком вершины Б
 * (мы его обязательно найдем, так как иначе Б - предок А, а мы это уже исключили).
 * Выбрав это предка А, берем его предка (который еще являлся предком Б), это и будет ответом.
 * */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;


class NextPair{
public:
    NextPair(long long a, long long b, long long x, long long y, long long z, long long n):
        _a(a), _b(b), _x(x), _y(y), _z(z), _n(n) {}


    pair<long long, long long> GetPair(long long result){
        pair<long long, long long> ans((_a + result) % _n, _b);
        _a = (_a * _x + _b * _y + _z) % _n;
        _b = (_b * _x + _a * _y + _z) % _n;
        return ans;
    }

private:
    long long _a;
    long long _b;
    long long _x;
    long long _y;
    long long _z;
    long long _n;
};

class LCA{
public:
    LCA(vector<vector<long long>>& parents){
        n = parents.size();
        tree = parents;
        tin.resize(parents.size());
        tout.resize(parents.size());
        up.resize(parents.size());
        lvl = 1;
        timer = 0;

        while((1<<lvl) <= n)
            ++lvl;

        for(long long i = 0; i < n; ++i)
            up[i].resize(lvl+1);

        dfs(0);
    }

    long long lca(long long a, long long b) {
        if (upper(a, b)) 
            return a;
        if (upper(b, a)) 
            return b;

        for (long long i = lvl; i >= 0; --i)
            if (!upper(up[a][i], b)) 
                a = up[a][i];

        return up[a][0];
    }

private:
    void dfs(long long v, long long p = 0){
        tin[v] = ++timer;
        up[v][0] = p;
        for (long long i = 1; i <= lvl; ++i)
            up[v][i] = up[up[v][i-1]][i-1];
        for (long long i = 0; i < tree[v].size(); ++i) {
            long long to = tree[v][i];
            if (to != p)
                dfs(to, v);
        }
        tout[v] = ++timer;
    }

    bool upper (long long a, long long b) {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    }


    long long n, lvl, timer;
    vector<vector<long long>> tree;
    vector<vector<long long>> up; //up[v][i] - номер вершины, в котрую мы придем, если пройдем из v вверх по дереву 2^i шагов
    vector<long long> tin, tout; //массивы хранящие время входа и время выхода из вершины соотв.
};

long long GetAnswer(LCA& lca, NextPair& nextPair, long long m){
    long long ans = 0, result = 0;
    for (long long i = 0; i < m; i++) {
        pair<long long, long long> node = nextPair.GetPair(result);
        result = lca.lca(node.first, node.second);
        ans += result;
    }
    return ans;
}

int main() {
    long long n, m;
    cin >> n >> m;
    vector<vector<long long>> parents(n);

    for (long long i = 1; i < n; ++i) {
        long long x;
        cin >> x;
        parents[x].emplace_back(i);
    }

    long long a1, a2;
    cin >> a1 >> a2;
    long long x, y, z;
    cin >> x >> y >> z;
    NextPair nextPair(a1, a2, x, y, z, n);

    LCA lca(parents);

    cout << GetAnswer(lca, nextPair, m);
}