/* This example includes different keywords using in multi-threading programming
 *  1. std::thread: Represents a thread of execution
 *    1.1. std::thread::join(): Wait for the thread to finish.
 *    1.2. std:: thread::detach: Detaches the thread, allowing it to run
 independently.
 *    1.3. std::thread::joinable() : return true if the thread isjoinable,
 meaning it is either running or has been started and can be joind or detached,
 and false otherwise.
 *    1.4. std::thread::get_id(): REturns the thread's ID
 *    1.5. std::thread::native_handle(): Provides acces to the native handle of
 the thread (platform-specific)
 *    1.6. std::thread::hardware_concurrency(): A function that returns the
 number of concurrent threads by the syste. This is generally the number of
 hardware *threads (core or hyperthreads) available on the CPU.
 *
 *  2. std::mutex and related classes: These classes are used for
 mutalexclusion, synchronization and locking.
 *    2.1. std::mutex: A basic mutex class that is used to protect shared data
 form beingaccessed by multiple threads simultaneously.
 *      2.1.1. std::mutex::lock(): Locks the mutex.
 *      2.1.2. std::mutex::unlock(): Unlocks the mutex
 *      2.1.3. std::mutex::try_lock(): Attempts to lock the mutex but does not
 block it if is is already locked.
 *    2.2. std::timed_mutex: A mutex that allows locking with a timeout.
 *    2.3. std::recursive_mutex: A meutex that allows the same thread to lock it
 multiple times.
 *    2.4 std::recursive_timed_mutex: A recursive mutex with a timeout.
 *    2,5 std::shared_mutex: A mutex that allows multiple threads to acquire
 shared(read-only) locks simultanously, while ensuring exclusive(write) access
 for thead.
 *    2.6 std::shared_timed_mutex: A mutex that allows shared and excusive
 locking with timed lock support.
 *
 *  3. mutex managment:
 *    3.1. std::lock: a function that locks multiple mutexes simultanously to
 avoid deadlocks.
 *    3.2. std::adopt_lock(): Indicates taht a mutex has already been locked by
 the caller, typically used with std::lock
 *    3.3. std::lock_guard: A simple RAII-based lock wrapper, automatically
 locking in its constructor and unlocking in its destructor.
 *    3.4. std::unique_lock:  A flexible lock, allowing manual unlocking,
 deferred locking and interaction with condition variables.
 *    3.5. std::scope_lock: A C++17 feature that locks multiple mutexes
 simultaneously, ensuring deadlock-free lockin in scope.
 *    3.6 std::shared_lock: A lock for shared ownership of a mutex,
 allowing multiple readers but only one writer.
 *    3.7 std::latch: A synchronization primitive used to block threads until a
 specific number of threads have completed execution.
 *    3.8. std::barrier: A synchronizatiion primitive that allows threads to
 wait until a specific number of threads reach a barrier before
 proceeding together.
 *
 *  4. std::condition_variable and related classes: Used  for signaling between
 threads.
 *    4.1. std::condition_variable: Used for blocking a thread until a
 particualr condition is met
 *      4.1.1. std::condition_variable::wait(): Makes the current thread wait
 until notified.
 *      4.1.2. std::condition_variable::notify_one(): Notifies one
 thread waiting on the condition variable.
 *      4.1.3. std::condition_variable::notify_all(): Notifies all threads
 waiting on the condition variable.
 *    4.2. std::condtion_variable_any: A generalization of
 std::condition_variable that works with any type of lock.
 *
 *  5. std::future and std::promise: Used for synchronizing result of
 asynchronous operations.
 *    5.1. std::future: Represents a vlaue that will be computed asynchronously.
 Allows getting the result once the thread completes.
 *      5.1.1. std::future::get(): Retrieves the rresult of the computation.
 *      5.1.2. std::future::wait(): Blocks until the results is ready.
 *      5.1.3. std::future::valid(): Checks whether the future has a valid
 shared state.
 *    5.2. std::promise: A mechanism that allows setting a value to be retrived
 by a future.
 *
 *  6. std::async: Starts an asynchronous operation.
 *    6.1. std::async: Launches a task asynchronously (either in a new thread or
 *using a thread pool). Can be used with std::future to retrieve the result once
 *available.
 *
 *  7. std::this_thread: Provides operations for the current thread.
 *    7.1. std::this_thread::sleep_for(): Makes the current thread sleep for a
 specific duration.
 *    7.2. std::this_thread::sleep_until(): Make the current thread speed until
 a specifi time.
 *    7.3. std::this_thread::yield(): Allows the current thread to yield its
 execution, suggesting that the sheduler might want to give another thread a
 chance to run.
 *
 *  8. std::atomic: Used for performing atomic operations, which are critical
 for thread synchronization.
 *    8.1. std::atomic::load(): Atomically loads the value.
 *    8.2. std::atomic::store(): Atomically stores a value.
 *    8.3. std::atomic::exchange(): Atomically exchanges values.
 *    8.4. std::atomic::compare_exchange_weak()/compare_exchange_strong():
 Atomically compares and swaps values.
 *
 * 10. std:: jthread: A thread wrapper insroduced in c++20, it automaticallly
 *joints when it goes out of scope (no need to manuallly call join()).
 *
 * 11. thread_local: Specifies that a variable should have thread storage
 *duration, meaning each thread gets its own instances of the variable
 */

