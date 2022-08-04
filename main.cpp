#include "Parser.h"
#include "CodeWriter.h"

int main() {
	Parser P;
	CodeWriter CW(P.path.substr(0,P.path.find('.')));

	while (P.hasMoreCommnads()) {
		P.advance();
		int type = P.commandType();
		if (type == C_ARITHMETIC) {
			CW.writerArithmetic(P.command);
		}
		else if (type == C_PUSH || type == C_POP) {
			CW.writePushPop(P.commandType(), P.Arg1(), P.Arg2());
		}
	}

}