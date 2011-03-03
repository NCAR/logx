/*
 * RecentHistoryAppender.cc
 */
#include "RecentHistoryAppender.h"
#include "private/LogLayout.h"

using namespace log4cpp;
namespace logx 
{

RecentHistoryAppender::RecentHistoryAppender(const std::string & name, 
        unsigned int maxHistoryLen) : 
        LayoutAppender(name),
        _msgList(),
        _maxHistoryLen(maxHistoryLen),
        _earliestIndex(-1) {
    // Use the logx default formatting
    setLayout(new LogLayout);
}

RecentHistoryAppender::~RecentHistoryAppender() {
}

void
RecentHistoryAppender::close() {
}

void
RecentHistoryAppender::_append(const LoggingEvent & event) {
    _msgList.push_back(_getLayout().format(event));
    // Set _earliestIndex if this is our first log entry
    if (_earliestIndex < 0)
        _earliestIndex = 0;
    // If the list is too long now, remove the oldest entry
    if (_msgList.size() > _maxHistoryLen) {
        _msgList.erase(_msgList.begin());
        _earliestIndex++;
    }
}

std::vector<std::string>
RecentHistoryAppender::getMessages(unsigned int & startIndex) const {
    std::vector<std::string> returnVector;
    
    if (_msgList.empty()) {
        return(returnVector);
    }
    
    if (int(startIndex) < _earliestIndex)
        startIndex = _earliestIndex;

    for (; startIndex < _earliestIndex + _msgList.size(); startIndex++) {
        returnVector.push_back(_msgList.at(startIndex - _earliestIndex));
    }
    return(returnVector);
}

} // end namespace logx
