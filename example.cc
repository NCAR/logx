
#include <logx/Logging.h>

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


LOGGING("example");


void usage()
{
    cout << "Usage: example [-h|--help] [log options] [options]\n\n";
    // print usage for program options
    // print loggging usage
    logx::LogUsage(cout);
}


int main(int argc, char* argv[])
{
    logx::ParseLogArgs(argc, argv, true/*skip_usage*/);
    // parse program-specific arguments
    if (argc == 2 && (string("-h") == argv[1] || string("--help") == argv[1]))
    {
        usage();
        return 0;
    }
    else if (argc != 1)
    {
        std::cerr << "unexpected argument, use --help for usage" << endl;
        return 1;
    }
    ILOG << "program continues...";
    DLOG << "debug messages enabled";
    ELOG << "an error (notice) message looks like this, exiting";
    return 0;
}
