/*
 * This file includes various examples demonstrating different std::map
 * functionalities as follows
 *
 * 1. Initialization
 * 2. Accessing and modiying
 * 3. Inserting and removing
 * 4. Capacity managment
 * 5. Searching algorithms
 * 6. Moifyinng algorihtms
 * 7. Comparing and checking aglorithms
 * 8. Counting algorithms
 * 9. Set operation algorithms
 * 10. Min/Max algorithms
 * 11. Numeric algorithms
 *
 */

#include <iostream>
#include <iterator>
#include <map>
#include <numeric>

template <typename T1, typename T2, typename Compare>
void printMap(const std::string& mapName, const std::map<T1, T2, Compare>& mp) {
  std::cout << mapName << ": ";
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    if (it == mp.begin()) {
      std::cout << "{{" << it->first << "," << it->second << "}, ";
    } else if (std::next(it) == mp.end()) {
      std::cout << "{" << it->first << "," << it->second << "}}";
    } else {
      std::cout << "{" << it->first << "," << it->second << "}, ";
    }
  }
  std::cout << std::endl;
};

bool compare(int a, int b) { return a > b; }

// 1. Initialization
void initialization() {
  // 1.1. Default initialization
  std::cout << "1.1. Default initialization" << std::endl;
  std::map<int, std::string> mp1;
  printMap("Map", mp1);

  // 1.2. Direct initialization with empty initializer list
  std::cout << std::endl
            << "1.2. Direct initialization with empty initializer list"
            << std::endl;
  std::map<int, std::string> mp2{};
  printMap("Map", mp2);

  // 1.3. Direct list initialization with brace/parantheses
  std::cout << std::endl
            << "1.3. Direct list initialization with brace/parantheses with "
               "elements {{1,one}, {2,two}, {3, three}}"
            << std::endl;
  std::map<int, std::string> mp3{{1, "one"}, {2, "two"}, {3, "three"}};
  // or std::map<int, std::string> mp3({1, "one"}, {2, "two"}, {3, "three"});
  printMap("Map", mp3);

  // 1.4. Direct list initialization with brace/parantheses and std::make_pair
  std::cout << std::endl
            << "1.4. Direct list initialization with brace/parantheses, "
               " and std::make_pair and {{2, two}, "
               " with elements {3, three}, {4, four}} "
            << std::endl;
  std::map<int, std::string> mp4{std::make_pair<int, std::string>(2, "two"),
                                 std::make_pair<int, std::string>(3, "three"),
                                 std::make_pair<int, std::string>(4, "four")};
  // or std::map<int, std::string> mp3(std::make_pair<int, std::string>(2,
  // "two"),
  //                                  std::make_pair<int, std::string>(3,
  //                                  "three"), std::make_pair<int,
  //                                  std::string>(4, "four"));
  printMap("Map", mp4);

  // 1.5. Copy list initialization
  std::cout << std::endl
            << "1.5. Copy list initialization with elements {{5, five}, {6, "
               "six}, {7, seven}} "
            << std::endl;
  std::map<int, std::string> mp5 = {{5, "five"}, {6, "six"}, {7, "seven"}};
  printMap("Map", mp5);

  // 1.6. Copy list initialization with std::make_pair
  std::cout
      << std::endl
      << "1.6. Copy list initalization with std::make_pair and elements {{6, "
         "six}, {7, seven}, {8, eight}}"
      << std::endl;
  std::map<int, std::string> mp6 = {
      std::make_pair<int, std::string>(6, "six"),
      std::make_pair<int, std::string>(7, "seven"),
      std::make_pair<int, std::string>(8, "eight")};
  printMap("Map", mp6);

  // 1.7. Direct initialization form another map using copy constructor with
  // brace/ parantheses
  std::cout
      << std::endl
      << "1.7. Direct initialization from another map with elements {{7, "
         "seven}, {8, eight}} using copy constructor with brace/parantheses"
      << std::endl;
  std::map<int, std::string> mp7a{{7, "seven"}, {8, "eight"}};
  std::map<int, std::string> mp7b{mp7a};  // or mp7b(mp7a)
  printMap("Map", mp7b);

  // 1.8. Copy initialization form another map using copy constructor
  std::cout << std::endl
            << "1.8. Copy initialization from another map with elements {{8, "
               "eight}, {9, nine}} using copy constructor"
            << std::endl;
  std::map<int, std::string> mp8a{{8, "eight"}, {9, "nine"}};
  std::map<int, std::string> mp8b = mp8a;
  printMap("Map", mp8b);

  // 1.9. Direct initiallization from another map using move constructor
  std::cout << std::endl
            << "1.9. Direct initialization from another map with elements {{9, "
               "nine}, {10, ten}} using move constructor with brace/parantheses"
            << std::endl;
  std::map<int, std::string> mp9a{{9, "nine"}, {10, "ten"}};
  std::map<int, std::string> mp9b{std::move(mp9a)};  // or mp9b(std::move(mp9a))
  printMap("Map", mp9b);

  // 1.10. Copy initialization from another map using move
  // constructor
  std::cout << std::endl
            << "1.10. Copy initialization from another map with elements {{10, "
               "ten}, {11, eleven}} using move constructor"
            << std::endl;
  std::map<int, std::string> mp10a{{10, "ten"}, {11, "eleven"}};
  std::map<int, std::string> mp10b = std::move(mp10a);
  printMap("Map", mp10b);

  // 1.11. Range initialization
  std::cout << std::endl
            << "1.11. Range initialization from another vector with elements "
               "[{1, One}, {2, Two}, {3, Three}]"
            << std::endl;
  std::vector<std::pair<int, std::string>> vec{
      {1, "One"}, {2, "Two"}, {3, "three"}};
  std::map<int, std::string> mp11(vec.begin(), vec.end());
  printMap("Map", mp11);

  // 1.12. Initialization with default comparator (std::less<Key>)
  std::cout << std::endl
            << "1.12. Initialization with default comparator (std::less<Key>) "
               "and elements {{2, two}, {1, one}, {3, three}}"
            << std::endl;
  std::map<int, std::string> mp12{{2, "two"}, {1, "one"}, {3, "three"}};
  printMap("Map", mp12);

  // 1.13. Initialization with built-in-comparator (e.g.std::greater<Key>)
  std::cout << std::endl
            << "1.13. Initialization wiith std::greater<Key> with elements "
               "{{2, two}, {1, one}, {3, three}}"
            << std::endl;
  std::map<int, std::string, std::greater<int>> mp13{
      {2, "two"}, {1, "one"}, {3, "three"}};
  printMap("Map", mp13);

  // 1.14. Initialization using Functor
  std::cout << std::endl
            << "1.14. Initialization in descending order with elements {{2, "
               "two},{1, one}, {3, three}} using functor"
            << std::endl;
  struct DescendingOrder {
    bool operator()(int a, int b) const { return a > b; }
  };
  std::map<int, std::string, DescendingOrder> mp14{
      {2, "two"}, {1, "one"}, {3, "three"}};
  printMap("Map", mp14);

  // 1.15. Initialization using lambda function
  std::cout << std::endl
            << "1.15. Initialization in descending order with elements {{2, "
               "two}, {1, one}, {3, three}} using lambda function"
            << std::endl;
  auto descendingOrder = [](int a, int b) { return a > b; };
  std::map<int, std::string, decltype(descendingOrder)> mp15(
      {{2, "two"}, {1, "one"}, {3, "three"}}, descendingOrder);
  printMap("Map", mp15);

  // 1.16. Initialization using function pointer
  std::cout << std::endl
            << "1.16. Initializattion using function pointer with elements "
               "{{2, two}, {1, one}, {3, three}}"
            << std::endl;
  std::map<int, std::string, bool (*)(int, int)> mp16(
      {{2, "two"}, {1, "one"}, {3, "three"}}, compare);
  printMap("Map", mp16);
}

