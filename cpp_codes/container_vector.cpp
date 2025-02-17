/* This file includes examples for vector container. Vector is a dynamic array
 * that can resize itself as elements are added or removed. It provides random
 * access to its elements, meaning you can access any element in constant time
 * (O(1)) using an index. While it offers efficient insertions and deletions at
 * the end (amortized O(1)), insertions and deletions at the beginning or middle
 * can be slow (O(n)) because it may require shifting elements. std::vector is a
 * good choice when you need a dynamic array that supports efficient random
 * access and additions/removals at the end.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

void printVector(const std::string& vectorName, const std::vector<int>& vec) {
  std::cout << vectorName << ": ";
  if (vec.size() == 1) {
    std::cout << "[" << vec[0] << "]";
  } else {
    for (int i = 0; i < vec.size(); ++i) {
      if (i == 0) {
        std::cout << "[" << vec[i] << ", ";
      } else if (i == vec.size() - 1) {
        std::cout << vec[i] << "]";
      } else {
        std::cout << vec[i] << ", ";
      }
    }
  }
  std::cout << std::endl;
};

// 1.Initializing a vector
void initialization() {
  // 1.1 Default initialization
  std::cout << "1.1 Default initialization" << std::endl;
  std::vector<int> v1;
  printVector("Vector", v1);

  // 1.2 Fill constructor with default value
  std::cout << std::endl
            << "1.2. Fill constructor with default value" << std::endl;
  std::vector<int> v2(5);
  printVector("Vector", v2);

  // 1.3. Fill constructor with a specific value
  std::cout << std::endl
            << "1.3. Fill constructor with elements equal to 1" << std::endl;
  std::vector<int> v3(5, 1);
  printVector("Vector", v3);

  // 1.4. Uniformm initialization
  std::cout << std::endl
            << "1.4. Uniform initialization with {1, 2, 3, 4, 5}" << std::endl;
  std::vector<int> v4{1, 2, 3, 4, 5};
  printVector("Vector", v4);

  // 1.5. Direct initialization with initializer list
  std::cout << std::endl
            << "1.5 Direct initialization with initializer list {1, 2, "
               "3, 4, 5}"
            << std::endl;
  std::vector<int> v5({2, 3, 4, 5, 6});
  printVector("Vector", v5);

  // 1.6. Copy initialization with initializer list
  std::cout << std::endl
            << "1.6 Copy initialization with initializer list {6, "
               "7, 8, 9, 10}"
            << std::endl;
  std::vector<int> v6 = {6, 7, 8, 9, 10};
  printVector("Vector", v6);

  // 1.7. Direct initialization from another vector usinng copy constructor
  std::cout << std::endl
            << "1.7 Direct initialization from another vector using copy "
               "constructor"
            << std::endl;
  std::vector<int> v7(v4);
  printVector("First Vector", v4);
  printVector("Second Vector", v7);

  // 1.8. Copy initialization from another vector using copy constructor
  std::cout
      << std::endl
      << "1.8 Copy initialization from another vector using copy constructor"
      << std::endl;
  std::vector<int> v8 = v5;
  printVector("First vector", v5);
  printVector("Second vector", v8);

  // 1.9. Direct initialization from another vector using move constructor
  std::cout << std::endl
            << "1.9 Direct initialization from another vector using move "
               "constructor"
            << std::endl;
  printVector("First Vector", v7);
  std::vector<int> v9(std::move(v7));
  printVector("Second vector", v9);

  // 1.10. Copy initialization from another vector using move constructor
  std::cout << std::endl
            << "1.10. Copy initialization from another vector using move "
               "constructor"
            << std::endl;
  printVector("First vector", v8);
  std::vector<int> v10 = std::move(v8);
  printVector("Second vector", v10);

  // 1.11. Range initialization
  std::cout
      << std::endl
      << "1.11. Range initialization using first 3 elements of anohter vector"
      << std::endl;
  std::vector v11(v4.begin(), v4.begin() + 3);
  printVector("First vector", v4);
  printVector("Second Vector", v11);
}

// 2, Accessing and modifying vector
void accessingAndModification() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 2.1 Using operator []
  std::cout
      << "2.1. Using operator[] to access and modify the second element to 20"
      << std::endl;
  printVector("Initial vector", vec);
  vec[1] = 20;
  printVector("Modified vector", vec);

  // 2.2. Using .at()
  std::cout << std::endl
            << "2.2. Using at() to acceess and modify the third element to 30"
            << std::endl;
  printVector("Initial vector", vec);
  vec.at(2) = 30;
  printVector("Modified vector", vec);

  // 2.3. Using .front()
  std::cout << std::endl
            << "2.3. Using front() to access and modify the first element to 10"
            << std::endl;
  printVector("Initial vector", vec);
  vec.front() = 10;
  printVector("Modified vector", vec);

  // 2.4. Using .back()
  std::cout
      << std::endl
      << "2.4. Using back() to access and modify the the last element to 50"
      << std::endl;
  printVector("Initial vector", vec);
  vec.back() = 50;
  printVector("Modified vector", vec);

  // 2.5 Using iterator
  std::cout
      << std::endl
      << "2.5. Using iterator to access and modify the fourth element to 41"
      << std::endl;
  printVector("Initial vector", vec);
  auto it = vec.begin() + 3;
  *it = 40;
  it = vec.end() - 2;
  *it = 41;
  printVector("Modified vector", vec);

  // 2.6. Using iterator-based for loop
  std::cout << std::endl
            << "2.6. Using iterator-based for loop to access and modiy "
               "elements to 11, 21, 31, 42, 51"
            << std::endl;
  printVector("Initial Vector", vec);
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    *it += 1;
  }
  printVector("Modified vector", vec);

  // 2.7. Using reversed iterator-based for loop
  std::cout << std::endl
            << "2.7. Using reversed iterator-based for loop to access and "
               "modify elements to 12, 22, 32, 43, 52"
            << std::endl;
  printVector("Initial vector", vec);
  for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    *it += 1;
  }
  printVector("Modified vector", vec);

  // 2.8. Using range-based for loop
  std::cout << std::endl
            << "2.8. Using range-based for loop to access and modify elements "
               "to [13, 23, 33, 44, 53])"
            << std::endl;
  printVector("Initial vector", vec);
  for (int& val : vec) {
    val += 1;
  }
  printVector("Modified vector", vec);

  // 2.9. Using data()
  std::cout << std::endl
            << "2.9. Using data() to access a raw pointer and modify first "
               "element to 14"
            << std::endl;
  printVector("Initial vector", vec);
  int* ptr = vec.data();
  ptr[0] = 14;
  printVector("Modified vector", vec);

  // 2.10 Using assign()
  std::cout << std::endl
            << "2.10. Using assign() to modify vector to [10, 20, 30, 40, 50]"
            << std::endl;
  printVector("Initial vector", vec);
  vec.assign({10, 20, 30, 40, 50});
  printVector("Modified vector", vec);

  // 2.11. Using swap()
  std::cout << std::endl
            << "Using swap() to swap  a vector to [1, 2, 3, 4, 5]" << std::endl;
  printVector("Inital vector", vec);
  std::vector<int> vec2{1, 2, 3, 4, 5};
  vec.swap(vec2);
  printVector("Modified vector", vec);
}

// 3. Inserting and Removing element
void insertingAndRemoving() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 3.1 Using push_back
  std::cout << "3.1. Using push_back() to add 6 to the vector" << std::endl;
  printVector("Initial vector", vec);
  vec.push_back(6);
  printVector("Modified vector", vec);

  // 3.2. Using emplace_back()
  std::cout << std::endl
            << "3.2. Using emplace_back() to add 7 to the vector" << std::endl;
  printVector("Initial vector", vec);
  vec.emplace_back(7);
  printVector("Modified vector", vec);

  // 3.3. Using insert()
  std::cout << std::endl
            << "3.3. Using insert() to insert 8 as a second element"
            << std::endl;
  printVector("Initial vector", vec);
  vec.insert(vec.begin() + 1, 8);
  printVector("Modified vector", vec);

  // 3.4. Using emplace()
  std::cout << std::endl
            << "3.4. Using emplace() to insert 9 as third element" << std::endl;
  printVector("Initial vector", vec);
  vec.emplace(vec.begin() + 2, 9);
  printVector("Modified vector", vec);

  // 3.5. Using erase()
  std::cout << std::endl
            << "3.5. Using erase() to remove first element" << std::endl;
  printVector("Initial vector", vec);
  vec.erase(vec.begin());
  printVector("Modified vector", vec);

  // 3.6 Using pop_back()
  std::cout << std::endl
            << "3.6. Using pop_back() to remove the last element" << std::endl;
  printVector("Initial vector", vec);
  vec.pop_back();
  printVector("Modified vector", vec);

  // 3.7. Using clear()
  std::cout << std::endl
            << "3.7. Using clear() to remove alll elements" << std::endl;
  printVector("Initial vector", vec);
  vec.clear();
  printVector("Modified vector", vec);
}

// 4. Capacity managment
void capacityManagement() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 4.1. Using size()
  std::cout << "4.1. Using size() to get the current number of elements"
            << std::endl;
  printVector("Vector", vec);
  std::cout << "Vector size: " << vec.size() << std::endl;

  // 4.2. Using max_size()
  std::cout << std::endl
            << "4.2. Using max_size() to get the upper limit" << std::endl;
  printVector("Vector", vec);
  std::cout << "Vector max size: " << vec.max_size() << std::endl;

  // 4.3. Using capacity()
  std::cout << std::endl
            << "4.3. Using capacity() to get the number of elements that the "
               "vector can hold before needing to allocate more memory"
            << std::endl;
  printVector("Vector", vec);
  std::cout << "Vector capacity: " << vec.capacity() << std::endl;

  // 4.4. Using empty()
  std::cout << std::endl << "4.4. Using empty()" << std::endl;
  printVector("Vector", vec);
  std::cout << "Vector is empty: " << std::boolalpha << vec.empty()
            << std::endl;

  // 4.5. Using reserve()
  std::cout << std::endl
            << "4.5. Using reserve() to increase the vector capacity"
            << std::endl;
  printVector("Vector", vec);
  std::cout << "Initial capacity: " << vec.capacity() << std::endl;
  vec.reserve(10);
  std::cout << "Capacity after reserve(10): " << vec.capacity() << std::endl;

  // 4.6. Using shrink_to_fit()
  std::cout << std::endl
            << "4.6. Using shrink_to_fit() to reduce the vector capacity to "
               "match the size"
            << std::endl;
  printVector("Vector", vec);
  std::cout << "Vector size: " << vec.size() << std::endl;
  std::cout << "Vector capacity before shrink_to_fit(): " << vec.capacity()
            << std::endl;
  vec.shrink_to_fit();
  std::cout << "Vector capacity after shrink_to_fit(): " << vec.capacity()
            << std::endl;

  // 4.7. Using resize()
  std::cout << std::endl
            << "4.7. Use resize() to change the size of vector" << std::endl;
  printVector("Initial vector", vec);
  std::cout << "Increase size to 8" << std::endl;
  vec.resize(8);
  printVector("Modified Vector", vec);
  std::cout << "Shrink size to 3" << std::endl;
  vec.resize(3);
  printVector("Modified vector", vec);
  std::cout << "Resize with value 10" << std::endl;
  vec.resize(6, 10);
  printVector("Modified vector", vec);
}

// 5. Sorting and ordering  algorithms
void sortingAndOrderingAlgorithms() {
  // 5.1. Use std::sort()
  std::cout
      << "5.1. Use std::sort() to sort the entire vector in ascending order"
      << std::endl;
  std::vector<int> vec{5, 3, 8, 3, 1, 2, 7, 4, 6};
  printVector("Initial vector", vec);
  std::cout << "Sorting in ascending order" << std::endl;
  std::sort(vec.begin(), vec.end());
  printVector("Modified vector", vec);
  std::cout << "Sorting in descendinng order" << std::endl;
  std::sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });
  printVector("Modified vector", vec);

  // 5.2. Use std::stable_sort()
  std::cout << std::endl
            << "5.2. Use std::stable_sort() to sort the entire vector while "
               "maintaining equal elements relative order"
            << std::endl;
  std::vector<int> vec2{5, 3, 8, 3, 1, 2, 7, 4, 6};
  printVector("Initial vector", vec2);
  std::stable_sort(vec2.begin(), vec2.end());
  printVector("Modified vector", vec2);

  // 5.3. Use std::partial_sort()
  std::cout << std::endl
            << "5.3. Use std::partial_sort() to sort first 3 elements"
            << std::endl;
  std::vector<int> vec3{5, 3, 8, 1, 2, 7, 4, 6};
  printVector("Initial vector", vec3);
  std::partial_sort(vec3.begin(), vec3.begin() + 3, vec3.end());
  printVector("Modified vector", vec3);

  // 5.4. Use std::nth_element()
  std::cout << std::endl
            << "5.4. Use std::nth_element() to place the 5th element in the "
               "correct order"
            << std::endl;
  std::vector<int> vec4{5, 3, 8, 1, 2, 7, 4, 6};
  printVector("intial vector", vec4);
  std::nth_element(vec4.begin(), vec4.begin() + 5, vec4.end());
  printVector("Modified vector", vec4);

  // 5.5. Use std::is_sorted()
  std::cout << std::endl
            << "5.5. Use std::is_sorted() to check if the vector is sorted"
            << std::endl;
  printVector("Vector", vec);
  std::cout << "Is the vector sorted? " << std::boolalpha
            << std::is_sorted(vec.begin(), vec.end()) << std::endl;
}

// 6. Searching algorithms
void searchingAlgorihtms() {
  std::vector<int> unsortedVec{3, 2, 1, 5, 4};
  std::vector<int> sortedVec{1, 2, 3, 4, 5};
  // 6.1. Using std::find()
  std::cout << "6.1. Using std::find() to find the first occurrence of 3"
            << std::endl;
  printVector("Vector", unsortedVec);
  auto it = std::find(unsortedVec.begin(), unsortedVec.end(), 3);
  if (it != sortedVec.end()) {
    auto dist = it - unsortedVec.begin() + 1;
    std::cout << "Found 3 at  postion: " << dist << std::endl;
  } else {
    std::cout << "Not found 3 in the vector" << std::endl;
  }
  // 6.2. Using std::find_if()
  std::cout
      << std::endl
      << "6.2. Using std::find_if to find the first element satisfying x > 3"
      << std::endl;
  printVector("Vector", unsortedVec);
  it = std::find_if(unsortedVec.begin(), unsortedVec.end(),
                    [](int x) { return x > 3; });
  if (it != unsortedVec.end()) {
    auto distance = it - unsortedVec.begin() + 1;
    std::cout << "Found value: " << *it << " at position: " << distance
              << std::endl;
  } else {
    std::cout << "Not found any value satisfying the condition" << std::endl;
  }

  // 6.3. std::find_if_not()
  std::cout << std::endl
            << "6.3. Using std::find_if_not()  to find the first element that "
               "does not satisfy the x > 3"
            << std::endl;
  printVector("Vector", unsortedVec);
  it = find_if_not(unsortedVec.begin(), unsortedVec.end(),
                   [](int x) { return x > 3; });
  if (it != unsortedVec.end()) {
    auto distance = it - unsortedVec.begin() + 1;
    std::cout << "Found value: " << *it << " at position: " << distance
              << std::endl;
  } else {
    std::cout << "Nof found any value satisfying the condition" << std::endl;
  }

  // 6.4. std::binary_search()
  std::cout
      << std::endl
      << "6.4. Use std::binary_search() to check if 3 exist in sorted vector"
      << std::endl;
  printVector("Vector", sortedVec);
  bool found = std::binary_search(sortedVec.begin(), sortedVec.end(), 3);
  if (found) {
    std::cout << "Found 3 in the vector" << std::endl;
  } else {
    std::cout << "Not found 3 in the vector" << std::endl;
  }

  // 6.5. std::lower_bound()
  std::cout << std::endl
            << "6.5. Use std::lower_bound() to find the first element greater "
               "than or equal to 3 int sorted vector"
            << std::endl;
  printVector("Vector", sortedVec);
  it = std::lower_bound(sortedVec.begin(), sortedVec.end(), 3);
  if (it != sortedVec.end()) {
    std::cout << "Found first element equal or greater than 3: " << *it
              << std::endl;
  } else {
    std::cout << "Not found any value equal or greater than 3" << std::endl;
  }

  // 6.6. std::upper_bound()
  std::cout << std::endl
            << "6.6. Using std::upper_bound() to find the first element that "
               "is greater than 3 in a sorted vector"
            << std::endl;
  printVector("Vector", sortedVec);
  it = std::upper_bound(sortedVec.begin(), sortedVec.end(), 3);
  if (it != sortedVec.end()) {
    std::cout << "Found first element greater than 3: " << *it << std::endl;
  } else {
    std::cout << "Not found any element greater than 3" << std::endl;
  }

  // 6.7. std::equal_range()
  std::cout
      << std::endl
      << "6.7. Use std::equal_range() to find pair of iterators representing "
         "range of elemnts that are equal to 3 in a sorted vector"
      << std::endl;
  printVector("Vector", sortedVec);
  auto range = std::equal_range(sortedVec.begin(), sortedVec.end(), 3);
  if (range.first != range.second) {
    auto distance1 = range.first - sortedVec.begin() + 1;
    auto distance2 = range.second - sortedVec.begin() + 1;
    std::cout << "First occurrence at index: " << distance1 << std::endl;
    std::cout << "Last occurrence at index: " << distance2 << std::endl;
  } else {
    std::cout << "Element not found in the container" << std::endl;
  }
}

// 7. Modifying algorithms
void modifyingAlgorithms() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 7.1. std::fill()
  std::cout << "7.1 Use std::fill() to replace first 3 elemnts with 10"
            << std::endl;
  printVector("Initial vector", vec);
  std::fill(vec.begin(), vec.begin() + 3, 10);
  printVector("Modified vector", vec);

  // 7.2. std::fill_n()
  std::cout << std::endl
            << "7.2 Use std::fill_n() to replace first 3 elements with 20"
            << std::endl;
  printVector("Initial vector", vec);
  std::fill_n(vec.begin(), 3, 20);
  printVector("Modified vector", vec);

  // 7.3. std::generate()
  std::cout << std::endl
            << "7.3. Use std::generate() to replace elements with 1, 2, 3, 4, "
               "5 which is generated by callable function"
            << std::endl;
  printVector("Initial vector", vec);
  int element{0};
  std::generate(vec.begin(), vec.end(), [&element]() { return ++element; });
  printVector("Modified vecctor", vec);

  // 7.4. std::generate_n()
  std::cout << std::endl
            << "7.4. Using std::generate_n() to replace first 3 elements with "
               "10, 20, 30 which is generated by calleble function"
            << std::endl;
  printVector("Initial vector", vec);
  element = 0;
  std::generate_n(vec.begin(), 3, [&element]() {
    element = element + 10;
    return element;
  });
  printVector("Modified vector", vec);

  // 7.5. std::replace()
  std::cout
      << std::endl
      << "7.5. Using std::replace() to replace all occurrences of 30 with 3"
      << std::endl;
  printVector("Initial vector", vec);
  std::replace(vec.begin(), vec.end(), 30, 3);
  printVector("Modified vector", vec);

  // 7.6. std::replace_if()
  std::cout << std::endl
            << "7.6. Using std::replace_if()  to replace elements that satisfy "
               "x >= 10 with 1"
            << std::endl;
  printVector("Initial vector", vec);
  std::replace_if(vec.begin(), vec.end(), [](int x) { return x >= 10; }, 1);
  printVector("Modified vector", vec);

  // 7.7. std::transform()
  std::cout << std::endl
            << "7.7. Use std::transform() to apply x^2 and stores them in "
               "anothe range"
            << std::endl;
  std::vector<int> vec3(vec.size());
  printVector("Initial vector", vec);
  std::transform(vec.begin(), vec.end(), vec3.begin(),
                 [](int x) { return x * x; });
  printVector("Modified vector", vec3);
}

// 8. Removing algorithms
void removingAlgorithms() {
  std::vector<int> vec{1, 2, 3, 4, 5};
  // // 8.1. std::remove()
  std::cout
      << "8.1. Using std::remove() to move 3 to the back of the vector and "
         "return a new end iterator. Using erase() to remove the element"
      << std::endl;
  printVector("Initial Vector", vec);
  auto newEndIt = std::remove(vec.begin(), vec.end(), 3);
  vec.erase(newEndIt, vec.end());
  printVector("Modified vector", vec);

  // 8.2. std::remove_if()
  std::cout
      << std::endl
      << "8.2. Using std::remove_if() to move any elment greater than 3 to "
         "the back of the vector and return a new end iterator. Using erase() "
         "to remove elements"
      << std::endl;
  printVector("Initial vector", vec);
  newEndIt =
      std::remove_if(vec.begin(), vec.end(), [](int x) { return x > 3; });
  vec.erase(newEndIt, vec.end());
  printVector("Modified vector", vec);

  // 8.3. std::unique()
  std::cout << std::endl
            << "8.3. Using std::unique() to move all  consecutive duplicate "
               "elements too the back o the vector and return new end iterator "
               "(vector must be sorted first). Using erase() to remove elements"
            << std::endl;
  std::vector<int> vec2{1, 2, 3, 4, 5};
  vec.insert(vec.end(), vec2.begin(), vec2.end());
  std::sort(vec.begin(), vec.end());
  printVector("Initial vector", vec);
  newEndIt = std::unique(vec.begin(), vec.end());
  vec.erase(newEndIt, vec.end());
  printVector("Modified vector", vec);

  /* C++20
  // 8.4. std::erase()
  std::cout << std::endl << "8.4. Using std::erase() to remove all occurrences
  of a 1 and resize the vector" << std::endl; printVector("Initial vector",
  vec); std::erase(vec.begin(), vec.end()); printVector("Modified vector", vec);

  // 8.5. std::erase_if()
  std::cout << std::endl << "8.5. Using std::erase_if() to remove elements
  matching x > 3 and resize the vector" << std::endl; printVector("Initial
  vector", vec); std::erase_if(vec.begin(), vec.end(), [](int x){return x >
  3;}); printVector("Modified vector", vec);
  */
}

