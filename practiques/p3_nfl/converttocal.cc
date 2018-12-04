#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;

int n, r, s;
VVVI results;

int main() {
  cin >> n >> r >> s;
  string welcome = "    CALENDARI DE LA NFL    ";
  cout << string(welcome.length(), '=') << "\n" << welcome << "\n" << string(welcome.length(), '=') << "\n";
}
