// -*- C++ -*-

#include <string>
#include <log4cpp/LayoutAppender.hh>

namespace logx
{

  /**
   * ACE_Appender logs log4cpp LoggingEvents with ACE using ACE_Log_Msg.
   *
   * An ACE_Appender appends log4cpp logging events to the ACE logging
   * service through ACE_Log_Msg.  There are two configurable format
   * strings.  The first is the conversion pattern with which a @ref
   * log4cpp::PatternLayout LayoutAppender will format the log4cpp logging
   * event into a message string.  The second is the ACE log format with
   * which the message string will be logged to ACE_Log_Msg.  The
   * default format strings:
   *
   *    PatternLayout: "%m%n"
   *    ACE format: "%T %M %n: %s"
   *
   * The default layout pattern "%m%n" merely echoes the log message
   * exactly, with the platform-dependent newline appended to the end.  The
   * ACE format includes the time, priority, and program name followed by
   * the log message string.
   *
   * The ACE_Appender does not depend upon PatternLayout.  The layout can
   * be replaced by any log4cpp::Layout, however each call to
   * set_Pattern_Layout() replaces the current layout with a new
   * PatternLayout.
   **/
  class ACE_Appender : public log4cpp::LayoutAppender
  {
  public:

    /**
     * Install the ACE_Appender @p ap on the root category in place of any
     * existing appenders.  If pointer @p ap is null, then a default
     * ACE_Appender will be created and installed.  This method does not
     * setup ACE logging (eg, by calling @ref acex::SetupLogger()); that is
     * up to the application.
     **/
    static void
    Install (ACE_Appender* ap = 0);

    /**
     * Create a default ACE_Appender with the default layout pattern and
     * ACE format, and with a default name of 'ACE_Appender'.
     **/
    ACE_Appender();

    /**
     * Create an ACE_Appender and set the ACE format and layout pattern
     * accordingly.
     **/
    ACE_Appender (const std::string& pattern,
		  const std::string& ace_format);
		  

    void
    set_Pattern_Layout (const std::string& pattern);

    void
    set_ACE_Format (const std::string& ace_format);

    virtual
    ~ACE_Appender();
        
    virtual bool
    reopen();

    virtual void
    close();

  protected:

    virtual void 
    _append (const log4cpp::LoggingEvent& event);

  private:

    std::string _ace_format;

  };

}

