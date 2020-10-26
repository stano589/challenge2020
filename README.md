# challenge2020
coding challenge

# Contents:
# Task 1: Own implementation of std::lock_guard
  Implemented own version of std::lock_guard, which is a RAII principle of locking and unlocking a mutex.
  Explicit constructor takes a lockable object and locks it, upon destruction of the lock guard the lock is unlocked.
  No copying is enabled.
  
# Task 2: Simple threads - producer consumer example
  Simple producer - consumer example over a queue of integers.
  Producers produce a number and put it into a queue until the queue is full(100 elements).
  Consumers consume an element from the queue if the queue is not empty.
  note: numbers across the producer threads are not random because the function is not reentrant.
  
# Task 3: 3 Threads sync using conditional variables
  Refering to the pseudocode - thread 1 does some work and wakes up thread 2 then sleeps
                               thread 2 does some work and wakes up thread 3 then sleeps
                               thread 3 does some work and wakes up thread 1 then sleeps.
  Using 3 conditional variables.

# Task 4: Protect a resource using own lock_guard implementation
  Simple thread example using 10 threads and counting to a certain amount.
  Upon disabling the lock we can see that due to race conditions we can achieve a sum less then expected.
  
# Task 5: JSON Dispatcher challenge
  Refer to the code.