// 9. Reversing and rotating algoirthms
void reversingAndRotatingAlgorithms() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 9.1. std::reverse()
  std::cout
      << "9.1. Using std::reverse() to reverse the order of elements in a range"
      << std::endl;
  printVector("Initial vector", vec);
  std::reverse(vec.begin(), vec.end());
  printVector("Modified vector", vec);

  // 9.2. std::reverse_copy()
  std::cout << std::endl
            << "9.2. Using std::reverse_copy() to copy first vector elements "
               "in reverse order into second vector"
            << std::endl;
  std::vector<int> vec2(vec.size());
  printVector("First vector", vec);
  printVector("Second vector", vec2);
  std::reverse_copy(vec.begin(), vec.end(), vec2.begin());
  printVector("Modified second vector", vec2);

  // 9.3. std::rotate()
  std::cout
      << std::endl
      << " 9.3. Using std::rotate() to rotate first two elements to the end"
      << std::endl;
  printVector("Vector", vec);
  std::rotate(vec.begin(), vec.begin() + 2, vec.end());
  printVector("Modified vector", vec);

  // 9.4. std::rotate_copy()
  std::cout
      << std::endl
      << "9.4. Using std::rotate_copy() to roatate first two elements of the "
         "first vector and copy the result vector into the second vector"
      << std::endl;
  vec2.assign(vec.size(), 0);
  printVector("First vector", vec);
  printVector("Second vector", vec2);
  std::rotate_copy(vec.begin(), vec.begin() + 2, vec.end(), vec2.begin());
  printVector("Modified vector", vec2);
}

