#include "parser.h"
#include<string>
#include<fstream>
#include<vector>


void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    //t.Print();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    TAC.reserve(1000);
    _lexer = lexer(filename);
}
void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}
//this function is for sample purposes only
//
//bool parser::statements()
//{
//    //statements-- > COLON LPAREN start RPAREN
//    if (_lexer.peek(1).tokenType == TokenType::COLON)
//    {
//        expect(TokenType::COLON);
//        if (_lexer.peek(1).tokenType == TokenType::LPAREN)
//        {
//            expect(TokenType::LPAREN);
//            start();
//            if (_lexer.peek(1).tokenType == TokenType::RPAREN)
//            {
//                expect(TokenType::RPAREN);
//                return true;
//            }
//        }
//    }
//    return false;
//}

bool flag = true;

bool parser::start()
{
    if (_lexer.peek(1).tokenType == TokenType::FUNC)
    {
        expect(TokenType::FUNC);
        if (_lexer.peek(1).tokenType == TokenType::INT)
        {
            expect(TokenType::INT);
        }
        else 
        {
            expect(TokenType::CHAR);
        }
        expect(TokenType::ID);
        Initializer();
        expect(TokenType::COLON);
        expect(TokenType::BEGIN);

        Initializer();
        //EXP1();
        A();

        expect(TokenType::END);

        start();
    }
    if (flag)
    {
        ofstream file;
        file.open("TAC.txt");
        if (file.is_open())
        {
            for (int i = 0; i < TAC.size(); i++)
            {
                cout << " " << TAC[i] << endl;
                file << TAC[i] << endl;
            }
        }
        else
        {
            cout << "File not oppened";
        }
        file.close();

        flag = false;
    }
    return true;
}
void parser::A()
{
    string temp,temp1; 
    int if_start_index = 0, if_end = 0, elif_end = 0, jumpelse = 0;
    bool flag = true;
    bool elseflag = false;
    if (_lexer.peek(1).tokenType == TokenType::IF)
    {
        temp = to_string(n) + " " + "if ";
        expect(TokenType::IF);
        
        temp = temp + EXP1() + " goto " + to_string(n+2);
        n++; 
        TAC.push_back(temp);
        if_start_index = TAC.size();
        temp1 = to_string(n) + " " + "goto ";
        TAC.push_back(temp1);
        n++;

        expect(TokenType::COLON);
        expect(TokenType::BEGIN);
        A();
        expect(TokenType::END);
       
        if (_lexer.peek(1).tokenType != TokenType::ELIF)
        {
            if (_lexer.peek(1).tokenType == TokenType::ELSE)
            {
                TAC[if_start_index] = TAC[if_start_index] + " " + to_string(n+1);
                flag = false;
            }
            else
            {
                TAC[if_start_index] = TAC[if_start_index] + " " + to_string(n);
                flag = false;
            }
        }
        else  if (_lexer.peek(1).tokenType == TokenType::ELIF)
        {
            TAC[if_start_index] = TAC[if_start_index] + " " + to_string(n+1);
            
            elif_end = TAC.size();
            TAC.push_back(to_string(n) + " goto");
            n++;
        }
        if (_lexer.peek(1).tokenType == TokenType::ELSE) // if there is no elif, but else after if
        {
            elseflag = true;
            jumpelse = TAC.size();

        }
        B();
        if (flag == true)
        {
            TAC[elif_end] = TAC[elif_end] + " " + to_string(n);
            flag = false;
        }
        if (elseflag == true)
        {
            TAC[jumpelse] = TAC[jumpelse] + " " + to_string(n+1);
        }
        A();
    }
    else  if (_lexer.peek(1).tokenType == TokenType::FOR)
    {
        string temp, temp1, temp2 ,temp3;
        int if_start = 0, if_start_index = 0;
        
        expect(TokenType::FOR);
        
        temp = to_string(n)+ " " +  Initializer2();
        TAC.push_back(temp);
        n++;

        expect(TokenType::COMMA);
        temp1 = to_string(n) + " " + "if "; 
        temp1 = temp1 + EXP1() + " goto " + to_string(n + 2);   
        if_start = n;
        n++;
        TAC.push_back(temp1);

        if_start_index = TAC.size();
        temp1 = to_string(n) + " " + "goto ";
        TAC.push_back(temp1);

        n++;
        expect(TokenType::COMMA);
        
        temp2 = Initializer2();

        expect(TokenType::COLON);
        expect(TokenType::BEGIN);
        A();
        temp2 = to_string(n) + " " + temp2;
        TAC.push_back(temp2);
        n++;

        temp3 = to_string(n) + " goto " + to_string(if_start);
        TAC.push_back(temp3);
        n++;
        expect(TokenType::END);

        TAC[if_start_index] = TAC[if_start_index] + " " + to_string(n);
        A();
    }
    else if (_lexer.peek(1).tokenType == TokenType::PRINT)
    {
        expect(TokenType::PRINT);
        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            string temp = to_string(n)+ " " + "out " + _lexer.peek(1).lexeme + ";";
           // cout << temp << endl;
            TAC.push_back(temp);
            n++;
           // cout << "out " << _lexer.peek(1).lexeme << " \n";
            
            expect(TokenType::ID);
            expect(TokenType::SEMICOLON);

            A();
        }
        else if (_lexer.peek(1).tokenType == TokenType::STRING)
        {
            string temp = to_string(n) + " " + "out \"" + _lexer.peek(1).lexeme + "\";";
          //  cout << temp <<endl;
            TAC.push_back(temp);
            n++;
           // cout << "out " << _lexer.peek(1).lexeme << " \n";
            expect(TokenType::STRING);
            expect(TokenType::SEMICOLON);

            A();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        Initializer();
        A();
    }
    else if (_lexer.peek(1).tokenType == TokenType::IN)
    {
        expect(TokenType::IN);

        string temp = to_string(n) + " " + "in " + _lexer.peek(1).lexeme + ";";
     //   cout << temp << endl;
        TAC.push_back(temp);
        n++;
        expect(TokenType::ID);
        expect(TokenType::SEMICOLON);
      
        A();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RETURN)
    {
        expect(TokenType::RETURN);

        string temp1 = E();
        if(temp1.size()>=2)
        {
            temp1 = helper(temp1);
        }

        string temp = to_string(n) + " ret ";
        temp = temp + temp1 + ";";
        TAC.push_back(temp);
        n++;
       /* if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            expect(TokenType::ID);
        }
        else if (_lexer.peek(1).tokenType == TokenType::NUMERIC)
        {
            expect(TokenType::NUMERIC);
        }*/
        expect(TokenType::SEMICOLON);
    }
    else if (_lexer.peek(1).tokenType == TokenType::CALL)
    {
        expect(TokenType::CALL);

        string temp = to_string(n) + " call" + _lexer.peek(1).lexeme;
        expect(TokenType::ID);

        int parm = 0;
       
        do {
            if (_lexer.peek(1).lexeme == ",")
            {
                expect(TokenType::COMMA);
            }
            string temp2 = E();
            if (temp2.size() > 2)
            {
                temp2 = helper(temp2);
            }
            if (temp2 != "")
            {
                parm++;
                temp2 = to_string(n) + " parm " + temp2;
                TAC.push_back(temp2);
                n++;
            }
        } while (_lexer.peek(1).lexeme == ",");


        

        temp = temp +", "+ to_string(parm) + ", t" + to_string(index);
        index++;
        TAC.push_back(temp);
        n++;

        expect(TokenType::SEMICOLON);
        A();
    }
   
}
void parser::B()
{
    string temp, temp1, temp2;
    int if_start_index = 0, if_end = 0, else_ = 0;
    bool flag = true;

    if (_lexer.peek(1).tokenType == TokenType::ELIF)
    {
        temp = to_string(n) + " " + "if ";
        expect(TokenType::ELIF);
       // EXP1();
        temp = temp + EXP1() + " goto " + to_string(n + 2); // in case of successfull if statement (jump into if statement)
        n++;
        TAC.push_back(temp);
        temp1 = to_string(n) + " " + "goto ";

        if_start_index = TAC.size();
        TAC.push_back(temp1);

        n++;

        expect(TokenType::COLON);
        expect(TokenType::BEGIN);
        A();
      
        expect(TokenType::END);
        if_end = TAC.size();

        if (_lexer.peek(1).tokenType != TokenType::ELSE)
        {
           temp2 = " goto ";
            TAC.push_back(to_string(n) + temp2);
            n++;
        }
        if (_lexer.peek(1).tokenType != TokenType::ELSE)
        {
            TAC[if_start_index] = TAC[if_start_index] + " " + to_string(n); // to jump at if not successfull or (at the end of if statment)
        }
        else  if (_lexer.peek(1).tokenType == TokenType::ELSE)
        {
            TAC[if_start_index] = TAC[if_start_index] + " " + to_string(n + 1); // to jump at else part as it is the last option 
        }

        B();
        if (_lexer.peek(1).tokenType != TokenType::ELSE) // fixed
        {
            TAC[if_end] = TAC[if_end] + " " + to_string(n); // to jump after last elseif ot else
        }  
    }
    else
    {
        if (_lexer.peek(1).tokenType == TokenType::ELSE)
        {
            C();
        }
    }
}
void parser::C()
{
    string temp, temp1, temp2;
    int if_start_index = 0, if_end = 0;

    if (_lexer.peek(1).tokenType == TokenType::ELSE)
    {
        if_end = TAC.size();
        temp = " goto";
        TAC.push_back(to_string(n) + temp);
        n++;

        expect(TokenType::ELSE);
        expect(TokenType::COLON);
        expect(TokenType::BEGIN);
        A();
        expect(TokenType::END);
      //  TAC[if_end] = TAC[if_end] +" " +  to_string(n); // jump above else if it is not to be executed
    }
}