#include <atomic>
#include <barrier>
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <latch>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <thread>

// Shared resources and synchronization primitives
int sharedResource1{0}, sharedResource2{0};
bool sharedResource3{false};
std::atomic<int> atomicCounter{0};
std::mutex mtx1, mtx2, mtx3;
std::timed_mutex tmtx;
std::recursive_mutex rmtx;
std::recursive_timed_mutex rtmtx;
std::shared_mutex smtx;
std::shared_timed_mutex stmtx;
std::condition_variable cv;
std::latch synchLatch(3);
std::barrier syncBarrier(2);
thread_local int threadLocalVar{0};

// 1. std::thread
void useThread() {
  auto threadFunction = [](int id) {
    std::cout << "Thread " << id << " is running." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " has finished." << std::endl;
  };

  // Static function taht provides an approximation of the number of hardware
  // threads available on the system
  unsigned int numThreads = std::thread::hardware_concurrency();
  if (numThreads == 0) {
    std::cout << "Unable to determine the number of hardware threads."
              << std::endl;
  } else {
    std::cout << "Number of available hardware threads: " << numThreads
              << std::endl;
  }

  // Create threads
  std::thread t1(threadFunction, 1);
  std::thread t2(threadFunction, 2);

  // Observers
  if (t1.joinable()) {
    std::cout << "Thread 1 is joinable." << std::endl;
    std::cout << "Thread 1 ID: " << t1.get_id() << std::endl;
    t1.join();  // wait for thread 1 to finish
  }

  if (t2.joinable()) {
    std::cout << "Thread 2 is joinable." << std::endl;
    std::cout << "Thread 2 ID: " << t2.get_id() << std::endl;
    t2.detach();  // Detach thread 2 (it will run independently)
  }

  // Using swap and move
  std::thread t3;  // Default constructor
  std::thread t4(threadFunction, 4);
  std::cout << "Swapping thread 3 and thread 4 ..." << std::endl;
  t3.swap(t4);  // Swap t3 and t4
  if (t3.joinable()) t3.join();

  // Move thread
  std::thread t5 = std::move(t3);
  if (!t3.joinable() && t5.joinable()) {
    std::cout << "thread 5 has successfully taken ownership from thread 3"
              << std::endl;
  }
  if (t5.joinable()) t5.join();

  // Native handle provides access to the underlying native handle used by the
  // operating system
  std::thread t6(threadFunction, 6);
  std::cout << "Native handle of thread 6: " << t6.native_handle() << std::endl;
  if (t6.joinable()) t6.join();

  std::cout << "All thread operations demonstrated." << std::endl;
}

// 2. std::mutex
void useMutex() {
  std::mutex mtx;
  int sharedResource{0};
  int numThreads{3};
  std::vector<std::thread> threads;

  auto threadFunction = [&](int id) -> void {
    mtx.lock();
    std::cout << "Thread " << id << " is modifying sharedResource" << std::endl;
    sharedResource += 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "sharedResource value: " << sharedResource << std::endl;
    mtx.unlock();
  };

  std::cout << "Initial sharedResource value: " << sharedResource << std::endl;

  for (int i = 0; i < numThreads; ++i) {
    threads.emplace_back(threadFunction, i + 1);
  }

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "Final sharedResource value: " << sharedResource << std::endl;
}

