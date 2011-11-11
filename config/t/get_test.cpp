#include "get.hpp"

#include <iostream>
using namespace std;

int main() {
  string file("test.txt");
  string data = get(string(file));
  cout << file << ":" << endl << data << endl;

  return 1;
}
