#pragma once


#include <iostream>

#include <math.h>
#include <string>
#include <stack>
#include <vector>
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
        if(clauses.size() >= 2)
        {

            std::cout << "process \n";
            for(int i = 0; i < clauses.size() -1; ++i)
            {
                std::cout << "checking " << i << "\n";
                //std::cout << clauses[i].top().data << "\n";
                clause firstClause = clauses[i].top();
                int start = firstClause.originalIndex;
                std::string tOp = processData.substr(start + 1,1);
                std::cout << "operator : " << tOp << "\n";
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
    
    float value = 0;
    Node * left;
    Node * right;
    Operator op = NONE;

    float getValue() {
        switch (op) {
            case ADD:
                return left->getValue() + right->getValue();
            case SUB:
                return left->getValue() - right->getValue();
            case MUL: 
                return left->getValue() * right->getValue();
            case DIV:   
                return left->getValue() * right->getValue();
            case SQRT:
                return sqrt(left->getValue());
            case COS:
                return cos(left->getValue());
            case SIN:
                return sin(left->getValue());
            default:
                return value;
        }
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