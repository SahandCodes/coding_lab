/*  This is a code example for storqge class specifiers. These specifiers are
 * sueed in declaration to define the storage duration and linkage of variables
 * and functions
 * 1. auto:
 *   scope: local
 *   lifetime: enclosing block
 *    use case: type deduction for variables
 *
 * 2.register (removed in C++17):
 *  scope: local
 *  lifetime:  enclosing block
 *  use case: hint for performance (now loargely obsolete)
 *
 * 3. static:
 *  scope: local or global
 *  lifetime: lifetime of the program
 *  use case:  persistent variables or limiting visibility
 *
 * 4. thread_local:
 *  scope: local or global
 *  lifetime: thread lifetime
 *  use case: per-thread data in multi-threaded programs
 *
 * 5.extern:
 *  scope: global
 *  lifetime: lifetime of the program
 *  use case: accessing variables/functions across files
 *
 * 6. mutable
 *  scope: class member
 *  lifetime: lifetime of the object
 *  use case: modify variables in const functions:
 * */

#include <iostream>
#include <thread>

// Extern specifier
extern int externVar;

// Thread-local specifier
thread_local int threadLocalVar = 0;

class MyClass {
 public:
  // Mutable specifier
  mutable int mutableVar = 10;

  void modify() const { mutableVar += 5; }
};

// Function demonstrating "auto"
void useAuto() {
  auto x = 42;
  std::cout << "Auto variable: " << x << std::endl;
}

// Function demonstrating "static"
void useStatic() {
  static int staticVar = 0;  // Retains value between calls
  ++staticVar;
  std::cout << "Static variable: " << staticVar << std::endl;
}

// Function demonstrating "thread_local"
void useThreadLocal() {
  ++threadLocalVar;
  std::cout << "Thread ID: " << std::this_thread::get_id()
            << ", Thread-local variable: " << threadLocalVar << std::endl;
}

// Function demonstrating "mutable"
void useMutable() {
  MyClass obj;
  std::cout << "Mutable variable before modification: " << obj.mutableVar
            << std::endl;
  obj.modify();
  std::cout << "Mutable variable after modification: " << obj.mutableVar
            << std::endl;
}

// Function demonstrating "extern"
void useExtern() { std::cout << "Extern variable: " << externVar << std::endl; }

int main() {
  // Demonstrate each storage specifier
  useAuto();
  useStatic();  // First call
  useStatic();  // Second call

  std::thread t1(useThreadLocal);
  std::thread t2(useThreadLocal);
  t1.join();
  t2.join();

  useMutable();
  useExtern();

  return 0;
}

int externVar = 20;
