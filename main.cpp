#include <iostream>
#include <fstream>
using namespace std;

class IntegerSorter
{
private:
  int *Keys;
  int TotalKeys;

  void BubbleSort()
  {
    bool swapped;
    for (int i = 0; i < TotalKeys; i++)
    {
      swapped = false;
      for (int j = 0; j < TotalKeys - i - 1; j++)
      {
        if (Keys[j] > Keys[j + 1])
        {
          swapped = true;
          swap(Keys[j], Keys[j + 1]);
        }
      }
      if (!swapped)
        break;
    }
  }

  void SelectionSort()
  {
    int min;
    int ind = 0;
    for (int i = 0; i < TotalKeys; i++)
    {
      min = INT32_MAX;
      for (int j = i; j < TotalKeys; j++)
      {
        if (Keys[j] < min)
        {
          min = Keys[j];
          ind = j;
        }
      }
      swap(Keys[i], Keys[ind]);
    }
  }

  void InsertionSort()
  {
    int val;
    for (int i = 1; i < TotalKeys; i++)
    {
      val = Keys[i];
      for (int j = i - 1; j >= 0 && val < Keys[j]; j--)
      {
        Keys[j + 1] = Keys[j];
        Keys[j] = val;
      }
    }
  }

  void BuildMaxHeap()
  {
  }

  void Heapify()
  {
  }

  void HeapSort()
  {
  }

  void Merge(int start, int mid, int end)
  {
    int aux[end - start + 1];
    int i = start;
    int j = mid + 1;
    int count = 0;
    while (i <= mid && j <= end)
    {
      if (Keys[i] < Keys[j])
      {
        aux[count] = Keys[i];
        ++i;
      }
      else
      {
        aux[count] = Keys[j];
        ++j;
      }
      ++count;
    }
    while (i <= mid)
    {
      aux[count] = Keys[i];
      ++i;
      ++count;
    }
    while (j <= end)
    {
      aux[count] = Keys[j];
      ++j;
      ++count;
    }
    for (int x = 0; x < count; ++x, ++start)
    {
      Keys[start] = aux[x];
    }
  }

  void TopDownMergeSort(int start, int end)
  {
    if (end > start)
    {
      int mid = (start + end) / 2;
      TopDownMergeSort(start, mid);
      TopDownMergeSort(mid + 1, end);
      Merge(start, mid, end);
    }
  }

  void BottomUpMergeSort()
  {
  }

  void Partition(int left, int right, int PivotIndex)
  {
  }

  void QuickSort()
  {
  }

  void CountingSort(int MaxValue)
  {
  }
  void RadixSort()
  {
  }

  void writeToFile()
  {
    cout << "Writing result to file...\n";
    ofstream fout("result.txt");
    fout.clear();
    for (int i = 0; i < TotalKeys; i++)
    {
      fout << Keys[i] << endl;
    }
    cout << "Done\n";
  }

public:
  IntegerSorter()
  {
    Keys = 0;
    TotalKeys = 0;
  }

  ~IntegerSorter()
  {
    if (Keys)
      delete[] Keys;
  }

  bool LoadData(char FileName[], int TotalKeys)
  {
    if (Keys)
      delete[] Keys;

    this->TotalKeys = 0;
    Keys = new int[TotalKeys];

    if (!Keys)
      return false;
    this->TotalKeys = TotalKeys;
    cout << "Reading data from file...\n";
    ifstream fin(FileName);
    int count = 0;
    for (string str; getline(fin, str); count++)
    {
      Keys[count] = stoi(str);
    }
    cout << "Data read successfully.\n";
    fin.close();
    return true;
  }

  void Sort(char Method)
  {
    cout << "Sorting...\n";
    clock_t beginTime = clock();
    switch (Method)
    {
    case 'B':
    case 'b':
      BubbleSort();
      break;
    case 'S':
    case 's':
      SelectionSort();
      break;
    case 'I':
    case 'i':
      InsertionSort();
      break;
    case 'm':
      TopDownMergeSort(0, TotalKeys - 1);
      break;
    case 'M':
      BottomUpMergeSort();
      break;

    case 'H':
    case 'h':
      HeapSort();
      break;
    case 'Q':
    case 'q':
      QuickSort();
      break;
    case 'C':
    case 'c':
      CountingSort(TotalKeys);
      break;
    case 'R':
    case 'r':
      RadixSort();
      break;
    default:
      cout << endl
           << "Invalid Algorithm Choice" << endl;
      break;
    }
    cout << "Exec time: " << float(clock() - beginTime) / CLOCKS_PER_SEC
         << " seconds." << endl;
    writeToFile();
  }
};

int main()
{
  IntegerSorter IS;

  float time = 0;

  do
  {
    cout << "Select Algorithm " << endl
         << "B. Bubble" << endl
         << "S. Selection" << endl
         << "I. Insertion" << endl
         << "H. Heap" << endl
         << "m. Top-Down Merge" << endl
         << "M. Bottom-Up Merge" << endl
         << "Q. Quick" << endl
         << "C. Counting" << endl
         << "R. Radix" << endl
         << "E. Exit" << endl;

    char Choice;
    cin >> Choice;

    if (Choice == 'E' || Choice == 'e')
      break;

    char FileName[] = "file.txt";

    if (!IS.LoadData(FileName, 1000000))
      return -1;

    IS.Sort(Choice);
    cout << "HIT ENTER TO CONTINUE OR C-c TO EXIT\n";
    cin.ignore();
    cin.get();

  } while (1);

  return 0;
}
