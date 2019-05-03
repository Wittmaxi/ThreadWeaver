/*
Copyright 2019 Maximilian Wittmer
Contact: wittmaxi@linux.pizza or wittmaxi@clinl.org

Licensed under the MIT License. 
https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE
*/

#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>

namespace TRW
{
struct FunctionBase
{
    virtual void callFunction() = 0;
    virtual ~FunctionBase(){};
};

template <class callable, class... args>
struct Function : public FunctionBase
{
  public:
    using bind_type = decltype(std::bind(std::declval<callable>(), std::declval<args>()...));

    Function(callable f, args... arguments)
        : bind_(f, arguments...)
    {
    }

    ~Function()
    {
    }

    void callFunction()
    {
        bind_();
    }

  private:
    bind_type bind_;
};

void execLoop(bool *exit, std::queue<std::unique_ptr<FunctionBase>> *functions)
{
    while (!*exit)
        if (!functions->empty())
        {
            functions->front()->callFunction();
            functions->pop();
        }
}

struct Thread
{
    Thread() : loopThread(std::thread(execLoop, &exit, &fun))
    {
    }
    Thread(const Thread &other) : loopThread(std::thread(execLoop, &exit, &fun))
    {
    }
    ~Thread()
    {
        exit = true;
        loopThread.join();
        while (!fun.empty())
            fun.pop();
    }
    void stop()
    {
        exit = true;
    }
    void waitUntilDone()
    {
        while (!fun.empty())
            ;
    }
    template <class callable, class... args>
    void queueFunction(callable f, args... arguments)
    {
        std::lock_guard<std::mutex> guard(queueMutex);
        fun.push(std::make_unique<Function<callable, args...>>(f, arguments...));
    }
    bool exit = false;
    std::queue<std::unique_ptr<FunctionBase>> fun;
    std::thread loopThread;
    std::mutex queueMutex;
};

struct ThreadScheduler
{
    ThreadScheduler(unsigned int amountOfThreads = 1) : threads(amountOfThreads, Thread{})
    {
    }
    void waitUntilAllClosed()
    {
        for (auto &i : threads)
            i.stop();
    }
    void waitUntilAllDone()
    {
        for (auto &i : threads)
            i.waitUntilDone();
    }
    template <class callable, class... args>
    void runFunction(callable function, args... arguments) noexcept
    {
        threads[dispatcher % size()].queueFunction(function, arguments...);
        dispatcher++;
    }
    size_t size()
    {
        return threads.size();
    }
    void resize(size_t newSize)
    {
        if (newSize > threads.size())
            addThreads(newSize - threads.size());
        else
            addThreads(threads.size() - newSize);
    }
    ~ThreadScheduler()
    {
        waitUntilAllClosed();
    }

  private:
    void addThreads (const size_t amount) {
        for (int i = 0; i < amount; i++) 
            threads.push_back (Thread{});
    }

    void removeThreads (const size_t amount) {
        for (int i = 0; i < amount; i++) {
            threads.end()->waitUntilDone();
            threads.pop_back();
        }
    }

    std::vector<Thread> threads;
    unsigned int dispatcher;
};
} // namespace THW