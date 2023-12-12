#include <iostream>
#include <string>
#include <stack>
#include "ADS_CA2_Tree.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main() {
    XMLDocument doc;
    doc.LoadFile("valid.xml");

    if (doc.Error()) {
        cerr << "Error loading XML file: " << doc.ErrorStr() << endl;
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


    delete root;

    return 0;
}