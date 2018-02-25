*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program1                                          **
                  Implements max heapsort of the input files
 ********************************************************************/


#include "maxheap.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>

MaxHeap::MaxHeap() {
  arr.push_back((int) NULL);
}
MaxHeap::~MaxHeap() {}


int MaxHeap::size() { 
	return arr.size();								// Returns size of the array (heapsize)
}

int MaxHeap::left(int parent) {	
	return parent*2; 								// Returns the index of left child
}

int MaxHeap::right(int parent) {	
	return parent*2+1;								// Returns the index of  right child
}
		
int MaxHeap::parent(int child) {
	return floor(child/2);							// Returns the index of parent-child
}
	
void MaxHeap::insert(int element) {
	arr.push_back(element);							// Push the element at the bottom leaf 
	int ePos = arr.size() - 1; 						// Initialize the index
	percolateUp(ePos);								// percolateUp index

}

int MaxHeap::deleteMax() {
	int child = arr.size() - 1;						// Initialize child to find the index of the element to be deleted
	int swapper = arr[child];						// Initiate swapper
	arr[child] = arr[1];
	arr[1] = swapper;
	int element = arr.back();  
	arr.pop_back(); 								// Pop out/Delete the maximum element (head)
	percolateDown(1);								// percolateDown
	return element; 
}
/***************As it is *****************/
void MaxHeap::display() {
	vector<int>::iterator it;
	cout << "MaxHeap:- ";
	for(it=arr.begin(); it!=arr.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}
/*****************************************/

void MaxHeap::percolateUp(int index) {
	if (index == 0)
    return;  										// Return if it is valid

	int parent = this->parent(index);				// Inserted index->parent
	if (parent != 0 && arr[parent] < arr[index]) {	// Loop to validate inserted element  
		int swapper = arr[parent]; 					// Initializing swapper
		arr[parent] = arr[index];
		arr[index] = swapper;
		percolateUp(parent); 						// percolateUp to parent
	}

}

void MaxHeap::percolateDown(int index) {
	int lChild = this->left(index); 				// Initilizing left-child 
	int rChild = this->right(index); 				// Initilizing right-child
	int aTop = index; 								// Initalizing parent with the index

	if (lChild < this->size() && arr[lChild] > arr[aTop])
		aTop = lChild; 								// Check if lChild is valid

	if (rChild < this->size() && arr[rChild] > arr[aTop])
		aTop = rChild; 								// Check if righChild is valid

	if (aTop != index) { 							// Loop until the parent != index
		int swapper = arr[aTop]; 					// Initializing swapper
		arr[aTop] = arr[index];
		arr[index] = swapper;
		percolateDown(aTop);						// percolateDown to the parent index
	}
}

void MaxHeap::buildHeap(vector<int> A,int n) {
	for (int x = 0; x < n; x++) {					
		this->insert(A[x]); 						// Initiate insert() function for A
	}
}

void MaxHeap::heapsort(vector<int>& A,int n) {
	this->buildHeap(A,n); 							// Initiate buildHeap function
	A.clear(); 										// Erase the array
	for (int x = 0; x < n; x++) {					// Until the value is achieved
		A.insert(A.begin(), this->deleteMax()); 	// Insert -> deleteMAx()
	}
}

