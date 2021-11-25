#include "n_puzzle.hpp"

/*
* Handle Errors
*/

/* Constructor */
MyException::MyException(const char *msg, const char *msg2 = ""){
	this->msg = msg;
	this->msg2 = msg2;
}

/* Destructor */
MyException::~MyException() throw(){
}

/* Print Error Message */
void MyException::print_msg(void){
	fprintf(stderr, "%sError:%s %s %s%s\n", _RED, _YALLOW, this->msg, this->msg2, _DEF);
}
