/*Дан массив из нулей и единиц a0, a1, ..., an-1.
 * Для каждого запроса [left, right] найдите такой подотрезок al, al+1, ...,ar этого массива (0 <= left <= l <= r <= right < n),
 * что числа al, al+1, …, ar являются максимально возможной последовательностью единиц.*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;


// Возвращает минимальное x, такое что: value < 2^x
int log2(int value){
    int answer = 0;
    for (int i = 1; i < value; i *= 2){
        answer++;
    }
    return answer;
}

// Возвращает 2^value
int pow(int value){
    int answer = 1;
    for (int i = 0; i < value + 1; i++){
        answer *= 2;
    }
    return answer;
}

class SegmentTree{
public:
    SegmentTree(const vector<int> &array) {
        int size = array.size();
        data node;
        node.prefix=node.suffix=node.max_subsequence=node.len=0;
        tree.assign(pow(log2(size)) * 2 + 1, node);

        for (int i = pow(log2(size)); i < pow(log2(size)) * 2 + 1; ++i){
            int x;
            if (i - pow(log2(size)) < size) {
                x = array[i - pow(log2(size))];
                tree[i].prefix = tree[i].suffix = tree[i].max_subsequence = x;
                tree[i].len = 1;
            }
            else
                tree[i].prefix = tree[i].suffix = tree[i].max_subsequence = 0;
        }

        build(1, 0, pow(log2(size)) - 1);
    }

    int GetAnswer(int N, int left, int right){
        return query(1, 0, pow(log2(N)) - 1, left, right).max_subsequence;
    }

private:
    struct data{
        int prefix; //Кол-во подряд идущих 1 в начале отрезка
        int suffix; //Кол-во подряд идущих едениц в конце отрезка
        int max_subsequence; //Наибольшая подпоследовательность 1 на отрезке
        int len; //Длина отрезка

        data() {}

        data(data left, data right){
            if (left.prefix == left.len){
                prefix = left.prefix + right.prefix;
            } else {
                prefix = left.prefix;
            }

            if (right.suffix == right.len){
                suffix = right.suffix + left.suffix;
            } else {
                suffix = right.suffix;
            }

            max_subsequence = max(left.suffix + right.prefix,
                                  max(left.max_subsequence, right.max_subsequence));

            len = left.len + right.len;
        }
    };

    void build (int StartVertex, int LeftBorder, int RightBorder){
        if (LeftBorder != RightBorder){
            int MiddleBorder = (LeftBorder + RightBorder) / 2;
            build (StartVertex * 2, LeftBorder, MiddleBorder);
            build (StartVertex * 2 + 1, MiddleBorder + 1, RightBorder);
            tree[StartVertex] = data(tree[StartVertex * 2], tree[StartVertex * 2 + 1]);
        }
    }

    data query(int StartVertex, int LeftBorder, int RightBorder, int Left, int Right){
        if (Left == LeftBorder && RightBorder == Right){
            return tree[StartVertex];
        }

        int MiddleBorder = (LeftBorder + RightBorder) / 2;
        if (Right <= MiddleBorder){
            return query (StartVertex * 2, LeftBorder, MiddleBorder, Left, Right);
        }
        if (Left > MiddleBorder){
            return query (StartVertex * 2 + 1, MiddleBorder + 1, RightBorder, Left, Right);
        }
        return data(query (StartVertex * 2, LeftBorder, MiddleBorder, Left, MiddleBorder),
                    query (StartVertex * 2 + 1, MiddleBorder + 1, RightBorder, MiddleBorder + 1, Right));
    }

    vector<data> tree;
};


int main(){
    int N, M;
    cin >> N >> M;

    vector<int> array(N);
    for(int i = 0; i < N; ++i){
        int x;
        cin >> x;
        array[i] = x;
    }

    SegmentTree Tree(array);

    for (int i = 0; i < M; ++i){
        int left, right;
        cin >> left >> right;
        cout << Tree.GetAnswer(N, left, right)<< endl;
    }
}