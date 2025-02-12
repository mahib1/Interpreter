#pragma once

#include "Errors.cpp"
#include "Token.cpp"
#include "TokenType.hpp"
#include "Logger.cpp"
#include <cstddef>
#include <stdlib.h>
#include <string>
#include <variant>
#include <vector>


#ifdef DEBUG

class Scanner {
  std::string _content;
  size_t _conSize;
  std::vector<LoxToken::Token> _tokens;
  size_t start = 0;
  size_t current = 0;
  size_t line = 1;

  bool isAtEnd() const noexcept { return current >= _conSize; }

  void scanToken() {
    char c = advance();
    Debug::Logger::Log("Scanning Character : " + _content.substr(current, 1));
    switch (c) {
    case '(':
      addToken(LoxToken::TokenType::LEFT_PAREN);
      break;
    case ')':
      addToken(LoxToken::TokenType::RIGHT_PAREN);
      break;
    case '{':
      addToken(LoxToken::TokenType::LEFT_BRACE);
      break;
    case '}':
      addToken(LoxToken::TokenType::RIGHT_BRACE);
      break;
    case ',':
      addToken(LoxToken::TokenType::COMMA);
      break;
    case '.':
      addToken(LoxToken::TokenType::DOT);
      break;
    case '-':
      addToken(LoxToken::TokenType::MINUS);
      break;
    case '+':
      addToken(LoxToken::TokenType::PLUS);
      break;
    case ';':
      addToken(LoxToken::TokenType::SEMICOLON);
      break;
    case '*':
      addToken(LoxToken::TokenType::STAR);
      break;
    case '!':
      addToken(match('=') ? LoxToken::TokenType::BANG_EQUAL
                          : LoxToken::TokenType::BANG);
      break;
    case '=':
      addToken(match('=') ? LoxToken::TokenType::EQUAL_EQUAL
                          : LoxToken::TokenType::EQUAL);
      break;
    case '<':
      addToken(match('=') ? LoxToken::TokenType::LESS_EQUAL
                          : LoxToken::TokenType::LESS);
      break;
    case '>':
      addToken(match('=') ? LoxToken::TokenType::GREATER_EQUAL
                          : LoxToken::TokenType::GREATER);
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        addToken(LoxToken::TokenType::SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '"' :
      makeString(); 
      break;
    default:
      Debug::Error::error(line, Debug::ErrorCode::UNEXPECTED_CHARACTER,
                           "You suck :/");
    }
  }

  void makeString() {
    while(peek() != '"' && !isAtEnd()) {
      if(peek() == '\n') {
        line++;
      }

      advance();
    }

    if(isAtEnd()) {
      Debug::Error::error(line, Debug::ErrorCode::SYNTAX_ERROR, "Unterminated String!");
      return;
    }
    
    std::string val = _content.substr(start + 1, current - start - 1); // to trim the ""
    addToken(LoxToken::TokenType::STRING, val);
    advance();
  }

  char advance() { return _content[current++]; }

  void addToken(LoxToken::TokenType t) { addToken(t, std::monostate()); }

  void addToken(LoxToken::TokenType t, LoxToken::literal_t l) {
    std::string text = _content.substr(start, current - start);
    _tokens.push_back(LoxToken::Token(t, text, l, line));
    Debug::Logger::Log(_tokens[_tokens.size() - 1].toString());
  }

  bool match(char exp) {
    if (isAtEnd())
      return false;

    if (_content[current] != exp)
      return false;

    current++;
    return true;
  }

  char peek() {
    if (isAtEnd())
      return '\0';
    return _content[current];
  }

public:
  Scanner(const char *isBuff) noexcept {
    _content = isBuff;
    _conSize = _content.length();
  }

  std::vector<LoxToken::Token> scanTokens() noexcept {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }
    _tokens.push_back(
        LoxToken::Token(LoxToken::TokenType::MEOF, "", std::monostate(), line));

    return _tokens;
  }
};

#endif 

#ifndef DEBUG

class Scanner {
  std::string _content;
  size_t _conSize;
  std::vector<LoxToken::Token> _tokens;
  size_t start = 0;
  size_t current = 0;
  size_t line = 1;

  bool isAtEnd() const noexcept { return current >= _conSize; }

  void scanToken() {
    // std::cout << "Scanning character - " << _content[current] << std::endl;
    char c = advance();
    switch (c) {
    case '(':
      addToken(LoxToken::TokenType::LEFT_PAREN);
      break;
    case ')':
      addToken(LoxToken::TokenType::RIGHT_PAREN);
      break;
    case '{':
      addToken(LoxToken::TokenType::LEFT_BRACE);
      break;
    case '}':
      addToken(LoxToken::TokenType::RIGHT_BRACE);
      break;
    case ',':
      addToken(LoxToken::TokenType::COMMA);
      break;
    case '.':
      addToken(LoxToken::TokenType::DOT);
      break;
    case '-':
      addToken(LoxToken::TokenType::MINUS);
      break;
    case '+':
      addToken(LoxToken::TokenType::PLUS);
      break;
    case ';':
      addToken(LoxToken::TokenType::SEMICOLON);
      break;
    case '*':
      addToken(LoxToken::TokenType::STAR);
      break;
    case '!':
      addToken(match('=') ? LoxToken::TokenType::BANG_EQUAL
                          : LoxToken::TokenType::BANG);
      break;
    case '=':
      addToken(match('=') ? LoxToken::TokenType::EQUAL_EQUAL
                          : LoxToken::TokenType::EQUAL);
      break;
    case '<':
      addToken(match('=') ? LoxToken::TokenType::LESS_EQUAL
                          : LoxToken::TokenType::LESS);
      break;
    case '>':
      addToken(match('=') ? LoxToken::TokenType::GREATER_EQUAL
                          : LoxToken::TokenType::GREATER);
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        addToken(LoxToken::TokenType::SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '"' :
      makeString(); 
      break;
    default:
      Debug::Error::error(line, Debug::ErrorCode::UNEXPECTED_CHARACTER,
                           "You suck :/");
    }
  }

  void makeString() {
    while(peek() != '"' && !isAtEnd()) {
      if(peek() == '\n') {
        line++;
      }

      advance();
    }

    if(isAtEnd()) {
      Debug::Error::error(line, Debug::ErrorCode::SYNTAX_ERROR, "Unterminated String!");
      return;
    }
 
    std::string val = _content.substr(start + 1, current - start - 1); // to trim the ""
    addToken(LoxToken::TokenType::STRING, val);
    advance();
  }

  char advance() { return _content[current++]; }

  void addToken(LoxToken::TokenType t) { addToken(t, std::monostate()); }

  void addToken(LoxToken::TokenType t, LoxToken::literal_t l) {
    std::string text = _content.substr(start, current - start);
    _tokens.push_back(LoxToken::Token(t, text, l, line));
  }

  bool match(char exp) {
    if (isAtEnd())
      return false;

    if (_content[current] != exp)
      return false;

    current++;
    return true;
  }

  char peek() {
    if (isAtEnd())
      return '\0';
    return _content[current];
  }

public:
  Scanner(const char *isBuff) noexcept {
    _content = isBuff;
    _conSize = _content.length();
  }

  std::vector<LoxToken::Token> scanTokens() noexcept {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }
    _tokens.push_back(
        LoxToken::Token(LoxToken::TokenType::MEOF, "", std::monostate(), line));

    return _tokens;
  }
};
#endif
