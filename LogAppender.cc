/*
 * LogAppender.cc
 */
#include <string>

#include <log4cpp/FileAppender.hh>
#include <log4cpp/Category.hh>

using namespace log4cpp;
namespace logx 
{
void
LogToFile(std::string logFile,  bool additivity = true)
{
    Appender *app =  new FileAppender("FileAppender", logFile);
   std::vector<Category*> *cats = Category::getCurrentCategories();
   
   for (std::vector<Category*>::iterator icat = cats->begin(); icat != cats->end(); ++icat)
   {
       (*icat)->setAppender(app);
       (*icat)->setAdditivity(additivity);
   }
   
}
}


