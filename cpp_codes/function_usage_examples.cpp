#include <cstdarg>
#include <functional>
#include <iostream>

// Inline function
inline void swap(int &a, int &b) {
  int temp = b;
  b = a;
  a = temp;
}

// Function overloading
int add(const int &a, const int &b) { return a + b; }

double add(const double &a, const double &b) { return a + b; }

// Function template
template <typename T>
T subtract(T &a, T &b) {
  return a - b;
}

// Recursive function
int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}

// Variadic function
int calculateSum(int count, ...) {
  va_list args;
  va_start(args, count);
  int total = 0;
  for (int i = 0; i < count; ++i) {
    total += va_arg(args, int);
  }
  va_end(args);
  return total;
}

// Highre order function
int operate(const int &a, const int b, std::function<int()> fun) {
  return fun();
}

// Operator overloading
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

std::pair<int, int> operator+(std::pair<int, int> frac1,
                              std::pair<int, int> frac2) {
  int num = frac1.first * frac2.second + frac2.first * frac1.second;
  int den = frac1.second * frac2.second;
  int divisor = gcd(num, den);
  num /= divisor;
  den /= divisor;
  return std::pair<int, int>{num, den};
}

std::ostream &operator<<(std::ostream &out, std::pair<int, int> frac) {
  out << frac.first << "/" << frac.second;
  return out;
}

int main() {
  // Inline function
  std::cout << "Inline function: " << std::endl;
  int a{3}, b{2};
  std::cout << "Swapping a = " << a << " and b = " << b << " ..." << std::endl;
  swap(a, b);
  std::cout << "Result: a = " << a << ", b = " << b << std::endl << std::endl;

  // Function overloading
  std::cout << "Function overloading:" << std::endl;
  std::cout << "Adding b = " << b << " to a = " << a << " ..." << std::endl;
  std::cout << "Result: " << add(a, b) << std::endl << std::endl;

  double c{3.4}, d{1.3};
  std::cout << "Adding d = " << d << " to a = " << c << " ..." << std::endl;
  std::cout << "Result: " << add(c, d) << std::endl << std::endl;

  // Function template
  std::cout << "Function template:" << std::endl;
  std::cout << "Subtracting b = " << b << " from a = " << a << "..."
            << std::endl;
  std::cout << "Result: " << subtract<int>(a, b) << std::endl << std::endl;

  // Lambda function
  std::cout << "Lambda function:" << std::endl;
  auto sum = [](const int &a, const int &b) { return a + b; };
  std::cout << "Adding b = " << b << " to a = " << a << "..." << std::endl;
  std::cout << "Result: " << sum(a, b) << std::endl << std::endl;

  // Function pointer
  std::cout << "Function pointer:" << std::endl;
  int (*funPtr)(const int &a, const int &b) = &add;
  std::cout << "Adding b = " << b << " to a =" << a << "..." << std::endl;
  std::cout << "Result: " << funPtr(a, b) << std::endl << std::endl;

  // Recursive function:
  int n = 7;
  std::cout << "Recursive function:" << std::endl;
  std::cout << "Calculating the factorial of n = " << n << "..." << std::endl;
  std::cout << "Result: " << factorial(n) << std::endl << std::endl;

  // Variadic function
  std::cout << "Variadic function:" << std::endl;
  std::cout << "Caclulating 1 + 2 + 3" << "..." << std::endl;
  std::cout << "Result: " << calculateSum(3, 1, 2, 3) << std::endl << std::endl;

  // Higher order function
  std::cout << "Higher order function:" << std::endl;
  std::cout << "Adding b = " << b << " to a = " << a << " ..." << std::endl;
  std::cout << "Result: " << operate(a, b, [a, b]() { return a + b; })
            << std::endl;
  std::cout << "Subtracting b = " << b << " from a = " << a << " ..."
            << std::endl;
  std::cout << "Result: " << operate(a, b, [a, b]() { return a - b; })
            << std::endl
            << std::endl;

  // Operator overloading
  std::pair<int, int> frac1{1, 2};
  std::pair<int, int> frac2{1, 4};
  std::cout << "Operator overloading:" << std::endl;
  std::cout << "Adding " << frac1 << " to " << frac2 << " ..." << std::endl;
  std::cout << "Result: " << frac1 + frac2 << std::endl << std::endl;

  return 0;
}

