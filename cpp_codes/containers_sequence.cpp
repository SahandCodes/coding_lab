/* This file includes examples for different sequence containers used in C++
 *
 * Sequence containers: These containers store elements in a linear order and
 * provide efficient element access, insertion, and deletion
 *
 *  1.1. std::vector: It is a dynamic array that can resize itself as elements
 * are added or removed. It provides random access to its elements, meaning you
 * can access any element in constant time (O(1)) using an index. While it
 * offers efficient insertions and deletions at the end (amortized O(1)),
 * insertions and deletions at the beginning or middle can be slow (O(n))
 * because it may require shifting elements. std::vector is a good choice when
 * you need a dynamic array that supports efficient random access and
 * additions/removals at the end.
 *
 *  1.2. std::deque (double-ended queue): It allows efficient insertions and
 * deletions at both the front and the back of the container. Unlike
 * std::vector, which stores elements in a contiguous block of memory,
 * std::deque stores its elements in chunks or blocks, enabling fast operations
 * at both ends of the sequence. Access to elements by index is still fast
 * (O(1)), but operations in the middle of the container are slower than at the
 * ends. It's useful when you need efficient additions/removals at both ends of
 * the sequence.
 *
 *  1.3. std::list: It is a doubly linked list that allows fast insertions and
 * deletions at both the beginning and the end of the sequence, as well as in
 * the middle of the list (O(1) for insertions and deletions). However, access
 * to elements by index is slow (O(n)) because you have to traverse the list. It
 * is ideal for situations where elements will be frequently inserted or removed
 * from the middle or ends of the container, but not for cases requiring fast
 * access by position.
 *
 *  1.4. std::array: It is a container that wraps a fixed-size array. Unlike a
 * regular C-style array, std::array provides a safer and more convenient
 * interface, including member functions like at(), size(), and begin(), among
 * others. The size of a std::array is known at compile time, and it is stored
 * in a contiguous block of memory. It is useful when the size of the array is
 * fixed and known beforehand, offering the safety and functionality of a
 * container with the performance of a C-style array.
 *
 */

#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

