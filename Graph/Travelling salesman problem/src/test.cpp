#include "../include/test.h"

void test(int N, int amountTests){
    Graph graph(N);
    vector<double> result; //тут храним апроксимации

    for(int i = 0; i < amountTests; ++i){
        generator_dots(graph);

        TSP tsp1(graph);
        TSP_2 tsp2;

        double ans_tsp1 = tsp1();
        double ans_tsp2 = tsp2(graph);
        double approximation = ans_tsp1/ans_tsp2;

        result.emplace_back(approximation);
        cout<<endl;
        cout<<"***** Test "<<i+1<<" *****"<<endl;
        cout<<"Value: "<<N<<endl;
        cout<<"Approximate answer: "<< ans_tsp1 <<endl;
        cout<<"Optimal answer: "<<ans_tsp2<<endl;
        cout<<"Approximation quality: "<<approximation<<endl;
        cout<<endl;
    }

    resultTests(result);

}

void resultTests(vector<double> &result){
    double avg_approxi = 0; //среднее значение апроксимации

    for (int i = 0; i < result.size(); ++i)
        avg_approxi += result[i];

    avg_approxi = avg_approxi/result.size();

    double kv = 0; //среднеквадратичное отклонение

    for(int i = 0; i < result.size(); ++i)
        kv += pow(avg_approxi - result[i], 2.0);

    kv = kv/result.size();

    cout<<"********** Results tests **********"<<endl;
    cout<<"Average quality of approximation: "<<avg_approxi<<endl;
    cout<<"Mean square departure: "<<kv<<endl;
    cout<<"***********************************"<<endl;
}

void test(int begin, int end, int amountTests){
    vector<double> result;

    for(int j = begin; j < end + 1; ++j) {
        Graph graph(j);

        for (int i = 0; i < amountTests; ++i) {
            generator_dots(graph);

            TSP tsp1(graph);
            TSP_2 tsp2;

            double ans_tsp1 = tsp1();
            double ans_tsp2 = tsp2(graph);
            double approximation = ans_tsp1 / ans_tsp2;

            result.emplace_back(approximation);
            cout << endl;
            cout << "***** Test " << i + 1 << " *****" << endl;
            cout << "Value: " << j << endl;
            cout << "Approximate answer: " << ans_tsp1 << endl;
            cout << "Optimal answer: " << ans_tsp2 << endl;
            cout << "Approximation quality: " << approximation << endl;
            cout << endl;
        }
    }
    resultTests(result);

}