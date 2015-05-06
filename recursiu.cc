#include <iostream>
using namespace std;
bool evalua () {
  bool left, right;
  char op,c;
  cin >> c;
  if (c == '(') {
    left = evalua();
    cin >> op;
    right = evalua();
    cin >> c;
    if (op == '.') return left and right;
    else return left or right;   
  }
  else return c - '0';
}

int main() {
  cout << evalua() << endl;
}
