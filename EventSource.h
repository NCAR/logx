// -*- C++ -*-
//
// $Id$
//

#include <sstream>

namespace logx
{

  class EventSourceBase
  {
  public:

    virtual
    void
    handleEventCapture (const std::string& msg) = 0;

    virtual
    ~EventSourceBase()
    {}

    std::ostringstream mEventStream;

  };    


  class CaptureEvent
  {
  public:

    CaptureEvent (EventSourceBase* that) :
      mSource (that)
    {
      mSource->mEventStream.str("");
    }

    template <typename X>
    inline
    CaptureEvent&
    operator<< (const X& x)
    {
      mSource->mEventStream << x;
      return *this;
    }

    ~CaptureEvent ()
    {
      mSource->handleEventCapture (mSource->mEventStream.str());
    }

  private:

    EventSourceBase* mSource;

  };


  template <typename T>
  class EventSource : public EventSourceBase
  {
  public:

    typedef void (T::*slot_type)(const std::string&);

    EventSource(T* source, slot_type slot) :
      mSource (source),
      mSlot (slot)
    {}

    virtual void
    handleEventCapture (const std::string& msg)
    {
      (mSource->*mSlot)(msg);
    }
    
    CaptureEvent
    eventStream()
    {
      return CaptureEvent(this);
    }

    CaptureEvent
    operator() ()
    {
      return CaptureEvent(this);
    }

  private:

    T* mSource;
    slot_type mSlot;

  };
}

