// MAGGIE PURSLEY
// Program 3

#include <limits>
#include "stack.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// MAGGIE
// function to check if a string is a palindrome
bool isPalindrome(string str) {
 Stack<char> stack;


 // push all characters on the stack
 for (int i = 0; i < str.length(); i++) { // loop
   stack.push(str[i]); // push
 }


 // compare characters from beginning with characters from end (popped from
 // stack)
 for (int i = 0; i < str.length(); i++) {
   if (stack.front() != str[i]) { // if characters do not match
     return false; // return false
   }
   stack.pop(); // pop the top character from the stack
 }


 return true; // return true if it is a palindrome
}


// SIVKAN
// Function to convert decimal to binary
 string decimalToBinary(int decimal) {
 if (decimal == 0) { // if the decimal is 0
   return "0"; // return 0
 }


 Stack<int> stack;


 // concert decimal number to binary by dividing it by 2 in a loop
 while (decimal > 0) { // while the decimal is greater than 0
   stack.push(decimal % 2); // push the remainder
   decimal /= 2; // divide the decimal by 2
 }


 // creates the binary string by popping elements from stack
 string binary = "";
 while (!stack.isEmpty()) {
   binary += to_string(stack.front()); // add the digits
   stack.pop(); // pop that digit from the stack
 }


 return binary; // return the string
}


// SIVKAN
// Function to evaluate a postfix expression
int evaluatePostfix(string expression) {
 Stack<int> stack;


 // process characters
 for (int i = 0; i < expression.length(); i++) {


   if (expression[i] == ' ') { // if the character is a space
     continue; // skip
   }


   // CHANGED BY KATY: implementation only handled single digit numbers, not
   // multi-digit numbers if current character is digit, extract complete
   // number
   if (isdigit(expression[i])) { // if the character is a digit
     int num = 0; // create num variable
     while (i < expression.length() && isdigit(expression[i])) {
       num = num * 10 + (expression[i] - '0'); // construct number
       i++; // iterate
     }
     i--; // adust for loop increment
     stack.push(num); // push the number onto the stack
   } else if (expression[i] == '+' || expression[i] == '-' ||
              expression[i] == '*' || expression[i] == '/') {
     if (stack.getSize() < 2) {
       cout << "Error: Invalid expression!" << endl; // error
       return -1; // return error if not enough operands
     }


     int operand2 = stack.front(); // pop second operand
     stack.pop();
     int operand1 = stack.front(); // pop first operand
     stack.pop();


     // operations to do based on the operand
     switch (expression[i]) {
     case '+':
       stack.push(operand1 + operand2);
       break;
     case '-':
       stack.push(operand1 - operand2);
       break;
     case '*':
       stack.push(operand1 * operand2);
       break;
     case '/':
       if (operand2 == 0) { // error
         cout << "Runtime Error: Cannot divide by 0." << endl; // message
         return -1; // return out
       }
       stack.push(operand1 / operand2);
       break;
     }
   }
 }


 // if the size is not 1
 if (stack.getSize() != 1) {
   cout << "Error: Invalid expression!" << endl; // return error
   return -1;
 }


 return stack.front(); // return final result
}


// KATY
// Function to evaluate if the parenthesis are balanced
bool isBalanced(string expression) {
 Stack<char> stack;


 // traverse expression and check balance of paretheses
 for (int i = 0; i < expression.length(); i++) {
   if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
     stack.push(expression[i]); // pushing opening parenthese onto stack
   } else if (expression[i] == ')' || expression[i] == ']' ||
              expression[i] == '}') {
     if (stack.isEmpty()) {
       return false; // false if no corresponding openeing parenthesis
     }


     char top = stack.front(); // get the top character
     stack.pop(); // pop the character


     // checks to see if the parenthese match or not
     if ((expression[i] == ')' && top != '(') ||
         (expression[i] == ']' && top != '[') ||
         (expression[i] == '}' && top != '{')) {
       return false; // returns false if they do not
     }
   }
 }
 return stack.isEmpty(); // otherwise return true if the stack is empty (means all parenthesis matched)
}


