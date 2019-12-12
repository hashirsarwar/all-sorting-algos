#include <iostream>
#include <fstream>
using namespace std;

class IntegerSorter{
    private:
        int* Keys;
        int TotalKeys;

        void BubbleSort(){

            bool swapped;
            for (int i = 0; i < TotalKeys; i++)
            {
                swapped = false;
                for (int j = 0; j < TotalKeys-i-1; j++)
                {
                    if (Keys[j] > Keys[j+1])
                    {
                        swapped = true;
                        swap(Keys[j], Keys[j+1]);
                    }
                }

                if (!swapped)
                    break;
            }
        }
        void SelectionSort(){
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
        void InsertionSort(){
            // Your implementation of Insertion Sort such that it also counts total comparisons,
			// total swaps and total time taken
            // to sort the 100,000 numbers
        }

		void BuildMaxHeap(){
			
		}
        void Heapify(){

        }
        void HeapSort(){
            // Your implementation of Heap Sort such that it also counts total comparisons, 
			// total swaps and total time taken
            // to sort the 100,000 numbers

        }

        void Merge(int Left, int Mid, int Right){
            // To merge the two parts of keys from left - Mid and Mid+1 to Right
        }
        void TopDownMergeSort(){
            // Your implementation of top-down (i.e. recursive) Merge Sort
            // such that it also counts total comparisons, total swaps and total time taken
            // to sort the 100,000 numbers
        }

        void BottomUpMergeSort(){
            // Your implementation of bottom-up (i.e. iterative) Merge Sort
            // such that it also counts total comparisons, total swaps and total time taken
            // to sort the 100,000 numbers
        }


        void Partition(int left, int right, int PivotIndex){
            // Partitioning algorithm using pivot at index PivotIndex
            // Don't forget to count the number of comparisons and swaps here
        }

        void QuickSort(){
            // Your implementation of quick sort
            // Also count the number of comparisons and swaps operations 
			// along with the time used for sorting
        }


        void CountingSort(int MaxValue){
            // Your implementation of counting sort for counting integers in the range 0-MaxValue
            // Also compute number of seconds used for sorting
        }
        void RadixSort(){
            // Your implementation of counting sort for counting integers in the range 0-MaxValue
            // Also compute number of seconds used for sorting
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

        IntegerSorter(){
            Keys = 0;
            TotalKeys = 0;
        }

        ~IntegerSorter(){
            if(Keys)
                delete[] Keys;
        }

        bool LoadData(char FileName[], int TotalKeys){
            if (Keys)
                delete[] Keys;

            this->TotalKeys = 0;
            Keys = new int[TotalKeys];

            if(!Keys)
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

        void Sort(char Method){
            cout << "Sorting...\n";
            clock_t beginTime = clock();
            switch (Method){
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
                TopDownMergeSort();
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
                CountingSort(100000);
            break;
            case 'R':
            case 'r':
                RadixSort();
            break;
            default:
                cout<<endl<<"Invalid Algorithm Choice"<<endl;
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

    do{
        cout<<"Select Algorithm "<<endl<<
        "B. Bubble"<<endl<<
        "S. Selection"<<endl<<
        "I. Insertion"<<endl<<
        "H. Heap"<<endl<<
        "m. Top-Down Merge"<<endl<<
        "M. Bottom-Up Merge"<<endl<<
        "Q. Quick"<<endl<<
        "C. Counting"<<endl<<
        "R. Radix"<<endl<<
        "E. Exit"<<endl;

        char Choice;
        cin>>Choice;

        if(Choice == 'E' || Choice == 'e')
            break;

        char FileName[] = "file.txt";

        if(!IS.LoadData(FileName, 100000))
            return -1;

        IS.Sort(Choice);
        cout << "HIT ENTER TO CONTINUE\n";
        cin.ignore();
        cin.get();

    }while(1);

    return 0;
}
