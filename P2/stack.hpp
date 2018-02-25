/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 2                                         **
                  Stack.hpp
				  Header file for Stack has class declaration
				  Just Added isEmpty() to return empty stack
				  Chose to stay with MAXSIZE of 100000
 ********************************************************************/

#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>

// Ideally this would not be a huge number, you could also use a vector
#define MAXSIZE 100000

using namespace std;
template<class T>
//class of the stack
class Stack{

private:
	T arr[MAXSIZE]; // the actual stack
	int topIndex;   // index of the top element
  
public:
	Stack(){
		topIndex = -1; // constructor
	};
	~Stack(){};      	// destructor

	void push(T c);  	// push c to the list
	T top();         	// return the top element in the stack
	void pop();      	// remove the top element in the stack
	// you may want a method that returns the top of the stack and removes it, feel free to add it
	int size();      	// returns the size of the stack
	void display();	// display the stack in stdout
	int isEmpty();	//return the empty stack
};
