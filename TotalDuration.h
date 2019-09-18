#pragma once
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>

using std::cerr;
using std::endl;
using std::string;
using std::ostringstream;

using namespace std::chrono;

struct TotalDuration {
    string message;
    steady_clock::duration value;
    explicit TotalDuration(const string& msg = "")
            : message(msg + ": ")
            , value(0)
    {
    }
    ~TotalDuration() {
        ostringstream os;
        os << message
           << duration_cast<milliseconds>(value).count()
           << " ms" << endl;
        cerr << os.str();
    }
};
class AddDuration {
public:
    explicit AddDuration(steady_clock::duration& dest)
            : add_to(dest)
            , start(steady_clock::now())
    {
    }
    explicit AddDuration(TotalDuration& dest)
            : AddDuration(dest.value)
    {
    }
    ~AddDuration() {
        add_to += steady_clock::now() - start;
    }
private:
    steady_clock::duration& add_to;
    steady_clock::time_point start;
};
#define ADD_DURATION(value) \
AddDuration UNIQ_ID(__LINE__){value};