// KATY
// Function to evaulate a preflix expression
int evaluatePrefix(string expression) {
  // tokenize the expression
  vector<string> tokens;
  string token;

  for (int i = 0; i < expression.length(); i++) {
    if (expression[i] == ' ') {
      if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
      }
    } else {
      token += expression[i];
    }
  }

  if (!token.empty()) {
    tokens.push_back(token);
  }

  // reverse the tokens to process them from right to left
  vector<string> reversedTokens;
  for (int i = tokens.size() - 1; i >= 0; i--) {
    reversedTokens.push_back(tokens[i]);
  }

  // evaluate using a stack
  Stack<int> evalStack;

  for (const string& token : reversedTokens) {
    // check if token is an operator
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      // need at least two operands
      if (evalStack.getSize() < 2) {
        cout << "Error: Invalid expression - not enough operands" << endl;
        return -1;
      }

      int op1 = evalStack.front();
      evalStack.pop();
      int op2 = evalStack.front();
      evalStack.pop();

      if (token == "+") {
        evalStack.push(op1 + op2);
      } else if (token == "-") {
        evalStack.push(op1 - op2);
      } else if (token == "*") {
        evalStack.push(op1 * op2);
      } else if (token == "/") {
        if (op2 == 0) {
          cout << "Runtime Error: Cannot divide by 0" << endl;
          return -1;
        }
        evalStack.push(op1 / op2);
      }
    } else {
      // token is a number
      try {
        evalStack.push(stoi(token));
      } catch (const invalid_argument&) {
        cout << "Error: Invalid token '" << token << "'" << endl;
        return -1;
      }
    }
  }

  // the final result should be the only item on the stack
  if (evalStack.getSize() != 1) {
    cout << "Error: Invalid expression - too many operands" << endl;
    return -1;
  }

  return evalStack.front();
}

// MAGGIE
// Main function with menu-driven interface
int main() {
 int choice; // var int choice


 do {
   // display menu options
   cout << "\n----- Stack Applications Menu -----" << endl;
   cout << "1. Check if a string is a palindrome" << endl;
   cout << "2. Convert decimal to binary" << endl;
   cout << "3. Evaluate postfix expression" << endl;
   cout << "4. Check balanced parenthesis" << endl;
   cout << "5. Evaluate prefix expression" << endl;
   cout << "6. Exit" << endl;
   cout << "Enter your choice (1-6): "; // ask for choice
   if (!(cin >> choice)) {
     cin.clear();
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
     cout << "Invalid input. Please enter a number." << endl;
     choice = 0;
   } 


   // user choice handling
   switch (choice) {
   case 1: {
     string input;
     cout << "Enter a string to check if it's a palindrome: ";
     cin >> input; // user input


     if (isPalindrome(input)) { // call function
       cout << input << " is a palindrome." << endl; // if true message
     } else {
       cout << input << " is NOT a palindrome." << endl; // if false message
     }
     break; // exit
   }
   case 2: {
     int decimal;
     cout << "Enter a decimal number to convert to binary: ";
     cin >> decimal; // user input


     string binary = decimalToBinary(decimal); // call function
     cout << "The decimal value: " << decimal << " is " << binary
               << " in binary." << endl; // message
     break; // exit
   }
   case 3: {
     string expression;
     cout << "Enter a postfix expression (use spaces between elements): ";
     cin.ignore();
     getline(cin, expression); // get input


     int result = evaluatePostfix(expression); // call function into variable
     if (result != -1) { // if result return is not -1
       cout << "The expression: " << expression << " = " << result << "."
                 << endl; // output final result
     }
     break;
   }
   case 4: {
     string expression;
     cout
         << "Enter an expression to check if it has balanced parenthesis: ";
     cin.ignore();
     getline(cin, expression); // get input


     if (isBalanced(expression)) { // call function
       cout << "The expression: " << expression << " is balanced."
                 << endl; // if true message
     } else {
       cout << "The expression: " << expression << " is not balanced."
                 << endl; // if false message
     }
     break;
   }
   case 5: {
     string expression;
     cout << "Enter a prefix expression (use spaces between elements): ";
     cin.ignore();
     getline(cin, expression); // get input


     int result = evaluatePrefix(expression);
     if (result != -1) { // if not false
       cout << "The expression: " << expression << " = " << result << "."
                 << endl; // message
     }
     break;
   }
   case 6:
     cout << "Exiting the program. Goodbye!" << endl;
     break;  // exit program
   }
 } while (choice != 6); // continue until user chooses to exit


 return 0;
}