// 10. Comparing and checking algorithms
void comparingAndCheckingAlgorithms() {
  std::vector<int> vec1{1, 2, 3, 4, 5};
  std::vector<int> vec2{1, 2, 3, 4};

  // 10.1. std::equal()
  std::cout << "10.1. Using std::equal() to check if two ranges are equal"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  bool result = std::equal(vec1.begin(), vec1.end(), vec2.begin());
  std::cout << "Result: " << std::boolalpha << result << std::endl;

  // 10.2. std::lexicographical_compare()
  std::cout << std::endl
            << "10.2. Using std::lexicographical_compare() to check if one "
               "range is lexicographically less than another"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  result = std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(),
                                        vec2.end());
  std::cout << "Result: " << std::boolalpha << result << std::endl;

  // 10.3. std::mismatch()
  std::cout << std::endl
            << "10.3. Using std::mismatch() to find the first position where "
               "two ranges differ"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  auto itPair = std::mismatch(vec1.begin(), vec1.end(), vec2.begin());
  auto dist1 = itPair.first - vec1.begin() + 1;
  auto dist2 = itPair.second - vec2.begin() + 1;
  std::cout << "First vector differs at position: " << dist1
            << " with value: " << *itPair.first << std::endl;
  std::cout << "Second vector differs at position: " << dist2
            << " with value: " << *itPair.second << std::endl;

  // 10.4. std::all_of()
  std::cout << std::endl
            << "10.4. Using std::all_of() to check if all elements satisfy x % "
               "2 == 0 condition"
            << std::endl;
  printVector("Vector", vec1);
  result =
      std::all_of(vec1.begin(), vec1.end(), [](int x) { return x % 2 == 0; });
  std::cout << "Result: " << std::boolalpha << result << std::endl;

  // 10.5. std::any_of()
  std::cout << std::endl
            << "10.5. Using std::any_of() to check if at least one element "
               "satisfies x % 2 == 0"
            << std::endl;
  printVector("Vector", vec1);
  result =
      std::any_of(vec1.begin(), vec2.end(), [](int x) { return x % 2 == 0; });
  std::cout << "Result: " << std::boolalpha << result << std::endl;

  // 10.6. std::none_of()
  std::cout << std::endl
            << "10.6. Using std::none_of() to check if no element satisfy a x "
               "% 2 == 0"
            << std::endl;
  printVector("Vector", vec1);
  result =
      std::none_of(vec1.begin(), vec1.end(), [](int x) { return x % 2 == 0; });
  std::cout << "Result: " << std::boolalpha << result << std::endl;
}

