#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

enum class EventType
{
    EVENT_MOUSE_ANY,
    EVENT_MOUSE_LCLICK,
    EVENT_ANY_THING,
    EVENT_DELETE
};

class event{
public:
    virtual ~event(){}
    int getId() const {return this->id;}
    EventType getEventType() const {return this->eventtype;}

    friend class eventSystem;
protected:
    int id;
    EventType eventtype;
};


class eventSystem{
public:
    template<typename T>
    void Bind(const EventType& eventType,const std::function<void(const T&)>& handler)
    {
	// So here's the explanation
        // jadi ini bikin lambda, nah itu lambda nya berparameter const event& e, karena
        // yang kita butuhkan nanti di event handler hanya 1 parameter yaitu const event& e (atau turunan nya)
        // jadi ini akan merubah handler (const event& e) berubah jadi handler(const (turunan nya event, karena udah di dynamic cast)& e) 
        auto processedHandler = [handler](const event& e)
        {
            if (const T* evtObj = dynamic_cast<const T*>(&e))
                return handler(*evtObj);
        };

        // put the processed handler into the list of evt handler
        m_eventHandler[eventType].push_back(processedHandler);
    }

    void Publish(const EventType& eventType, const event& e)
    {
        // Ubah ke non-const event& sementara untuk memberi nilai event type nya
        // "mungkin" berbahaya tapi kayanya aman aman aja
        const_cast<event&>(e).eventtype = eventType;
        auto it = m_eventHandler.find(eventType);
        if (it != m_eventHandler.end())
            for (auto& handler : it->second)
                handler(e);
    }
    
private:
    std::unordered_map<EventType,std::vector<std::function<void(const event&)>>> m_eventHandler;
};

class eventListener
{
public:
    virtual void OnEvent(const event& e)
    {
        std::cout << "Triggered event id: " << e.getId() << std::endl;
    }
};