// 3. std::timed_mutex
void useTimedMutex() {
  std::timed_mutex tmtx;
  int sharedResource{0};
  int numThreads{3};
  std::vector<std::thread> threads;

  auto threadFunction = [&](int id) -> void {
    if (tmtx.try_lock_for(std::chrono::milliseconds(100))) {
      // Try to lock for 100 ms
      std::cout << "Thread " << id << " acquired the lock" << std::endl;
      sharedResource += 1;
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      std::cout << "Thread " << id << " released the lock" << std::endl;
      tmtx.unlock();
    } else {
      std::cout << "Thread " << id
                << " could not acquire the lock within the timeout"
                << std::endl;
    }
  };

  std::cout << "Initial sharedResource value: " << sharedResource << std::endl;

  for (int i = 0; i < numThreads; ++i) {
    threads.emplace_back(threadFunction, i + 1);
  }

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "Final sharedResource value:  " << sharedResource << std::endl;
}

// 4. std::recursive_mutex
void useRecursiveMutex() {
  std::recursive_mutex rmtx;
  int sharedResource{0};
  std::vector<std::thread> threads;

  // Recursive lambda function for recursive resource modification
  std::function<void(int, int)> threadFunction = [&](int id,
                                                     int depth) -> void {
    if (depth <= 0) return;
    rmtx.lock();
    std::cout << "Thread " << id << " acquired the lock at depth " << depth
              << std::endl;
    sharedResource += 1;
    std::cout << "Thread " << id
              << " modified sharedResource to: " << sharedResource << std::endl;

    // Recursive call using the lambda itself
    threadFunction(id, depth - 1);
    std::cout << "Thread " << id << " released the lock at depth " << depth
              << std::endl;
    rmtx.unlock();
  };

  threads.emplace_back(threadFunction, 1, 3);
  threads.emplace_back(threadFunction, 2, 2);

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "Final sharedResource value: " << sharedResource << std::endl;
}

// 5. std::recursive_timed_mutex
void useRecursiveTimedMutex() {
  int sharedResource{0};
  std::vector<std::thread> threads;

  std::function<void(int, int)> threadFunction = [&](int id,
                                                     int depth) -> void {
    if (depth <= 0) return;
    if (rtmtx.try_lock_for(std::chrono::milliseconds(100))) {
      std::cout << "Thread " << id << " acquired the lock at depth " << depth
                << std::endl;
      sharedResource += 1;
      std::cout << "Thread " << id
                << " modified sharedResource to: " << sharedResource
                << std::endl;
      threadFunction(id, depth - 1);
      std::cout << "Thread " << id << " released the lock at depth " << depth
                << std::endl;
      rtmtx.unlock();
    } else {
      std::cout << "Thread " << id << " failed to acquire the lock at depth "
                << depth << std::endl;
    }
  };

  threads.emplace_back(threadFunction, 1, 3);
  threads.emplace_back(threadFunction, 2, 2);

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "Final sharedResource value: " << sharedResource << std::endl;
}

// 6. std::lock() and std::adopt_lock
void useStdLock() {
  std::mutex mtx1, mtx2;
  int sharedResource1{0};
  int sharedResource2{0};

  auto threadFunction1 = [&](int id) {
    mtx1.lock();
    std::cout << "Thread " << id << " acquired the lock for mtx1" << std::endl;
    sharedResource1 += 1;
    std::cout << "Thread " << id
              << " modified sharedResource1 to: " << sharedResource1
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " released the lock for mtx1" << std::endl;
    mtx1.unlock();
  };

  auto threadFunction2 = [&](int id) {
    mtx2.lock();
    std::cout << "Thread " << id << " acquired the lock for mtx2 " << std::endl;
    sharedResource2 += 1;
    std::cout << "Thread " << id
              << " modified sharedResource2 to: " << sharedResource2
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread " << id << " released the lock for mtx2" << std::endl;
    mtx2.unlock();
  };

  auto threadFunction3 = [&](int id) {
    std::lock(mtx1, mtx2);
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
    std::cout << "Thread " << id << " acquired the lock for mtx1 and mtx2"
              << std::endl;
    sharedResource1 += 1;
    sharedResource2 += 1;
    std::cout << "Thread " << id
              << " modified the sharedResource1 to: " << sharedResource1
              << " and sharedResouce2 to: " << sharedResource2 << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " released the lock for mtx1 and mtx2"
              << std::endl;
  };

  std::thread t2(threadFunction2, 2);
  std::thread t3(threadFunction3, 3);
  std::thread t1(threadFunction1, 1);

  if (t1.joinable()) t1.join();
  if (t2.joinable()) t2.join();
  if (t3.joinable()) t3.join();

  std::cout << "Final sharedResource1 value : " << sharedResource1
            << " and final sharedResource2 value: " << sharedResource2
            << std::endl;
}

