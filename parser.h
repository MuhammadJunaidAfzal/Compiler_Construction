#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include<string>
//for future assignments leave it as it is
class parser
{
    lexer _lexer;
    int n=1;
    int index = 0;
public:
    vector<string> TAC;
    
   // parser(string str);

    void syntax_error();

    token expect(TokenType expected_type);

    parser(const char filename[]);

    void readAndPrintAllInput();

    void resetPointer();

    /*Terminal functions goes here use peek and expect*/

    /*use TokenType:: for token names for example

        expect(TokenType::ASSIGN);   //example function call

      */

      //all your parser function goes here
    bool start();

    void A();
    void B();
    void C();

    string EXP1();
    //void EXP3();
    //void EXP2();
    string RO();

    string E();
    string E1();
    string T();
    string T1();
    string F();

    void Initializer();
    string Initializer2();

    string helper(string str);
    string update(vector<string> tokenE);
    
};

#endif

