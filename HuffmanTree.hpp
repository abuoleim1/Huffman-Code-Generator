//layalie abuoleim
//header file for HuffmanTree.cpp U60659634

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <stack>
#include <string>
#include <iostream>
#include <iterator>

#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_


class HuffmanTree: public HuffmanTreeBase{

    public:
        std::string compress(const std::string inputStr);
        std::string serializeTree() const;;
        void char_code(std::string str,std::map<char,std::string> &serial, HuffmanNode* root); 
        //helper function for compression
        void PostOrderTraverse(HuffmanNode *root); 
        //helper function for serlize

    private:
            std::string ser_string = ""; 
            // universal serilized string
            std::string code_string = ""; 
            // universal binary code string


}

#endif