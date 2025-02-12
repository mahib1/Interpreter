#pragma once

#include <cstddef>
#include <iostream>
#include "Errors.cpp"

namespace Debug {
class Logger {
public:
  static void Log(const char* msg) {
    std::cout << msg << std::endl;
  }

  static void Log(const std::string& s1) {
    std::cout << s1 << std::endl;
  }

  static void lineBreak(size_t n) {
    for(size_t i = 0; i < n; i++) {
      std::cout << "==========================================" << std::endl;
    }
  }

  static void logError(int line, std::string where) {
    if(!Debug::Error::hasError()) return; 

    std::cout << "[line " << line << "] Where : " << where << " : " << Debug::Error::strError() << std::endl;
  }
};
} // namespace Debug
