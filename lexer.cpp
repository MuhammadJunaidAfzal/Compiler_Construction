#include "lexer.h"
#include<fstream>
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE"
    "EQ",
    "GT",
    "LT",
    "GTEQ",
    "LTEQ",
    "NT",
    "NTEQ",
    "FUNC",
    "INT",
    "CHAR",
    "CALL",
    "IF",
    "ELIF",
    "ELSE",
    "FOR",
    "PRINT",
    "PRINTLN",
    "RETURN",
    "IN",
    "ASSIGNMENT",
    "BEGIN",
    "END",
    "ID",
    "NUMERIC",
    "STRING",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "MAIN",
    "SEMICOLON",
    "COLON",
    "COMMA",
    "ERROR"
};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType-1] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}

void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}
void lexer::Tokenize()//function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();

    //your implementation goes here
    while (it != stream.end())
    {
        if (*it == '#') // ignore comments till the end of line charcter occur
        {
            while (*it != '\n')
            {
                it++;
            }
        }
        else if (*it == ';')
        {
            tokens.push_back(token(string(";"), TokenType::SEMICOLON));
        }
        else if (*it == ':')
        {
            tokens.push_back(token(string(":"), TokenType::COLON));
        }
        else if (*it == ',')
        {
            tokens.push_back(token(string(","), TokenType::COMMA));
        }
        else if ((*it >= 'a' && *it <= 'z') || ( *it >= 'A' && *it <= 'Z') )
        {
            std::string temp;
            temp.push_back(*it);  // = string.valueOfchar(*it);
            it++;

            while ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || (*it >= '0' && *it <= '9'))
            {
                temp.push_back(*it);// = temp + string.valueOfchar(*it);

                it++;
            }
            //  cout << endl << temp << endl;
            if (temp == "func")
            {
                tokens.push_back(token(string(temp), TokenType::FUNC));
            }
            else if (temp == "int")
            {
                tokens.push_back(token(string(temp), TokenType::INT));
            }
            else if (temp == "char")
            {
                tokens.push_back(token(string(temp), TokenType::CHAR));
            }
            else if (temp == "if")
            {
                tokens.push_back(token(string(temp), TokenType::IF));
            }
            else if (temp == "elif")
            {
                tokens.push_back(token(string(temp), TokenType::ELIF));
            }
            else if (temp == "else")
            {
                tokens.push_back(token(string(temp), TokenType::ELSE));
            }
            else if (temp == "for")
            {
                tokens.push_back(token(string(temp), TokenType::FOR));
            }
            else if (temp == "print")
            {
                tokens.push_back(token(string(temp), TokenType::PRINT));
            }
            else if (temp == "println")
            {
                tokens.push_back(token(string(temp), TokenType::PRINT));
            }
            else if (temp == "return")
            {
                tokens.push_back(token(string(temp), TokenType::RETURN));
            }
            else if (temp == "in")
            {
                tokens.push_back(token(string(temp), TokenType::IN));
            }
            else if (temp == "begin")
            {
                tokens.push_back(token(string(temp), TokenType::BEGIN));
            }
            else if (temp == "end")
            {
                tokens.push_back(token(string(temp), TokenType::END));
            }
            else if (temp == "call")
            {
                tokens.push_back(token(string(temp), TokenType::CALL));
            }
            /*else if (temp == "main")
            {
                tokens.push_back(token(string(temp), TokenType::MAIN));
            }*/
            else
            {
                tokens.push_back(token(string(temp), TokenType::ID));
            }
            it--;

        // check keywords.
        // store the pair.
        }
        else if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))
        {
            std::string temp;
            temp.push_back(*it);  // = string.valueOfchar(*it);

            tokens.push_back(token(string(temp), TokenType::ID));
        }
        else if (*it == '\'')
        {
            it++;
            std::string temp;
            temp.push_back(*it);  // = string.valueOfchar(*it);
            it++;
           
            tokens.push_back(token(string(temp), TokenType::CHAR));
        }
        else if (*it == '"')
        {
            it++;
            std::string temp;
            //temp.push_back(*it);  // = string.valueOfchar(*it);
            while (*it != '"')
            {
                temp.push_back(*it);// = temp + string.valueOfchar(*it);
                it++;
            }
 
            tokens.push_back(token(string(temp), TokenType::STRING));
        }
        else if (*it >= '0' && *it <= '9')
        {
            std::string temp;
            temp.push_back(*it);  // = string.valueOfchar(*it);
            it++;

            while (*it >= '0' && *it <= '9')
            {
                temp.push_back(*it);// = temp + string.valueOfchar(*it);

                it++;
            }
            tokens.push_back(token(string(temp), TokenType::NUMERIC));
            it--;
        }
        else if (*it == '=')
        {
            tokens.push_back(token(string("="), TokenType::EQ));
        }
        else if (*it == '>')
        {
            it++;
            if (*it == '=')
            {
                tokens.push_back(token(string(">="), TokenType::GTEQ));
            }
            else
            {
                tokens.push_back(token(string(">"), TokenType::GT));
                it--;
            }
        }
        else if (*it == '<')
        {
            it++;
            if (*it == '=')
            {
                tokens.push_back(token(string("<="), TokenType::LTEQ));
            }
            else if (*it == '-')
            {
                tokens.push_back(token(string("<-"), TokenType::ASSIGNMENT));
            }
            else
            {
                tokens.push_back(token(string("<"), TokenType::LT));
                it--;
            }
        }
        else if (*it == '~')
        {
            it++;
            if (*it == '=')
            {
                tokens.push_back(token(string("~="), TokenType::NTEQ));
            }
            else
            {
                tokens.push_back(token(string("~"), TokenType::NT));
                it--;
            }
        }
        else if (*it == '+')
        {
            tokens.push_back(token(string("+"), TokenType::ADD));
        }
        else if (*it == '-')
        {
            tokens.push_back(token(string("-"), TokenType::SUB));
        }
        else if (*it == '*')
        {
            tokens.push_back(token(string("*"), TokenType::MUL));
        }
        else if (*it == '/')
        {
            tokens.push_back(token(string("/"), TokenType::DIV));
        }
        else if (*it == '%')
        {
            tokens.push_back(token(string("%"), TokenType::MOD));
        }

        it++;
    }
    //push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));

    //for (int k = 0; k < tokens.size(); k++)
    //{
    //    cout << " ( " << tokens[k].lexeme << " ,\n ";//<<p.tokenType<<"  )\n";
    //}
}
lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' ');//dummy spaces appended at the end
        stream.push_back(' ');  
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();

        generateSymbolTable();
        printSymbolTable();
        generateSymbolTableFile();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}