// 11. Couning algorithms
void countingAlgorithms() {
  std::vector<int> vec{1, 2, 2, 3, 4};

  // 11.1.std::count()
  std::cout << "11.1. Using std::count() to count how many times 2 appears in "
               "the vector"
            << std::endl;
  printVector("Vector", vec);
  int count = std::count(vec.begin(), vec.end(), 2);
  std::cout << "Result: " << count << std::endl;

  // 11.2. std::count_if()
  std::cout
      << std::endl
      << "11.2. Using std::count_if() to count elements that satisfy x > 2"
      << std::endl;
  printVector("Vector", vec);
  count = std::count_if(vec.begin(), vec.end(), [](int x) { return x > 2; });
  std::cout << "Result: " << count << std::endl;
}
// 12. Randomization algorithms
void randomizationAlgorithms() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 12.1. std::shuffle()
  std::cout << "12.1.Using std::shuffle() to randomly shuffles the elements of "
               "the vector ussing a given "
               "random number generator"
            << std::endl;
  printVector("Initial vector", vec);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(vec.begin(), vec.end(), g);
  printVector("Modified vector", vec);
}

// 13. Set operation algorithms
void setOperationAlgorithms() {
  std::vector<int> vec1{5, 3, 1, 3, 4};
  std::vector<int> vec2{3, 3, 3, 4, 6, 5};
  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());

  // 13.1. std::set_union()
  std::cout << "13.1. Using std::set_union() to compute the union of two "
               "sorted vectors"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vectorr", vec2);
  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());
  std::vector<int> vec3(vec1.size() + vec2.size());
  auto it = std::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                           vec3.begin());
  vec3.resize(it - vec3.begin());
  printVector("Result vector", vec3);

  // 13.2. std::set_intersection()
  std::cout << std::endl
            << "13.2. Using std::intersection() to compute the intersectionn "
               "of two sorted vectors"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  vec3.resize(std::min(vec1.size(), vec2.size()), 0);
  it = std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                             vec3.begin());
  vec3.resize(it - vec3.begin());
  printVector("Result vector", vec3);

  // 13.3. std::set_difference()
  std::cout << std::endl
            << "13.3. Using std::set_difference() to compute the difference "
               "(elements in the first vector but not in the second)"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  vec3.resize(vec1.size(), 0);
  it = std::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
                           vec3.begin());
  vec3.resize(it - vec3.begin());
  printVector("Result vector", vec3);

  // 13.4. std::set_symmetric_difference()
  std::cout << std::endl
            << "13.4. Using std::symetric_difference() to compute the "
               "symmetric difference (elements in either vector but not both)"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  vec3.resize(vec1.size() + vec2.size(), 0);
  it = std::set_symmetric_difference(vec1.begin(), vec1.end(), vec2.begin(),
                                     vec2.end(), vec3.begin());
  vec3.resize(it - vec3.begin());
  printVector("Result vector", vec3);

  // 13.5. std::includes()
  std::cout << std::endl
            << "13.5. Using std::includes() to check if the second vector is "
               "subset of the first vector"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  bool result =
      std::includes(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
  std::cout << "Result: " << std::boolalpha << result << std::endl;
}

