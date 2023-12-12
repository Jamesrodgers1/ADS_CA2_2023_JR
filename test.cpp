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
    doc.LoadFile("data.xml");
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
    doc.LoadFile("missing_closing_tag.xml");
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
    doc.LoadFile("mismatched_tags.xml");
    assert(!doc.Error());

    TreeNode* root = new TreeNode("root", true);
    FileTree fileTree(root);
    stack<string> tags;

    bool isValid = validateAndParseXML(doc.FirstChildElement(), root, fileTree, tags);
    assert(!isValid);  // Should be invalid due to mismatched tags

    // Cleanup
    delete root;

}