// 2. Accessing and modiying
void accessingAndModifying() {
  // 2.1. Using operator []
  std::cout
      << "2.1. Using operator [] to modify value assoicated with key 1 to I"
      << std::endl;
  std::map<int, std::string> mp{{1, "one"}, {2, "two"}, {3, "three"}};
  printMap("Initial Map", mp);
  mp[1] = "I";
  printMap("Modified map", mp);

  // 2.2. Using the at() member function
  std::cout << std::endl
            << "2.2 Using the at() member function to modify value associated "
               "with key 2 to II"
            << std::endl;
  printMap("Initial map", mp);
  mp.at(2) = "II";
  printMap("Modified map", mp);

  // 2.3. Usinng interator
  std::cout << std::endl
            << "2.3 Using iterator to modify value associated with key 3 to III"
            << std::endl;
  printMap("Initial map", mp);
  auto it = mp.begin();
  std::advance(it, 2);
  it->second = "III";
  printMap("Modfied map", mp);

  // 2.4. Using iterator-based for loop
  std::cout << std::endl
            << "2.4. Using iterator-based for loop to modify elements to {{1, "
               "one}, {2, two}, {3, three}}"
            << std::endl;
  printMap("Initial map", mp);
  std::map<int, std::string> newMap{{1, "one"}, {2, "two"}, {3, "three"}};
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    it->second = newMap[it->first];
  }
  printMap("Modified map", mp);

  // 2.5. Using reversed iterator-based for loop
  std::cout << std::endl
            << "2.5. Using reversed iterator-based for loop to modify elements "
               "to {{1, I}, {2, II}, {3, III}}"
            << std::endl;
  printMap("Initial map", mp);
  newMap = {{1, "I"}, {2, "II"}, {3, "III"}};
  for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
    it->second = newMap[it->first];
  }
  printMap("Modified map", mp);

  // 2.6. Using range-based for loop
  std::cout << std::endl
            << "2.6. Using range-based for loop  to modify elements to {{1, "
               "one}, {2, two}, {3, three}}"
            << std::endl;
  printMap("Initial map", mp);
  for (auto& [key, value] : mp) {
    value = (key == 1) ? "one" : (key == 2) ? "two" : "three";
  }
  printMap("Modified map", mp);

  // 2.7. Using find() function
  std::cout
      << std::endl
      << "2.7. Using find() function to modify value associated to key 1 to I"
      << std::endl;
  printMap("Initial map", mp);
  it = mp.find(1);
  if (it != mp.end()) it->second = "I";
  printMap("Modified map", mp);

  // 2.8. Using swap()
  std::cout << std::endl
            << "2.8. Using swap to change the content of the map to {{4, "
               "four}, {5, five}, {6, six}} "
            << std::endl;
  printMap("Initial map", mp);
  newMap = {{4, "four"}, {5, "five"}, {6, "six"}};
  mp.swap(newMap);
  printMap("Modified map", mp);

  // 2.9. Using std::for_each with iterators
  std::cout << std::endl
            << "2.9. Using std::for_each with iterators to modify elements to "
               "{{4, IV}, {5, V}, {6, VI}}"
            << std::endl;
  printMap("Initial map", mp);
  std::for_each(mp.begin(), mp.end(),
                [](std::pair<const int, std::string>& element) {
                  element.second = (element.first == 1)   ? "IV"
                                   : (element.first == 2) ? "V"
                                                          : "VI";
                });
  printMap("Modified map", mp);

  // 2.10. Using c++20 ranges
}

