/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 2                                         **
                  postfixEval.cpp
				  This program transfroms an infix expression 
				  into the postfix
 ********************************************************************/


#include "stack.hpp"

using namespace std;

// Function to calculate the value
char doTheMath(char operation, char operand1, char operand2);

// Function to verify operator
bool IsOperator(char C);


/*----------------------------------------------------------------------------------------------*/	
int main(){
  freopen("input_postfixEval.txt", "r", stdin);
  string s;
  int solution;
  int line_counter = 0;
  while(cin>>solution){
    cin>>s;
    Stack<int> stack;
    // The input file is in the format "expected_solution postfix_expression"

    for(int i=0; i<s.length(); ++i){
      // At the end of the loop, stack.top() should contain the value of the postfix expression
      // We assume that all operands in the input are one digit (so they range from 0 to 9)
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/       
		if ( ! IsOperator(s[i])){
		stack.push(s[i]- '0');
		} 
		else if( IsOperator(s[i])){
			char optrA = s[i];								// Declaring Temp Variables
			char optrB = stack.top();						// Declaring optrB to the top of stack
			stack.pop();									// POP fron the stack
			char optrC = stack.top();						// Declaring optrC to the top of stack
			stack.pop(); 									// POP from the stack
			optrA = doTheMath(s[i], optrC, optrB); 			// Calculate the value
			stack.push(optrA);								// Push the value in the stack
		}
	}
	
/*--------------------------------------------------------------------------------------------*/	
    // Checking whether the value you calculated is correct ...
    int value = stack.top();

    if(solution == value){
      cout << "line " << line_counter << ": OK [" << solution << " " << value << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << value << "]" << endl;
    }
    line_counter++;
  } // END of while loop
}	// END of int main()
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

// Defining the Functions
char doTheMath(char operation, char operand1, char operand2)
{
	if(operation == '+') return operand1 + operand2;
	else if(operation == '-') return operand1 - operand2;
	else if(operation == '*') return operand1 * operand2;
	else if(operation == '/') return operand1 / operand2;
	else if(operation == '^') return operand1 ^ operand2;
	else cout << "Invalid operator" << endl;
	return operation;
}

bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}