// Use std::vector
void useVector() {
  auto printVector = [](const std::string& vectorName,
                        const std::vector<int>& vec) {
    std::cout << vectorName << ": ";
    for (int i = 0; i < vec.size(); ++i) {
      if (i == 0) {
        std::cout << "[" << vec[i] << ", ";
      } else if (i == vec.size() - 1) {
        std::cout << vec[i] << "]";
      } else {
        std::cout << vec[i] << ", ";
      }
    }
    std::cout << std::endl;
  };
  // 1.1 Create and initilize a vector
  std::cout << "1.1 Create and initilize a vector" << std::endl;
  std::vector<int> vec{1, 2, 3, 4, 5};
  printVector("Vector", vec);

  // 1.2. Accessing elements
  std::cout << std::endl << "1.2. Accessing elements" << std::endl;
  printVector("Vector", vec);
  std::cout << "First element (operator []): " << vec[0] << std::endl;
  std::cout << "First element (at()): " << vec.at(0) << std::endl;
  std::cout << "First element (front()): " << vec.front() << std::endl;
  std::cout << "Last element (back()): " << vec.back() << std::endl;

  // 1.3. Modifying elements
  std::cout << std::endl << "1.3. Modifying elements" << std::endl;
  printVector("Initial vector", vec);
  std::cout << "Changing first element to 10  and second element to 11"
            << std::endl;
  vec[0] = 10;
  vec.at(1) = 11;
  printVector("Modified vector", vec);

  // 1.4. Adding elements
  std::cout << std::endl << "1.4. Adding elements" << std::endl;
  printVector("Initial vector", vec);
  std::cout << "Adding two elements of 6 and 7 to the vector" << std::endl;
  vec.push_back(6);
  vec.emplace_back(7);
  printVector("Modified vector", vec);

  // 1.5. Removing elements
  std::cout << std::endl << "1.5. Removing elements" << std::endl;
  printVector("Vector", vec);
  std::cout << "Removing second and last elements" << std::endl;
  vec.pop_back();
  vec.erase(vec.begin() + 1);
  printVector("Modified vector", vec);

  // 1.6. Inserting elements
  std::cout << std::endl << "1.6. Inserting elements" << std::endl;
  printVector("Initial vector", vec);
  std::cout << "Inserting 100 as a second element" << std::endl;
  vec.insert(vec.begin() + 1, 100);
  printVector("Modified vector", vec);

  // 1.7. Emplace (construct element in-place)
  std::cout << std::endl
            << "1.7. Emplace (construct element in-place)" << std::endl;
  printVector("Initial vector", vec);
  std::cout << "Emplacing 200 as a third element" << std::endl;
  vec.emplace(vec.begin() + 2, 200);
  printVector("Modified vector", vec);

  // 1.8. Resizing
  std::cout << std::endl << "1.8. Resizing" << std::endl;
  printVector("Initial vector", vec);
  std::cout
      << "Resizing the vector to 10 and initilizing all new elements to 99"
      << std::endl;
  vec.resize(10, 99);
  printVector("Modified vector", vec);

  // 1.9. Capacity functions
  std::cout << std::endl << "1.9. Capacity functions" << std::endl;
  printVector("Vector", vec);
  std::cout << "Size: " << vec.size() << std::endl;
  std::cout << "Capacity: " << vec.capacity() << std::endl;
  std::cout << "Max size: " << vec.max_size() << std::endl;

  // 1.10. Clearing and shrinking
  std::cout << std::endl << "1.10. Clearing and shrinking" << std::endl;
  printVector("Vector", vec);
  vec.shrink_to_fit();
  std::cout << "After shrink_to_fit(), capacity: " << vec.capacity()
            << std::endl;
  vec.clear();
  std::cout << "After clear(), size: " << vec.size() << std::endl;

  // 1.11. Assigning new values
  std::cout << std::endl << "1.11. Assigning new values" << std::endl;
  printVector("Initial vector", vec);
  std::cout << "New values: 10, 20, 30, 40, 50" << std::endl;
  vec.assign({10, 20, 30, 40, 50});
  printVector("Modified vector", vec);

  // 1.12. Swapping two vectors
  std::cout << std::endl << "1.12. Swapping two vectors" << std::endl;
  printVector("First vector", vec);
  std::vector<int> vec2{99, 88, 77};
  printVector("Second vector", vec2);
  vec.swap(vec2);
  printVector("First vector after swapping", vec);
  printVector("Second vector after swapping", vec2);

  // 1.13. Checking empty
  std::cout << std::endl << "1.13. Checking empty" << std::endl;
  printVector("Vector", vec);
  std::cout << "Vector is empty: " << std::boolalpha << vec2.empty()
            << std::endl;

  // 1.14. Iterator
  std::cout << std::endl << "1.14. Iterator" << std::endl;
  printVector("Vector", vec);
  std::cout << "Printing vector using iterator: ";
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (it == vec.begin()) {
      std::cout << "[" << *it << ", ";
    } else if (it == vec.end() - 1) {
      std::cout << *it << "]";
    } else {
      std::cout << *it << ", ";
    }
  }
  std::cout << std::endl;

  // 1.15. Reverse iterator
  std::cout << std::endl << "1.15. Reverse iterator: " << std::endl;
  printVector("Vector", vec);
  std::cout << "Printing Reverese orderd vector: ";
  for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    if (it == vec.rbegin()) {
      std::cout << "[" << *it << ", ";
    } else if (it == vec.rend() - 1) {
      std::cout << *it << "] ";
    } else {
      std::cout << *it << ", ";
    }
  }
  std::cout << std::endl;

  // 1.16. Sorting
  std::cout << std::endl << "1.16. Sorting:" << std::endl;
  printVector("Initial vector", vec);
  std::sort(vec.begin(), vec.end());
  printVector("Modified vector", vec);

  // 1.17. Finding an element
  std::cout << std::endl << "1.17. Finding an element" << std::endl;
  printVector("Vector", vec);
  auto it = std::find(vec.begin(), vec.end(), 99);
  if (it != vec.end()) {
    std::cout << "Found 99 at position " << std::distance(vec.begin(), it)
              << std::endl;
  } else {
    std::cout << "99 not found" << std::endl;
  }

  // 1.18. Counting occurrences
  std::cout << std::endl << "1.18. Counting occurrences" << std::endl;
  printVector("Vector", vec);
  int count = std::count(vec.begin(), vec.end(), 99);
  std::cout << "Occurrences of 99: " << count << std::endl;

  // 1.19. Summing elements
  std::cout << std::endl << "1.19. Summing elements" << std::endl;
  printVector("Vector", vec);
  int sum = std::accumulate(vec.begin(), vec.end(), 0);
  std::cout << "Sum of elements: " << sum << std::endl;

  // 1.20. Removing duplicates
  std::cout << std::endl << "1.20. Removing duplicates" << std::endl;
  vec.emplace_back(99);
  printVector("Initial vector", vec);
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  printVector("Modified vector", vec);

  // 1.21. Reversing element
  std::cout << std::endl << "1.21. Reversing element" << std::endl;
  printVector("Initial vector", vec);
  std::reverse(vec.begin(), vec.end());
  printVector("Modified vector", vec);
}

