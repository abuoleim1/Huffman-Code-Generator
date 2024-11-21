//layalie abuoleim u60659634
#include "HuffmanTree.hpp"

std::string HuffmanTree::compress(const std::string inputStr){
    //map that takes in string to get characters and frequencies
    std::map<char,int> char_freq;
    //gets characters and their frequencies in the string
    //avoids warnings
    int fixed=inputStr.size();
    
    //loop to fill the map of characters and their frequencies
    for(int i=0;i<fixed;i++){
        int freq = fixed - i;
        for(int j = i + 1; j < fixed; j++){
            if(inputStr[i] != inputStr[j]){
                freq--;
            }
        }
        char_freq.insert(std::pair<char, int>(inputStr[i], freq));
    }
    //the priority queue that the values from map are stored in
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pri_que; 
    //iterator to navigate through the map
    std::map<char, int>::iterator itr; 
    //for loop to fill the priority queue
    for(std::map<char, int>::iterator itr = char_freq.begin(); itr!= char_freq.end(); itr++) {

        HuffmanNode* now = new HuffmanNode(itr->first, itr->second);
        pri_que.insert(now);
    }

    //removing from priority queue and making nodes for binary search tree
    while(pri_que.size() != 1){ //runs until there is only one node in the priority queue
    
        //remove from priority queue in groups of two smallest
        HuffmanNode *lnode = pri_que.min(); //smallest
        pri_que.removeMin();
        HuffmanNode *rnode = pri_que.min(); //second smallest
        pri_que.removeMin();

        //creation of intermediate node that holds sum of two smallest nodes frequency
        int sum;
        sum = rnode->getFrequency() + lnode->getFrequency();
        HuffmanNode *Bnode = new HuffmanNode('\0', sum, NULL, lnode, rnode);
        pri_que.insert(Bnode);

        //making two smallest nodes children of intermediate node created 
        lnode->parent = Bnode;
        rnode->parent = Bnode;
    }

    //connecting the queue
    HuffmanNode* tree = pri_que.min();
    //calling the PostOrderTraverse function that will fill the serlize string
    PostOrderTraverse(tree);
    
    //creating the binary code string
    std::map<char, std::string> serial_map;
    char_code(code_string,serial_map,tree);

    // filling code in the univeral variable
    for(auto itr = inputStr.begin(); itr != inputStr.end(); itr++){ 

        code_string += serial_map[*itr];
    }
    
    return code_string;
}

// this function only returns the universal variable because that variable was manipulated in the compress function
std::string HuffmanTree::serializeTree() const{
    return ser_string;
}

// given a code string and a serialized string, this fucntion decompresses it
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){

    // creating a tree using a stack
    std::stack<HuffmanNode*> treeStack;
    std::string decompressed = "";

    // creating a tree out of the serial string
    for(int i = 0; i < int(serializedTree.size()); i++){
        
        // same process as compress but reversed
        if (serializedTree[i] == 'B'){
            HuffmanNode* lnode = treeStack.top();
            treeStack.pop();
            HuffmanNode* rnode = treeStack.top();
            treeStack.pop();

            HuffmanNode* bnode = new HuffmanNode('\0', 0, nullptr, rnode, lnode);
            treeStack.push(bnode);
        }
        
        // if we see an L add the next char to the tree
        if(serializedTree[i] == 'L'){
            i++;
            HuffmanNode* leafNode = new HuffmanNode(serializedTree[i], 0);
            treeStack.push(leafNode);
        }

    }

    //keeping track of the tree's root
    HuffmanNode* root =  treeStack.top();
    HuffmanNode* backToRoot = root;

    // for loop to use the code to interate through the serilized tree
    for (int i = 0; i < int(inputCode.size()); i++){
        
        //if we see a zero, take a left
        if(inputCode[i] == '0'){
            root = root -> left;
        }
        //if we see a one, take a right
        if(inputCode[i] == '1'){
            root = root -> right;
        }

        // when we get to a leaf, record the char in the decompressed string
        if(root->isLeaf()){
            decompressed += root->getCharacter();
            root = backToRoot; //go back to the root of the tree
        }
    }
    return decompressed;
}

// function that turns charafcters into binary code
void HuffmanTree::char_code(std::string str,std::map<char,std::string> &serial, HuffmanNode* tree){
    if (tree==nullptr) return; //stop when we go through the whole tree
    if (tree->isLeaf()) serial[tree->getCharacter()]=str;

    //recursively records a zero for a left and a one for a right
    char_code(str+"0",serial,tree->left);
    char_code(str+"1",serial,tree->right);
}

// function that recursively go through the tree to creat a serilized string
void HuffmanTree::PostOrderTraverse(HuffmanNode *tree){
    if(tree == NULL){
        return;
    }

    // recursive calling
    HuffmanTree::PostOrderTraverse(tree->left); 
    HuffmanTree::PostOrderTraverse(tree->right);

    // if branch add a B
    if(tree->isBranch()){
        ser_string += "B";
    }
    // if leaf, add a L and the char
    if(tree->isLeaf()){
        ser_string += "L";
        ser_string += tree->getCharacter();
    }
}

// void delete_tree(HuffmanNode *t_node){
//     if (t_node == NULL){
//         return;
//     }
//     delete_tree(t_node->left);
//     delete_tree(t_node->right);
//     delete t_node;
// }




