#include <cstdlib>
#include <ftl/prelude.h>
#include <iostream>
#include <limits>
#include <string>
#include "parser_combinator/parser_combinator.h"

using namespace ftl;
using namespace std;

int string2int(const string& str) {
	return atoi(str.c_str());
}

parser<int>    parseNatural();
parser<string> whitespace();
parser<char>   parseOperator();
parser<int>    parseCalc();
parser<int>    parseExpr();

int main() {

	auto parser = parseExpr();

	auto res = run(parser, cin);

	while(!res) {
		cout << "expected " << res.left().message() << endl;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        res = run(parser, cin);
	}

    cout << *res << endl;

    return 0;
}

parser<int> parseNatural() {
	return string2int % many1(oneOf("0123456789"));
}

parser<string> whitespace() {
	return many1(oneOf(" \t\r\n"));
}

parser<char> parseOperator() {
    return oneOf("+-*/%");
}

parser<int> parseCalc() {
    return
        parseChar('(') >> whitespace() >> parseOperator()
                       >> whitespace() >> lazy(parseExpr)
                       >> whitespace() >> lazy(parseExpr)
                       << whitespace()
                       << parseChar(')');
}

parser<int> parseExpr() {
    return parseNatural() | parseCalc();
}