// 7. std:lock_guard
void useLockGuard() {
  std::mutex mtx;
  int sharedResource{0};
  int numThread{2};
  std::vector<std::thread> threads;

  auto threadFunction = [&](int id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << id << " acquired the lock" << std::endl;
    sharedResource += 1;
    std::cout << "Thread " << id
              << " modified the sharedResource to: " << sharedResource
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " released the lock" << std::endl;
  };

  for (int i = 0; i < numThread; ++i) {
    threads.emplace_back(threadFunction, i + 1);
  }

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "Final sharedResource value: " << sharedResource << std::endl;
}

// 8. std::unique_lock
void useUniqueLock() {
  std::mutex mtx1, mtx2;
  std::condition_variable cv;
  int sharedResource1{0};
  bool sharedResource2{false};

  auto threadFunction1 = [&](int id) {
    // 1. Manual locking and unlocking
    std::unique_lock<std::mutex> lock1(mtx1);
    std::cout << "Manual locking/unlocking: Thread " << id
              << " acquired lock for mtx1" << std::endl;
    sharedResource1 += 1;
    std::cout << "Manual locking/unlocking: Thread " << id
              << " modified the sharedResource1 to: " << sharedResource1
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Manual locking/unlocking: Thread " << id
              << " released the lock for mtx1" << std::endl;
    lock1.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    lock1.lock();
    std::cout << "Manual locking/unlocking: Thread " << id
              << " acquired lock again for mtx1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Manual locking/unlocking: Thread " << id
              << " released the lock again for mtx1" << std::endl;
    lock1.unlock();

    // 2. Deferred locking
    std::unique_lock<std::mutex> lock2(mtx1, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    lock2.lock();
    std::cout << "Deferred locking: Thread " << id << " acquired lock for mtx1"
              << std::endl;
    sharedResource1 += 1;
    std::cout << "Deffered locking: Thread " << id
              << " modified the sharedResource1 to: " << sharedResource1
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Deffered locking: Thread " << id
              << " released the lock for mtx1" << std::endl;
    lock2.unlock();

    // 3. Using std::unique_lock with condition variables and locking multiple
    // mutexes
    {
      std::unique_lock<std::mutex> lock3(mtx1, std::defer_lock);
      std::unique_lock<std::mutex> lock4(mtx2, std::defer_lock);
      std::lock(lock3, lock4);
      std::cout << "Condition variable: Thread " << id
                << " acquired lock for mtx1 and mtx2" << std::endl;
      std::cout << "Condition variable: Thread " << id << " waiting ..."
                << std::endl;
      while (!sharedResource2) cv.wait(lock3);
      std::cout << "Condition variable: Thread " << id << " is working"
                << std::endl;
      sharedResource1 += 1;
      std::cout << "Condition variable: Thread " << id
                << " modified the sharedResouce1 to: " << sharedResource1
                << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout << "Condition variable: Thread " << id
                << "released the lock for mtx1 and mtx3" << std::endl;
    }

    // 4. Automatic unlocking and RAII
    try {
      std::unique_lock<std::mutex> lock4(mtx1);
      std::cout << "Automatic unlocking: Thread " << id
                << "acquired lock for mtx1" << std::endl;
      throw std::runtime_error("Something went wrong!");
    } catch (const std::exception& e) {
      std::cout << "Automatic unlocking: Caught exception: " << e.what()
                << std::endl;
    }
    // Mutex is automatically unlocked here when lock goes out of scope
    std::cout << "Automatic unlocking: Thread" << id
              << " released lock for mtx1" << std::endl;
  };

  auto threadFunction2 = [&](int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::lock_guard<std::mutex> lock(mtx2);
    std::cout << "Condition variable: Thread " << id
              << " acquired lock for mtx3" << std::endl;
    std::cout << "Condition variable: Thread " << id
              << " Notifying other threads" << std::endl;
    sharedResource2 = true;
    cv.notify_all();
  };

  std::thread t1(threadFunction1, 1);
  std::thread t2(threadFunction1, 2);
  std::thread t3(threadFunction2, 3);

  if (t1.joinable()) t1.join();
  if (t2.joinable()) t2.join();
  if (t3.joinable()) t3.join();
}

// 9. std::scoped_lock
void useScopeLock() {
  std::mutex mtx1, mtx2;
  int sharedResource1{0};
  int sharedResource2{0};
  int numThread{4};
  std::vector<std::thread> threads;

  auto threadFunction = [&](int id) {
    std::scoped_lock lock(mtx1, mtx2);
    std::cout << "Thread " << id << " acquierd lock for mtx1 and mtx2"
              << std::endl;
    sharedResource1 += 1;
    sharedResource2 += 1;
    std::cout << "Thread " << id
              << " modified sharedResource1 to:" << sharedResource1
              << " and sharedResurce2 to: " << sharedResource2 << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " released lock for mtx1 and mxt2"
              << std::endl;
  };

  for (int i = 0; i < numThread; ++i) {
    threads.emplace_back(threadFunction, i);
  }

  for (auto& thread : threads) {
    if (thread.joinable()) thread.join();
  }
}

// 10. std::shared_mutex, std::shared_timed_mutex, std::shared_lock
void useSharedLock() {
  std::shared_mutex smtx;
  std::shared_timed_mutex stmtx;
  int sharedResource{0};
  const int numReaders{5};
  const int numWriters{2};
  const int numTimedReaders{3};
  const int numTimedWriters{2};
  std::vector<std::thread> threads;

  auto readerTaskUsingSharedMutex = [&](int id) {
    std::shared_lock<std::shared_mutex> lock(smtx);
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + id));
    std::cout << "Thread " << id << " acuired lock for smtx" << std::endl;
    std::cout << "Thread " << id << " reads sharedResource: " << sharedResource
              << std::endl;
    std::cout << "Thread " << id << " released lock for smtx" << std::endl;
  };

  auto writerTaskUsingSharedMutex = [&](int id) {
    std::lock_guard<std::shared_mutex> lock(smtx);
    std::cout << "Thread " << id << " acquired lock for smtx" << std::endl;
    sharedResource += 1;
    std::cout << "Thread " << id
              << " modified sharedResource to: " << sharedResource << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Thread " << id << " released lock for smtx" << std::endl;
  };

  auto readerTaskUsingSharedTimedMutex = [&](int id) {
    if (std::shared_lock<std::shared_timed_mutex> lock{
            stmtx, std::chrono::milliseconds(100)}) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100 + id));
      std::cout << "Thread " << id << " acquired lock for stmtx" << std::endl;
      std::cout << "Thread " << id
                << " reads sharedResource: " << sharedResource << std::endl;
    } else {
      std::cout << "Thread " << id << " failed to acquire lock for stmtx"
                << std::endl;
    }
  };

  auto writerTaskUsingSharedTimedMutex = [&](int id) {
    if (std::unique_lock<std::shared_timed_mutex> lock{
            stmtx, std::chrono::milliseconds(100)}) {
      std::cout << "Thread " << id << " acquired lock for stmtx" << std::endl;
      sharedResource += 1;
      std::cout << "Thread " << id
                << " modified sharedResource to: " << sharedResource
                << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
      std::cout << "Thread " << id << " faield to acquired lock for stmtx"
                << std::endl;
    }
  };

  for (int i = 0; i < numTimedWriters; ++i) {
    threads.emplace_back(writerTaskUsingSharedTimedMutex, i + 1);
  }

  for (int i = 0; i < numWriters; ++i) {
    threads.emplace_back(writerTaskUsingSharedMutex, numTimedWriters + i);
  }

  for (int i = 0; i < numReaders; ++i) {
    threads.emplace_back(readerTaskUsingSharedMutex,
                         numTimedWriters + numWriters + i);
  }

  for (int i = 0; i < numTimedReaders; ++i) {
    threads.emplace_back(readerTaskUsingSharedTimedMutex,
                         numTimedWriters + numWriters + numReaders + i);
  }

  for (auto& thread : threads) {
    if (thread.joinable()) thread.join();
  }

  std::cout << "Final shardResource value: " << sharedResource << std::endl;
}

