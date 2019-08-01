/*Реализуйте структуру данных типа “множество строк”
на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми.
Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.
1_1 Для разрешения коллизий используйте квадратичное пробирование. i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.*/

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Node{
    Node(): data(""), deleted(false){}

    string data;
    bool deleted;
};

class HashTable{
public:
    HashTable();

    bool insert(const string &key) noexcept;
    bool search(const string &key) const noexcept;
    bool remove(const string &key) noexcept;

private:
    explicit HashTable (int new_size): bufferSize(new_size), size(0), buffer(new_size) {};
    void rehash() noexcept ;
    int hash(const string &key) const noexcept;

    int bufferSize;
    int size;
    vector<Node> buffer;
};


HashTable::HashTable(): bufferSize(8), size(0), buffer(8){}


bool HashTable::insert(const string &key) noexcept {
    if(search(key)) 
        return false;

    if(3*bufferSize <= 4*size ) 
        rehash();

    int hash_val = hash(key); 

    int i = 0;
    while(i < bufferSize){
        if(buffer[hash_val].data.empty()){
            buffer[hash_val].data = key;
            size++;
            return true;
        }
        else if(buffer[hash_val].deleted){ 
            buffer[hash_val].data = key;
            buffer[hash_val].deleted = false;
            size++;
            return true;
        }
        i++;
        hash_val = (hash_val + i) % bufferSize;
    }
    return false;
}



bool HashTable::search(const string &key) const noexcept{
    int hash_val = hash(key); 
    int i = 0;

    while(!buffer[hash_val].data.empty() && i < bufferSize){ 
        if(buffer[hash_val].data == key && !buffer[hash_val].deleted)
            return true;
        i++;
        hash_val = (hash_val + i) % bufferSize;
    }
    return false;
}



bool HashTable::remove(const string &key) noexcept{
    if(!search(key))
        return false;

    int hash_val = hash(key);

    int i = 0;
    while(i < bufferSize){
        if(buffer[hash_val].data == key && !buffer[hash_val].deleted){
            buffer[hash_val].deleted = true;
            size--;
            return true;
        }
        i++;
        hash_val = (hash_val + i) % bufferSize;
    }
    return false;
}

void HashTable::rehash() noexcept{
    HashTable new_buffer(bufferSize * 2);
    for (int i = 0; i < bufferSize; ++i){
        if (!buffer[i].data.empty() && !buffer[i].deleted){
            new_buffer.insert(buffer[i].data);
        }
    }
    bufferSize *= 2;
    size = new_buffer.size;
    buffer = new_buffer.buffer;
}

int HashTable::hash(const string &key) const noexcept{
    int hash_val = 0;
    for (const auto& i : key)
        hash_val = (hash_val * 23 + i) % bufferSize;
    return hash_val;
}

int main(){
    HashTable hashTable;
    char command;
    string str;

    while((cin >> command) && cin.ignore() && getline(cin, str)){
        if(command == '+'){
            if(hashTable.insert(str))
                cout <<"OK"<< endl;
            else
                cout <<"FAIL"<< endl;
        }
        else if(command == '?'){
            if(hashTable.search(str))
                cout <<"OK"<< endl;
            else
                cout <<"FAIL"<< endl;
        }
        else if(command == '-'){
            if(hashTable.remove(str))
                cout <<"OK"<< endl;
            else
                cout <<"FAIL"<< endl;
        }
    }

    return 0;
}