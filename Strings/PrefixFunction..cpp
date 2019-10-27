/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).*/
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::string;

vector<int> PrefixFunction(const string& pattern){
    vector<int> ans(pattern.size(), 0);
    for(size_t i = 1; i < pattern.size(); ++i){
        int k = ans[i-1];
        while(k > 0 && pattern[i] != pattern[k]){
            k = ans[k-1];
        }
        if(pattern[i] == pattern[k]){
            k++;
        }
        ans[i] = k;
    }
    return ans;
}

vector<int> SearchSubStr(const string& pattern){
    vector<int> ans;
    const vector<int> prefix_func_pattern = PrefixFunction(pattern);
    size_t last_prefix_func_value = 0;
    size_t i = 0;
    char symb;
    while(cin.get(symb)){
        size_t current_value = last_prefix_func_value;

        while(current_value > 0 && symb != pattern[current_value]){
            current_value = prefix_func_pattern[current_value - 1];
        }

        if(symb == pattern[current_value]){
            last_prefix_func_value = current_value + 1;
        } else {
            last_prefix_func_value = 0;
        }

        if(last_prefix_func_value == pattern.size()){
            ans.push_back(i - pattern.size() + 1);
        }
        ++i;

        if(cin.peek() == EOF || cin.peek() == '\n'){
            break;
        }
    }
    return ans;
}

int main(){
    string pattern;
    cin >> pattern;
    cin.ignore(1); //пробел или \n
    vector<int> ans = SearchSubStr(pattern);

    for(auto i : ans){
        cout << i << " ";
    }
    return 0;
}
