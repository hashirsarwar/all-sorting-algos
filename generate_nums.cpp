/*
Generates 100000 random integers
and saves them in file.txt.
*/
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
  ofstream fout;
  fout.open("file.txt");
  for (int i = 0; i < 1000000; i++)
  {
    fout << rand() << endl;
  }
  fout.close();
  cout << "Done\n";
  return 0;
}