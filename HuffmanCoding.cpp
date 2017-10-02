#include <iostream>
#include <fstream>
using namespace std;

class HeapSort
{
	public:
	int rootIndex;
	int fatherIndex;
	int kidIndex;
	int leftKidIndex;
	int rightKidIndex;
	int minKidIndex;
	int *heapAry;
	int temp;
	int size;
	int data;
	
		HeapSort()
		{
			heapAry = new int[1]();
			heapAry[0] = 0;
			rootIndex = 1;
		}
		
		HeapSort(int s)  
		{
			heapAry = new int[s]();
			size = s;
			heapAry[0] = 0;
			rootIndex = 1;
		}
		
		void buildHeap(ifstream &is, ofstream &os1)
		{
			rootIndex = 1;
			int input;
			while (is >> input)
			{
				data = input;
				insertOneDataItem(input);
				bubbleUp (kidIndex);
				printHeap(os1);
			}
		}
		
		void insertOneDataItem(int d)
		{
			heapAry[0]++;
			kidIndex = heapAry[0];
			heapAry[kidIndex] = d;
		}
		
		int getRoot ()
		{
			return heapAry[1];
		}
		
		int deleteHeap(ofstream &os1, ofstream &os2)
		{
			while(heapAry[0] != 0)
			{
				data = getRoot();
				os2 << data << " ";
				deleteRoot();
				fatherIndex = 1;
				bubbleDown(fatherIndex);
				printHeap(os1);
			}
		}
		
		void bubbleUp (int kidIndex)
		{
			if(isRoot(kidIndex))
				return;
			else
			{
				fatherIndex = kidIndex/2;
				if (heapAry[kidIndex] < heapAry[fatherIndex])
				{
					temp = heapAry[kidIndex];
					heapAry[kidIndex] = heapAry[fatherIndex];
					heapAry[fatherIndex] = temp;
					bubbleUp(fatherIndex);
				}
			}
		}
		
		void bubbleDown(int fatherIndex)
		{
			if(isLeaf(fatherIndex))
				return;
			else
			{
				leftKidIndex = fatherIndex*2;
				rightKidIndex = fatherIndex*2+1;
			}
			minKidIndex = findMinKidIndex(fatherIndex);
			if(heapAry[minKidIndex] == 0)
				return;
			else
			{
				if(heapAry[minKidIndex] < heapAry[fatherIndex])
				{
					temp = heapAry[minKidIndex];
					heapAry[minKidIndex] = heapAry[fatherIndex];
					heapAry[fatherIndex] = temp;
					bubbleDown(minKidIndex);
				}
			}
		}
		
		void deleteRoot()
		{
			heapAry[1] = heapAry[heapAry[0]];
			heapAry[heapAry[0]] = 0;
			heapAry[0]--;
		}
		
		bool isLeaf(int index)
		{
			
			if(index*2==0 || index*2+1==0 || index*2 >= size)
				return true;
			else
				return false;
		}
		
		bool isRoot(int index)
		{
			if(index==1)
				return true;
			else
				return false;
		}
		
		int findMinKidIndex (int fatherIndex) 
		{
			leftKidIndex = fatherIndex*2;
			rightKidIndex = fatherIndex*2+1;
			
			if(rightKidIndex == size)
				return leftKidIndex; 
			if(heapAry[leftKidIndex] < heapAry[rightKidIndex])
				return leftKidIndex;
			else
				return rightKidIndex;
		}
		
		bool isHeapEmpty()
		{
			if(heapAry[0]==0)
				return true;
			else
				return false;
		}
		
		bool isHeapFull()
		{
			return heapAry[0]>=size;
		}
		
		void printHeap(ofstream &os)
		{
			for (int i=0; i<size; i++)
			{
				if (heapAry[i]==0)
				{
					if(heapAry[0]==0)
						os << 0;
					break;
				}
				else
				{	
					os << heapAry[i] << " ";
				}
			}
			os << endl;
		}
};

int main(int argc, char *argv[])
{
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1;
	ofstream outFile2;
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	HeapSort* hs;
	
	int input = 0;
	int count = 0;
	while (inFile >> input)
	{
		count++;
	}
	inFile.close();
	hs = new HeapSort(++count);
	inFile.open(argv[1]);
	hs->buildHeap(inFile, outFile1);
	hs->deleteHeap(outFile1, outFile2);
	
	inFile.close();
	outFile1.close();
	outFile2.close();
	
	return 0;
} 
