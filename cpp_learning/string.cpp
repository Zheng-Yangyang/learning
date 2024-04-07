#include <iostream>
#include <cstring>

class String {
public:
    String(const char* str = nullptr) : m_data(nullptr) {
        if (str != nullptr) {
            m_data = new char[strlen(str) + 1];
            strcpy(this->m_data, str);
        } else {
            m_data = new char[1];
            *m_data = '\0';
        }
    }

    ~String() {
        delete[] m_data;
        m_data = nullptr;
    }

    String(const String& str) : m_data(nullptr) {
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
    }

    String& operator=(const String& str) {
        if (this == &str) {
            return *this;
        }
        delete[] m_data;
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
        return *this;
    }

    String& operator=(const char* str) {
        delete[] m_data;
        if (str != nullptr) {
            m_data = new char[strlen(str) + 1];
            strcpy(m_data, str);
        } else {
            m_data = new char[1];
            *m_data = '\0';
        }
        return *this;
    }

private:
    char* m_data;
};

int main() {
    String str1;
    String str2("hello");
    String str3 = "world";
    String str4 = str2;

    return 0;
}
