#include <string>
#include <vector>
#include <iostream>
#include "tinyxml2.h"
#include <stack>

using namespace std;
using namespace tinyxml2;


class TreeNode {
public:
    std::string name;
    bool isFolder; // Flag to identify if it's a folder
    std::vector<TreeNode*> children; // List of children for a folder

    TreeNode(std::string name, bool folder) : name(name), isFolder(folder) {}

    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

class FileTree {
private:
    TreeNode* root;

    TreeNode* findNode(TreeNode* node, const std::string& name) {
        if (node->name == name) {
            return node;
        }
        for (TreeNode* child : node->children) {
            TreeNode* found = findNode(child, name);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;

    }
    void display(TreeNode* node, int level = 0) {
        if (!node) return;
        cout << string(level, ' ') << (node->isFolder ? "[Folder] " : "[File] ") << node->name << endl;
        for (auto child : node->children) {
            display(child, level + 4);
        }
    }


public:
    FileTree(TreeNode* rootNode) : root(rootNode) {}

    ~FileTree() {
        delete root;
    }

    void addNode(const std::string& parentFolder, const std::string& name, bool isFolder) {
        TreeNode* parentNode = findNode(root, parentFolder);
        if (parentNode != nullptr && parentNode->isFolder) {
            TreeNode* newNode = new TreeNode(name, isFolder);
            parentNode->children.push_back(newNode);
        }
    }
    TreeNode* getNode(const std::string& name) {
        return findNode(root, name);
    }
    void displayTree() {
        display(root);
    }
};

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
            // This is a file (no children)
            fileTree.addNode(parentNode->name, name, false);
        }

        element = element->NextSiblingElement();
    }
    return true; // Successfully validated and parsed
}


int main() {
    XMLDocument doc;
    doc.LoadFile("data.xml");

    if (doc.Error()) {
        cout << "Error loading XML file." << endl;
        return -1;
    }

    TreeNode* root = new TreeNode("root", true);
    FileTree fileTree(root);
    stack<string> tags;

    if (validateAndParseXML(doc.FirstChildElement(), root, fileTree, tags)) {
        if (!tags.empty()) {
            cout << "Invalid XML: Missing closing tags." << endl;
        }
        else {
            fileTree.displayTree(); // Display the tree if XML is valid
        }
    }
    else {
        cout << "Invalid XML structure." << endl;
    }

    return 0;
}