#pragma once
#include <list>
#include <memory>

template <class Event>
class Observable;

template <class Event>
class IObserver {
    protected:
        virtual void notify (Event event) = 0;

        friend class Observable<Event>;
};

template <class Event>
class Observable {
    private:
        using SubsList = std::list<std::shared_ptr<IObserver<Event>>>;

        SubsList subs;
    
    protected:
        void notifySubs (Event event) {
            for (const auto &sub : subs) sub->notify(event);
        }

    public:
        void subscribe (std::shared_ptr<IObserver<Event>> sub) {
            subs.push_back(sub);
        }
};