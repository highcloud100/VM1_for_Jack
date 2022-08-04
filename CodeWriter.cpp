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

CodeWriter::CodeWriter(std::string filename) { //setfilename 겸용
	out.open(filename + ".asm");
	fileName = filename;
}

int count = 0;

 void CodeWriter::writerArithmetic(std::string cmd) {
	if (cmd == "not") {

		out << "@SP\n"; // SP-1 참조
		out << "A = M-1\n";
		out << "D = M\n";

		out << "@SP\n"; // SP-1 참조
		out << "A = M-1\n";
		out << "M = !D\n";
	}
	else if (cmd == "neg") {
		out << "@SP\n"; // SP-1 참조
		out << "A = M-1\n";
		out << "D = M\n";

		out << "@SP\n"; // SP-1 참조
		out << "A = M-1\n";
		out << "M = -D\n";
	}
	else {
		out << "@SP\n"; // SP 감소
		out << "M = M-1\n";

		out << "@SP\n"; // SP 값 참조
		out << "A=M\n"; // SP 값 참조

		out << "D = M\n"; // D = X

		out << "@SP\n"; // SP-1 참조
		out << "A = M-1\n";

		if (cmd == "add") {
			out << "D = D+M\n";

			out << "@SP\n"; // SP 값 참조
			out << "A = M-1\n";
			out << "M = D\n";
		}
		else if (cmd == "sub") {
			out << "D = D-M\n";

			out << "@SP\n"; // SP-1 참조
			out << "A = M-1\n";
			out << "M = -D\n";
		}
		else if (cmd == "eq") {
			out << "D = D-M\n";

			out << "@TRUE" <<count<<"\n";
			out << "D;JEQ\n";

			out << "(FALSE" << count << ")\n";
			out << "\t@SP\n";// SP-1 참조
			out << "\tA = M-1\n";
			out << "\tM=0\n";

			out << "@NEXT" << count << "\n"; // True 패스
			out << "0;JMP\n";

			out << "(TRUE" << count << ")\n";
			out << "\t@SP\n";// SP-1 참조
			out << "\tA = M-1\n";
			out << "\tM=-1\n";

			out << "(NEXT" << count << ")\n";
			count++;
		}
		else if (cmd == "gt") {
			out << "D = D-M\n";

			out << "@TRUE" << count << "\n";
			out << "D;JLT\n"; // x y 순서 뒤집음

			out << "(FALSE" << count << ")\n";
			out << "\t@SP\n";// SP-1 참조
			out << "\tA = M-1\n";
			out << "\tM=0\n";

			out << "@NEXT" << count << "\n"; // True 패스
			out << "0;JMP\n";

			out << "(TRUE" << count << ")\n";
			out << "\t@SP\n";// SP-1 참조
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
			out << "\t@SP\n";// SP-1 참조
			out << "\tA = M-1\n";
			out << "\tM=0\n";

			out << "@NEXT" << count << "\n"; // True 패스
			out << "0;JMP\n";

			out << "(TRUE" << count << ")\n";
			out << "\t@SP\n";// SP-1 참조
			out << "\tA = M-1\n";
			out << "\tM=-1\n";

			out << "(NEXT" << count << ")\n";
			count++;
		}
		else if (cmd == "and") {
			out << "D = D&M\n";
			out << "@SP\n"; // SP-1 참조
			out << "A = M-1\n";
			out << "M = D\n";
		}
		else if (cmd == "or") {
			out << "D = D|M\n";
			out << "@SP\n"; // SP-1 참조
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
		if (seg == "static") { // 예외처리
			out << "@" << fileName <<"." << index << "\n";
			out << "D=M\n";
			
			out << "@SP\n"; // SP 값 참조
			out << "A = M\n";

			out << "M = D\n";

			out << "@SP\n"; // SP 값 증가
			out << "M = M+1\n";

		}
		else if (seg=="constant") { // constant
			out << "@" << index << "\n";
			out << "D=A\n";

			out << "@SP\n"; // SP 값 참조
			out << "A = M\n";

			out << "M = D\n"; 

			// SP 증가
			out << "@SP\n";
			out << "M = M+1\n";
		}
		else if (seg == "temp" || seg=="pointer") {
			out << "@" << index+addr << "\n";
			out << "D=M\n";

			out << "@SP\n"; // SP 값 참조
			out << "A = M\n";

			out << "M = D\n";

			// SP 증가
			out << "@SP\n";
			out << "M = M+1\n";
		}
		else {
			out << "@" << index << "\n";
			out << "D=A\n"; // index 저장

			out << "@" << addr<< "\n";
			out << "A = M+D\n"; // 주소로 이동

			out << "D = M\n";

			out << "@SP\n"; // SP 값 참조
			out << "A = M\n";

			out << "M = D\n"; 

			out << "@SP\n"; // SP 값 증가
			out << "M = M+1\n";
		}

	}
	else if (cmd == C_POP) {
		if (seg == "static") {
			out << "@SP\n"; // SP-1 참조
			out << "A = M-1\n";

			out << "D = M\n"; // 값 저장 

			out << "@" << fileName << "." << index << "\n";
			out << "M = D\n";

			out << "@SP\n"; // SP 값 감소
			out << "M = M-1\n";
		}
		else if (seg == "temp" || seg=="pointer") {

			out << "@SP\n"; // SP-1 참조
			out << "A = M-1\n";

			out << "D = M\n"; // 값 저장 

			out << "@" <<addr+index <<"\n";
			out << "M = D\n";

			out << "@SP\n"; // SP 값 감소
			out << "M = M-1\n";
		}
		else {
			out << "@" << index << "\n";
			out << "D=A\n"; // index 저장

			out << "@" << addr << "\n";
			out << "D = M+D\n";

			out << "@R13\n"; // 주소 저장
			out << "M = D\n";

			out << "@SP\n"; // SP-1 참조
			out << "A = M-1\n";

			out << "D = M\n"; // 값 저장 

			out << "@R13\n";
			out << "A=M\n";
			out << "M = D\n";

			out << "@SP\n"; // SP 값 감소
			out << "M = M-1\n";
		}
	
	}

}

 CodeWriter::~CodeWriter() {
	out.close();
}