// 2. Use std::deque
void useDeque() {
  auto printDeque = [](const std::string& dequeName,
                       const std::deque<int>& dq) {
    std::cout << dequeName << ": ";
    for (int i = 0; i < dq.size(); ++i) {
      if (i == 0) {
        std::cout << "[" << dq[i] << ", ";
      } else if (i == dq.size() - 1) {
        std::cout << dq[i] << "]";
      } else {
        std::cout << dq[i] << ", ";
      }
    }
    std::cout << std::endl;
  };

  // 2.1 Creating and initializing a deque
  std::cout << "2.1. Creating and initializing a dequeue" << std::endl;
  std::deque<int> dq{1, 2, 3, 4, 5};
  printDeque("Deque", dq);

  // 2.2. Accessing elements
  std::cout << std::endl << "2.2. Accessing eleemnts" << std::endl;
  printDeque("Deque", dq);
  std::cout << "First element (operator []): " << dq[0] << std::endl;
  std::cout << "First element (at()): " << dq[0] << std::endl;
  std::cout << "First element (front()): " << dq.front() << std::endl;
  std::cout << "Last element (back()): " << dq.back() << std::endl;

  // 2.3. Adding elements at both ends
  std::cout << std::endl << "2.3. Adding elements at both ends" << std::endl;
  printDeque("Initial Deque", dq);
  std::cout << "Adding -1 and 0 to the front and 6 and 7 to the back of the que"
            << std::endl;
  dq.push_front(0);
  dq.emplace_front(-1);
  dq.push_back(6);
  dq.emplace_back(7);
  printDeque("Modified deque", dq);

  // 2.4. Removinng elements from both ends
  std::cout << std::endl
            << "2.4. Removing elements from both ends" << std::endl;
  printDeque("Initial deque", dq);
  std::cout << "Removing first and last elements" << std::endl;
  dq.pop_back();
  dq.pop_front();
  printDeque("Modified deque", dq);

  // 2.5. Inserting elements
  std::cout << std::endl << "2.5. Inserting elements" << std::endl;
  printDeque("Initial deque", dq);
  std::cout << "Inserting 100 as a third element and inserting 200 as a fourth "
               "element"
            << std::endl;
  dq.insert(dq.begin() + 2, 100);
  dq.emplace(dq.begin() + 3, 200);
  printDeque("Modified deque", dq);

  // 2.6. Erasing elements
  std::cout << std::endl << "2.6. Erasing elements" << std::endl;
  printDeque("Initial deque", dq);
  std::cout << "Erasing third element" << std::endl;
  dq.erase(dq.begin() + 2);
  printDeque("Modified deque", dq);

  // 2.7. Resizing
  std::cout << std::endl << "2.7. Resizing" << std::endl;
  printDeque("Initial deque", dq);
  std::cout << "Resize the deque to 10 and set all new elements to 99"
            << std::endl;
  dq.resize(10, 99);
  printDeque("Modified deque", dq);

  // 2.8 Capacity function
  std::cout << std::endl << "2.8. Capacity function" << std::endl;
  printDeque("Deque", dq);
  std::cout << "Size: " << dq.size() << std::endl;
  std::cout << "Max size: " << dq.max_size() << std::endl;

  // 2.9. Clearing the deque
  std::cout << std::endl << "2.9. Clearing deque" << std::endl;
  printDeque("Initial deque", dq);
  dq.clear();
  printDeque("Modified deque", dq);

  // 2.10. Assigning new vlues
  std::cout << std::endl << "Assigning new values" << std::endl;
  printDeque("Initial deque", dq);
  std::cout << "New values: 10, 20, 30, 40, 50" << std::endl;
  dq.assign({10, 20, 30, 40, 50});
  printDeque("Modified deque", dq);

  // 2.11. Swapping two deques
  std::cout << std::endl << "2.11. Swapping two deques" << std::endl;
  std::deque<int> dq2{99, 88, 77};
  printDeque("First deque", dq);
  printDeque("Second deque", dq2);
  dq.swap(dq2);
  printDeque("First deque after swaping", dq);
  printDeque("Second deque after swapping", dq2);

  // 2.12. Checking empty
  std::cout << std::endl << "2.12. Checking empty" << std::endl;
  std::cout << "deque is empty: " << std::boolalpha << dq.empty() << std::endl;

  // 2.13. Iterating using iterators
  std::cout << std::endl << "2.13. Iterating using iterators" << std::endl;
  printDeque("Deque", dq);
  std::cout << "Printing deuqe uisng iterator" << std::endl;
  std::cout << "Deque: ";
  for (auto it = dq.begin(); it != dq.end(); ++it) {
    if (it == dq.begin()) {
      std::cout << "[" << *it << " ,";
    } else if (it == dq.end() - 1) {
      std::cout << *it << "]";
    } else {
      std::cout << *it << ", ";
    }
  }
  std::cout << std::endl;

  // 2.14. Reverse iteration
  std::cout << std::endl << "2.14. Reverse iteration" << std::endl;
  printDeque("Deque", dq);
  std::cout << "Printing reverse deque using iterator" << std::endl;
  std::cout << "Reversed deque: ";
  for (auto it = dq.rbegin(); it != dq.rend(); ++it) {
    if (it == dq.rbegin()) {
      std::cout << "[" << *it << ", ";
    } else if (it == dq.rend() - 1) {
      std::cout << *it << "]";
    } else {
      std::cout << *it << ", ";
    }
  }
  std::cout << std::endl;

  // 2.15. Sorting the deque
  std::cout << std::endl << "2.15. Sorting the deque" << std::endl;
  printDeque("Initial deque", dq);
  std::sort(dq.begin(), dq.end());
  printDeque("Modified deque", dq);

  // 2.16. Finding an element
  std::cout << std::endl << "2.16. Finding an element" << std::endl;
  printDeque("Initial deque", dq);
  auto it = std::find(dq.begin(), dq.end(), 99);
  if (it != dq.end()) {
    std::cout << "Found 99 at position " << std::distance(dq.begin(), it)
              << std::endl;
  } else {
    std::cout << "99 not found" << std::endl;
  }

  // 2.17. Counting occurrences
  std::cout << std::endl << "2.17. Counting occurrences" << std::endl;
  printDeque("Deque", dq);
  int count = std::count(dq.begin(), dq.end(), 99);
  std::cout << "Occurrences of 99: " << count << std::endl;

  // 2.18. Summing elements
  std::cout << std::endl << "2.18. Summing elements" << std::endl;
  printDeque("Deque", dq);
  int sum = std::accumulate(dq.begin(), dq.end(), 0);
  std::cout << "Sum of elemments: " << sum << std::endl;

  // 2.19. Removing duplicates
  std::cout << std::endl << "2.19. Removing duplicates" << std::endl;
  dq.emplace_back(99);
  printDeque("Initial deque", dq);
  dq.erase(std::unique(dq.begin(), dq.end()), dq.end());
  printDeque("Sorted deque", dq);

  // 2.20. Reversing elements
  std::cout << std::endl << "2.20. Reversing elements" << std::endl;
  printDeque("Initial deque", dq);
  std::reverse(dq.begin(), dq.end());
  printDeque("Reversed deque", dq);
}

