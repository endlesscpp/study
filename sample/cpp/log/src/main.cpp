#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <iostream>

namespace spd = spdlog;

int main(int argc, char** argv) {
  int *p = new int(88);
  try {
    auto console = spd::stdout_color_mt("console");
    console->info("Welcome to spdlog...");
    console->info("Pointer = {}", (void *)p);
    console->error("Some error message with arg{}, {}..", 1, 2);

    // Formatting examples
    console->warn("Easy padding in numbers like {:08d}", 12);
    console->critical(
        "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    console->info("Support for floats {:03.2f}", 1.23456);
    console->info("Positional args are {1} {0}..", "too", "supported");
    console->info("{:<30}", "left aligned");

    // SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}",
    // 1, 3.23);

    SPDLOG_INFO("Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);
    } catch (const spd::spdlog_ex& ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
    
