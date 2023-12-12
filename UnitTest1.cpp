#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\jamie\source\repos\Project1\ADS_CA2_Tree.h"
#include <stack>
#include <string>
#include "C:\Users\jamie\source\repos\Project1\tinyxml2.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tinyxml2;

namespace UnitTest1
{
    TEST_CLASS(XMLTreeTests)
    {
    public:

        // Test valid XML
        TEST_METHOD(TestValidXML)
        {
            XMLDocument doc;
            doc.LoadFile("valid.xml"); 
            Assert::IsFalse(doc.Error(), L"XML Loading failed");

            TreeNode root("root", true);
            FileTree fileTree(&root);
            stack<string> tags;

            bool isValid = validateAndParseXML(doc.FirstChildElement(), &root, fileTree, tags);
            Assert::IsTrue(isValid, L"XML should be valid");
            Assert::IsTrue(tags.empty(), L"Tags stack should be empty");

            
        }

        // Test XML with missing closing tag
        TEST_METHOD(TestInvalidXMLMissingClosingTag)
        {
            XMLDocument doc;
            doc.LoadFile("missing_closing_tag.xml"); 
            Assert::IsFalse(doc.Error(), L"XML Loading failed");

            TreeNode root("root", true);
            FileTree fileTree(&root);
            stack<string> tags;

            bool isValid = validateAndParseXML(doc.FirstChildElement(), &root, fileTree, tags);
            Assert::IsFalse(isValid, L"XML should be invalid due to missing closing tag");
        }

        // Test XML with mismatched tags
        TEST_METHOD(TestInvalidXMLMismatchedTags)
        {
            XMLDocument doc;
            doc.LoadFile("mismatched_tags.xml"); 
            Assert::IsFalse(doc.Error(), L"XML Loading failed");

            TreeNode root("root", true);
            FileTree fileTree(&root);
            stack<string> tags;

            bool isValid = validateAndParseXML(doc.FirstChildElement(), &root, fileTree, tags);
            Assert::IsFalse(isValid, L"XML should be invalid due to mismatched tags");
        }

    };
}