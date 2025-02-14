#pragma once

#include "TokenType.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>

#define ha(a) std::holds_alternative<a>

namespace LoxToken {

using literal_t = std::variant<std::monostate, double, std::string>;

std::unordered_map<TokenType, std::string> initTokenStringMap() {
  return {
      {TokenType::LEFT_PAREN, "LEFT_PAREN"},   {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
      {TokenType::LEFT_BRACE, "LEFT_BRACE"},   {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
      {TokenType::COMMA, "COMMA"},             {TokenType::DOT, "DOT"},
      {TokenType::MINUS, "MINUS"},             {TokenType::PLUS, "PLUS"},
      {TokenType::SEMICOLON, "SEMICOLON"},     {TokenType::SLASH, "SLASH"},
      {TokenType::STAR, "STAR"},               {TokenType::BANG, "BANG"},
      {TokenType::BANG_EQUAL, "BANG_EQUAL"},   {TokenType::EQUAL, "EQUAL"},
      {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"}, {TokenType::GREATER, "GREATER"},
      {TokenType::GREATER_EQUAL, "GREATER_EQUAL"}, {TokenType::LESS, "LESS"},
      {TokenType::LESS_EQUAL, "LESS_EQUAL"},   {TokenType::IDENTIFIER, "IDENTIFIER"},
      {TokenType::STRING, "STRING"},           {TokenType::NUMBER, "NUMBER"},
      {TokenType::AND, "AND"},                 {TokenType::CLASS, "CLASS"},
      {TokenType::ELSE, "ELSE"},               {TokenType::FALSE, "FALSE"},
      {TokenType::FUN, "FUN"},                 {TokenType::FOR, "FOR"},
      {TokenType::IF, "IF"},                   {TokenType::NIL, "NIL"},
      {TokenType::OR, "OR"},                   {TokenType::PRINT, "PRINT"},
      {TokenType::RETURN, "RETURN"},           {TokenType::SUPER, "SUPER"},
      {TokenType::THIS, "THIS"},               {TokenType::TRUE, "TRUE"},
      {TokenType::VAR, "VAR"},                 {TokenType::WHILE, "WHILE"},
      {TokenType::MEOF, "EOF"}};
}

class Token2String {
  static std::unordered_map<TokenType, std::string> tokenStringMap;

public:
  static std::string get(TokenType t1) {
    if (tokenStringMap.empty()) {
      tokenStringMap = initTokenStringMap();
    }
    return tokenStringMap[t1];
  }
};

std::unordered_map<TokenType, std::string> Token2String::tokenStringMap = initTokenStringMap();

std::string literal2string(literal_t &l) {
  if (ha(double)(l)) {
    return std::to_string(std::get<double>(l));
  } else if (ha(std::string)(l)) {
    return std::get<std::string>(l);
  }
  return "";
}

class Token {
  TokenType type;
  std::string lexemme;
  literal_t literal;
  int line;

public:
  Token(TokenType type, std::string lexemme, literal_t literal, int line)
      : type(type), lexemme(lexemme), literal(literal), line(line) {}

  std::string toString() {
    return Token2String::get(type) + " " + lexemme + " " + literal2string(literal);
  }

  std::string getLiteral() { return literal2string(literal); }
  std::string getLexemme() { return lexemme; }
};

} // namespace LoxToken