// 3. Inserting and removing
void insertingAndRemoving() {
  std::map<int, std::string> mp{{1, "one"}, {2, "two"}, {3, "three"}};
  // 3.1. Using insert() to add an element to the map. If the key already
  // exists, the insertion is ignored
  std::cout << "3.1. Using insert() to insert {1, I} and {4, four} to the map"
            << std::endl;
  printMap("Initial map", mp);
  mp.insert({{1, "I"}, {4, "four"}});
  // or mp.insert({1, "one"}); mp.insert({4, "four"});
  // or mp.insert(std::make_pair(1, "one")); mp.insert(std::make_pair(4,
  // "four"));
  printMap("Modified map", mp);

  // 3.2. Using insert () to insert from anothe container
  std::cout << std::endl
            << "3.2. Using insert() to insert form another container with "
               "elements {{2, II}, {5, five}}"
            << std::endl;
  printMap("Initial map", mp);
  std::map<int, std::string> mp2{{2, "II"}, {5, "five"}};
  mp.insert(mp2.begin(), mp2.end());
  printMap("Modified map", mp);

  // 3.3. Using insert_or_assign() to insert a new element if the key does not
  // exist,or update the exisiting element if the key exists (does not support
  // inserting multiple elemments at once)
  std::cout << std::endl
            << "3.3. Using insert_or_assign() to insert {1, I} and  {6, six} "
               "to the map"
            << std::endl;
  printMap("initial map", mp);
  mp.insert_or_assign(1, "I");
  auto it = --mp.end();
  mp.insert_or_assign(it, 6, "six");  // using hint to faster insertion
  printMap("Modified map", mp);

  // 3.4. Using emplace() to allow inserting elements efficiently by
  // constructing them in-place. If the key already exists, the insertion is
  // ignored
  std::cout << std::endl
            << "3.4. Using emplace() to insert {2, II} and {7, seven}"
            << std::endl;
  printMap("Initial map", mp);
  mp.emplace(2, "II");
  mp.emplace(7, "seven");
  printMap("Modified map", mp);

  // 3.5. Using emplace_hint() to insert an element into the container by
  // hinting the location
  std::cout << std::endl
            << "3.5. Using emplace_hint() to insert {8, eight}" << std::endl;
  printMap("Initial map", mp);
  it = --mp.end();
  mp.emplace_hint(it, 8, "eight");
  printMap("Modified map", mp);

  // 3.6. Using operator []
  std::cout << std::endl
            << "3.6. Using operator [] to insert {9, nine}" << std::endl;
  printMap("initial map", mp);
  mp[9] = "nine";
  printMap("Modified map", mp);

  // 3.7. Using erase() to remove by key
  std::cout << std::endl
            << "3.7. Using erase() to remove {9, nine}" << std::endl;
  printMap("Initial map", mp);
  mp.erase(9);
  printMap("Modifed  map", mp);

  // 3.8. Using erase with an iterator
  std::cout << std::endl
            << "3.8. Using erase with an iterator to remove {8, eight}"
            << std::endl;
  printMap("Initial map", mp);
  it = mp.find(8);
  mp.erase(it);
  printMap("Modified map", mp);

  // 3.9. Using erase() with range of iterators
  std::cout << std::endl
            << "3.9. Using erase() with range iterator to remove {4, four}, "
               "{5, five}, {6, six} "
            << std::endl;
  printMap("Initial map", mp);
  auto itStart = mp.find(4);
  auto itEnd = mp.find(7);
  mp.erase(itStart, itEnd);
  printMap("Modified map", mp);

  // 3.10. Using clear()
  std::cout << std::endl << "3.10. Using clear()" << std::endl;
  printMap("Initial map", mp);
  mp.clear();
  printMap("Modified map", mp);
}

