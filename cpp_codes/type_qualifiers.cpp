/* Type qualifiers are keywords that modify the properties of variables,
 * providing additional information about how a variable should be treated by
 * the compiler. The main type qualifiers are:
 * 1. const:
 *  Purpose: Specifies that a variable value cannot be changed after it is
 * initialaized. Usage: Used to define read-only variables or enforce
 * immutability.
 *
 * 2. volatile:
 *  Purpose: indicates that a variable value can be changed externally (e.g., by
 * the hardware or a di fferent thread). Usage: Prevents the compiler form
 * optimizing accesses to the variable.
 *
 * 3. restrict:
 * Purpose: A pointer qualifier that informs the compiler no other pointer will
 * access the same memory. Allows better optimization. Usage: Primarily used in
 * low-level or performance-critical code.
 *
 * 4. mutable:
 * Purpose: Allows a member variable of a class to be modified even if the
 * object or member function are declared as const. Usage: Often used in
 * conjunction with const member functions.
 */

#include <iostream>
#include <thread>

volatile bool stopFlag = false;

// Function demonstrating const
void useConst() {
  const int constVar = 10;  // Cannot modified after initialization
  std::cout << "Const variable: " << constVar << std::endl;
}

// Function demonstrating volatile (std::atomic is prefered to volatile for
// thread-safe operation )
void useVolatile() {
  std::thread t([]() {
    while (!stopFlag) {
    }
    std::cout << "Thread stopped by volatile flag" << std::endl;
  });
  std::this_thread::sleep_for(std::chrono::seconds(1));
  stopFlag = true;
  t.join();
}

// Function demonstrating mutable
void useMutable() {
  class MyClass {
   public:
    mutable int mutableVar = 0;
    void modify() { ++mutableVar; }
  };

  MyClass obj;
  std::cout << "Murable variable before: " << obj.mutableVar << std::endl;
  obj.modify();
  std::cout << "Mutable variable after: " << obj.mutableVar << std::endl;
}

// Function demonstrating restrict
void restrictExample(int* __restrict x, int* __restrict y) {
  *x = *y + 5;  // Assumes no aliasing
}

void useRestrict() {
  int a{5}, b{10};
  restrictExample(&a, &b);
  std::cout << "Restrict example result: " << a << std::endl;
}

int main() {
  std::cout << "Using const: " << std::endl;
  useConst();

  std::cout << std::endl << "Using volatile: " << std::endl;
  useVolatile();

  std::cout << std::endl << "Using mutable: " << std::endl;
  useMutable();

  std::cout << std::endl << "Using restrict" << std::endl;
  useRestrict();

  return 0;
}

