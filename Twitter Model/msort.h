#include <vector>
#include <string>
#include <iostream>

//PROTOTYPING
template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp);

template <class T, class Comparator>
void mergeSortH(std::vector<T>& myArray, int start, int end, Comparator comp);

template <class T, class Comparator>
void merge(std::vector<T>& myArray, int start, int mid, int end, Comparator comp);

template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp)//function to get ball rolling 
{
	mergeSortH(myArray, 0, myArray.size()-1, comp);
}

template <class T, class Comparator>
void mergeSortH(std::vector<T>& myArray, int start, int end, Comparator comp)//helper function
{
	//base case
	if (start >= end) return;

	//recursive
	else
	{
		int mid = (start+end)/2;
		mergeSortH(myArray, start, mid, comp);
		mergeSortH(myArray, mid+1, end, comp);
		merge(myArray, start, mid, end, comp);
	}
}

template <class T, class Comparator>
void merge(std::vector<T>& myArray, int start, int mid, int end, Comparator comp)
{
	//vectors which will deal with left half and right half of the chunks
	std::vector<T> temp1;
	std::vector<T> temp2;

	int size1 = mid-start+1;
	int size2 = end-mid;

	//fill those vectors
	for (int i = 0; i < size1; i++)
	{
		temp1.push_back(myArray[start+i]);
	}
	for (int i = 0; i < size2; i++)
	{
		temp2.push_back(myArray[mid+1+i]);
	}

	int i = 0;
	int j = 0; 
	int z = start; //first index of myArray

	//comparing the respective indexes of each chunk
	while (i < size1 && j < size2)
	{
		if (comp(temp1[i], temp2[j]))
		{
			myArray[z] = temp1[i];
			i++;
		}
		else
		{
			myArray[z] = temp2[j];
			j++;
		}
		z++; 
	}
	//since each chunk may not be of the exact same length, we need to look at those...
	//...final indexes if necessary
	while (i < size1)
	{
		myArray[z] = temp1[i];
		i++;
		z++;
	}
	while (j < size2)
	{
		myArray[z] = temp2[j];
		j++;
		z++;
	}
}