// 4. Capacity managment
void capacityManagment() {
  std::map<int, std::string> mp{{1, "one"}, {2, "two"}, {3, "three"}};

  // 4.1. Using empty() to check if the map is empty
  std::cout << "4.1. Using empty to check if the map is empty" << std::endl;
  printMap("Map", mp);
  std::cout << "Is map empty: " << std::boolalpha << mp.empty() << std::endl;
  ;

  // 4.2. Using size() to return number of elements in the map
  std::cout << std::endl
            << "4.2. Using size() to return number of elements in the map"
            << std::endl;
  printMap("Map", mp);
  std::cout << "Map size: " << mp.size() << std::endl;

  // 4.3. Using max_size() to return the maximum number or elements the map can
  // hold
  std::cout << std::endl
            << "4.3. Using maz_size() to return the maximum number or elements "
               "the map can hold"
            << std::endl;
  std::cout << "Map max size: " << mp.max_size() << std::endl;
}

// 5. Searching algorithms
void searchingAlgorithms() {
  std::map<int, std::string> mp{{1, "one"}, {2, "two"}, {3, "three"}};

  // 5.1. Using find() to return an iterator to the element
  std::cout << "5.1. Using find() to return an iterator to key = 2"
            << std::endl;
  printMap("Map", mp);
  auto it = mp.find(2);
  if (it != mp.end()) {
    std::cout << "Found value: " << it->second << std::endl;
  }

  // 5.2. Using count() to check if the key exists
  std::cout << std::endl
            << "5.2. Using count() to check if the key = 2 exists" << std::endl;
  printMap("Map", mp);
  if (mp.count(2)) {
    std::cout << "Key 2 exists" << std::endl;
  }

  // 5.3. Using lower_bound() to find first element >= key
  std::cout << std::endl
            << "5.3. Using lower_bound() to find  the first element >= 2"
            << std::endl;
  it = mp.lower_bound(2);
  if (it != mp.end()) {
    std::cout << " Loweer bound: " << it->second << " with key: " << it->first
              << std::endl;
  }

  // 5.4. Using upper_bound() to find first element > key
  std::cout << std::endl
            << "5.4. Using upper_bound() to find the first element > 2"
            << std::endl;
  it = mp.upper_bound(2);
  if (it != mp.end()) {
    std::cout << "Upper bound: " << it->second << " with key: " << it->first
              << std::endl;
  }

  // 5.5. Using equal_range() to get both lower_bound() and upper_bound()
  std::cout << std::endl
            << "5.5. Using equal_range() to get both lower_bound and "
               "upper_bound() for key = 2"
            << std::endl;
  auto range = mp.equal_range(2);
  if (range.first != mp.end()) {
    std::cout << "Lower bound: " << range.first->second
              << " with key: " << range.first->first << std::endl;
  }
  if (range.second != mp.end()) {
    std::cout << "Upper bound: " << range.second->second
              << " with key: " << range.second->first << std::endl;
  }

  // 5.6. Using std::find_if with iterator to find the value instead of the key
  std::cout << std::endl
            << "5.6. Using std::find_if with iterator if to find the value "
               "instead of the key"
            << std::endl;
  printMap("Map", mp);
  it = std::find_if(mp.begin(), mp.end(),
                    [](const auto& pair) { return pair.second == "two"; });
  if (it != mp.end()) {
    std::cout << "Found key: " << it->first << std::endl;
  }

  // 5.7. Using containers in C++20 to check if the key exists
}

