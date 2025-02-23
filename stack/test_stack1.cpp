#include <iostream>
#include "stack.h"

using namespace std;
using namespace cop4530;

int main() {
    // Test 1: Two empty stacks
    Stack<int> stack1;
    Stack<int> stack2;
    std::cout << "Test 1: Two empty stacks: " << (stack1 <= stack2 ? "true" : "false") << std::endl;

    // Test 2: One non-empty stack and one empty stack
    stack1.push(10);
    std::cout << "Test 2: One non-empty stack and one empty stack: " << (stack1 <= stack2 ? "true" : "false") << std::endl;

    // Test 3: Two non-empty stacks with different sizes
    stack2.push(20);
    stack2.push(30);
    std::cout << "Test 3: Two non-empty stacks with different sizes: " << (stack1 <= stack2 ? "true" : "false") << std::endl;

    // Test 4: Two non-empty stacks with the same size but different elements
    stack1.push(20);
    stack1.push(30);
    std::cout << "Test 4: Two non-empty stacks with the same size but different elements: " << (stack1 <= stack2 ? "true" : "false") << std::endl;

    // Test 5: Pushing and popping with l-values
    stack1.push(40);
    stack1.push(50);
    std::cout << "Test 5: Pushing and popping with l-values" << std::endl;
    while (!stack1.empty()) {
        std::cout << stack1.top() << " ";
        stack1.pop();
    }
    std::cout << std::endl;

    // Test 6: Pushing and popping with r-values
    stack2.push(60);
    stack2.push(70);
    std::cout << "Test 6: Pushing and popping with r-values" << std::endl;
    while (!stack2.empty()) {
        int value = std::move(stack2.top());
        std::cout << value << " ";
        stack2.pop();
    }
    std::cout << std::endl;

    return 0;
}
