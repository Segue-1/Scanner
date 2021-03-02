#ifndef SCANNER_H
#define SCANNER_H

bool isDelmiter(char ch);
bool isOperator(char ch);
bool validIdentifier(char * str);
bool isKeyword(char * str);
bool isInteger(char * str);
bool isRealNumber(char * str);
char * subString(char * str, int left, int right);
void parse(char * str);


#endif
