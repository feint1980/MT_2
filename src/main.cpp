
#include <iostream>

#include "FormulaLoader.h"
//#include <taskflow/taskflow.hpp>
#include <fstream>

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

    Node * node = new Node();


    node->parseData(fomula);    

    std::cout << node->getValue();

    return 0;
}