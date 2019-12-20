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
    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size < TotalKeys; curr_size = 2 * curr_size)
    {
      for (left_start = 0; left_start < TotalKeys - 1; left_start += 2 * curr_size)
      {
        int mid = min(left_start + curr_size - 1, TotalKeys - 1);
        int right_end = min(left_start + 2 * curr_size - 1, TotalKeys - 1);

        Merge(left_start, mid, right_end);
      }
    }
  }

  int Partition(int left, int right)
  {
    // uniform_int_distribution<int> dist{left, right};
    // int piv = dist(rd);
    int num = Keys[right];
    // swap(Keys[piv], Keys[right]);
    int pInd = left;
    for (int i = left; i < right; ++i)
    {
      if (Keys[i] <= num)
      {
        swap(Keys[i], Keys[pInd]);
        ++pInd;
      }
    }
    swap(Keys[right], Keys[pInd]);
    return pInd;
  }

  void QuickSort(int left, int right)
  {
    if (left < right)
    {
      int p = Partition(left, right);
      QuickSort(left, p-1);
      QuickSort(p+1, right);
    }
  }

  void CountingSort()
  {
    int MaxValue;
    cout << "enter maximum value\n";
    cin >> MaxValue;
    ++MaxValue;
    int count[MaxValue] = { 0 };
    for (int i = 0; i < TotalKeys; ++i)
    {
      ++count[Keys[i]];
    }
    for (int i = 1; i < MaxValue; ++i)
    {
      count[i] += count[i-1];
    }
    int num;
    int* sorted = new int[TotalKeys];
    for (int i = TotalKeys-1; i >= 0; --i)
    {
      num = Keys[i];
      sorted[--count[num]] = num;
    }
    delete[] Keys;
    Keys = sorted;
  }
  void RadixSort()
  {
    int max = 0;
    for (int i = 0; i < TotalKeys; ++i)
    {
      if (Keys[i] > max)
      {
        max = Keys[i];
      }
    }

    for (int pos = 1; max/pos > 0; pos = pos*10)
    {
      int count[10] = { 0 };
      int* aux = new int[TotalKeys];
      for (int i = 0; i < TotalKeys; i++)
      {
        int index = (Keys[i] / pos) % 10;
        ++count[index];
      }
      for (int i = 1; i < 10; ++i)
      {
        count[i] += count[i-1];
      }

      for (int i = TotalKeys-1; i >= 0; --i)
      {
        aux[--count[(Keys[i] / pos) % 10]] = Keys[i];
      }
      delete[] Keys;
      Keys = aux;
    }
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
      QuickSort(0, TotalKeys-1);
      break;
    case 'C':
    case 'c':
      CountingSort();
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
