/** ==========================================================================
* 2020 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
 *
 * For more information see g3log/LICENSE or refer refer to http://unlicense.org
* ============================================================================*/

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <iomanip>
#include <thread>
#include <iostream>


namespace
{
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
   const std::string path_to_log_file = "./";
#else
   const std::string path_to_log_file = "/tmp/";
#endif
}

int main(int argc, char **argv)
{
   auto worker = g3::LogWorker::createLogWorker();
   auto handle= worker->addDefaultLogger(argv[0], path_to_log_file);
   g3::initializeLogging(worker.get());
   std::future<std::string> log_file_name = handle->call(&g3::FileSink::fileName);

   // Exmple of overriding the default formatting of log entry
   auto changeFormatting = handle->call(&g3::FileSink::overrideLogDetails, g3::LogMessage::FullLogDetailsToString);
   const std::string newHeader = "\t\tLOG format: [YYYY/MM/DD hh:mm:ss uuu* LEVEL THREAD_ID FILE->FUNCTION:LINE] message\n\t\t(uuu*: microseconds fractions of the seconds value)\n\n";
   // example of overriding the default formatting of header
   auto changeHeader = handle->call(&g3::FileSink::overrideLogHeader, newHeader);

   changeFormatting.wait();
   changeHeader.wait();


   std::cout << "\tThis is an example of g3log." << std::endl;
   std::cout << "\tLog file location: [" << log_file_name.get() << std::endl;
   std::cout << "\tThe log file location will also be printed (for the default sink) at logger shutdown" << std::endl;

   LOGF(INFO, "Hi log %d", 123);
}