void parser::Initializer()
{
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        string temp = " " + _lexer.peek(1).lexeme + " = ";

        expect(TokenType::ID);

        if (_lexer.peek(1).tokenType == TokenType::ASSIGNMENT)
        {
            expect(TokenType::ASSIGNMENT);
           
            //E();
            string newtemp;
            string temp4 = E();
            if (temp4.size() >= 2)
            {
                newtemp = helper(temp4);
            }
            else
            {
                newtemp = temp4;
            }
            temp = to_string(n) + temp + newtemp + ";";
                  
            TAC.push_back(temp);
            this->n++;

            if (_lexer.peek(1).tokenType == TokenType::INT || _lexer.peek(1).tokenType == TokenType::CHAR)
            {
                if (_lexer.peek(1).tokenType == TokenType::INT)
                {
                    expect(TokenType::INT);
                }
                else
                {
                    expect(TokenType::CHAR);
                }
            }
            else if (_lexer.peek(1).tokenType == TokenType::COMMA)
            {
                expect(TokenType::COMMA);
            }
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                expect(TokenType::SEMICOLON);
            }
            Initializer();
        }   
        else if(_lexer.peek(1).tokenType == TokenType::INT || _lexer.peek(1).tokenType == TokenType::CHAR)
        {
            if (_lexer.peek(1).tokenType == TokenType::INT)
            {
                expect(TokenType::INT);
            }
            else
            {
                expect(TokenType::CHAR);
            }
            
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                expect(TokenType::SEMICOLON);
            }
            Initializer();
        }
        else if (_lexer.peek(1).tokenType == TokenType::COMMA)
        {
            expect(TokenType::COMMA);
            Initializer();
        }
    }
}