// 11. std::latch
void useLatch() {
  const int threadNum{5};
  std::latch syncPoint(5);
  std::vector<std::thread> threads;

  auto threadFunction = [](std::latch& syncPoint, int id) {
    std::cout << "Thread " << id << " initializing." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread " << id << " finished initilization" << std::endl;

    syncPoint.count_down();
  };

  for (int i = 0; i < threadNum; ++i) {
    threads.emplace_back(threadFunction, std::ref(syncPoint), i + 1);
  }

  syncPoint.wait();
  std::cout << "All threads finished initialization. Main thead proceeds."
            << std::endl;

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }
}

// 12. std::barrier
void useBarrier() {
  const size_t numThread = 4;
  const size_t numData = 8;
  std::vector<double> data(numData, 0.0);
  double globalMagnitude{0.0};

  std::cout << "data: [";
  for (size_t i = 0; i < numData; ++i) {
    data[i] = i;
    if (i < numData - 1) {
      std::cout << data[i] << ", ";
    } else {
      std::cout << data[i] << "]" << std::endl;
    }
  }

  std::barrier syncPoint(numThread, []() {
    std::cout
        << "All threads reached the barrier. Proceeding to the next phase."
        << std::endl;
  });

  auto threadFunction = [&](size_t threadId) {
    size_t chunkSize = numData / numThread;
    size_t startIdx = (threadId - 1) * chunkSize;
    size_t endIdx = (threadId == numThread) ? numData : startIdx + chunkSize;

    // Phase 1: Calculate partial sum of squares
    double localMagnitude = 0.0;
    for (size_t i = startIdx; i < endIdx; ++i) {
      localMagnitude += data[i] * data[i];
    }
    {
      std::lock_guard<std::mutex> lock(mtx1);
      globalMagnitude += localMagnitude;
    }
    // Synchronize threads after pahse 1
    syncPoint.arrive_and_wait();

    // Phase2: Normalize the data
    if (globalMagnitude != 0) {
      for (size_t i = startIdx; i < endIdx; ++i) {
        data[i] /= globalMagnitude;
      }
    }
  };

  std::vector<std::thread> threads;
  for (size_t i = 1; i <= numThread; ++i) {
    threads.emplace_back(threadFunction, i);
  }

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "data/||data||^2: [";
  for (size_t i = 0; i < numData; ++i) {
    if (i < numData - 1) {
      std::cout << data[i] << " ";
    } else {
      std::cout << data[i] << "]" << std::endl;
    }
  }
}

