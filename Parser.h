#pragma once
#include <iostream>
#include <fstream>
#include <string>

enum TYPEOFCOMMAND
{
	C_ARITHMETIC,
	C_PUSH,
	C_POP,
	C_LABEL,
	C_GOTO,
	C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL,
	ERROR,
};

class Parser
{
	
	std::string curCmd;
	int curType;

	std::string arg1;
	int arg2;

	std::ifstream in;
public:
	std::string command;
	std::string path;
	Parser();

	bool hasMoreCommnads();

	void advance();

	int commandType();

	std::string Arg1();

	int Arg2();
};

