#include "CodeWriter.h"


void CodeWriter::incSP()
{
}

void CodeWriter::decSP()
{
}

void CodeWriter::refSP()
{
}

CodeWriter::CodeWriter(std::string filename) { //setfilename ���
	out.open(filename + ".asm");
	fileName = filename;
}

int count = 0;

 void CodeWriter::writerArithmetic(std::string cmd) {
	if (cmd == "not") {

		out << "@SP\n"; // SP-1 ����
		out << "A = M-1\n";
		out << "D = M\n";

		out << "@SP\n"; // SP-1 ����
		out << "A = M-1\n";
		out << "M = !D\n";
	}
	else if (cmd == "neg") {
		out << "@SP\n"; // SP-1 ����
		out << "A = M-1\n";
		out << "D = M\n";

		out << "@SP\n"; // SP-1 ����
		out << "A = M-1\n";
		out << "M = -D\n";
	}
	else {
		out << "@SP\n"; // SP ����
		out << "M = M-1\n";

		out << "@SP\n"; // SP �� ����
		out << "A=M\n"; // SP �� ����

		out << "D = M\n"; // D = X

		out << "@SP\n"; // SP-1 ����
		out << "A = M-1\n";

		if (cmd == "add") {
			out << "D = D+M\n";

			out << "@SP\n"; // SP �� ����
			out << "A = M-1\n";
			out << "M = D\n";
		}
		else if (cmd == "sub") {
			out << "D = D-M\n";

			out << "@SP\n"; // SP-1 ����
			out << "A = M-1\n";
			out << "M = -D\n";
		}
		else if (cmd == "eq") {
			out << "D = D-M\n";

			out << "@TRUE" <<count<<"\n";
			out << "D;JEQ\n";

			out << "(FALSE" << count << ")\n";
			out << "\t@SP\n";// SP-1 ����
			out << "\tA = M-1\n";
			out << "\tM=0\n";

			out << "@NEXT" << count << "\n"; // True �н�
			out << "0;JMP\n";

			out << "(TRUE" << count << ")\n";
			out << "\t@SP\n";// SP-1 ����
			out << "\tA = M-1\n";
			out << "\tM=-1\n";

			out << "(NEXT" << count << ")\n";
			count++;
		}
		else if (cmd == "gt") {
			out << "D = D-M\n";

			out << "@TRUE" << count << "\n";
			out << "D;JLT\n"; // x y ���� ������

			out << "(FALSE" << count << ")\n";
			out << "\t@SP\n";// SP-1 ����
			out << "\tA = M-1\n";
			out << "\tM=0\n";

			out << "@NEXT" << count << "\n"; // True �н�
			out << "0;JMP\n";

			out << "(TRUE" << count << ")\n";
			out << "\t@SP\n";// SP-1 ����
			out << "\tA = M-1\n";
			out << "\tM=-1\n";

			out << "(NEXT" << count << ")\n";
			count++;
		}
		else if (cmd == "lt") {
			out << "D = D-M\n";

			out << "@TRUE" << count << "\n";
			out << "D;JGT\n";

			out << "(FALSE" << count << ")\n";
			out << "\t@SP\n";// SP-1 ����
			out << "\tA = M-1\n";
			out << "\tM=0\n";

			out << "@NEXT" << count << "\n"; // True �н�
			out << "0;JMP\n";

			out << "(TRUE" << count << ")\n";
			out << "\t@SP\n";// SP-1 ����
			out << "\tA = M-1\n";
			out << "\tM=-1\n";

			out << "(NEXT" << count << ")\n";
			count++;
		}
		else if (cmd == "and") {
			out << "D = D&M\n";
			out << "@SP\n"; // SP-1 ����
			out << "A = M-1\n";
			out << "M = D\n";
		}
		else if (cmd == "or") {
			out << "D = D|M\n";
			out << "@SP\n"; // SP-1 ����
			out << "A = M-1\n";
			out << "M = D\n";
		}


	}

}

 void CodeWriter::writePushPop(int cmd, std::string seg, int index) {
	
	int addr = 0;
	if (seg == "argument") {
		addr = 2;
	}
	else if (seg == "local") {
		addr = 1;
	}
	else if (seg == "this") {
		addr = 3;
	}
	else if (seg == "that") {
		addr = 4;
	}
	else if (seg == "temp") {
		addr = 5; //~12
	}
	else if (seg == "pointer") {
		addr = 3;
	}

	if (cmd == C_PUSH) {
		if (seg == "static") { // ����ó��
			out << "@" << fileName <<"." << index << "\n";
			out << "D=M\n";
			
			out << "@SP\n"; // SP �� ����
			out << "A = M\n";

			out << "M = D\n";

			out << "@SP\n"; // SP �� ����
			out << "M = M+1\n";

		}
		else if (seg=="constant") { // constant
			out << "@" << index << "\n";
			out << "D=A\n";

			out << "@SP\n"; // SP �� ����
			out << "A = M\n";

			out << "M = D\n"; 

			// SP ����
			out << "@SP\n";
			out << "M = M+1\n";
		}
		else if (seg == "temp" || seg=="pointer") {
			out << "@" << index+addr << "\n";
			out << "D=M\n";

			out << "@SP\n"; // SP �� ����
			out << "A = M\n";

			out << "M = D\n";

			// SP ����
			out << "@SP\n";
			out << "M = M+1\n";
		}
		else {
			out << "@" << index << "\n";
			out << "D=A\n"; // index ����

			out << "@" << addr<< "\n";
			out << "A = M+D\n"; // �ּҷ� �̵�

			out << "D = M\n";

			out << "@SP\n"; // SP �� ����
			out << "A = M\n";

			out << "M = D\n"; 

			out << "@SP\n"; // SP �� ����
			out << "M = M+1\n";
		}

	}
	else if (cmd == C_POP) {
		if (seg == "static") {
			out << "@SP\n"; // SP-1 ����
			out << "A = M-1\n";

			out << "D = M\n"; // �� ���� 

			out << "@" << fileName << "." << index << "\n";
			out << "M = D\n";

			out << "@SP\n"; // SP �� ����
			out << "M = M-1\n";
		}
		else if (seg == "temp" || seg=="pointer") {

			out << "@SP\n"; // SP-1 ����
			out << "A = M-1\n";

			out << "D = M\n"; // �� ���� 

			out << "@" <<addr+index <<"\n";
			out << "M = D\n";

			out << "@SP\n"; // SP �� ����
			out << "M = M-1\n";
		}
		else {
			out << "@" << index << "\n";
			out << "D=A\n"; // index ����

			out << "@" << addr << "\n";
			out << "D = M+D\n";

			out << "@R13\n"; // �ּ� ����
			out << "M = D\n";

			out << "@SP\n"; // SP-1 ����
			out << "A = M-1\n";

			out << "D = M\n"; // �� ���� 

			out << "@R13\n";
			out << "A=M\n";
			out << "M = D\n";

			out << "@SP\n"; // SP �� ����
			out << "M = M-1\n";
		}
	
	}

}

 CodeWriter::~CodeWriter() {
	out.close();
}
