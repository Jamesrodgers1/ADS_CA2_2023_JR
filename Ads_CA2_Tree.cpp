#include "ADS_CA2_Tree.h"
#include "tinyxml2.h"
#include <iostream>

// TreeNode functions
TreeNode::TreeNode(const std::string& name, bool folder, int size)
    : name(name), isFolder(folder), size(size), children() {
    // Constructor logic
}

TreeNode::~TreeNode() {
    for (auto* child : children) {
        delete child;
    }
}

// FileTree functions
FileTree::FileTree(TreeNode* rootNode) : root(rootNode) {
    // Constructor logic
}

FileTree::~FileTree() {
    delete root;
}

TreeNode* FileTree::findNode(TreeNode* node, const std::string& name) {
    // Logic to find a node
    if (node == nullptr) return nullptr;
    if (node->name == name) return node;

    for (auto* child : node->children) {
        TreeNode* result = findNode(child, name);
        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}

void FileTree::display(TreeNode* node, int level) {
    if (node == nullptr) return;

    std::cout << std::string(level * 2, ' ') << node->name << std::endl;
    for (auto* child : node->children) {
        display(child, level + 1);
    }
}

void FileTree::addNode(const std::string& parentFolder, const std::string& name, bool isFolder, int size) {
    TreeNode* parentNode = findNode(this->root, parentFolder);
    if (parentNode && parentNode->isFolder) {
        TreeNode* newNode = new TreeNode(name, isFolder, size);
        parentNode->children.push_back(newNode);
    }
    else {
        std::cerr << "Parent folder not found or is not a folder: " << parentFolder << std::endl;
    }
}

TreeNode* FileTree::getNode(const std::string& name) {
    return findNode(root, name);
}

void FileTree::listAll(TreeNode* node, int level) {
    display(node, level);
}

TreeNode* FileTree::search(TreeNode* node, const std::string& name) {
    return findNode(node, name);
}

void FileTree::displayTree() {
    display(root, 0);
}

int FileTree::calculateFolderSize(const std::string& folderName) {
    // implementation
}

int FileTree::countItemsInFolder(const std::string& folderName) {
    // implementation
}
bool FileTree::validateAndParseXML(tinyxml2::XMLElement* element, TreeNode* parentNode, FileTree& fileTree, std::stack<std::string>& tags) {
    if (!element) return false;

    while (element) {
        std::string tagName = element->Value();
        std::string name = element->Attribute("name");
        bool isFolder = tagName == "folder";
        int size = isFolder ? 0 : std::atoi(element->Attribute("size"));

        if (tagName != "folder" && tagName != "file") {
            std::cerr << "Invalid tag: " << tagName << std::endl;
            return false;
        }

        if (name.empty()) {
            std::cerr << "Missing name attribute in " << tagName << std::endl;
            return false;
        }

        if (!isFolder && size <= 0) {
            std::cerr << "Invalid or missing size for file: " << name << std::endl;
            return false;
        }

        tags.push(tagName);

        TreeNode* newNode = new TreeNode(name, isFolder, size);
        parentNode->children.push_back(newNode);

        if (isFolder) {
            if (!validateAndParseXML(element->FirstChildElement(), newNode, fileTree, tags)) {
                return false;
            }

            if (tags.top() != "folder") {
                std::cerr << "Tag mismatch. Expected closing tag for folder." << std::endl;
                return false;
            }

            tags.pop();
        }

        element = element->NextSiblingElement();
    }

    return true;
}

int FileTree::calculateFolderSizeBFS(const std::string& folderName) {
    TreeNode* startNode = getNode(folderName);
    if (!startNode || !startNode->isFolder) {
        return -1; // Return -1 if not a folder or node not found
    }

    std::queue<TreeNode*> queue;
    queue.push(startNode);

    int totalSize = 0;
    while (!queue.empty()) {
        TreeNode* currentNode = queue.front();
        queue.pop();

        if (!currentNode->isFolder) {
            totalSize += currentNode->size;
        }

        for (auto* child : currentNode->children) {
            queue.push(child);
        }
    }

    return totalSize;
}
