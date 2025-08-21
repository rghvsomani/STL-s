



This Implementation is wrong , see string.cpp 


#include <iostream>

using namespace std;

class String{
    private: 
    char* res;
    unsigned int len;
    public:
        String():res(nullptr),len(0)
        {
            
        }
        
        String(const char* obj)
        {
            len= strlen(obj);
            res=new char[len+1];
            strcpy(res,obj);
        }

        String(const String &str)
        {
            if (str.res) {
                res = new char[len + 1];
                strcpy(res, str.res);
            } else {
                res = nullptr;
            }
        }

        String& operator=(const String& str)
        {
            if(this!=&str)
            {
                delete[] res;
                len=str.len;
                if (str.res) {
                    res = new char[len + 1];
                    strcpy(res, str.res);
                } else {
                    res = nullptr;
                }
            }
            return *this;
        }

        unsigned int length()
        {
            return len;
        }
        friend ostream& operator<<(ostream& cout, const String & str);
        friend istream& operator>>(istream& cin, String & str);

        ~String()
        {
            delete[] res;
        }
};

ostream& operator<<(ostream& cout,const String & str)
{
    if (str.res) 
        cout << str.res;
    return cout;
}

istream& operator>>(istream& cin, String & str)
{
    char temp[1000]; // Temporary buffer
    cin >> temp;
    delete[] str.res; // Free old memory
    str.len = strlen(temp);
    str.res = new char[str.len + 1];
    strcpy(str.res, temp);
    return cin;

}

int main()
{
    String s1;
    String s2 = "abc";
    String s3 = s1;
    s3=s2;
    int len=s2.length();
    cout<<s2;
     cin>>s3;
}