// 13. std::condition_variable
void useConditionVar() {
  std::mutex mtx;
  std::condition_variable cv;
  std::queue<std::string> taskQueue;
  bool done{false};
  const int numWorkers{3};
  std::vector<std::thread> workers;

  auto producer = [&](int id) {
    std::vector<std::string> requests = {
        "Move joint 1 to 45 degrees",
        "Move joint 2 to 30 degrees",
        "Calculate IK for target (x = 0.5, y = 0.2, z = 0.3)",
        "Read LIDAR data",
        "Process camera image",
    };

    for (auto& request : requests) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      {
        std::lock_guard<std::mutex> lock(mtx);
        taskQueue.push(request);
        std::cout << "Thread " << id << " recived request to: " << request
                  << std::endl;
      }
      cv.notify_one();
    }

    {
      std::lock_guard<std::mutex> lock(mtx);
      done = true;
    }
    cv.notify_all();
  };

  auto consumer = [&](int id) {
    while (true) {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [&]() { return !taskQueue.empty() || done; });
      if (!taskQueue.empty()) {
        std::string task{taskQueue.front()};
        taskQueue.pop();
        std::cout << "worker " << id << " processing: " << task << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      } else if (done) {
        break;
      }
    }
  };

  for (int i = 0; i < numWorkers; ++i) {
    workers.push_back(std::thread(consumer, i + 1));
  }

  std::thread producerThread(producer, numWorkers + 2);

  for (auto& worker : workers) {
    if (worker.joinable()) worker.join();
  }
  if (producerThread.joinable()) producerThread.join();
}

