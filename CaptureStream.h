// -*- C++ -*-
//
// $Id$
//

#ifndef _logx_CaptureStream_h_
#define _logx_CaptureStream_h_

#include <sstream>

namespace logx
{

  /**
   * A CaptureStream object collects output in an output stream and then
   * fires a signal with the completed message when the object is destroyed.
   * Thus the intended use is as a temporary object which will pass a message
   * on to the interested recipient before disappearing.
   *
   * Example:
   * @verbatim

   class Writer;

   typedef std::mem_fun1_t<void,Writer,std::string> writer_message_t;
   typedef std::binder1st<writer_message_t> writer_message_slot;

   logx::CaptureStream< writer_message_slot >
   Writer::
   errorStream ()
   {
     return logx::CaptureStream< writer_message_slot >
        (std::bind1st (mem_fun (&Writer::setError), this), _errorStream);
   }

   * @endverbatim
   *
   **/
  template <typename SLOT>
  class CaptureStream
  {
  public:

    CaptureStream (const SLOT& slot) :
      mSignal (slot)
    {}

    template <typename X>
    inline
    CaptureStream&
    operator<< (const X& x)
    {
      mStream << x;
      return *this;
    }

    ~CaptureStream ()
    {
      mSignal(mStream.str());
    }

  private:

    SLOT mSignal;
    std::ostringstream mStream;
  };


  template <typename SLOT>
  inline CaptureStream<SLOT>
  captureStream (const SLOT& slot)
  {
    return CaptureStream<SLOT> (slot);
  }

}


#endif // _logx_CaptureStream_h_
