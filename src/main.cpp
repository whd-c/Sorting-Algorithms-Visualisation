#include "program.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

int main()
{
    std::ofstream g_errorLog("error_log.log", std::ios::app);

    if (g_errorLog.is_open())
    {
        std::cerr.rdbuf(g_errorLog.rdbuf());
    }
    else
    {
        std::cerr << "WARNING! Unable to open error log file.\n";
    }

    try
    {
        Program program;
        program.run();
    }
    catch (const std::runtime_error &e)
    {
        auto except_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cerr << std::put_time(std::localtime(&except_time), "%Y-%m-%d\t%H:%M:%S") << "\tRUNTIME ERROR: " << e.what();
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "An unknown error occured.\n";
        return EXIT_FAILURE;
    }

    return 0;
}