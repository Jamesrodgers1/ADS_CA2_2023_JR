#ifndef ADS_CA2_TREE_H
#define ADS_CA2_TREE_H

#include <string>
#include <vector>
#include "tinyxml2.h"
#include <stack>

class TreeNode {
public:
    std::string name;
    bool isFolder;
    std::vector<TreeNode*> children;

    TreeNode(std::string name, bool folder);
    ~TreeNode();
};

class FileTree {
private:
    TreeNode* root;

    TreeNode* findNode(TreeNode* node, const std::string& name); 
    void display(TreeNode* node, int level = 0);

public:
    FileTree(TreeNode* rootNode);
    ~FileTree();
    void addNode(const std::string& parentFolder, const std::string& name, bool isFolder);
    TreeNode* getNode(const std::string& name);
    void listAll(TreeNode* node, int level = 0);
    TreeNode* search(TreeNode* node, const std::string& name);
    void displayTree();
    
};

bool validateAndParseXML(tinyxml2::XMLElement* element, TreeNode* parentNode, FileTree& fileTree, std::stack<std::string>& tags);


bool runTests();

#endif // ADS_CA2_TREE_H