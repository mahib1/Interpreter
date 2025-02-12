#pragma once

#include "TokenType.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

#define ha(a) std::holds_alternative<a>

#ifdef DEBUG
namespace LoxToken {

class Token2String {
  static std::unordered_map<TokenType, std::string> tokenStringMap;

private:
  static void Init() {
    tokenStringMap.insert({{TokenType::LEFT_PAREN, "LEFT_PAREN"},
                           {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
                           {TokenType::LEFT_BRACE, "LEFT_BRACE"},
                           {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
                           {TokenType::COMMA, "COMMA"},
                           {TokenType::DOT, "DOT"},
                           {TokenType::MINUS, "MINUS"},
                           {TokenType::PLUS, "PLUS"},
                           {TokenType::SEMICOLON, "SEMICOLON"},
                           {TokenType::SLASH, "SLASH"},
                           {TokenType::STAR, "STAR"},
                           {TokenType::BANG, "BANG"},
                           {TokenType::BANG_EQUAL, "BANG_EQUAL"},
                           {TokenType::EQUAL, "EQUAL"},
                           {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
                           {TokenType::GREATER, "GREATER"},
                           {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
                           {TokenType::LESS, "LESS"},
                           {TokenType::LESS_EQUAL, "LESS_EQUAL"},
                           {TokenType::IDENTIFIER, "IDENTIFIER"},
                           {TokenType::STRING, "STRING"},
                           {TokenType::NUMBER, "NUMBER"},
                           {TokenType::AND, "AND"},
                           {TokenType::CLASS, "CLASS"},
                           {TokenType::ELSE, "ELSE"},
                           {TokenType::FALSE, "FALSE"},
                           {TokenType::FUN, "FUN"},
                           {TokenType::FOR, "FOR"},
                           {TokenType::IF, "IF"},
                           {TokenType::NIL, "NIL"},
                           {TokenType::OR, "OR"},
                           {TokenType::PRINT, "PRINT"},
                           {TokenType::RETURN, "RETURN"},
                           {TokenType::SUPER, "SUPER"},
                           {TokenType::THIS, "THIS"},
                           {TokenType::TRUE, "TRUE"},
                           {TokenType::VAR, "VAR"},
                           {TokenType::WHILE, "WHILE"},
                           {TokenType::MEOF, "EOF"}});
  }

public:
  static std::string get(TokenType t1) {
    if (tokenStringMap.find(t1) != tokenStringMap.end()) {
      return tokenStringMap[t1];
    }

    Init();
    return tokenStringMap[t1];
  }
};

std::unordered_map<TokenType, std::string> Token2String::tokenStringMap;

using literal_t = std::variant<std::monostate, double, std::string>;

std::string literal2string(literal_t &l) {
  std::string temp;
  if (ha(double)(l)) {
    temp = std::to_string(std::get<double>(l));
  } else if (ha(std::string)(l)) {
    temp = std::get<std::string>(l);
  } else {
    temp = "";
  }

  return temp;
}

class Token {
  TokenType type;
  std::string lexemme;
  literal_t literal;
  int line;

public:
  Token(TokenType type, std::string lexemme, literal_t literal, int line) {
    this->type = type;
    this->lexemme = lexemme;
    this->literal = literal;
    this->line = line;
  }

  std::string toString() {
    std::string s1 = "";

    s1 += Token2String::get(type) + " ";
    s1 += lexemme + " ";
    s1 += literal2string(literal);

    return s1;
  }
};
} // namespace LoxToken

#endif

#ifndef DEBUG 

namespace LoxToken {

class Token2String {
  static std::unordered_map<TokenType, std::string> tokenStringMap;

private:
  static void Init() {
    tokenStringMap.insert({{TokenType::LEFT_PAREN, "LEFT_PAREN"},
                           {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
                           {TokenType::LEFT_BRACE, "LEFT_BRACE"},
                           {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
                           {TokenType::COMMA, "COMMA"},
                           {TokenType::DOT, "DOT"},
                           {TokenType::MINUS, "MINUS"},
                           {TokenType::PLUS, "PLUS"},
                           {TokenType::SEMICOLON, "SEMICOLON"},
                           {TokenType::SLASH, "SLASH"},
                           {TokenType::STAR, "STAR"},
                           {TokenType::BANG, "BANG"},
                           {TokenType::BANG_EQUAL, "BANG_EQUAL"},
                           {TokenType::EQUAL, "EQUAL"},
                           {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
                           {TokenType::GREATER, "GREATER"},
                           {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
                           {TokenType::LESS, "LESS"},
                           {TokenType::LESS_EQUAL, "LESS_EQUAL"},
                           {TokenType::IDENTIFIER, "IDENTIFIER"},
                           {TokenType::STRING, "STRING"},
                           {TokenType::NUMBER, "NUMBER"},
                           {TokenType::AND, "AND"},
                           {TokenType::CLASS, "CLASS"},
                           {TokenType::ELSE, "ELSE"},
                           {TokenType::FALSE, "FALSE"},
                           {TokenType::FUN, "FUN"},
                           {TokenType::FOR, "FOR"},
                           {TokenType::IF, "IF"},
                           {TokenType::NIL, "NIL"},
                           {TokenType::OR, "OR"},
                           {TokenType::PRINT, "PRINT"},
                           {TokenType::RETURN, "RETURN"},
                           {TokenType::SUPER, "SUPER"},
                           {TokenType::THIS, "THIS"},
                           {TokenType::TRUE, "TRUE"},
                           {TokenType::VAR, "VAR"},
                           {TokenType::WHILE, "WHILE"},
                           {TokenType::MEOF, "EOF"}});
  }

public:
  static std::string get(TokenType t1) {
    if (tokenStringMap.find(t1) != tokenStringMap.end()) {
      return tokenStringMap[t1];
    }

    Init();
    return tokenStringMap[t1];
  }
};

std::unordered_map<TokenType, std::string> Token2String::tokenStringMap;

using literal_t = std::variant<std::monostate, double, std::string>;

std::string literal2string(literal_t &l) {
  std::string temp;
  if (ha(double)(l)) {
    temp = std::to_string(std::get<double>(l));
  } else if (ha(std::string)(l)) {
    temp = std::get<std::string>(l);
  } else {
    temp = "";
  }

  return temp;
}

class Token {
  TokenType type;
  std::string lexemme;
  literal_t literal;
  int line;

public:
  Token(TokenType type, std::string lexemme, literal_t literal, int line) {
    this->type = type;
    this->lexemme = lexemme;
    this->literal = literal;
    this->line = line;
  }

  std::string toString() {
    std::string s1 = "";

    s1 += Token2String::get(type) + " ";
    s1 += lexemme + " ";
    s1 += literal2string(literal);

    return s1;
  }
};
} // namespace LoxToken

#endif