// 14. Min/Max algoirhtms
void minMaxAlgorithms() {
  std::vector<int> vec{4, 1, 7, 3, 9};

  // 14.1. std::min_element()
  std::cout << "14.1. Using std::min_elemeent() to find the smallest element"
            << std::endl;
  printVector("Vector", vec);
  auto min_it = std::min_element(vec.begin(), vec.end());
  if (min_it != vec.end()) {
    std::cout << "Minimum element: " << *min_it << std::endl;
  }

  // 14.2. std::max_element()
  std::cout << std::endl
            << "14.2. Using std::max_element() to find the largest element"
            << std::endl;
  printVector("Vector", vec);
  auto max_it = std::max_element(vec.begin(), vec.end());
  if (max_it != vec.end()) {
    std::cout << "Maximum element: " << *max_it << std::endl;
  }

  // 14.3. minmax_element()
  std::cout << std::endl
            << "14.3. Using std::minmax_element() to find both smallest and "
               "largest elements"
            << std::endl;
  printVector("Vector", vec);
  auto minMaxIt = std::minmax_element(vec.begin(), vec.end());
  if (min_it != vec.end() && max_it != vec.end()) {
    std::cout << "Minimum element: " << *minMaxIt.first << std::endl;
    std::cout << "Maximum element: " << *minMaxIt.second << std::endl;
  }
}

