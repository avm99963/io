#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Crida ./uniformgen n a b" << endl;
    return 1;
  }
  
  int n = atoi(argv[1]);
  int a = atoi(argv[2]);
  int b = atoi(argv[3]);

  cout << "param n:=" << n << ";" << endl << "param a:=" << a << ";" << endl << "param b:=" << b << ";" << endl << endl << "param x:= ";
  for (int i = 0; i <= n; ++i) {
    cout << i << " " << a*((double)i/n)*((double)i/n) << " " << (i == n ? ";" : "");
  }
}
