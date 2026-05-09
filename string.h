#ifndef STRING_H
#define STRING_H

class String {
private:
    char* data;
    int strLen;

    int calculateLen(const char* str) const;
    char* copyStr(const char* source);

public:
    String();
    String(const char* str);
    String(const String& obj);
    ~String();

    String& operator=(const String& obj);
    bool operator==(const String& obj) const;
    const char* getString() const;
    int getLength() const;
};

#endif