#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

struct cmp {
    bool operator()(const char a, const char b) const {
        return a > b;
    }
};

int main() {
    map<string, set<char,cmp> > m;
    m["hola"] = {'a','b','c','d'};
    m["adeu"] = {'e','z'};
    map<string, set<char,cmp> >::const_iterator it = m.begin();
    while (it != m.end()) {
        cout << it->first << '\t';
        set<char,cmp>::const_iterator its = it->second.begin();
        while (its != it->second.end()) {
            cout << *its << ' ';
            ++its;
        }
        cout << '\n';
        ++it;
    }
    cout << endl;
}
