#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include "tinyxml2.h"
#include "ADS_CA2_Tree.h"

using namespace std;
using namespace tinyxml2;

void test_validXML();
void test_invalidXML_missingClosingTag();
void test_invalidXML_mismatchedTags();

bool runTests() {
    test_validXML();
    test_invalidXML_missingClosingTag();
    test_invalidXML_mismatchedTags();
    

    cout << "All tests passed successfully." << endl;
    return true;
}

void test_validXML() {
    XMLDocument doc;
    doc.LoadFile("C:/Users/jamie/source/repos/Project1/valid.xml");
    assert(!doc.Error());

    TreeNode* root = new TreeNode("root", true);
    FileTree fileTree(root);
    stack<string> tags;

    bool isValid = validateAndParseXML(doc.FirstChildElement(), root, fileTree, tags);
    assert(isValid);
    assert(tags.empty());  // All tags should be closed

    // Cleanup
    delete root;
}

void test_invalidXML_missingClosingTag() {
    XMLDocument doc;
    doc.LoadFile("C:/Users/jamie/source/repos/Project1/missing_closing_tag.xml");
    assert(!doc.Error());

    TreeNode* root = new TreeNode("root", true);
    FileTree fileTree(root);
    stack<string> tags;

    bool isValid = validateAndParseXML(doc.FirstChildElement(), root, fileTree, tags);
    assert(!isValid);  // Should be invalid due to missing closing tag

    // Cleanup
    delete root;

}

void test_invalidXML_mismatchedTags() {
    XMLDocument doc;
    doc.LoadFile("C:/Users/jamie/source/repos/Project1/mismatched_tags.xml");
    assert(!doc.Error());

    TreeNode* root = new TreeNode("root", true);
    FileTree fileTree(root);
    stack<string> tags;

    bool isValid = validateAndParseXML(doc.FirstChildElement(), root, fileTree, tags);
    assert(!isValid);  // Should be invalid due to mismatched tags

    // Cleanup
    delete root;

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
            TreeNode* found = nullptr;  
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