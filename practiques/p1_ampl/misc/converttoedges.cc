#include <iostream>
using namespace std;

int main() {
  int i, j, k;
  while (cin >> i >> j >> k) {
    cout << "\\path [->] (" << i << ") edge node {" << k << "} (" << j << ");" << endl;
  }
}
