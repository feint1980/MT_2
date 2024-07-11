
#include <iostream>

#include "FormulaLoader.h"
//#include <taskflow/taskflow.hpp>
#include <fstream>
#include "AST_Node.h"

int main()
{

    std::string fomula;// = "(a + 2 * b) / ( cos(b)  * 2 * b)";
    FILE * file = fopen("fomula.txt", "r");

    if (file == NULL)
    {
        std::cout << "error";
    }

    char buff[1024];
    while (fgets(buff, 1024, file))
    {
        fomula += buff;
    }

    std::vector<float> factors;

    factors.push_back(3.0);
    factors.push_back(4.0);
    factors.push_back(2.0);
    factors.push_back(6.0);


    Feintgine::AST_Node * ast_node = new Feintgine::AST_Node();

    ast_node->setFactors(factors);
    float t = 0.1;
    float r = 45.0;
    float * t_value = &t;
    ast_node->setTvalue(t_value);
    ast_node->setRvalue(&r);
    ast_node->parseData(fomula);

    //Node * node = new Node();
    //node->parseData(fomula);
    //std::cout << node->getValue();


    // *t_value = 0.50f;

    // std::cout << t << "\n";
    std::cout << ast_node->getValue() << "\n";
    //t= 15.1f;

    //ast_node->setValue('a', 10.0f);

        //std::cout << *t_value << "\n";
    for(int i = 0 ; i < 10 ; i ++)
    {

        t += 0.1f;
         std::cout << ast_node->getValue() << "\n";
    }

       //std::cout << ast_node->getTvalue() << "\n";


    std::cin.get();

    return 0;
}