string parser::Initializer2()
{
    string temp, temp1;
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {

        temp = _lexer.peek(1).lexeme;
        expect(TokenType::ID);
        temp = temp + "=";
        expect(TokenType::ASSIGNMENT);

        temp1 = E();
        if (temp1.size() >= 2)
        {
            temp1 = helper(temp1);
        }
        temp = temp + temp1;
    }
    return temp;
}
string parser::EXP1()
{
    string temp, temp1, temp2;
    string newtemp, newtemp2;
    temp = E();
    temp1 = RO();
    temp2 = E();

    if (temp.size() > 2)
    {
        temp = newtemp = helper(temp);
    }
    if (temp2.size() > 2)
    {
        temp2 = newtemp2 = helper(temp2);
    }


    temp = temp + temp1 + temp2;

    return temp;
}
string parser::RO()
{
    string temp;
    if (_lexer.peek(1).tokenType == TokenType::EQ)
    {
        temp = _lexer.peek(1).lexeme;
        expect(TokenType::EQ);
    }
    else if (_lexer.peek(1).tokenType == TokenType::NTEQ)
    {
        temp = _lexer.peek(1).lexeme;
        expect(TokenType::NTEQ);
    }
    else if (_lexer.peek(1).tokenType == TokenType::GT)
    {
        temp = _lexer.peek(1).lexeme;
        expect(TokenType::GT);
    }
    else if(_lexer.peek(1).tokenType == TokenType::GTEQ)
    {
        temp = _lexer.peek(1).lexeme;
        expect(TokenType::GTEQ);
    }
    else if (_lexer.peek(1).tokenType == TokenType::LT)
    {
        temp = _lexer.peek(1).lexeme;
        expect(TokenType::LT);
    }
    else if (_lexer.peek(1).tokenType == TokenType::LTEQ)
    {
        temp = _lexer.peek(1).lexeme;
        expect(TokenType::LTEQ);
    }
    return temp;
}
string parser::E()
{
    string temp,temp1,temp2;

    temp1 = T(); 
    temp2 = E1();
    temp = temp1 + temp2;


    return temp;
}
string parser::T()
{
    string temp, temp1, temp2;

    temp1 = F(); 
    temp2 = T1();

    temp = temp1 + temp2;

    return temp;
}
string parser::E1()
{
    string temp, temp1, temp2;

    if (_lexer.peek(1).tokenType == TokenType::ADD)
    {
        expect(TokenType::ADD); 
        temp = "+";
        temp1 = T(); 
        temp2 = E1();
    }
    else if (_lexer.peek(1).tokenType == TokenType::SUB)
    {
        expect(TokenType::SUB);
        temp = "-";
        temp1 = T(); 
        temp2 = E1();
    }

    temp = temp + temp1 + temp2;
    return temp;
}
string parser::T1()
{
    string temp, temp1, temp2;

    if (_lexer.peek(1).tokenType == TokenType::MUL)
    {
        expect(TokenType::MUL); 
        temp = "*";
        temp1 = F(); 
        temp2 = T1();
    }
    else if (_lexer.peek(1).tokenType == TokenType::DIV)
    {
        expect(TokenType::DIV);
        temp = "/";
        temp1 = F(); 
        temp2 = T1();
    }
    temp = temp + temp1 + temp2;
    return temp;
}
string parser::F()
{
    string temp, temp1, temp2;
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        temp1 = _lexer.peek(1).lexeme;

        expect(TokenType::ID);
        
        temp2 = E();
    }
    else  if (_lexer.peek(1).tokenType == TokenType::NUMERIC)
    {
        temp1 = _lexer.peek(1).lexeme;
        
        expect(TokenType::NUMERIC);
        
        temp2 = E();
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHAR)
    {
        temp1 = _lexer.peek(1).lexeme;
        
        expect(TokenType::CHAR);
    }
    /*else
    {
        cout << "Bad Tokken";
    }*/
    temp = temp1 + temp2;
    return temp;
}
string parser::helper(string str) // this function tokenize the given expression
{
    vector<string> tokenE;

    int start = 0, end = 0;
    int i = 0, j = 0, k = 0;

    while (i < str.size())
    {
        string temp1;
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            temp1 = temp1 + str[i];
            tokenE.push_back(temp1);
            i++;
        }
        else
        {
            start = i; j = 0;
            while (i < str.size())
            {
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
                    break;
                i++; j++;
            }
            end = start + j;
            k = start; string temp;
            while (k < end)
            {
                temp = temp + str[k];
                k++;
            }
            i = end;
            tokenE.push_back(temp);
        }
    }
  /*  for (int i = 0; i < tokenE.size(); i++)
    {
        cout << tokenE[i] << endl;
    }*/
    string finalans;
   
    finalans = update(tokenE);
  
    return finalans;
}
string parser::update(vector<string> tokenE)  // this function splits the expression into smaller parts
{
    int i = 0;
    bool flag = true;

    flag = true;
    while (flag == true) // for / symbol
    {
        flag = false;
        while (tokenE.size() > 2 && i < tokenE.size())
        {
            if (tokenE[i] == "/")
            {
                string temp2 = "t" + to_string(index); index++;
                string temp = temp2 + "=";
                temp = temp + tokenE[i-1] + tokenE[i] + tokenE[i+1];

                tokenE[i] = temp2;
                tokenE[i-1] = "";
                tokenE[i+1] = "";

                TAC.push_back(to_string(this->n) + " " + temp);
                n++; flag = true;
                break; 
            }
            i++;
        }
        for (int jj = 0; jj < tokenE.size(); jj++)
        {
            if (tokenE[jj] == "")
            {
                int kk = 0;
                for (kk = jj; kk < tokenE.size() - 1; kk++)
                {
                    tokenE[kk] = tokenE[kk+1];
                }
                tokenE[kk] = "";
                tokenE.resize(tokenE.size() - 1);
            }
        }
    }
    
    flag = true; i = 0;
    while (flag == true) // for * symbol
    {
        flag = false;
        while (tokenE.size() > 2 && i < tokenE.size())
        {
            if (tokenE[i] == "*")
            {
                string temp2 = "t" + to_string(index); index++;
                string temp = temp2 + "=";
                temp = temp + tokenE[i - 1] + tokenE[i] + tokenE[i + 1];

                tokenE[i] = temp2;
                tokenE[i - 1] = "";
                tokenE[i + 1] = "";

                TAC.push_back(to_string(this->n) + " " + temp);
                n++; flag = true;
                break;
            }
            i++;
        }
        for (int jj = 0; jj < tokenE.size(); jj++)
        {
            if (tokenE[jj] == "")
            {
                int kk = 0;
                for (kk = jj; kk < tokenE.size() - 1; kk++)
                {
                    tokenE[kk] = tokenE[kk + 1];
                }
                tokenE[kk] = "";
                tokenE.resize(tokenE.size() - 1);
            }
        }
    }

    flag = true; i = 0;
    while (flag == true) // for + symbol
    {
        flag = false;
        while (tokenE.size() > 2 && i < tokenE.size())
        {
            if (tokenE[i] == "+")
            {
                string temp2 = "t" + to_string(index); index++;
                string temp = temp2 + "=";
                temp = temp + tokenE[i - 1] + tokenE[i] + tokenE[i + 1];

                tokenE[i] = temp2;
                tokenE[i - 1] = "";
                tokenE[i + 1] = "";

                TAC.push_back(to_string(this->n) + " " + temp);
                n++; flag = true;
                break;
            }
            i++;
        }
        for (int jj = 0; jj < tokenE.size(); jj++)
        {
            if (tokenE[jj] == "")
            {
                int kk = 0;
                for (kk = jj; kk < tokenE.size() - 1; kk++)
                {
                    tokenE[kk] = tokenE[kk + 1];
                }
                tokenE[kk] = "";
                tokenE.resize(tokenE.size() - 1);
            }
        }
    }

    flag = true; i = 0;
    while (flag == true) // for - symbol
    {
        flag = false;
        while (tokenE.size() > 2 && i < tokenE.size())
        {
            if (tokenE[i] == "-")
            {
                string temp2 = "t" + to_string(index); index++;
                string temp = temp2 + "=";
                temp = temp + tokenE[i - 1] + tokenE[i] + tokenE[i + 1];

                tokenE[i] = temp2;
                tokenE[i - 1] = "";
                tokenE[i + 1] = "";

                TAC.push_back(to_string(this->n) + " " + temp);
                n++; flag = true;
                break;
            }
            i++;
        }
        for (int jj = 0; jj < tokenE.size(); jj++)
        {
            if (tokenE[jj] == "")
            {
                int kk = 0;
                for (kk = jj; kk < tokenE.size() - 1; kk++)
                {
                    tokenE[kk] = tokenE[kk + 1];
                }
                tokenE[kk] = "";
                tokenE.resize(tokenE.size() - 1);
            }
        }
    }

    return tokenE[0];
}




