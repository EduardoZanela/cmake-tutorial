#include <iostream>
#include <wg/error_logger/error_logger.h>

int main(void) 
{
    std::cout << "aaa" << std::endl;
    enableLogToConsole(0);
    u_debug("", "Test message");
    return 0;
}