// 6. Modifying algorithms
void modifyingAlgorithms() {
  std::map<int, std::string> mp{{1, "one"}, {2, "two"}, {3, "three"}};

  // 6.1. Using std::for_each to modify values in the map
  std::cout
      << "6.1. Using std::for_each to modify values in the map to {I, II, III}"
      << std::endl;
  printMap("Initial map", mp);
  std::for_each(mp.begin(), mp.end(), [](std::pair<const int, std::string>& p) {
    p.second = (p.first == 1) ? "I" : (p.first == 2) ? "II" : "III";
  });
  printMap("Modified map", mp);

  // 6.2. Using std::transform to transform map elements and stores them in
  // another map
  std::cout << std::endl
            << "6.2. Using std::transform to transform map  to {{1, one}, {2, "
               "II}, {3, three}, {4, four}} "
            << std::endl;
  printMap("Initial map", mp);
  std::map<int, std::string> newMap{
      {1, "one"}, {2, "II"}, {3, "three"}, {4, "four"}};
  std::transform(newMap.begin(), newMap.end(), std::inserter(mp, mp.begin()),
                 [](const auto& p) { return p; });
  printMap("Modified map", mp);
}

// 7. Comparing and checking algorithms
void comparingAndCheckingAlgorithms() {
  std::map<std::string, int> mp{{"one", 1}, {"two", 2}, {"three", 3}};

  // 7.1. Using std::all_of to check if all elements satisfy a condition
  std::cout << "7.1. Using std::all_of to check if all values are positive"
            << std::endl;
  printMap("Map", mp);
  bool allGreaterThanZero = std::all_of(
      mp.begin(), mp.end(), [](const auto& pair) { return pair.second > 0; });
  std::cout << "All valus positive: " << std::boolalpha << allGreaterThanZero
            << std::endl;

  // 7.2. Using std::any_of to check if at least one element satisfies a
  // condition
  std::cout
      << std::endl
      << "7.2. Using std::any_of to check if at least one element is positive"
      << std::endl;
  printMap("Map", mp);
  bool anyGreaterThanZero = std::any_of(
      mp.begin(), mp.end(), [](const auto& pair) { return pair.second > 0; });
  std::cout << "Any value positive: " << std::boolalpha << anyGreaterThanZero
            << std::endl;

  // 7.3. Using std::none_of to check if no elements satisfy a condition
  std::cout << std::endl
            << "7.3. Using std::none_of to check if no element is positive"
            << std::endl;
  printMap("Map", mp);
  bool noneOfGreaterThanZero = std::none_of(
      mp.begin(), mp.end(), [](const auto& pair) { return pair.second > 0; });
  std::cout << "No value positive: " << std::boolalpha << noneOfGreaterThanZero
            << std::endl;

  // 7..4. Using std::count_if to count elements matching a condition
  std::cout << std::endl
            << "7.4. Using std::count_if to count positive values" << std::endl;
  printMap("Map", mp);
  int count = std::count_if(mp.begin(), mp.end(),
                            [](const auto& pair) { return pair.second > 0; });
  std::cout << "Positive values:  " << count << std::endl;

  // 7.5. Using std::equal to compare two std::map objects
  std::cout << std::endl
            << "7.5. Using std::equal to compare two maps values are equal"
            << std::endl;
  std::map<std::string, int> mp1{{"two", 2}, {"three", 3}, {"four", 4}};
  printMap("First map", mp);
  printMap("Second map", mp1);
  bool areValuesEqual = std::equal(
      mp.begin(), mp.end(), mp1.begin(), mp1.end(),
      [](const auto& p1, const auto& p2) { return p1.second == p2.second; });
  std::cout << "Two maps have same values: " << std::boolalpha << areValuesEqual
            << std::endl;

  // 7.6. Using std::lexicographical_compare to compare two maps in order
  std::cout
      << std::endl
      << "7.6. Using std::lexicographical_compare to compare values of two maps"
      << std::endl;
  printMap("First map", mp);
  printMap("Second map", mp1);
  areValuesEqual = std::lexicographical_compare(
      mp.begin(), mp.end(), mp1.begin(), mp1.end(),
      [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
  if (areValuesEqual) {
    std::cout << "Values of the first map larger than second map" << std::endl;
  } else {
    std::cout << "Values of the second map larger than first map" << std::endl;
  }

  // 7.7. Using std::mismatch to find first difference between two maps
  std::cout
      << std::endl
      << "7.7. Using std::mismatch to find first difference between two maps"
      << std::endl;
  printMap("First map", mp);
  printMap("Second map", mp1);
  auto mismatchResult =
      std::mismatch(mp.begin(), mp.end(), mp1.begin(), mp1.end(),
                    [](const auto& p1, const auto& p2) {
                      return (p1.first == p2.first) && (p1.second == p2.second);
                    });
  if (mismatchResult.first != mp.end() && mismatchResult.second != mp1.end()) {
    std::cout << "First mismatch from the first map: {"
              << mismatchResult.first->first << ", "
              << mismatchResult.first->second << "}"
              << " First mismatch from the second map:  {"
              << mismatchResult.second->first << ", "
              << mismatchResult.second->second << "}" << std::endl;
  } else {
    std::cout << "The ranges are identical." << std::endl;
  }
}

// 8. Counting algorithms
void countingAlgorithms() {
  std::map<int, std::string> mp{{1, "one"}, {2, "one"}, {3, "three"}};
  // 8.1. Using std::count to count the number of elements in a range that are
  // equal to specific value
  std::cout << "8.1. Using std::count to count the number of elements that "
               "values equal to {1, one}"
            << std::endl;
  printMap("Map", mp);
  int countResult = std::count(mp.begin(), mp.end(),
                               std::pair<const int, std::string>{1, "one"});
  std::cout << "Result: " << countResult << std::endl;

  // 8.2. Using std::count_if to count the elemments in the range that satisfy a
  // specific predicate
  std::cout
      << std::endl
      << "8.2. Using std::count_if to count the elements in the range that "
         "satisfy key > 2"
      << std::endl;
  printMap("Map", mp);
  countResult =
      std::count_if(mp.begin(), mp.end(), [](auto p) { return p.first > 2; });
  std::cout << "Result: " << countResult << std::endl;

  // 8.3. Using std::ranges::count and std::ranges::count_if
  // (c++20) same as std::count and std::count_if
}

// 9. Set operation algorithms
void setOperationAlgorithms() {
  std::map<int, std::string> mp1{{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> mp2{{2, "II"}, {3, "III"}, {4, "IV"}};

  // 9.1. Using std::set_union to merge two sorted ranges into a single sortedd
  // range containing the union of the elements, removing duplicates.
  std::cout << "9.1. Using std::set_union to merge two maps" << std::endl;
  printMap("First map", mp1);
  printMap("Second map", mp2);
  std::map<int, std::string> mpUnion;
  std::set_union(
      mp1.begin(), mp1.end(), mp2.begin(), mp2.end(),
      std::inserter(mpUnion, mpUnion.end()),
      [](const auto& a, const auto& b) { return a.first < b.first; });
  printMap("Result", mpUnion);

  // 9.2. std::set_intersection to compute  the common pair between to map
  std::cout << std::endl
            << "9.2. std::set_intersection to compute the common pair between "
               "two maps"
            << std::endl;
  printMap("First map", mp1);
  printMap("Second map", mp2);
  std::map<int, std::string> mpIntersection;
  std::set_intersection(mp1.begin(), mp1.end(), mp2.begin(), mp2.end(),
                        std::inserter(mpIntersection, mpIntersection.end()));
  printMap("Resullt", mpIntersection);

  // 9.3. Using std::set_difference to commpute  elements in the first map but
  // not in the second map
  std::cout
      << std::endl
      << "9.3. Using std::set_difference to compute ellements in the first map "
         "but not in the second map"
      << std::endl;
  printMap("First map", mp1);
  printMap("Second map", mp2);
  std::map<int, std::string> mpDifference;
  std::set_difference(mp1.begin(), mp1.end(), mp2.begin(), mp2.end(),
                      std::inserter(mpDifference, mpDifference.end()));
  printMap("Result", mpDifference);

  // 9.4. Using std::set_symmetric_difference to compute elements that are in
  // the first map or the second map but not in both maps
  std::cout
      << std::endl
      << "9.4. Using std::set_symmetric_difference to compute elements that "
         "are in the first map or the second map but no in both maps"
      << std::endl;
  printMap("First map", mp1);
  printMap("Second map", mp2);
  std::map<int, std::string> mpSymDiff;
  std::set_symmetric_difference(mp1.begin(), mp1.end(), mp2.begin(), mp2.end(),
                                std::inserter(mpSymDiff, mpSymDiff.end()));
  printMap("Result", mpSymDiff);
}

// 10. Min/Max algorithms
void minMaxAlgorithms() {
  std::map<std::string, int> mp{{"one", 1}, {"two", 2}, {"three", 3}};

  // 10.1. Using std::min_element to compute the minimmum element
  std::cout
      << "10.1. Using std::min_element to compute the minumum value of the map"
      << std::endl;
  ;
  printMap("Map", mp);
  auto result = std::min_element(
      mp.begin(), mp.end(),
      [](const auto& a, const auto& b) { return a.second < b.second; });
  std::cout << "Minimmum value: " << result->second << std::endl;

  // 10.2. Using std::max_element to compute the maximum element
  std::cout
      << std::endl
      << "10.2. Using std::max_element to compute the maximum value of the map"
      << std::endl;
  printMap("Map", mp);
  result = std::max_element(
      mp.begin(), mp.end(),
      [](const auto& a, const auto& b) { return a.second < b.second; });
  std::cout << "Maximum value: " << result->second << std::endl;
}

// 11. Numeric algorithms
void numericAlgorithms() {
  std::map<std::string, int> mp{{"first", 1}, {"second", 2}, {"third", 3}};
  std::map<std::string, int> mp2{{"first", 2}, {"second", 3}, {"third", 4}};

  // 11.1. Using std::accumulate
  std::cout
      << "11.1. Using std::accumulate to compute sum of the values of the map"
      << std::endl;
  printMap("Map", mp);
  int sum = std::accumulate(
      mp.begin(), mp.end(), 0,
      [](int total, const auto& a) { return total + a.second; });
  std::cout << "Result: " << sum << std::endl;

  // 11.2. Using std::inner_product
  std::cout
      << std::endl
      << "11.2. Using std::inner_product to compute inner product of map values"
      << std::endl;
  printMap("Firjst map", mp);
  printMap("Second map", mp2);
  int innerProduct = std::inner_product(
      mp.begin(), mp.end(), mp2.begin(), 0, std::plus<>(),
      [](const auto& a, const auto& b) { return a.second * b.second; });
  std::cout << "Inner product: " << innerProduct << std::endl;

  // 11.3. Using std::transform_reduce
  std::cout << std::endl
            << "11.3. Using std::transform to compute sum of squared values in "
               "the map"
            << std::endl;
  printMap("Map", mp);
  int squaredSum =
      std::transform_reduce(mp.begin(), mp.end(), 0, std::plus<>(),
                            [](const auto& p) { return p.second * p.second; });
  std::cout << "Sum of squared: " << squaredSum << std::endl;
}

int main() {
  // 1. Initialization
  std::cout << "1. Initialization" << std::endl;
  initialization();

  // 2. Accessing and modifying
  std::cout << std::endl << "2. Accessing and modifying" << std::endl;
  accessingAndModifying();

  // 3. Inserting and removing
  std::cout << std::endl << "3. Inserting and removing" << std::endl;
  insertingAndRemoving();

  // 4. Capacity managment
  std::cout << std::endl << "4. Capacity managment" << std::endl;
  capacityManagment();

  // 5. Searching algorithms
  std::cout << std::endl << "5. Searching algorithms" << std::endl;
  searchingAlgorithms();

  // 6. Modifying Algorithms
  std::cout << std::endl << "6. Modifying algorithms" << std::endl;
  modifyingAlgorithms();

  // 7. Comparing and checking algorithms
  std::cout << std::endl << "7. Comparing and checking algorithms" << std::endl;
  comparingAndCheckingAlgorithms();

  // 8. Counting algorithms
  std::cout << std::endl << "8. Counting algorithms" << std::endl;
  countingAlgorithms();

  // 9. Set operation algorithms
  std::cout << std::endl << "9. Set operation algorithms" << std::endl;
  setOperationAlgorithms();

  // 10. Min/Max algorithms
  std::cout << std::endl << "10. Min/Max algorithms" << std::endl;
  minMaxAlgorithms();

  // 11. Numeric algorithms
  std::cout << std::endl << "11. Numeric algorithms" << std::endl;
  numericAlgorithms();

  return 0;
}
