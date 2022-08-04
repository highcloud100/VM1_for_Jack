#pragma once
#include <iostream>
#include <fstream>
#include "Parser.h"

enum ADDRESS
{
	STACK = 256,
	HEAP = 2048,
	IO = 16384,
	STATIC = 16
};

class CodeWriter
{
public:
	std::string fileName;
	int sp = STACK;

	void incSP();
	void decSP();
	void refSP();

	std::ofstream out;

	CodeWriter(std::string filename);

	void writerArithmetic(std::string cmd);

	void writePushPop(int cmd, std::string seg, int index);

	~CodeWriter();
};

