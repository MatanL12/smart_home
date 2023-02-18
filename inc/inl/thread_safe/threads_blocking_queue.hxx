#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include "threads_blocking_queue.hpp"

namespace threads {

inline static size_t checkCapNotZero(size_t a_capacity)
{
	if(a_capacity == 0) {
		throw BlockingQueueException("blocking queue ctor", "invalid capacity", 0);
	}
	return a_capacity;
}

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_capacity(checkCapNotZero(a_capacity))
, m_queue()
, m_mtx()
, m_emptySlots(a_capacity)
, m_fullSlots(0)
#ifdef DEBUG_TIMESTAMP
, m_insertCounter(0)
, m_popCounter(0)
#endif
{

}

template <typename T>
void BlockingQueue<T>::Enqueue(T const& a_element)
{
	m_emptySlots.Wait();
	{
		try {
			std::lock_guard<std::mutex> guard{m_mtx};
			#ifdef DEBUG_TIMESTAMP
				a_element.m_insertOrder = m_insertCounter;
				++m_insertCounter;
			#endif
			m_queue.push(a_element);
		}
		catch (...){
			//Note: cant throw as we will never overflow
			m_emptySlots.Post();

			throw;
		}
	}
	m_fullSlots.Post();
}


template <typename T>
void BlockingQueue<T>::Enqueue(T && a_element)
{
	m_emptySlots.Wait();
	{
		try {
			std::lock_guard<std::mutex> guard{m_mtx};
			#ifdef DEBUG_TIMESTAMP
				a_element.m_insertOrder = m_insertCounter;
				++m_insertCounter;
			#endif
			m_queue.push(std::move(a_element));
		}
		catch (...){
			//Note: cant throw as we will never overflow
			m_emptySlots.Post();

			throw;
		}
	}
	m_fullSlots.Post();
}


template <typename T>
void BlockingQueue<T>::Dequeue(T& a_elemRemoved)
{
	m_fullSlots.Wait();
	{
		try {
			std::lock_guard<std::mutex> guard{m_mtx};
			a_elemRemoved =std::move(m_queue.front());
			#ifdef DEBUG_TIMESTAMP
				a_elemRemoved.m_popOrder = m_popCounter;
				++m_popCounter;
			#endif
			m_queue.pop();
			m_emptySlots.Post();
		}
		catch (...) {
			m_fullSlots.Post();
			throw;
		}
	}
}

template <typename T>
size_t BlockingQueue<T>::Size() const
{
	std::lock_guard<std::mutex> guard{m_mtx};
	return m_queue.size();
}

template <typename T>
bool BlockingQueue<T>::IsEmpty() const
{
	std::lock_guard<std::mutex> guard{m_mtx};
	return (m_queue.size() == 0);
}


}//threads


#endif /* BLOCKING_QUEUE_HXX */