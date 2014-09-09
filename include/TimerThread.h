#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H 

#include "echo/NonCopyable.h"
#include "echo/Thread.h"
#include "Timer.h"
#include <functional>


class TimerThread : private NonCopyable
{
    public:
        typedef std::function<void()> TimerCallback;
        void setTimer(int value, int interval);
        void setTimerCallback(const TimerCallback &cb);
        void startTimerThread();
        void cancelTimerThread();

    private:
        Timer timer_;
        Thread thread_; 
};


#endif  /*TIMERTHREAD_H*/
