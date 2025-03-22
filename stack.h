#ifndef STACK_H
#define STACK_H


#include <iostream>
#include <string>
using namespace std;


//Maggie:
// Node template class for the stack
template <typename T> class Node {
public:
   T data; // data of node of type T
   Node<T> *next; // pointer to next node


   // constructor
   Node(T val) {
       data = val;
       next = nullptr;
   }
};


// Katy:
// Stack template class using singly linked list
template <typename T> class Stack {
private:
   Node<T> *top; // pointer to top of class
   int size; // size of class


public:
   // constructor initializer
   Stack() {
       top = nullptr; // initialize top to equal nullptr
       size = 0; // initialize size to equal 0
   }


   // deconstructor (empties the stack)
   ~Stack() {
       while (!isEmpty()) { // while the list is not empty
           pop(); // pop elements
       }
   }


   // Sivkan
   // push element into stack
   void push(T data) {
       Node<T> *newNode = new Node<T>(data); // create new node
       newNode->next = top; // link it to the top
       top = newNode; // update top to new node
       size++; // incrememnt
   }


   // Maggie
   // pop element
   void pop() {
       if (isEmpty()) { // if the stack is empty
           std::cout << "Error: Stack is empty!" << std::endl; // error message
           return;
       }


       Node<T> *temp = top; // store top node in temp
       top = top->next; // update top to next
       delete temp; // delete old top
       size--; // decrement
   }


   // Katy
   // returns the top element of stack
   T front() {
       if (isEmpty()) { // if empty
           std::cout << "Error: Stack is empty!" << std::endl; // error message
           T defaultValue = T(); // return default value
           return defaultValue;
       }
       return top->data; // otherwise return data of top node
   }


   // Sivkan
   bool isEmpty() { return top == nullptr; } // check if empty


   int getSize() { return size; } // get size
};


// Function declarations (non-template functions that will be implemented in the
// .cpp file)


// PRE: Takes in a string
// POST: returns a boolean. True if it is a palindrome and false otherwise.
bool isPalindrome(string str);


// Pre: Takes in an expression
// POST: Returns bool, true if parentheses are balanced, false otherwise
bool isBalanced(string expression);


//PRE: Takes in expressiom
// POST: evaluates the expression and returns the result
int evaluatePrefix(string expression);


// PRE: Takes in a decimal
// POST: converts the decimal to its binary and returns that as a string.
string decimalToBinary(int decimal);


// Pre: takes in expression
// POST: evaluates the expression and returns the result
int evaluatePostfix(string expression);


#endif // STACK_H
