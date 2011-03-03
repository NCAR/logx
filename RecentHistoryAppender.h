// -*- C++ -*-

#ifndef _logx_RecentHistoryAppender_h_
#define _logx_RecentHistoryAppender_h_

#include <vector>
#include <string>
#include <log4cpp/LayoutAppender.hh>

namespace logx
{

/**
 * RecentHistoryAppender is an Appender which keeps a std::deque<std::string> 
 * list of the most recently logged messages.
 */
class RecentHistoryAppender : public log4cpp::LayoutAppender
{

public:
    /**
     * Construct an with a specified maximum list length.
     * @param name the name of this appender
     * @param maxHistoryLen the maximum number of messages to retain in this
     *    queue
     */
    RecentHistoryAppender(const std::string & name, 
            unsigned int maxHistoryLen = 100);
    
    virtual ~RecentHistoryAppender();
    
    /**
     * Return a std::vector<std::string> containing all messages in this
     * history which have index greater than or equal to the given start
     * index. If startIndex is zero, it is guaranteed that all messages in
     * the appender will be returned.
     * @param startIndex[in,out] On entry, startIndex is the desired starting
     * index for the list of messages. On exit, startIndex holds the index
     * of the next message after the last in the returned list, i.e., a good 
     * starting index for the next call to getMessages().
     * @return a std::vector<std::string> containing all messages in this
     * history which have index greater than or equal to the give start
     * index.
     */
    std::vector<std::string> getMessages(unsigned int & startIndex) const;
    
    virtual void close();

protected:
    /**
     * Append a logging event to the queue.
     * @param event the LoggingEvent to be appended
     */
    virtual void _append(const log4cpp::LoggingEvent & event);

private:
    // vector holding our list of messages
    std::vector<std::string> _msgList;
    // Maximum number of log messages we will retain.
    const unsigned int _maxHistoryLen;
    // Earliest message index we're still retaining
    int _earliestIndex;
};

}
// namespace logx

#endif // _logx_RecentHistoryAppender_h_