// 14. std::promise and std::future
void usePromiseAndFuture() {
  auto producer = [](std::promise<double> resultPromise, double x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    try {
      if (x < 0) throw std::invalid_argument("Negative input for computation!");
      resultPromise.set_value(sqrt(x));
    } catch (...) {
      resultPromise.set_exception(std::current_exception());
    }
  };

  auto consumer = [](std::future<double> resultFuture) {
    std::cout << "Consumer waiting for computation result ..." << std::endl;
    try {
      double result = resultFuture.get();
      std::cout << "Computation result: " << result << std::endl;

    } catch (const std::exception& ex) {
      std::cerr << "Error during computation: " << ex.what() << std::endl;
    }
  };

  std::promise<double> resultPromise;
  std::future<double> resultFuture = resultPromise.get_future();

  std::thread consumerThread(consumer, std::move(resultFuture));
  std::thread producerThread(producer, std::move(resultPromise), 10);

  if (producerThread.joinable()) producerThread.join();
  if (consumerThread.joinable()) consumerThread.join();
}

// 15. std::async
void useStdAsync() {
  // 1. Basic asynch task
  auto computeSum = [](int a, int b) -> int {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return a + b;
  };

  std::future<int> sumResult = std::async(std::launch::async, computeSum, 5, 7);

  std::cout << "Task running asynchronously..." << std::endl;
  std::cout << "Result: " << sumResult.get() << std::endl;

  // 2. std::launch::deferred
  auto computeProduct = [](int a, int b) -> int {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return a * b;
  };

  std::future<int> productResult =
      std::async(std::launch::deferred, computeProduct, 3, 4);

  std::cout << "Task will run when result is needed ..." << std::endl;
  std::cout << "Result: " << productResult.get() << std::endl;

  // 3. multiple async tasks
  auto computeSquare = [](double x) -> double {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return x * x;
  };

  auto computeSqrt = [](double x) -> double {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return std::sqrt(x);
  };

  std::future squareResult = std::async(std::launch::async, computeSquare, 5.0);
  std::future sqrtResult = std::async(std::launch::async, computeSqrt, 25.0);

  std::cout << "Computing results in parallel..." << std::endl;
  std::cout << "Square of 5: " << squareResult.get() << std::endl;
  std::cout << "Square root of 25: " << sqrtResult.get() << std::endl;
}

// 16. std::atomic
void useAtomic() {
  std::atomic<int> sharedValue{0};

  auto threadBasic = [&](int id) {
    sharedValue = id * 10;
    std::cout << "Thread " << id
              << " directly assigned value: " << sharedValue.load()
              << std::endl;
  };

  auto threadStoreAndLoad = [&](int id) {
    sharedValue.store(id);
    int value = sharedValue.load();
    std::cout << "Thread " << id << " stored and loaded value: " << value
              << std::endl;
  };

  auto threadExchange = [&](int id) {
    int oldValue = sharedValue.exchange(id);
    int newValue = sharedValue.load();
    std::cout << "Thread " << id << " exchanged value: " << oldValue << " -> "
              << newValue << std::endl;
  };

  auto threadCompareExchangeStrong = [&](int id) {
    int expected{id - 1};
    if (sharedValue.compare_exchange_strong(expected, id)) {
      std::cout << "Thread " << id << " successfully updated value to: " << id
                << std::endl;
    } else {
      std::cout << "Thread " << id
                << "failed compare_exchange_strong. Expected: " << id - 1
                << " Actual: " << expected << std::endl;
    }
  };

  auto threadCompareExchangeWeak = [&](int id) {
    int expected{id - 1};
    while (!sharedValue.compare_exchange_weak(expected, id))
      std::this_thread::yield();
    std::cout << "Thread " << id
              << " successfully updated value using comapre_exchange_weak to: "
              << id << std::endl;
  };

  auto threadFetchAndSub = [&](int id) {
    int addedValue{sharedValue.fetch_add(10)};
    std::cout << "Thread " << id << " added 10 to: " << addedValue
              << ", new value: " << sharedValue.load() << std::endl;

    int subtractedValue{sharedValue.fetch_sub(5)};
    std::cout << " Thread " << id << " subtracted 5 from : " << subtractedValue
              << ", New value: " << sharedValue.load() << std::endl;
  };

  std::vector<std::thread> threads;
  threads.emplace_back(threadBasic, 1);
  threads.emplace_back(threadStoreAndLoad, 2);
  threads.emplace_back(threadExchange, 3);
  threads.emplace_back(threadCompareExchangeStrong, 4);
  threads.emplace_back(threadCompareExchangeWeak, 5);
  threads.emplace_back(threadFetchAndSub, 6);

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }
}
// 17. std::thread_local
void useThreadLocal() {
  thread_local int counter{0};
  auto increamentCounter = [](int id) {
    for (int i = 0; i < 5; ++i) {
      ++counter;
      std::cout << "Thread " << id << " Counter: " << counter << std::endl;
    }
  };

  int numThread{3};
  std::vector<std::thread> threads;

  for (int i = 0; i < numThread; ++i) {
    threads.emplace_back(increamentCounter, i + 1);
  }

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }
}

