#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <queue>
#include <mutex>
#include <thread>
#include <stdint.h>
#include <bits/stdc++.h>

#include "threads_semaphore.hpp"

namespace threads {

class BlockingQueueException : public ThreadException {
public:
    using ThreadException::ThreadException;
    ~BlockingQueueException() = default;
};

template <typename T>
class BlockingQueue {
public:
	BlockingQueue(size_t a_capacity = INT_MAX);
	BlockingQueue(BlockingQueue const& a_other) = delete;
	BlockingQueue& operator=(BlockingQueue const&)  = delete;
	~BlockingQueue() = default;

	void Enqueue(T const& a_element);
	void Enqueue(T && a_element);
	void Dequeue(T& a_elemRemoved);
	void Dequeue(T&& a_elemRemoved);


	size_t Size() const;
	bool IsEmpty() const;

private:
	size_t m_capacity;
	std::queue<T> m_queue;
	mutable std::mutex m_mtx;
	Semaphore m_emptySlots;
	Semaphore m_fullSlots;
	#ifdef DEBUG_TIMESTAMP
		size_t m_insertCounter;
		size_t m_popCounter;
	#endif
};

}//threads

#include "threads_blocking_queue.hxx"

#endif /* BLOCKING_QUEUE_HPP */