/*
Generates random integers
and saves them in file.txt.
*/
#include <fstream>
#include <iostream>
#include <random>
using namespace std;
int main()
{
  ofstream fout;
  random_device rd;
  int elements, start, end;
  cout << "enter no of elements\n";
  cin >> elements;
  cout << "enter range start\n";
  cin >> start;
  cout << "enter range end\n";
  cin >> end;
  uniform_int_distribution<int> dist{start, end};
  fout.open("file.txt");
  for (int i = 0; i < elements; i++)
  {
    fout << dist(rd) << endl;
  }
  fout.close();
  cout << "Done\n";
  return 0;
}