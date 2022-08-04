#include "Parser.h"
#include <iostream>
#include <sstream>

Parser::Parser() {
	std::cin >> path;
	in.open(path);
	if (!in) {
		std::cerr << "open error" << "\n";
		return;
	}
}

bool Parser::hasMoreCommnads() {
	return in.peek() != EOF;
}

void Parser::advance() {

	std::stringstream ss;

	if (hasMoreCommnads()) {
		std::getline(in, curCmd);

		// curCmd 전처리
		curCmd = curCmd.substr(0, curCmd.find('/'));
		ss << curCmd;

		arg1 = "null"; //초기화
		arg2 = 0;

		std::string temp;
		int i = 0;
		while (ss >> temp) {
			if (i == 0) {
				command = temp;
			}
			else if (i == 1) {
				arg1 = temp;
			}
			else if (i == 2) {
				arg2 = stoi(temp);
			}
			else break;
			i++;
		}

		

		curType = commandType();
	}

}

int Parser::commandType() {
	if (command == "add" || command=="sub" || command == "neg" || command == "eq" || command == "gt" 
		|| command == "lt" || command == "and" || command == "or" || command == "not") return C_ARITHMETIC;
	
	if (command == "push")
		return C_PUSH;

	if (command == "pop")
		return C_POP;

	if (command == "return")
		return C_RETURN;

	if (command == "label")
		return C_LABEL;

	if (command == "goto")
		return C_GOTO;

	if (command == "if-goto")
		return C_IF;

	if (command == "function")
		return C_FUNCTION;

	if (command == "call")
		return C_CALL;

	return -1; // error
}

std::string Parser::Arg1()
{
	if (curType == C_RETURN) return "error";

	if (arg1 == "null") return command;

	return arg1;
}

int Parser::Arg2()
{
	if (curType == C_PUSH || curType == C_POP || curType == C_FUNCTION || curType == C_CALL) {
		return arg2;
	}
	
	return -1;
}