lexer lexer::copy(lexer& l1,lexer &l2)
{
    this->index= l2.index;

    for (auto itr = l2.stream.begin() ; itr != l2.stream.end();itr++)
    {
        l1.stream.push_back(*itr);   
    }
    for (auto itr = l2.tokens.begin(); itr != l2.tokens.end(); itr++)
    {
        l1.tokens.push_back(*itr);
    }

    return l1;
}
void lexer::generateSymbolTable()
{   
    for (auto itr = this->tokens.begin(); itr != tokens.end(); itr++)
    {
        if (itr.operator*().tokenType == TokenType::FUNC || itr.operator*().tokenType == TokenType::IN)
        {
            itr++;
        }
        else if (itr.operator*().tokenType == TokenType::ID)
        {
            SymbolTable temp;
            temp.identifer = itr.operator*().lexeme;
            itr++;
            if (itr.operator*().tokenType == TokenType::ASSIGNMENT)
            {
                itr++;
                if (itr.operator*().tokenType == TokenType::NUMERIC || itr.operator*().tokenType == TokenType::CHAR)
                {
                    temp.value = itr.operator*().lexeme;
                    int  count = 0;
                    while (itr != tokens.end())
                    {
                        if (itr.operator*().tokenType == TokenType::INT)
                        {
                            temp.type = "INT"; break;
                        }
                        else if (itr.operator*().tokenType == TokenType::CHAR)
                        {
                            temp.type = "CHAR"; break;
                        }
                        count++;
                       /* if (count == 10)
                        {
                            break;
                        }*/
                        itr++;
                    }
                    for (int k = 0; k < count-1; k++)
                    {
                        itr--;
                    }
                }
                itr--;
               // cout << itr.operator*().lexeme << endl;
                if (!checkInTable(temp.identifer))
                {
                    this->SymbolT.push_back(temp);
                }
            }
            else
            {
                temp.value = "0";
                int  count = 0;
                while (itr != tokens.end())
                {
                    if (itr.operator*().tokenType == TokenType::INT)
                    {
                        temp.type = "INT"; break;
                    }
                    else if (itr.operator*().tokenType == TokenType::CHAR)
                    {
                        temp.type = "CHAR"; break;
                    }
                    count++;
                  /*  if (count == 10)
                    {
                        break;
                    }*/
                    itr++;
                }
                for (int k = 0; k < count - 1; k++)
                {
                    itr--;
                }
                // cout << itr.operator*().lexeme << endl;
                if (!checkInTable(temp.identifer))
                {
                    this->SymbolT.push_back(temp);
                }
            }
            itr--;

            
        }
    }
}
void lexer::printSymbolTable()
{
    for (auto itr = this->SymbolT.begin(); itr != this->SymbolT.end(); itr++)
    {
        cout << itr.operator*().identifer << "\t " << itr.operator*().value << "\t " << itr.operator*().type << endl;
    }
    cout << endl << endl << endl << endl;
}
bool lexer::checkInTable(string str)
{
    for (auto itr = this->SymbolT.begin(); itr != this->SymbolT.end(); itr++)
    {
        if (itr.operator*().identifer == str)
        {
            return true;
        }
    }
    return false;
}
void lexer::generateSymbolTableFile()
{
    ofstream file;
    file.open("symbol_table.txt");

    for (auto itr = this->SymbolT.begin(); itr != this->SymbolT.end(); itr++)
    {
        file << itr.operator*().identifer << "\t " << itr.operator*().value << "\t " << itr.operator*().type << endl;
    }
    file.close();
}