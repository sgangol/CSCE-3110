/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 2                                         **
                  infix2postfix.cpp
				  This program transfroms an infix expression 
				  into the postfix
 ********************************************************************/

 #include "stack.hpp"

using namespace std;
// Auxiliary method, you probably find it useful
// Operands are all lower case and upper case characters
bool isOperand(char c);

bool IsOperator(char C);

/*-------------------------------------------------------------------------------*/
// Auxiliary method, you probably find it useful
int precedence(char c)
{
  if (c == '+' || c == '-')
  {
    return 0;
  }
  if (c == '*' || c == '/')
  {
    return 1;
  }
  if (c == '^')
  {
    return 2;
  }
  return -1;
}

int main()
{
  freopen("input_infix2postfix.txt", "r", stdin);
  string input;
  string solution;
  int line_counter = 0;
  while (cin >> solution)
  {
    cin >> input;
    Stack<char> stack;
    string result;
	// The input file is in the format "expected_solution infix_input", 
	// where expected_solution is the infix_expression in postfix format
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	
    int k = -1;

    for (int i = 0; i < input.length(); ++i){ // Analysing the input
		if (input[i] == ' ' || input[i] == ',') continue; 
		// Ignores white space and , comma ','

		else if (IsOperator(input[i])){ // If Operator
			if (precedence(input[i]) < precedence(stack.top()))
			{ // Check for the precedence
				while (!stack.isEmpty() && stack.top() != '('){
					result += stack.top();
					stack.pop();
				} 	// Pop an element from the stack until it finds operator of the lower-
					// priority in the current scope
			}
			stack.push(input[i]);		// Then push the current input
		}
		
		
		else if (isOperand(input[i])){ 	// If Operand
		result += input[i];
		}

		else if (input[i] == '('){		// If opening bracket
		stack.push(input[i]);			// Then PUSH in the stack
		}
		
		else if (input[i] == ')'){		// If closing bracket

			while (!stack.isEmpty() && stack.top() != '('){
				result += stack.top();
				stack.pop();
			} 								// Simply POP 
		stack.pop();						// POP all elements from the stack
		}
    }


    while (!stack.isEmpty())
    {
      result += stack.top();
      stack.pop();
    }
	
/*----------------------------------------------------------------------------------------------*/	
	// Checking whether the result you got is correct
    if (solution == result){
      cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
    }
    line_counter++;
  }	// END of while loop
}	// END of int main()
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/ 



// Defining Function
bool isOperand(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool IsOperator(char C){
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '^'){
		return true;
	}
	else return false;
} // Function that returns true if it fiinds Operator