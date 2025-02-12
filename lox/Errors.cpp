#pragma once
#include <cstddef>
#include <cstring>
#include <string>
#include <unordered_map>

namespace Debug {
  enum class ErrorCode {
    DEFAULT = 0,
    UNEXPECTED_CHARACTER = 1,
    SYNTAX_ERROR,
    INVALID_TOKEN,
    MISSING_SEMICOLON,
  };

  class Error {
    inline static bool hadError = false;
    inline static ErrorCode errorNumber = ErrorCode::DEFAULT;
    static size_t line;

    static std::unordered_map<ErrorCode, std::string> ErrorMap;
    static std::string custom_message;

  public:
    static void error(size_t line, ErrorCode code, std::string msg) {
      Error::line = line;
      Error::errorNumber = code;
      Error::hadError = true;
      Error::custom_message = msg; 
    }

    static std::string strError() noexcept {
      auto it = ErrorMap.find(errorNumber);
      if (it != ErrorMap.end()) {
        return it->second;
      }
      return "Unknown error.";
    }

    static bool hasError() noexcept { return hadError; }

    static ErrorCode getErrorNumber() noexcept { return errorNumber; }

    static size_t getLine() noexcept { return line; }

    static std::string basicErrorString(std::string where) {
      std::string e1 = "";
      e1 += "[line :" + std::to_string(line) + "] : Where : ";
      e1 += where;
      e1 += " " + strError();
      return e1; 
    }
  };

  size_t Error::line = 1;
  std::string Error::custom_message = "";
  std::unordered_map<ErrorCode, std::string> Error::ErrorMap = {
      {ErrorCode::DEFAULT, "No Errors! :)"},
      {ErrorCode::UNEXPECTED_CHARACTER, "Unexpected character encountered."},
      {ErrorCode::SYNTAX_ERROR, "Syntax error."},
      {ErrorCode::INVALID_TOKEN, "Invalid token."},
      {ErrorCode::MISSING_SEMICOLON, "Missing semicolon."},
  };
} // namespace Debug 