// 3. Use std::list
void useList() {
  auto printList = [](const std::string& listName, const std::list<int>& lst) {
    std::cout << listName << ": ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
      if (it == lst.begin()) {
        std::cout << "[" << *it << ", ";
      } else if (std::next(it) == lst.end()) {
        std::cout << *it << "]";
      } else {
        std::cout << *it << ", ";
      }
    }
    std::cout << std::endl;
  };

  // 3.1. Create and initialize a list
  std::cout << "3.1. Create and initialize a list" << std::endl;
  std::list<int> lst{1, 2, 3, 4, 5};
  printList("List", lst);

  // 3.2. Accessing elements
  std::cout << std::endl << "3.2. Accessing elemnts" << std::endl;
  printList("List", lst);
  std::cout << "First element (front()): " << lst.front() << std::endl;
  std::cout << "Last element (back()): " << lst.back() << std::endl;

  // 3.3 Adding elements at both ends
  std::cout << std::endl << "3.3. Adding elements at both ends" << std::endl;
  printList("Initial list", lst);
  std::cout
      << "Adding -1 and 0 to the begining and 6 and 7 to the end of the list"
      << std::endl;
  lst.push_front(0);
  lst.emplace_front(-1);
  lst.push_back(6);
  lst.emplace_back(7);
  printList("Modified list", lst);

  // 3.4. Removing elements from both ends
  std::cout << std::endl
            << "3.4. Removing elements from both ened" << std::endl;
  printList("Initial list", lst);
  std::cout << "Removing first and last elements" << std::endl;
  lst.pop_front();
  lst.pop_back();
  printList("Modified list", lst);

  // 3.5. Inserting elements at a specific position
  std::cout << std::endl
            << "3.5. Inserting elements at a specific position" << std::endl;
  printList("Initial list", lst);
  std::cout << "Inserting 100 at the third position" << std::endl;
  auto it = lst.begin();
  std::advance(it, 2);
  lst.insert(it, 100);
  printList("Modified list", lst);

  // 3.6. Emplacing elements at specific position
  std::cout << std::endl
            << "3.6. Emplacing elements at specific position" << std::endl;
  printList("Initial list", lst);
  std::cout << "Emplacing 200 at the fourth position" << std::endl;
  it = lst.begin();
  std::advance(it, 3);
  lst.emplace(it, 200);
  printList("Modified list", lst);

  // 3.7. Erasing elements
  std::cout << std::endl << "3.7. Erasing elements" << std::endl;
  printList("Initial list", lst);
  it = lst.begin();
  std::cout << "Removing Second element" << std::endl;
  std::advance(it, 1);
  lst.erase(it);
  printList("Modified list", lst);

  // 3.8. Removing all elemnts with a specific value
  std::cout << std::endl
            << "3.8. Removing all elements with specific value" << std::endl;
  printList("Initial list", lst);
  std::cout << "Remvoe 200" << std::endl;
  lst.remove(200);
  printList("Modified list", lst);

  // 3.9. Removing elements baseed on a condition
  std::cout << std::endl
            << "3.9. Removing elements based on a condition" << std::endl;
  printList("Initial list", lst);
  std::cout << "Remove all even numbers" << std::endl;
  lst.remove_if([](int n) { return n % 2 == 0; });
  printList("Modified list", lst);

  // 3.10. Reversing the list
  std::cout << std::endl << "3.10. Reversing the list" << std::endl;
  printList("Initial list", lst);
  lst.reverse();
  printList("Modified list", lst);

  // 3.11. Sorting the list
  std::cout << std::endl << "3.11. Sorting the list" << std::endl;
  printList("Initial list", lst);
  lst.sort();
  printList("Modified list", lst);

  // 3.12. Merging two sorted lists
  std::cout << std::endl << "3.12. Merging two sorted lists" << std::endl;
  std::list<int> lst2{7, 6, 5};
  printList("First list", lst);
  printList("second list", lst2);
  lst2.sort();
  lst.merge(lst2);
  printList("Final list", lst);

  // 3.13. Splicing elements from one list to another
  std::cout << std::endl
            << "3.13. Splicing elements from on list to another" << std::endl;
  std::list<int> lst3{20, 10};
  printList("First list", lst);
  printList("Second list", lst3);
  lst.splice(lst.end(), lst3);
  printList("Final list", lst);

  // 3.14. Checking if the list is empy
  std::cout << std::endl << "3.14. Checking if the list is empty" << std::endl;
  printList("List", lst);
  std::cout << "List is empty: " << std::boolalpha << lst.empty() << std::endl;

  // 3.15. Clearing the list
  std::cout << std::endl << "3.15. Clearing the list" << std::endl;
  printList("Initial list", lst);
  lst.clear();
  printList("Modified list", lst);

  // 3.16. Swapping two lists
  std::cout << std::endl << "3.16. Swapping two lists" << std::endl;
  std::list<int> lst4{1, 2, 3, 4};
  printList("First list", lst);
  printList("Second list", lst4);
  lst.swap(lst4);
  printList("First list after swapping", lst);
  printList("Second list after swapping", lst4);

  // 3.17. Reverse iteration
  std::cout << std::endl << "3.17. Revere iteration" << std::endl;
  printList("List", lst);
  std::cout << "Printing list in reverse order: ";
  for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
    if (it == lst.rbegin()) {
      std::cout << "[" << *it << ", ";
    } else if (std::next(it) == lst.rend()) {
      std::cout << *it << "]" << std::endl;
    } else {
      std::cout << *it << ", ";
    }
  }

  // 3.18. Counting occurrences of a specific value
  std::cout << std::endl
            << "3.18. Counting occurrences of a specific value" << std::endl;
  lst.emplace_back(1);
  printList("List", lst);
  int count = std::count(lst.begin(), lst.end(), 1);
  std::cout << "Occurrences of 1: " << count << std::endl;

  // 3.19. Summing all elements
  std::cout << std::endl << "3.19. Summing all elements" << std::endl;
  printList("List", lst);
  int sum = std::accumulate(lst.begin(), lst.end(), 0);
  std::cout << "Sum of elements: " << sum << std::endl;
}

