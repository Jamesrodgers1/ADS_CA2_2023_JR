#ifndef ADS_CA2_TREE_H
#define ADS_CA2_TREE_H

#include <string>
#include <vector>
#include <stack>
#include <queue> 
#include "tinyxml2.h"

class TreeNode {
public:
    std::string name;
    bool isFolder;
    std::vector<TreeNode*> children;
    int size; // Size in bytes for files, not used for folders

    TreeNode(const std::string& name, bool folder, int size = 0);
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
    void addNode(const std::string& parentFolder, const std::string& name, bool isFolder, int size = 0);
    TreeNode* getNode(const std::string& name);
    void listAll(TreeNode* node, int level = 0);
    TreeNode* search(TreeNode* node, const std::string& name);
    void displayTree();
    int calculateFolderSize(const std::string& folderName);
    int calculateFolderSizeBFS(const std::string& folderName);
    int countItemsInFolder(const std::string& folderName);

    // Placeholder for XML validation and parsing
    bool validateAndParseXML(tinyxml2::XMLElement* element, TreeNode* parentNode, FileTree& fileTree, std::stack<std::string>& tags);
};

#endif // ADS_CA2_TREE_H