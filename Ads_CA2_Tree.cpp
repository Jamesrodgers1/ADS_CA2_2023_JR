#include <string>
#include <vector>
#include <iostream>
#include "tinyxml2.h"
#include <stack>
#include "ADS_CA2_Tree.h"
#include "test.cpp"

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
            // This is a file (no children)
            fileTree.addNode(parentNode->name, name, false);
        }

        element = element->NextSiblingElement();
    }
    return true; // Successfully validated and parsed
}


int main() {

        if (!runTests()) {
            cerr << "Tests failed. Exiting." << endl;
            return -1;
        }

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
            TreeNode* found = nullptr;  // Declare 'found' outside the switch
            int choice;
            do {
                cout << "1. List All Files/Folders" << endl;
                cout << "2. Search" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string searchQuery;
                switch (choice) {
                case 1:
                    fileTree.listAll(root);
                    break;
                case 2:
                    cout << "Enter name to search for: ";
                    getline(cin, searchQuery);
                    found = fileTree.search(root, searchQuery);  // Assign to 'found'
                    if (found) {
                        cout << "Found: " << found->name << endl;
                    }
                    else {
                        cout << "Not found." << endl;
                    }
                    break;
                case 3:
                    cout << "Exiting." << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            } while (choice != 3);
        }
    }
    else {
        cout << "Invalid XML structure." << endl;
    }

    // Clean up dynamically allocated memory.
    delete root;

    return 0;
}