// 15. Partitioning algorthms
void partitioningAllgorithms() {
  std::vector<int> vec{1, 4, 3, 2, 5, 8, 7, 6};

  // 15.1. std::partition()
  std::cout << "15.1. Using  std::partition() to rearrange elements so that "
               "those satisfying  x % 2 == 0 come before others"
            << std::endl;
  std::vector<int> vec2 = vec;
  printVector("Initial vector", vec2);
  std::partition(vec2.begin(), vec2.end(), [](int x) { return x % 2 == 0; });
  printVector("Modified vector", vec2);

  // 15.2. std::stable_partition()
  std::cout << std::endl
            << "15.2. Using std::stable_partitioning() to rearrange elements "
               "so that those satisfying x % 2 == 0 come before others while "
               "maintaining thre relativ order of elemments"
            << std::endl;
  std::vector<int> vec3 = vec;
  printVector("Initial vector", vec3);
  std::stable_partition(vec3.begin(), vec3.end(),
                        [](int x) { return x % 2 == 0; });
  printVector("Modified vector", vec3);

  // 15.3. std::is_partitioned()
  std::cout << std::endl
            << "15.3. Using std::is_partitioned() if even numbers are before "
               "odd numbers"
            << std::endl;
  printVector("Vector", vec);
  bool isPart = std::is_partitioned(vec.begin(), vec.end(),
                                    [](int x) { return x % 2 == 0; });
  std::cout << "Result: " << std::boolalpha << isPart << std::endl;

  // 15.4. std::partition_point()
  std::cout << std::endl
            << "15.4. Using std::partition_point() to return an iterator to "
               "the first element that does not satisfy x % 2 == 0"
            << std::endl;
  printVector("Vector", vec);
  auto it = std::partition_point(vec.begin(), vec.end(),
                                 [](int x) { return x % 2 == 0; });
  int dist = it - vec.begin() + 1;
  std::cout << "Partition poin value: " << *it << " at position: " << dist
            << std::endl;
}

