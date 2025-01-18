/* In C++ function specifiers modify how a function behaves or is treateed by
 * the compiler
 *
 * 1. inline: Suggests a commpiler to replace functon call with the function's
 * code to reduce function call overhead
 *
 * 2. constexpr: Specifies that the function or object can be evaluated at
 * compile time, provided its its arguments are also constant expressions
 *
 * 3. const: Declares that a member function does not modify the state of the
 * object.
 *
 * 4. virtual: Allows a function to be overridden in a derived class, enabling
 * polymorphism.
 *
 * 5. override: Ensures that a function in a derived class overrides a virtual
 * function in the base class. It prevents accidental mismatches due to typos or
 * incorrect signatures
 *
 * 6. final: Prevents further overriding of a virtal function or subclassing.
 *
 * 7. default: Explicitly tells the compiler to use the default implementation
 * for a special member function(constructor, destructor, copy/move)
 *
 * 8. delete: Disable a function, preventing it from being used.
 *
 * 9. static: Declares a function that does not operates on an instances of the
 * class
 *
 * 10. explicit: Prevents implicit conversion or copy-initialization for
 * constructors or conversion operators
 *
 * 11. friend: Grants a function or another class access to the
 * private/protected members of the clas*/

#include <iostream>

// Inline function
inline void useInline() {
  std::cout << "This is an inline function" << std::endl;
}

// Constexpr function
constexpr int useConstexpr(int x) { return x * x; }

// Const function in a class
class ConstExample {
 public:
  void setValue(int val) { mValue = val; };
  int getValue() const { return mValue; }

 private:
  int mValue = 0;
};
void useConst() {
  ConstExample obj;
  obj.setValue(10);
  std::cout << "Value (via const function): " << obj.getValue() << std::endl;
}

// Virtual function
class Base {
 public:
  virtual void useVirtual() const {
    std::cout << "Base class virtual function." << std::endl;
  }
  virtual ~Base() = default;
};
class Derived : public Base {
 public:
  void useVirtual() const override {
    std::cout << "Derived class override of virtual function." << std::endl;
  }
};

void useVirtual() {
  Base baseObj;
  Derived derivedObj;
  Base* basePtr = &derivedObj;
  baseObj.useVirtual();
  basePtr->useVirtual();
}

// Final function
class Derived2 : public Base {
 public:
  void useVirtual() const override final {
    std::cout << "Final class override of virtual function." << std::endl;
  }
};
void useFinal() {
  Derived2 obj;
  obj.useVirtual();
}

// Default keyword
class DefaultExample {
 public:
  DefaultExample() = default;
};
void useDefault() {
  DefaultExample obj;
  std::cout << "Default constructor invoked." << std::endl;
}

// Delete keyword
class DeleteExample {
 public:
  DeleteExample& operator=(const DeleteExample&) = delete;
};
void useDelete() {
  DeleteExample obj;
  DeleteExample obj2;
  std::cout << "copy assignment deleted" << std::endl;
  // obj2 = obj1; Uncommenting this will cause a compilation error
}

// Static function
class staticExample {
 public:
  static void DisplayValue() {
    std::cout << "StaticVariabe = " << staticVariable << std::endl;
  };
  static void setValue(int var) { staticVariable = var; }

 private:
  static int staticVariable;
};
int staticExample::staticVariable = 0;
void useStatic() {
  staticExample::setValue(3);
  staticExample::DisplayValue();
}

// Explicit constructor
class ExplicitExample {
 public:
  explicit ExplicitExample(int x) : value(x) {
    std::cout << "Explicit constructor called with value: " << value
              << std::endl;
  }

 private:
  int value;
};

void useExplicit() {
  ExplicitExample obj(42);
  // ExplicitExample obj2 = 42; // Uncommenting this will cause a compilation
  // error
}

// Friend function
class FriendExample {
 public:
  friend void useFriend();  // Declaring the friend function
 private:
  int value = 42;
};
void useFriend() {
  FriendExample obj;
  std::cout << "Friend function accessed private value:" << obj.value
            << std::endl;
}

int main() {
  // Inline
  std::cout << "Using inline" << std::endl;
  useInline();

  // Constexpr
  std::cout << std::endl << "Using constexpr:" << std::endl;
  constexpr int result = useConstexpr(5);
  std::cout << "Constexpr result: " << result << std::endl;

  // Const
  std::cout << std::endl << "Using const:" << std::endl;
  useConst();

  // Virtual
  std::cout << std::endl << "Using virtual:" << std::endl;
  useVirtual();

  // Final
  std::cout << std::endl << "Using final:" << std::endl;
  useFinal();

  // Default
  std::cout << std::endl << "Using default:" << std::endl;
  useDefault();

  // Delete
  std::cout << std::endl << "Using delete:" << std::endl;
  useDelete();

  // Static
  std::cout << std::endl << "Using static:" << std::endl;
  useStatic();

  // Explicit
  std::cout << std::endl << "Using explicit: " << std::endl;
  useExplicit();

  // Friend
  std::cout << std::endl << "Using friend:" << std::endl;
  useFriend();

  return 0;
}
