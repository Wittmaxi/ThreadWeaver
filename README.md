# ThreadWeaver
A threadscheduler that was written with efficiency in mind. 
This tool is meant to allow you to feed the thread-scheduler with any amount of functions which will be then into an already existing thread - thus knowing the amount of threads in advance and 
avoiding the overhead caused by the creation of new threads. 

*Threadweaver is currently in developement and not usable as-is. It it neither threadsafe nor particularly efficient due to it using spinlocks.*

# Installation
Simply running 
```console
make installl
```
Should be enough. Alternatively, you can copy the Headerfile threadweaver.hpp into your include directory or even into your project directory.

# Usage
The threadscheduler is completely wrapped in the namespace `TRW`.
The Relevant class is called `TRW::ThreadScheduler`.

```C++ 
     ThreadScheduler(unsigned int amountOfThreads = 1);
```
Constructs ThreadScheduler, by giving it an amount of threads it should support at once. 

```C++ 
    void stopThreads()
```
Sends all threads a signal to stop execution. Waits until all threads are stopped. 
```C++     
    void waitUntilAllDone()
```
Waits until all threads are done executing every one of their tasks. 

```C++ 
    template <class callable, class... args>
    void runFunction(callable function, args... arguments) noexcept
```
Runs a function, in any of the threads. May be a lambda or even a funciton pointer. Put the function arguments next to the function like this:
```C++
ts.runFunction(functionwiththreeintarguments, 2, 3, 5);
```


```C++ 
    size_t size()
```
Returns the amount of threads available. 
```C++ 
    void resize(size_t newSize)
```
Sets a new amount of threads. Will not stop other threads from working in the meantime. 

```C++ 
    ~ThreadScheduler()
```
Calls stopThreads.
