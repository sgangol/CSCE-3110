/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 2                                         **
                  Stack.cpp
				  The core of the program! It's the stack 
				  implementation.
	 Asst. File:  stack.hpp
 ********************************************************************/

#include "stack.hpp"

using namespace std;

template<class T>
void Stack<T>::push(T c){
	if ( topIndex >= MAXSIZE)cout << "Sorry Stack Exceeded it's limit!!! " << endl;
	// If data somehow exceeds the MaxSize of the Stack
	else{ 
		topIndex++;
		arr[topIndex] = c;
	}
	// If everything is fine, push it into the stack
}	// Ends of Void Stack()


template<class T>
T Stack<T>::top(){
  // your code goes here, check stack.hpp for the description of each method
  
  return arr[topIndex];
}

template<class T>
void Stack<T>::pop(){
  // Pop Function begins
  if(topIndex == -1)
    cout << "underflow" << endl;
      else
        {
          T c;
          c = arr[topIndex];
            topIndex--;
        }  
        
}


template<class T>
int Stack<T>::size(){
	return topIndex + 1;
	// Returns the size of the index
}

template<class T>
void Stack<T>::display(){
  // your code goes here, check stack.hpp for the description of each method
  for(int i=0;i <= topIndex; i++)
  {
    cout << arr[i] << '\t';
  }
  cout << endl;
}


template<class T>
int Stack<T>::isEmpty(){
	return topIndex == -1;  
}

template class Stack<char>;
template class Stack<int>;