/*
// std::jthread
void useJthread() {
auto threadFunction = [](std::stop_token stop_token,int id){
  int count{0};
  while (!stop_token.stop_requested() && count < 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread " << id << "running the task..." << count++ <<
std::endl;
  }
    std::cout << "Thread " << id << " stopped the task after " <<count <<
"iterations." << std::endl;
};

int numThread = 3;
std::vector<jthread> threads;

for(int i = 0; i < numThread; ++i) {
  threads.emplace_back(threadFunction, i +1);
}

threads[1].request_stop();
std::cout << "Main thread finished,  othre threads continue." << std::endl;
}
*/

int main() {
  // Use std::thread
  std::cout << "*** Example 1: std::thread ***" << std::endl;
  useThread();

  // Use std::mutex
  std::cout << std::endl << "*** Example 2: std::mutex ***" << std::endl;
  useMutex();

  // Use std::timed_mutex
  std::cout << std::endl << "*** Example 3: std::timed_mutex ***" << std::endl;
  useTimedMutex();

  // Use std::recursive_mutex
  std::cout << std::endl
            << "*** Example 4: std::recursive_mutex ***" << std::endl;
  useRecursiveMutex();

  // Use std::recursive_timed_mutex
  std::cout << std::endl
            << "*** Example 5: std::recursive_timed_mutex ***" << std::endl;
  useRecursiveTimedMutex();

  // Use std::lock and std::adopt_lock
  std::cout << std::endl
            << "*** Example 6: std::lock and std::adopt_lock ***" << std::endl;
  useStdLock();

  // Use std::lock_guard
  std::cout << std::endl << "*** Example 7: std::lock_guard ***" << std::endl;
  useLockGuard();

  // Use std::unique_lock
  std::cout << std::endl << "*** Example 8: std::unique_lock ***" << std::endl;
  useUniqueLock();

  // Use std::scope_lock
  std::cout << std::endl << "*** Example 9: std::scope_lock ***" << std::endl;
  useScopeLock();

  // Use std::shared_lock
  std::cout << std::endl << "*** Example 10: std::shared_lock ***" << std::endl;
  useSharedLock();

  // Use std::latch
  std::cout << std::endl << "*** Example 11: std::latch ***" << std::endl;
  useLatch();

  // Use std::barrier
  std::cout << std::endl << "*** Example 12: std::barrier ***" << std::endl;
  useBarrier();

  // Use std::condition_variable
  std::cout << std::endl
            << "*** Example 13: std::condition_variable ***" << std::endl;
  useConditionVar();

  // Use std::future and std::promise
  std::cout << std::endl
            << "*** Example 14: std::future and std::promise ***" << std::endl;
  usePromiseAndFuture();

  // Use std::async
  std::cout << std::endl << "*** Example 15: std::async ***" << std::endl;
  useStdAsync();

  // Use std::atomic
  std::cout << std::endl << "*** Example 16: std::atomic ***" << std::endl;
  useAtomic();

  // Use std::thread_local
  std::cout << std::endl
            << "*** Example 17: std::thread_local ***" << std::endl;
  useThreadLocal();

  return 0;
}
