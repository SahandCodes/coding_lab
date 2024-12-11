#include <iostream>
#include <new>

void print(int *ptr, const size_t &size) {
  std::cout << "data = [";
  for (size_t i = 0; i < size; ++i) {
    std::cout << ptr[i];
    if (i < size - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

void print(int **ptr, const size_t &numRows, const size_t &numColumns) {
  std::cout << "data = [";
  for (size_t i = 0; i < numRows; ++i) {
    std::cout << "[";
    for (size_t j = 0; j < numColumns; ++j) {
      std::cout << ptr[i][j];
      if (j < numColumns - 1) std::cout << ", ";
    }
    std ::cout << "]";
    if (i < numRows - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

void staticMemoryAllocation() {
  int arr[5]{1, 2, 3, 4, 5};
  print(arr, 5);
}

void dynamicMemoryAllocationInC() {
  int *ptr;
  size_t size = 5;
  ptr = (int *)malloc(size * sizeof(int));

  if (ptr == NULL) {
    std::cout << "Memory allocation failed!" << std::endl;
    return;
  }

  for (size_t i = 0; i <= size; ++i) {
    ptr[i] = i;
  }

  print(ptr, size);

  free(ptr);
  ptr = NULL;
}

void dynamicMemoryAllocationInCPlusPlus() {
  size_t size = 5;
  int *ptr;
  try {
    ptr = new int[size]{1, 2, 3, 4, 5};
  } catch (const std::bad_alloc &e) {
    std::cout << "Memory allocation failed: " << e.what() << std::endl;
  }

  print(ptr, size);

  delete[] ptr;
  ptr = nullptr;

  size_t numRows = 2;
  size_t numColumns = 3;
  int **matrix = nullptr;

  try {
    matrix = new int *[numRows];
    for (size_t i = 0; i < numRows; ++i) {
      matrix[i] = new int[numColumns];
    }
  } catch (const std::bad_alloc &e) {
    std::cout << "Memory allocation failed: " << e.what() << std::endl;
    for (size_t i = 0; i < numRows; ++i) {
      delete[] matrix[i];
    }
    return;
  }

  for (size_t i = 0; i < numRows; ++i) {
    for (size_t j = 0; j < numColumns; ++j) {
      matrix[i][j] = i + j;
    }
  }

  print(matrix, numRows, numColumns);

  for (size_t i = 0; i < numRows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;

  matrix = nullptr;
}

void pointerArithmetic() {
  constexpr size_t size = 5;
  int arr[size]{1, 2, 3, 4, 5};
  int *ptr = arr;

  ptr[0] = 0;
  print(ptr, size);

  // No need to free ptr as arry is stack-allocated
  ptr = nullptr;
}

int main() {
  std::cout << "Static memory allocation" << std::endl;
  staticMemoryAllocation();
  std::cout << std::endl;

  std::cout << "Dynamic memory allocation in C" << std::endl;
  dynamicMemoryAllocationInC();
  std::cout << std::endl;

  std::cout << "Dynamic memory allocation in C++" << std::endl;
  dynamicMemoryAllocationInCPlusPlus();
  std::cout << std::endl;

  std::cout << "Pointer arithmetic" << std::endl;
  pointerArithmetic();
  std::cout << std::endl;

  return 0;
}
