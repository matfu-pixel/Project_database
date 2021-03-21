#pragma once

#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
	DATE, // 2020-01-01
	EVENT, // "event"
	COLUMN, // event, date
	LOGICAL_OP, // AND, OR
	COMPARE_OP, // <=, >=, <, >, ==, !=
	PAREN_LEFT, // left bracket
	PAREN_RIGHT, // right bracket
};

struct Token {
	const string value;
	const TokenType type;
};

vector<Token> Tokenize(istream& cl);
