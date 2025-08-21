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
        }
        return *this;
    }

    // Move constructor
    String(String&& str) noexcept {
        res = str.res;
        len = str.len;
        str.res = nullptr;
        str.len = 0;
    }

    // Move assignment operator
    String& operator=(String&& str) noexcept {
        if (this != &str) {
            delete[] res;
            res = str.res;
            len = str.len;
            str.res = nullptr;
            str.len = 0;
        }
        return *this;
    }

    // Return length
    unsigned int length() const {
        return len;
    }

    // Friend functions for stream operators
    friend ostream& operator<<(ostream& cout, const String& str);
    friend istream& operator>>(istream& cin, String& str);

    // Destructor
    ~String() {
        delete[] res;
    }
};

ostream& operator<<(ostream& cout, const String& str) {
    if (str.res)
        cout << str.res;
    return cout;
}

istream& operator>>(istream& cin, String& str) {
    char temp[1000]; // Temporary buffer
    cin >> temp;
    delete[] str.res; // Free old memory
    str.len = strlen(temp);
    str.res = new char[str.len + 1];
    strcpy(str.res, temp);
    return cin;
}

// Example usage
int main() {
    String s1;
    String s2 = "abc";
    String s3 = s1;
    s3 = s2;
    int len = s2.length();
    cout << s2 << endl;
    cout << "Enter a string: ";
    cin >> s3;
    cout << "You entered: " << s3 << endl;
    return 0;
}
