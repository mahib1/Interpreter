#include "Errors.cpp"
#include "Logger.cpp"
#include "Scanner.cpp"
#include "Token.cpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <unistd.h>
#define MAX_BUFF_SIZE 1024

class Lox {
private:
  inline static bool hadError = false;

  static void runFile(const std::string path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
      std::cerr << "Error opening file : " << path << std::endl;
      return;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buff(size + 1);
    if (file.read(buff.data(), size)) {
      buff[size] = '\0';
      run(buff.data());
      
      printTokens(buff.data());  
      return;
    }
  }

  static void runPrompt() {
    std::cout << "Welcome to lox!" << std::endl;
    std::cout << std::endl;
    int i = 1;

    while (i) {
      std::cout << ">> ";
      char isBuff[MAX_BUFF_SIZE];
      std::cin.getline(isBuff, MAX_BUFF_SIZE);

      run(isBuff);

      #ifdef DEBUG
      std::cout << "Error : " << hadError << std::endl;
      #endif

      if (hadError)
        error(i, Debug::Error::getErrorNumber(), "Error on current line!");
      hadError = false;

      i++;
    }
  }

  static void run(const char *content) {
    Scanner scanner(content);
    std::vector<LoxToken::Token> tokens = scanner.scanTokens();

    #ifdef DEBUG
    for (int i = 0; i < tokens.size(); i++) {
      std::string tokenString = tokens[i].toString();
      if (tokens[i].getLiteral()[0] == '@')
        hadError = true;
      Debug::Logger::Log(tokenString);
    }
    #endif

    std::cout << std::endl;
    return;
  }

  static void error(int line, Debug::ErrorCode code, std::string msg) {
    Debug::Error::error(line, code, msg);
    report("");
  }

  static void report(std::string where) {
    Debug::Error::basicErrorString(where);
    hadError = true;
  }

  static void printTokens(const char* content) {
    Scanner scanner(content);
    std::vector<LoxToken::Token> Tokens = scanner.scanTokens();

    for(int i = 0; i < Tokens.size(); i++) {
      std::string tokenString = Tokens[i].toString();
      Debug::Logger::Log(tokenString);
    }

    return;
  }

public:
  static void main(int argc, char *argv[]) {
    if (argc > 2) {
      std::cout << "Usage : clox [script]" << std::endl;
      exit(64);
    } else if (argc == 2) {
      runFile(argv[1]);
    } else {
      runPrompt();
    }
  }
};

int main(int argc, char *argv[]) {
  Lox::main(argc, argv);
  return 0;
}
