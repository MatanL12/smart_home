#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <semaphore.h>

#include "threads_exception.hpp"

namespace threads {

class SemaphoreException : public ThreadException {
public:
    using ThreadException::ThreadException;
    ~SemaphoreException() = default;
};

class Semaphore {
public:
    Semaphore(size_t a_counter);
    Semaphore(const Semaphore& a_other) = delete;
    Semaphore& operator=(Semaphore & a_ptr) = delete;
    ~Semaphore();

    void Post(); //increment
    void Wait() noexcept; //decrement

private:
    sem_t m_sem;
};

}//threads

#endif /* SEMAPHORE_HPP */