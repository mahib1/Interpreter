
#pragma once

#include "Errors.cpp"
#include "Logger.cpp"
#include "Token.cpp"
#include "TokenType.hpp"
#include <cstddef>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

class Scanner {
  std::string _content;
  size_t _conSize;
  std::vector<LoxToken::Token> _tokens;
  size_t start = 0;
  size_t current = 0;
  size_t line = 1;
  static std::unordered_map<std::string , LoxToken::TokenType> keywords;

  bool isAtEnd() const noexcept { return current >= _conSize; }

  void scanToken() {
    char c = advance();

#ifdef DEBUG
    Debug::Logger::Log("Scanning Character : " + _content.substr(current, 1));
#endif

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
    case '"':
      makeString();
      break;
    default:
      if (isDigit(c)) {
        number();
      } else if(isAlpha(c)) {
        identifier();
      } else {
        Debug::Error::error(line, Debug::ErrorCode::UNEXPECTED_CHARACTER,
                            "You suck :/");
      }
    }
  }

  bool isDigit(char c) { return c >= '0' && c <= '9'; }

  char peekNext() {
    if (current + 1 >= _content.length())
      return '\0';

    return _content[current + 1];
  }

  void identifier() {
    while(isAplhaNumeric(peek())) advance();

    std::string text = _content.substr(start, current - start);
    if(keywords.find(text) != keywords.end()) {
      LoxToken::TokenType type = keywords[text];
      addToken(type);
      return;
    }
    
    addToken(LoxToken::TokenType::IDENTIFIER);
  }

  bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') || 
           (c == '_');
  }

  bool isAplhaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
  }

  void number() {
    while (isDigit(peek()))
      advance();

    if (peek() == '.' && isDigit(peekNext())) {
      advance();

      while (isDigit(peek()))
        advance();
    }

    addToken(LoxToken::TokenType::NUMBER,
             std::stod(_content.substr(start, current - start)));
  }

  void makeString() {
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') {
        line++;
      }

      advance();
    }

    if (isAtEnd()) {
      Debug::Error::error(line, Debug::ErrorCode::SYNTAX_ERROR,
                          "Unterminated String!");
      return;
    }

    std::string val =
        _content.substr(start + 1, current - start - 1); // to trim the ""
    addToken(LoxToken::TokenType::STRING, val);
#ifdef DEBUG
    Debug::Logger::Log("The string added was : " + val);
#endif // DEBUG
    advance();
  }

  char advance() { return _content[current++]; }

  void addToken(LoxToken::TokenType t) { addToken(t, std::monostate()); }

  void addToken(LoxToken::TokenType t, LoxToken::literal_t l) {
    if (t == LoxToken::TokenType::STRING) {
      std::string text = _content.substr(start + 1, current - start - 1);
      _tokens.push_back(LoxToken::Token(t, text, l, line));
#ifdef DEBUG
      Debug::Logger::Log("The string added was : " + text);
#endif // deBUG
      return;
    }

    std::string text = _content.substr(start, current - start);
    _tokens.push_back(LoxToken::Token(t, text, l, line));

#ifdef DEBUG
    Debug::Logger::Log(_tokens[_tokens.size() - 1].toString());
#endif
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

std::unordered_map<std::string, LoxToken::TokenType> Scanner::keywords = {
  {"and",    LoxToken::TokenType::AND},
  {"class",  LoxToken::TokenType::CLASS},
  {"else",   LoxToken::TokenType::ELSE},
  {"false",  LoxToken::TokenType::FALSE},
  {"for",    LoxToken::TokenType::FOR},
  {"fun",    LoxToken::TokenType::FUN},
  {"if",     LoxToken::TokenType::IF},
  {"nil",    LoxToken::TokenType::NIL},
  {"or",     LoxToken::TokenType::OR},
  {"print",  LoxToken::TokenType::PRINT},
  {"return", LoxToken::TokenType::RETURN},
  {"super",  LoxToken::TokenType::SUPER},
  {"this",   LoxToken::TokenType::THIS},
  {"true",   LoxToken::TokenType::TRUE},
  {"var",    LoxToken::TokenType::VAR},
  {"while",  LoxToken::TokenType::WHILE},
};
