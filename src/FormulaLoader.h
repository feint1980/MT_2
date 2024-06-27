#pragma once


#include <iostream>

#include <math.h>
#include <string>
#include <stack>
#include <vector>


#define A 3
#define B 4
#define C 2

enum Operator{
    NONE,
    ADD,
    SUB,
    MUL,
    DIV,
    SQRT,
    COS, 
    SIN
};


struct clause
{
    clause(const std::string & _data, int index) : data(_data), originalIndex(index) {}
    std::string data;
    int originalIndex = -1;
};


struct operationSign
{
    operationSign(char _sign, int _index) : sign(_sign), index(_index) {}
    char sign = ' ';
    int index = -1;
};


struct Node {

    //void processClauses(const std::string & data)
    void parseData(const std::string & data)
    {
        // data is a string of a fomula defined by user
        // from the data string 
        
        std::cout << "start parsing data : " << data << "\n";


        std::string processData = data;
        std::vector<int> removeIndicies;
        // remove whitespace
        for(int i = 0; i < processData.size(); ++i)
        {
            if(processData[i] == ' ')
            {
                removeIndicies.push_back(i);
            }
        }
        for(int i = 0; i < removeIndicies.size(); ++i)
        {
            processData.erase(removeIndicies[i] - i, 1);
        }

        std::cout << "after process " << processData << "\n";


        int openCracketCount = 0;
        int closeCracketCount = 0;
        bool isSpecialMath = false;
        for(int i = 0; i < processData.size(); ++i)
        {

            
            if(processData[i] == '(')
            {
                int foundIndex = i ;
                if(i > 3 )
                {
                    // check if before the '(' is cos or sin 
                    // if yes, then pushback the letter c(cos) or s(sin)
                    std::string cutprocessData = processData.substr(i - 3, 3);
                    if(cutprocessData == "cos" || cutprocessData == "sin")
                    {
                        foundIndex = i - 3;
                        isSpecialMath = true;
                    }
                    
                }
                bracketStack.push(foundIndex);
                openCracketCount++;

            }
            else if(processData[i] == ')')
            {
                std::string tClause = processData.substr(bracketStack.top(), i - bracketStack.top() + 1);
                std::cout << "tClause : " << tClause << "\n";

                bracketStack.pop();
                clauseStack.push(clause(tClause, i));
                closeCracketCount++;
                if(bracketStack.empty())
                {
                    clauses.push_back(clauseStack);
                    while(!clauseStack.empty())
                    {
                        clauseStack.pop();
                    }
                }
            }
        }
        // first rule, open bracket should be equal to close bracket
        if (openCracketCount != closeCracketCount)
        {
            std::cout << "parse error !!! \n";
            return;
        }

        std::cout << "total clauses found : " << clauses.size() << "\n";

        int middleOperator = 0;
        if(clauses.size() >= 2)
        {    
            auto copyClauseStack = clauses;

            for(int i = 0; i < copyClauseStack.size(); ++i)
            {
                std::cout << "clause " << i + 1 << ":\n";
                int tab = 0;
                while(!copyClauseStack[i].empty())
                {
                    for(int j = 0; j < tab; ++j)
                    {
                        std::cout << "\t";
            
                    }
                    std::cout << copyClauseStack[i].top().data << "\n";
                    copyClauseStack[i].pop();
                    tab++;
                }
                
            }
            // find the operators among the clauses
          

            std::vector<operationSign> operatorSignsLocation;
            std::cout << "process \n";
            for(int i = 0; i < clauses.size() -1; ++i)
            {
                std::cout << "checking " << i << "\n";
                //std::cout << clauses[i].top().data << "\n";
                clause firstClause = clauses[i].top();
                int start = firstClause.originalIndex;
                std::string tOp = processData.substr(start + 1,1);
                operatorSignsLocation.emplace_back(operationSign(tOp[0], start+1));
                std::cout << "operator : " << tOp << "\n";
            }

                // look for * and / first
            for(int i = 0; i < operatorSignsLocation.size(); ++i)
            {
                if (operatorSignsLocation[i].sign == '*' || operatorSignsLocation[i].sign == '/')
                {
                    middleOperator = operatorSignsLocation[i].index;
                    break;
                }
            }
            // overwrite the middle operator if there is + or - (math things)
            for(int i = 0; i < operatorSignsLocation.size(); ++i)
            {
                if (operatorSignsLocation[i].sign == '+' || operatorSignsLocation[i].sign == '-')
                {
                    middleOperator = operatorSignsLocation[i].index;
                    break;
                }
            }
            
            std::cout << "middle operator : " << middleOperator << "\n";
            std::cout << processData.substr(middleOperator, 1) << "\n";

            char middleOperatorChar = processData[middleOperator];
            if(middleOperatorChar == '+')
            {
                op = ADD;
            }
            else if(middleOperatorChar == '-')
            {
                op = SUB;
            }
            else if(middleOperatorChar == '*')
            {
                op = MUL;
            }
            else if(middleOperatorChar == '/')
            {
                op = DIV;
            }

            std::string leftClause = processData.substr(0, middleOperator);
            std::string rightClause = processData.substr(middleOperator + 1, processData.size() - middleOperator );
            std::cout << "left clause : " << leftClause << "\n";
            std::cout << "right clause: " << rightClause << "\n";

            left = new Node();
            right = new Node();
            left->parseData(leftClause);
            right->parseData(rightClause);
        }
        else
        {
           
            std::vector<operationSign> operatorSignsLocation;
            std::cout << "process \n";

            std::string singleClause = clauses[0].top().data;
            std::cout << "single clause : " << singleClause << "|\n";
            for(int i = 0; i < singleClause.size(); ++i)
            {
                // find * and / first
                if (singleClause[i] == '*' || singleClause[i] == '/')
                {
                    middleOperator = i;
                    break;
                    
                }
                if(singleClause[i] == '+' || singleClause[i] == '-')
                {
                    std::cout << "overwrite middle operator !!!!! \n";
                    middleOperator = i;
                    break;
                }
            }


            if(middleOperator == 0)
            {
                if(!isSpecialMath)
                {

                
                    std::cout << "no more operator found !!!!!!!!!! \n";
                    std::string strValue = singleClause.substr(1, singleClause.size() - 2);
                    std::cout << "strValue is : " << strValue << "\n";
                    if(strValue == "a")
                    {
                        
                        value = A;
                        std::cout << "a value found \n";
                        std::cout << "value is : " << value << "\n";
                    }
                    else if(strValue == "b")
                    {
                        value = B;
                        std::cout << "b value found \n";
                        std::cout << "value is : " << value << "\n";
                    }
                    else if(strValue == "c")
                    {
                        value = C;
                        std::cout << "c value found \n";
                        std::cout << "value is : " << value << "\n";
                    }
                    else
                    {
                        value = std::stof(strValue);
                    }
                }
                else
                {
                    std::cout << "special math found \n";
                    int is_cos_sin = 0;
                    // if keyword cos found in the clause
                    if(singleClause.find("cos") != std::string::npos)
                    {
                        is_cos_sin = 1;

                      
                    }
                    else if(singleClause.find("sin") != std::string::npos)
                    {
                        is_cos_sin = 2;
                    }
                    else if (singleClause.find("tan") != std::string::npos)
                    {
                        is_cos_sin = 3;
                    }
                    std::string strValue = singleClause.substr(5, singleClause.size() - 7);
                    std::cout << "strValue special math : " << strValue << "\n";
                    
                    if(strValue == "a")
                    {
                        
                        value = A;
                        std::cout << "a value found \n";
                        std::cout << "value is : " << value << "\n";
                    }
                    else if(strValue == "b")
                    {
                        value = B;
                        std::cout << "b value found \n";
                        std::cout << "value is : " << value << "\n";
                    }
                    else if(strValue == "c")
                    {
                        value = C;
                        std::cout << "c value found \n";
                        std::cout << "value is : " << value << "\n";
                    }
                    else
                    {
                        value = std::stof(strValue);
                    }

                    if(is_cos_sin == 1)
                    {
                        value = std::cos(value);
                    }
                    else if(is_cos_sin == 2)
                    {
                        value = std::sin(value);
                    }
                    else if(is_cos_sin == 3)
                    {
                        value = std::tan(value);
                    }

                    //value = std::stof(strValue);
                }
            }
            else 
            {

                char middleOperatorChar = singleClause[middleOperator];
                std::cout << "middle operator char : " << middleOperatorChar << "\n";
                if(middleOperatorChar == '+')
                {
                    op = ADD;
                }
                else if(middleOperatorChar == '-')
                {
                    op = SUB;
                }
                else if(middleOperatorChar == '*')
                {
                    op = MUL;
                }
                else if(middleOperatorChar == '/')
                {
                    op = DIV;
                }

                std::string leftClause = singleClause.substr(1, middleOperator - 1); // left out the opening bracket
                std::string rightClause = singleClause.substr(middleOperator + 1, singleClause.size() - leftClause.size());
                rightClause = rightClause.substr(0, rightClause.size() - 1); // left out the closing bracket
                bool isLast = rightClause.size() == 0;
                if(isLast)
                {
                    leftClause = leftClause.substr(0, leftClause.size() - 1);
                }
                std::cout << "left clause : " << leftClause << "\n";
                std::cout << "right clause: " << rightClause << "\n";   

                left = new Node();  
                left->parseData( "(" + leftClause + ")");
                if(!isLast)
                {
                    right = new Node();
                    right->parseData("("+rightClause +")");
                }
              
            }
         
        }


        std::cout << "parse OK !!! \n";
    }

    void processClauses(const std::string & data)
    {
       int first = data.find_first_of('(');
       int last = data.find_last_of(')');

    }

    std::vector<std::stack <int>> bracketStackVector;
    std::stack <int> bracketStack;
    std::stack<clause> clauseStack;
    std::vector<std::stack<clause>> clauses;
    
    float value = 0.0;
    Node * left;
    Node * right;
    Operator op = NONE;

    float getValue() {
        //std::cout << "get value called \n";
        std::cout << "value before add : " << value << "\n";
        switch (op) {
            case ADD:
                std::cout << "add value called \n";
                return value + (left->getValue() + right->getValue());
            case SUB:
                std::cout << "sub value called \n";
                return value +  (left->getValue() - right->getValue());
            case MUL: 
                std::cout << "mul value called \n";
                return value +  (left->getValue() * right->getValue());
            case DIV:   
                std::cout << "div value called \n";
                return value +  (left->getValue() / right->getValue());
            default:
                std::cout << "default value called \n";
                return value;
        }
       // std::cout << "value after add : " << value << "\n";
    }   

};


class FormulaLoader
{

public:
    FormulaLoader();
    ~FormulaLoader();

    void parseData(const std::string & data);



private : 
    Node * root = nullptr;

};