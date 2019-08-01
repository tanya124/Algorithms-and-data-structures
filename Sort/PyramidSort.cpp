/*Группа людей называетс€ современниками если был такой момент, когда они могли собраться вместе.
 * Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
 * Дан список жизни великих людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собрани€х,
 * а в день 80лети€ и в день смерти уже не может.*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::swap;


struct Date {
    Date(){}
    Date(int year, int month, int day, int type):
        year(year), month(month), day(day), type(type){}

    friend bool operator< (const Date& d1, const Date& d2){
        return (d1.year < d2.year) ||
                (d1.year == d2.year && d1.month < d2.month) ||
                (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day) ||
                (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.type > d2.type);
    }

    int year;
    int month;
    int day;
    int type; //0-рождение, 1 - смерть
};

struct Man {
    Date birth;
    Date death;

    Man(Date& birth, Date& death) {
        this->birth = birth;
        this->death = death;
    }

    Date birth18(){
        Date date_18(birth.year+18, birth.month, birth.day, 0);
        return (date_18);
    }


    Date date_end(){
        Date date_eighty(birth.year+80, birth.month, birth.day, 1);
        return (date_eighty < death ? date_eighty : death);
    }

    bool dead_after_eighteen(){
        Date tmp(birth.year+18, birth.month, birth.day, 0);
        return tmp < death;
    }
};

template <typename T>
class Heap {
public:
    Heap(): size(0) { }

    Heap(vector<T>& arr) {
        size = arr.size();
        buffer = arr;

        for(int i = size/2 - 1; i >= 0; i--)
            siftDown(i);
    }

    void siftDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if(left < size && buffer[largest]<(buffer[left]))
            largest = left;

        if(right < size && buffer[largest]<(buffer[right]))
            largest = right;

        if(largest != index) {
            swap(buffer[largest], buffer[index]);
            siftDown(largest);
        }
    }

    void Sort() {
        int old_size = size;
        while(size > 1) {
            swap(buffer[0], buffer[size-1]);
            --size;
            siftDown(0);
        }
        size = old_size;
    }

    int max_num_sovr() const{
        int k = 0, max_k = 0;
        for(int i = 0; i < size; i++) {
            if(buffer[i].type == 0) {
                k++;
            }
            if(buffer[i].type == 1) {
                k--;
            }
            if(k > max_k)
                max_k = k;
        }

        return max_k;
    }

private:
    int size;
    vector <T> buffer;
};

int main() {
    vector<Date> arr;
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        Date birth, death;
        cin>> birth.day >> birth.month >>birth.year >> death.day >> death.month >> death.year;
        birth.type = 0; death.type = 1;
        Man man(birth, death);
        
        if(man.dead_after_eighteen()) { 
            arr.push_back(man.birth18());
            arr.push_back(man.date_end());
        }
    }
    
    Heap<Date> heap(arr);
    heap.Sort();
    cout<<heap.max_num_sovr();

    return 0;
}
