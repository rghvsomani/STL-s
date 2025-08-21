#include <iostream>
#include <cstring>

using namespace std;

class String {
private:
    char* res;
    unsigned int len;
public:
    // Default constructor
    String() : res(nullptr), len(0) {}

    // Constructor from C-string
    String(const char* obj) {
        if (obj) {
            len = strlen(obj);
            res = new char[len + 1];
            strcpy(res, obj);
        } else {
            res = nullptr;
            len = 0;
        }
    }

    // Copy constructor
    String(const String& str) {
        len = str.len;
        if (str.res) {
            res = new char[len + 1];
            strcpy(res, str.res);
        } else {
            res = nullptr;
        }
    }

    // Copy assignment operator
    String& operator=(const String& str) {
        if (this != &str) {
            delete[] res;
            len = str.len;
            if (str.res) {
                res = new char[len + 1];
                strcpy(res, str.res);
            } else {
                res = nullptr;
            }

