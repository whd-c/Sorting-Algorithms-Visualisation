#include "program.hpp"

int main()
{
    try
    {
        Program program;
        program.run();
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }

    return 0;
}