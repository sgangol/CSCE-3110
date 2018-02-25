/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 2                                         **
                  Checks whether an expression is balanced or not!
 ********************************************************************/
#include "stack.hpp"

using namespace std;
//function to check if the parenthesis have all its pairs
bool validPairs(char opening,char closing);


//Main Function Begins
/*-------------------------------------------------------------------------------*/
int main(){
  freopen("input_balanced.txt", "r", stdin);
  string s,r;
  int line_counter;
  while(cin >> r){
    cin>>s;
    Stack<char> stack;
    bool isBalanced = true;
    bool solution;
    if(r[0] == 'Y' || r[0] == 'y' ){
      solution = true;
    }else{
      solution = false;
    }
    // The input file is in the format "expected_solution expression"
    // so variable solution tells you whether 'expression' is balanced or not
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

// Edit Begins inside While Loop  and Main Function 

// For Loop to varify that isBalanced indicates whether 's' is balanced
    for(int i=0; i<s.length(); ++i){
        if(s[i] == '(' || s[i] == '{' || s[i] == '[') stack.push(s[i]);
		// Pushes all opening brackets into the stack
        else if (s[i] ==')' || s[i] == '}' || s[i]  == ']'){
		// Checking if all the opening brackets closes        
			if(stack.isEmpty() || !validPairs(stack.top(),s[i])) {
				isBalanced = false;}
			// if the closing bracket exists and the stack is empty or
			// the corrosponding opening bracket is not at the top of 
			// the stack, it's not balanced
			
            else {					// else pop out the corrosponding
				stack.pop();}		// opening bracket from top of the stack
        } 	// END of - else if
    
    } 		// END of -For
	
    // checking if stored in isBalanced the correct value
	
/*---------------------------------------------------------------------------------------------*/
    if(isBalanced == solution){
      cout << "line " << line_counter << ": OK [" << solution << " " << isBalanced << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << isBalanced << "]" << endl;
    }
    line_counter++;
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
  } // END of While Loop
}	// End of int Main() 



// Defininng the functions
bool validPairs(char opening,char closing)
{
	if(opening == '(' && closing == ')') return true;
	else if(opening == '{' && closing == '}') return true;
	else if(opening == '[' && closing == ']') return true;
	else
		return false;
}