// 16. Heap  algoirhtms
void heapAlgorithms() {
  // 16.1. std::make_heap()
  std::cout << "16.1 Using std::make_heap() to convert vector into heap"
            << std::endl;
  std::vector<int> vec{2, 1, 3, 5, 4};
  printVector("Vector", vec);
  std::make_heap(vec.begin(), vec.end());
  printVector("Modified vector", vec);

  // 16.2. std::push_heap()
  std::cout << std::endl
            << "16.2. Using std::push_heap() to insert 7" << std::endl;
  printVector("Initial vector", vec);
  vec.push_back(7);
  printVector("Vector after using push_back(7)", vec);
  std::push_heap(vec.begin(), vec.end());
  printVector("Vector after using std::push_heap()", vec);

  // 16.3. std::pop_heap()
  std::cout << std::endl
            << "16.3. Using std::pop_heap() to remvoe the largest element"
            << std::endl;
  printVector("Initial vector", vec);
  std::pop_heap(vec.begin(), vec.end());
  printVector("Vector after using std::pop_heap()", vec);
  vec.pop_back();
  printVector("Vector aftere using pop_back()", vec);

  // 16.4. std::sort_heap()
  std::cout << std::endl
            << "16.4. Using std::sort_heap() to convert heap to sorted array"
            << std::endl;
  printVector("Initial vector", vec);
  std::sort_heap(vec.begin(), vec.end());
  printVector("Modified vector", vec);

  // 16.5. std::is_heap()
  std::cout << std::endl
            << "16.5. Using std::is_heap() to check if a the vector is a heap"
            << std::endl;
  printVector("Vector", vec);
  bool isHeap = std::is_heap(vec.begin(), vec.end());
  std::cout << "Vector is a heap: " << std::boolalpha << isHeap << std::endl;

  // 16.6. std::is_heap_until()
  std::cout << std::endl
            << "16.6. Using std::is_heap_until() to find first heap violation"
            << std::endl;
  printVector("Vector", vec);
  auto it = std::is_heap_until(vec.begin(), vec.end());
  if (it != vec.end()) {
    std::cout << "Heap property holds until index: " << it - vec.begin()
              << std::endl;
  } else {
    std::cout << "Heap property holds for whole vector" << std::endl;
  }
}

// 17. Additional algoirhtms
void additionalAlgorithms() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  // 17.1. std::for_each()
  std::cout << "17.1. Using std::for_each() to calcuagte square of each element"
            << std::endl;
  printVector("Initial vector", vec);
  std::for_each(vec.begin(), vec.end(),
                [](int& element) { element = element * element; });
  printVector("Modified vector", vec);

  // // 17.2. std::sample()
  std::cout
      << std::endl
      << "17.2 Using std::sample() to choose two random sample from the vector"
      << std::endl;
  printVector("Vector", vec);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> sample;
  std::sample(vec.begin(), vec.end(), std::back_inserter(sample), 2, gen);
  printVector("Sample vector", sample);
}

