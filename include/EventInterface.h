#ifndef EVENTINTERFACE_H
#define EVENTINTERFACE_H
#include <SFML/Graphics.hpp>
#include <vector>

class EventInterface {
    public:
        virtual const EventType& getEventType(void) const = 0;
        virtual float GetTimeStamp(void) const = 0;
        virtual Serialize(const std::ostream& o) const = 0;
        virtual EventDataInterface* copy(void) const = 0;
};

#endif