// Use std::array
void useArray() {
  auto printArray = [](const std::string& arrayName, const auto& arr) {
    std::cout << arrayName << ": ";
    for (size_t i = 0; i < arr.size(); ++i) {
      if (i == 0) {
        std::cout << "[" << arr[i] << ", ";
      } else if (i == arr.size() - 1) {
        std::cout << arr[i] << "]" << std::endl;
      } else {
        std::cout << arr[i] << ", ";
      }
    }
  };
  // 4.1. Creatging and initializing an array
  std::cout << "4.1. Creating and initializing array" << std::endl;
  std::array<int, 5> arr{1, 2, 3, 4, 5};
  printArray("Array", arr);

  // 4.2. Accessing elements
  std::cout << std::endl << "4.2. Accessing elements" << std::endl;
  printArray("Array", arr);
  std::cout << "First element (operator[]): " << arr[0] << std::endl;
  std::cout << "First element (at()): " << arr.at(0) << std::endl;
  std::cout << "First element (front()): " << arr.front() << std::endl;
  std::cout << "Last element (back()): " << arr.back() << std::endl;

  // 4.3. Modifying elements
  std::cout << std::endl << "4.3. Modifying elements" << std::endl;
  printArray("Initial array", arr);
  std::cout << "Modiying second element to 10" << std::endl;
  arr[1] = 10;
  printArray("Modified element", arr);

  // 4.4. Filling array with specific value
  std::cout << std::endl
            << "4.4. Filling array with specific value" << std::endl;
  printArray("Initial array", arr);
  std::cout << "Fill the array with 99" << std::endl;
  arr.fill(99);
  printArray("Modified array", arr);

  // 4.5. Iterating through the array
  std::cout << std::endl << "4.5. Iterating through the array" << std::endl;
  arr = {1, 2, 5, 3, 4};
  printArray("Array", arr);
  std::cout << "Printing array using iterator: ";
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    if (it == arr.begin()) {
      std::cout << "[" << *it << ", ";
    } else if (std::next(it) == arr.end()) {
      std::cout << *it << "]" << std::endl;
    } else {
      std::cout << *it << ", ";
    }
  }

  // 4.6. Reverse iteration
  std::cout << std::endl << "4.6. Reverse iteration" << std::endl;
  printArray("Array", arr);
  std::cout << "Printing array using revere iterator: ";
  for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
    if (it == arr.rbegin()) {
      std::cout << "[" << *it << ", ";
    } else if (std::next(it) == arr.rend()) {
      std::cout << *it << "]" << std::endl;
    } else {
      std::cout << *it << ", ";
    }
  }

  // 4.7. Sorting the array
  std::cout << std::endl << "4.7. Sorting the array" << std::endl;
  printArray("Initial array", arr);
  std::sort(arr.begin(), arr.end());
  printArray("Sorted array", arr);

  // 4.8. Finding an element
  std::cout << std::endl << "4.8. Finding an element" << std::endl;
  printArray("Array", arr);
  std::cout << "Find 3" << std::endl;
  auto it = std::find(arr.begin(), arr.end(), 3);
  if (it != arr.end()) {
    auto dist = std::distance(arr.begin(), it);
    std::cout << "Fount 3 at position " << dist << std::endl;
  } else {
    std::cout << "3 not fount" << std::endl;
  }

  // 4.9. Counting occurrence of value
  std::cout << std::endl << "4.9. Counting occurrence of value" << std::endl;
  printArray("Array", arr);
  int count = std::count(arr.begin(), arr.end(), 3);
  std::cout << "Occurrence of 3: " << count << std::endl;

  // 4.10. Summing all elements
  std::cout << std::endl << "4.10. Summing all elements" << std::endl;
  printArray("Array", arr);
  int sum = std::accumulate(arr.begin(), arr.end(), 0);
  std::cout << "Sum of elements: " << sum << std::endl;

  // 4.11. Swapping two arrays
  std::cout << std::endl << "4.11. Swapping two arrays" << std::endl;
  std::array arr2{10, 20, 30, 40, 50};
  printArray("Frist array", arr);
  printArray("Second array", arr2);
  arr.swap(arr2);
  printArray("First array after swapping", arr);
  printArray("Second array after swapping", arr2);

  // 4.12. Checking size
  std::cout << std::endl << "4.12. Checking size" << std::endl;
  printArray("Array", arr);
  std::cout << "Size of array: " << arr.size() << std::endl;

  // 4.13. Getting raw C-style array pointer
  std::cout << std::endl << "4.13. Getting C-style array pointer" << std::endl;
  printArray("Array", arr);
  int* ptr = arr.data();
  std::cout << "First element using data(): " << *ptr << std::endl;
}

int main() {
  // 1. std::vector
  std::cout << "*** 1. std::vector ***" << std::endl;
  useVector();

  // 2. std::deque
  std::cout << std::endl << "*** 2. std::deque ***" << std::endl;
  useDeque();

  // 3. std::list
  std::cout << std::endl << "*** 3. std::list ***" << std::endl;
  useList();

  // 4. std::array
  std::cout << std::endl << "*** 4. std::array ***" << std::endl;
  useArray();
}
