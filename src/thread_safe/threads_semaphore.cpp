#include <cassert> //assert()
#include <cerrno> //errno

#include "threads_semaphore.hpp"

namespace threads {

static const char* Ooops = "Ooopss - invalid semaphore, see ctor";
Semaphore::Semaphore(size_t a_counter)
{
    if(::sem_init(&m_sem, 0, a_counter) == -1){
        switch (errno) {
            case EINVAL:
                throw SemaphoreException("semaphore ctor", "semaphore exceed max value", errno);
            case ENOSYS:
                assert(false); // cant happen as we do not use pshared semaphore
                // throw SemaphoreException("semaphore ctor", "the system does not support process shared semaphores", errno);
        }
    }
}

Semaphore::~Semaphore()
{
    if(::sem_destroy(&m_sem) == -1) {
        switch (errno) {
            case EINVAL:
                assert(!Ooops);
        }
    }
}

void Semaphore::Post()
{
    if(::sem_post(&m_sem) == -1) {
        switch (errno) {
            case EINVAL:
                assert(!Ooops);
            case EOVERFLOW:
                throw SemaphoreException("semaphore post", "The maximum allowable value for a semaphore would be exceeded", errno);
        }
    }
}

void Semaphore::Wait() noexcept
{
    if(::sem_wait(&m_sem) == -1) {
        switch (errno) {
            case EINVAL :
                assert(!Ooops);
            case EINTR:
                //TODO: retry the sem-wait
                // no throw
                //throw SemaphoreException("semaphore wait", "The call was interrupted by a signal handler", errno);
                break;
        }
    }
}



}//threads