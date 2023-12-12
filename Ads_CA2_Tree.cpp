#include <string>
#include <vector>
#include <iostream>
#include "tinyxml2.h"
#include <stack>
#include "ADS_CA2_Tree.h"


using namespace std;
using namespace tinyxml2;


TreeNode::TreeNode(std::string name, bool folder) : name(name), isFolder(folder) {}

TreeNode::~TreeNode() {
    for (auto child : children) {
        delete child;
    }
}

// FileTree class method definitions
FileTree::FileTree(TreeNode* rootNode) : root(rootNode) {}

FileTree::~FileTree() {
    delete root;
}

void FileTree::addNode(const string& parentFolder, const string& name, bool isFolder) {
    TreeNode* parentNode = findNode(root, parentFolder);
    if (parentNode != nullptr && parentNode->isFolder) {
        TreeNode* newNode = new TreeNode(name, isFolder);
        parentNode->children.push_back(newNode);
    }
}

TreeNode* FileTree::getNode(const string& name) {
    return findNode(root, name);
}

void FileTree::listAll(TreeNode* node, int level) {
    if (!node) return;
    cout << string(level, ' ') << node->name << (node->isFolder ? "/" : "") << endl;
    for (auto child : node->children) {
        listAll(child, level + 2);
    }
}

TreeNode* FileTree::search(TreeNode* node, const string& name) {
    if (node->name == name) {
        return node;
    }
    for (auto child : node->children) {
        TreeNode* result = search(child, name);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

void FileTree::display(TreeNode* node, int level) {
    if (!node) return;
    cout << string(level, ' ') << (node->isFolder ? "[Folder] " : "[File] ") << node->name << endl;
    for (auto child : node->children) {
        display(child, level + 1);
    }
}

TreeNode* FileTree::findNode(TreeNode* node, const string& name) {
    if (node == nullptr) return nullptr;
    if (node->name == name) return node;
    for (auto child : node->children) {
        TreeNode* found = findNode(child, name);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

void FileTree::displayTree() {
    display(root, 0);
}


bool validateAndParseXML(XMLElement* element, TreeNode* parentNode, FileTree& fileTree, stack<string>& tags) {
    while (element != nullptr) {
        string name = element->Value();

        // Opening tag
        if (!element->NoChildren()) {
            tags.push(name);
            bool isFolder = true;
            fileTree.addNode(parentNode->name, name, isFolder);
            TreeNode* newParentNode = fileTree.getNode(name);

            // Recursively validate child nodes
            if (!validateAndParseXML(element->FirstChildElement(), newParentNode, fileTree, tags)) {
                return false; // Invalid XML
            }

            // Closing tag
            if (tags.empty() || tags.top() != name) {
                return false; // Invalid XML: Mismatched tag or improper nesting
            }
            tags.pop();
        }
        else {
            
            fileTree.addNode(parentNode->name, name, false);
        }

        element = element->NextSiblingElement();
    }
    return true; // Successfully validated and parsed
}
