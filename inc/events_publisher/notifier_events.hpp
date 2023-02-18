#ifndef NOTIFIER_EVENTS_HPP
#define NOTIFIER_EVENTS_HPP

#include "threads_abstract_act.hpp"
#include "threads_thread_pool.hpp"
#include "interface_save_events.hpp"
#include "events_publisher_interface.hpp"

#include "threads_concurrent_hash_table.hpp"


namespace smart_home 
{

class NotifierEvents
{
private:
    using PtrThreadsPool = std::shared_ptr<threads::ThreadPool>;
    using PtrProxy = std::shared_ptr<IEventsPublisher>;
    using PtrAgent = std::shared_ptr<IAgent>;
    using PtrEvent = std::shared_ptr<Event>;

public:
    NotifierEvents(InterfaceSaveEvents& a_logStream, size_t a_numOfThreads = 1);
    NotifierEvents(NotifierEvents const& a_other) = default;
    NotifierEvents& operator=(NotifierEvents const& a_other) = default;
    ~NotifierEvents();

    void SubmitNotify(Event const& a_event, std::vector<PtrAgent> const& a_distributionList, PtrProxy a_ptrProxyEventsPublisher);

private:
    class NotifyAct : public threads::AbstractAct
    {
    public:
        NotifyAct(PtrEvent a_eventPtr, std::vector<PtrAgent> const& a_distributionList, PtrProxy a_proxyPtr, PtrThreadsPool a_threadsPool, InterfaceSaveEvents& a_logStream);
        NotifyAct(NotifyAct const& a_other) = default;
        NotifyAct& operator=(NotifyAct const& a_other) = default;
        virtual ~NotifyAct() = default;

        virtual void Act() override;

    private:
        using EventData = std::pair<std::string, Location>;

    private:
        PtrEvent m_eventPtr;
        std::vector<PtrAgent> m_distributionList;
        PtrProxy m_proxyPtr;
        PtrThreadsPool m_threadsPool;
        InterfaceSaveEvents& m_logStream;
    };

    class InformAgentAct : public threads::AbstractAct
    {
    public:
        InformAgentAct(PtrEvent a_eventPtr, PtrAgent a_agentsPtr, std::vector<std::string> const& a_eventData, PtrProxy a_proxyPtr);
        InformAgentAct(InformAgentAct const& a_other) = default;
        InformAgentAct& operator=(InformAgentAct const& a_other) = default;
        virtual ~InformAgentAct() = default;

        virtual void Act() override;

    private:
        // PtrEvent m_eventPtr;
        PtrAgent m_agentsPtr;
        std::vector<std::string> m_eventData;
        PtrProxy m_proxyPtr;
    };



private:
    PtrThreadsPool m_threadsPool;
    InterfaceSaveEvents& m_logStream;
};

} //smart_home


#endif /* NOTIFIER_EVENTS_HPP */