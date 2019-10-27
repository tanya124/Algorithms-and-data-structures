/*Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z.*/
#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::set;
using std::pair;


class Alphabet{
public:
    Alphabet(const set<char>& alphabet_elements) : _size(alphabet_elements.size()), _alphabet(alphabet_elements.begin(), alphabet_elements.end())
    {}

    const char& operator[](size_t index) const {
        return _alphabet[index];
    }

    size_t size() const {
        return _size;
    }

    size_t get_index(char ch) const {
        for(size_t i = 0; i < _size; ++i){
            if(ch == _alphabet[i]){
                return i;
            }
        }
    }

private:
    size_t _size;
    vector<char> _alphabet;
};

string BuildFromPrefix(const vector<int>& prefix_vector, const Alphabet& alphabet){
    string ans;
    const size_t ALPHABET_SIZE = alphabet.size();

    for(size_t i = 0; i < prefix_vector.size(); ++i){
        if(prefix_vector[i] == 0){
            if(i == 0){
                ans += alphabet[0];
            }
            else{
                //Спускаемся по последовательности, как в префикс функции
                vector<bool> used_letters (ALPHABET_SIZE, false);
                int j = prefix_vector[i - 1];

                while(j > 0){
                    used_letters[alphabet.get_index(ans[j])] = true;
                    j = prefix_vector[j - 1];
                }

                //Находим еще не использованную букву
                char c = alphabet[1];
                while(used_letters[alphabet.get_index(c)]){
                    c = alphabet[alphabet.get_index(c) + 1];
                }
                ans += c;
            }

        }
        else {
            ans += ans[prefix_vector[i] - 1];
        }
    }
    return ans;
}



int main(){
    vector<int> v ;//= {0,0,1,0,1,2,3,0};
    int i;
    while(cin >> i){
        v.push_back(i);
    }
    const set<char> a = {'a', 'c', 'e', 'g', 'z'};
    //0,0,1,0,1,2,3,0 = acaeacag
    Alphabet alphabet(a);
    cout << BuildFromPrefix(v, alphabet);
    return 0;
}
