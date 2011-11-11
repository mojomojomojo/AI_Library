#include "get.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string get( string name ) {
  char* temp = tmpnam(NULL);
  stringstream cmd(stringstream::in|stringstream::out);
  cmd << "python get.py " << name << " " << temp;
  system(cmd.str().c_str());
  ifstream fin(temp,ifstream::in);
  string data;
  char buffer[1024];
  while (fin.good()) {
    fin.get(buffer,1024);
    data += string(buffer);
  }
  fin.close();
  unlink(temp);
  return data;
}

void put( string data ) {
}

void put( string name, string remote ) {
}
