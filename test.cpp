#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


int main() {
    test_validXML();
    test_invalidXML_missingClosingTag();
    test_invalidXML_mismatchedTags();
    

    cout << "All tests passed successfully." << endl;
    return 0;
}

void test_validXML() {

}

void test_invalidXML_missingClosingTag() {


}

void test_invalidXML_mismatchedTags() {


}