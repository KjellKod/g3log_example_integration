/** ==========================================================================
* 2020 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
 *
 * For more information see g3log/LICENSE or refer refer to http://unlicense.org
* ============================================================================*/

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <g3sinks/LogRotate.h>
#include <g3sinks/LogRotateWithFilter.h>
#include <iomanip>
#include <thread>
#include <iostream>
#include <vector>

namespace
{
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
   const std::string directory = "./";
#else
   const std::string directory = "/tmp/";
#endif
}

// This example will use 2 sinks
// 1. the logrotate sink
// 2. the logrotate sink with filtration
int main(int argc, char **argv)
{
   auto logworker = g3::LogWorker::createLogWorker();
   // logging initalization can happen before or after you add the logging sinks
   g3::initializeLogging(logworker.get());

   // ------------ RotateSink: you can set max log size in bytes before triggering a log rotation.
   //              See the docs and the code and unit tests
   std::string rotateFileLog = "logrotate_file_test";
   auto rotateSinkHandle = logworker->addSink(std::make_unique<LogRotate>(rotateFileLog, directory),
                              &LogRotate::save);
   // --------------- Filtered RotateSink --------
   // internally the filtered sink uses a normal LogRotate
    std::string filteredFileLog = "filtered_rotate_file_test";
    auto logRotatePtr = std::make_unique<LogRotate>(filteredFileLog, directory);
    // for the filterd log rotate we want to only see WARNING and FATAL so INFO and DEBUG are filtered out
    std::vector<LEVELS> filterOut = {G3LOG_DEBUG, INFO};
    auto filteredRotateSinkHandle = logworker->addSink(std::make_unique<LogRotateWithFilter>(std::move(logRotatePtr), filterOut),
                                      &LogRotateWithFilter::save);

   LOGF(INFO, "First (%d) entry", 1);
   LOG(DEBUG) << "Second (" << 2 << ") entry ";
   LOGF(WARNING, "Third entry (%d) - and the only one that will show up in the filtered log file", 1);
}