// 18. Numeric algoirhtms
void numericAlgorithms() {
  std::vector<int> vec1{1, 2, 3, 4, 5};
  std::vector<int> vec2{6, 7, 8, 9, 10};

  // 18.1. std::accumulate()
  std::cout << "18.1 Using std::accumulate() to calculate sume of elements"
            << std::endl;
  printVector("Vector", vec1);
  int result = std::accumulate(vec1.begin(), vec1.end(), 0);
  std::cout << "Result: " << result << std::endl;

  // 18.2. std::inner_product()
  std::cout << std::endl
            << "18.2. Using std::inner_product() to calcuate dot product of "
               "two vectors"
            << std::endl;
  printVector("First vector", vec1);
  printVector("Second vector", vec2);
  result = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
  std::cout << "Result: " << result << std::endl;

  // 18.3. std::adjacent_difference()
  std::cout << std::endl
            << "18.3. Using std::adjacent_difference() to caculate difference "
               "between adjacent elements"
            << std::endl;
  printVector("Vector", vec1);
  std::vector<int> diff(vec1.size());
  std::adjacent_difference(vec1.begin(), vec1.end(), diff.begin());
  printVector("Adjacent difference: ", diff);

  // 18.4. std::partial_sum()
  std::cout << std::endl
            << "18.4. Using std::partial_sum() to compute comulative sum of a "
               "range, storing each intermediate resullt in an output sequence"
            << std::endl;
  printVector("Vector", vec1);
  std::vector<int> partialSum(vec1.size());
  std::partial_sum(vec1.begin(), vec1.end(), partialSum.begin());
  printVector("Partial sum: ", partialSum);

  // 18.5. std::reduce()
  std::cout
      << std::endl
      << "18.5.Using std::reduce() to perform a paraller-friendly reduction of "
         "a range using a specified binary operation (e.g. sum)"
      << std::endl;
  printVector("Vector", vec1);
  result = std::reduce(vec1.begin(), vec1.end());
  std::cout << "Sum: " << result << std::endl;

  // 18.6. std::transform_reduce()
  std::cout << std::endl
            << "18.6. Using std::transform_reduce() to combine both "
               "transformation and reduction in a single step"
            << std::endl;
  printVector("Vector", vec1);
  int transformedSum = std::transform_reduce(
      vec1.begin(), vec1.end(), 0, std::plus<>(), [](int x) { return x * x; });
  std::cout << "Result: " << transformedSum << std::endl;

  // 18.7. std::exclusive_scan()
  std::cout
      << std::endl
      << "18.7. Using std::exclusive_scan() to computes the prefix sum of a "
         "sequence, excluding the current element in the sum for each position"
      << std::endl;
  printVector("Vector", vec1);
  std::vector<int> resultVector(vec1.size());
  std::exclusive_scan(vec1.begin(), vec1.end(), resultVector.begin(), 0);
  printVector("Result", resultVector);

  // 18.8. std::inclusive_scan()
  std::cout
      << std::endl
      << "18.8. Using std::inclusive_scan() to compute the prefix sum of a "
         "sequence, including the current element in the sum for each position"
      << std::endl;
  printVector("Vector", vec1);
  resultVector.clear();
  resultVector.resize(vec1.size());
  std::inclusive_scan(vec1.begin(), vec1.end(), resultVector.begin());
  printVector("Result", resultVector);
}

int main() {
  // 1. Initializing a vector
  std::cout << "*** 1. Initializing a vector ***" << std::endl;
  initialization();

  // 2. Accessing and modifying a vector
  std::cout << std::endl
            << "*** 2. Accessing and modifying a vector ***" << std::endl;
  accessingAndModification();

  // 3. Inserting and removing element
  std::cout << std::endl
            << "*** 3. Inserting and removing element from a vector ***"
            << std::endl;
  insertingAndRemoving();

  // 4. Capacity managment in a vector
  std::cout << std::endl
            << "***  4. Capacity managment in a vector ***" << std::endl;
  capacityManagement();

  // 5. Sorting and ordering algorithms
  std::cout << std::endl
            << "*** 5. Sorting and ordering algorithms ***" << std::endl;
  sortingAndOrderingAlgorithms();

  // 6. Searching algorithms
  std::cout << std::endl << "*** 6. Searching algorithms ***" << std::endl;
  searchingAlgorihtms();

  // 7. Modifying algorithms
  std::cout << std::endl << "*** 7. Modifying algorithms ***" << std::endl;
  modifyingAlgorithms();

  // 8. Removing algorithms
  std::cout << std::endl << "*** 8. Removing algorithms ***" << std::endl;
  removingAlgorithms();

  // 9. Reversig and rotating algorithms
  std::cout << std::endl
            << "*** 9. Reversing and rotating algorithms ***" << std::endl;
  reversingAndRotatingAlgorithms();

  // 10. Comparing and checking algorihtms
  std::cout << std::endl
            << "*** 10. Comparing and checking algorithms ***" << std::endl;
  comparingAndCheckingAlgorithms();

  // 11. Counting algorithms
  std::cout << std::endl << "*** 11. Counting algorithms ***" << std::endl;
  countingAlgorithms();

  // 12. Randomization algorithms
  std::cout << std::endl << "*** 12. Randomization algorithms ***" << std::endl;
  randomizationAlgorithms();

  // 13. Set operation algorithms
  std::cout << std::endl << "*** 13. Set operation algoirhtms ***" << std::endl;
  setOperationAlgorithms();

  // 14. Min/Max algoirthms
  std::cout << std::endl << "*** 14. Min/Max algorithms ***" << std::endl;
  minMaxAlgorithms();

  // 15. Partitioning algorithms
  std::cout << std::endl << "*** 15. Partitioning algorithms ***" << std::endl;
  partitioningAllgorithms();

  // 16. Heap  algorithms
  std::cout << std::endl << "*** 16. Heap algorithms ***" << std::endl;
  heapAlgorithms();

  // 17. Additional algorithms
  std::cout << std::endl << "*** 17. Additional algorithms ***" << std::endl;
  additionalAlgorithms();

  // 18. Numeric algorithms
  std::cout << std::endl << "*** 18. Numeric algorithms ***" << std::endl;
  numericAlgorithms();

  return 0;
}

