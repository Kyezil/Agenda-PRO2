#include <iostream>
#include <list>
#include <set>
using namespace std;

template<typename Iterator>
void merge_or(Iterator in1, Iterator in2, list<int>& l){
    list<int>::iterator it_l = l.begin();
    while (in1 != in2 and not l.empty()) {
        if (*in1 < *it_l){
            l.insert(it_l, *in1);
            ++in1;
        }
        else if (*it_l < *in1) ++it_l;
        else ++it_l, ++in1;
    }
    while (in1 != in2) {
        l.insert(it_l, *in1);
        ++in1;
    }
}

template<typename Iterator>
void merge_and(Iterator in1, Iterator in2, list<int>& l){
    list<int>::iterator it_l = l.begin();
    while (in1 != in2 and not l.empty()) {
        if(*in1 < *it_l) ++in1;
        else if(*it_l < *in1) it_l = l.erase(it_l);
        else ++it_l, ++in1;
    }
    while (it_l != l.end()) it_l = l.erase(it_l);
}

void print(list<int>& l) {
    for (int i : l)
        cout << i << ' ';
    cout << '\n';
}

int main() {
    set<int> s1 = {1,3,5,7,9};
    list<int> s2 = {2,4,6,8};
    list<int> fusio;
    merge_or(s1.begin(), s1.end(), fusio);
    print(fusio);
    merge_or(s2.begin(), s2.end(), fusio);
    print(fusio);
    set<int> s3 = {1,5,6,9};
    merge_and(s3.begin(), s3.end(), fusio);
    print(fusio);

    cout << "CASOS ****" << endl;
    set<int> s4 = {};
    merge_and(s4.begin(), s4.end(), fusio);
    print(fusio);
}
