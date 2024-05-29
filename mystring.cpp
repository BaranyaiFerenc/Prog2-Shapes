#include "mystring.h"


#define DEBUG 0

mString::mString()
{
    len = 0;
    text = new char[1];
    text[0] = '\0';
}

mString::mString(const char* t)
{
    len = GetLen(t);
    text = new char[len+1];

    for(size_t i = 0; i<len; i++)
    {
        text[i] = t[i];
    }

    text[len] = '\0';


#if DEBUG
    std::cout<<"mString(const char*):"<<*this<<" -> size: "<<len<<std::endl;
#endif
}


mString::mString(const mString& str)
{
    len = str.len;
    text = new char[len+1];


    for(size_t i = 0; i<len; i++)
    {
        text[i] = str[i];
    }

    text[len] = '\0';


#if DEBUG
    std::cout<<"mString(const mString&):"<<*this<<" -> size: "<<len<<std::endl;
#endif
}

int mString::Length() const
{
    return len;
}

char* mString::getText() const
{
    return text;
}


int GetLen(const char* str)
{
    int len = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
        len++;
    }

#if DEBUG
    std::cout<<"GetLen(const char*):"<<str<<" -> size: "<<len<<std::endl;
#endif

    return len;
}

char& mString::operator[](size_t index)
{
    if(index >= len)
        throw std::out_of_range("Out of array - char& mString::operator[](size_t index)");

    return text[index];
}

char mString::operator[](size_t index) const
{
    if(index >= len)
        throw std::out_of_range("Out of array - char mString::operator[](size_t index) const");

    return text[index];
}

void mString::operator=(const mString& str)
{
    if(text != 0)
        delete[] text;

    text = new char[str.len+1];

    for(size_t i = 0; i<str.len;i++)
    {
        text[i] = str[i];
    }

    text[str.len] = '\0';
    len = str.len;
}
void mString::operator=(const char* str)
{
    if(text != 0)
        delete[] text;

    int tLen = GetLen(str);

    text = new char[tLen+1];

    for(int i = 0; i<tLen;i++)
    {
        text[i] = str[i];
    }
    text[tLen] = '\0';
    len = tLen;
}

mString mString::operator+(const mString& str) const
{
    int sLen = str.Length();
    char* temp = new char[sLen+len+1];

    int ind = 0;
    for(size_t i = 0; i<len; i++)
    {
        temp[ind] = text[i];
        ind++;
    }
    for(int i = 0; i<sLen; i++)
    {
        temp[ind] = str[i];
        ind++;
    }

    temp[sLen+len] = '\0';
    mString newStr(temp);

    delete[] temp;

    return newStr;
}
mString mString::operator+(const char* str) const
{
    int sLen = GetLen(str);

    char* temp = new char[sLen+len+1];

    int ind = 0;

    for(size_t i = 0; i<len; i++)
    {
        temp[ind] = text[i];
        ind++;
    }
    for(int i = 0; i<sLen; i++)
    {
        temp[ind] = str[i];
        ind++;
    }

    temp[sLen+len] = '\0';
    mString newStr(temp);

    delete[] temp;

    return newStr;
}

mString mString::operator+(const char ch) const
{
    char* temp = new char[len+2];

    for(size_t i = 0; i<len; i++)
    {
        temp[i] = text[i];
    }
    temp[len] = ch;
    temp[len+1] = '\0';

    mString newStr = mString(temp);

    delete[] temp;

    return newStr;
}

void mString::operator+=(const mString& str)
{
    *this = *this+str;

#if DEBUG
    std::cout<<"operator+=(const mString&):"<<*this<<" -> size: "<<len<<std::endl;
#endif

}

void mString::operator+=(const char ch)
{
    *this = *this+ch;
}

void mString::operator+=(const char* str)
{
    *this = *this+str;

#if DEBUG
    std::cout<<"operator+=(const char*):"<<*this<<" -> size: "<<len<<std::endl;
#endif
}

int mString::Split(char separator, mString*& out) const
{
    int seps = 1;
    int* partLengths = new int[256];
    partLengths[0] = 1;

    for(size_t i = 0; i<len; i++)
    {
        if(text[i] != separator && text[i+1]==separator)
        {
            partLengths[seps] = 1;
            seps++;
        }
        else if(text[i] != separator)
        {
            partLengths[seps-1]++;
        }
    }

    char** res = new char*[seps];
    int sIndex = 0;
    int partIndex = 0;

    res[0] = new char[partLengths[0]+1];

    for(size_t i = 0; i<len; i++)
    {
        if(text[i] != separator)
        {
            res[sIndex][partIndex] = text[i];
            partIndex++;
        }

        if(text[i] != separator && text[i+1]==separator)
        {
            res[sIndex][partIndex] = '\0';
            sIndex++;
            res[sIndex] = new char[partLengths[sIndex]+1];
            partIndex = 0;
        }
    }

    res[sIndex][partIndex] = '\0';

    out = new mString[seps];

    for(int i = 0; i<seps; i++)
    {
        out[i]=res[i];
    }

    delete[] partLengths;

    for(int i = 0; i<seps; i++)
    {
        delete[] res[i];
    }

    delete[] res;
    return seps;
}

mString mString::RemoveAt(size_t startIndex, size_t endIndex) const
{
    if(startIndex > len-1 && endIndex>len-1)
        throw std::out_of_range("Out of array - mString mString::RemoveAt(size_t startIndex, size_t endIndex) const");

    int s = (len-((endIndex-startIndex)+1))+2;

    char* t = new char[s];

    int ind = 0;

    for(size_t i = 0; i<len+1; i++)
    {
        if(i < startIndex || i > endIndex)
        {
            t[ind] = text[i];
            ind++;
        }
    }
    t[s-1] = '\0';

    mString newStr = mString(t);
    delete[] t;

    return newStr;
}

ostream& operator<<(ostream& os, const mString& str)
{
    os << str.text;

#if DEBUG
    os<<(str.text[str.len] == '\0'?"\\0":"");
#endif

    return os;
}


istream& operator>>(istream& is, mString& str)
{
    char* text = new char[256];
    is>>text;
    str = text;

    delete[] text;

    return is;
}


void mString::clear()
{
    delete[] text;
    len = 0;
    text = new char[1];
    text[0] = '\0';
}

mString mString::toLower() const
{
    mString newStr = mString(text);
    for(size_t i = 0; i<len; i++)
    {
        newStr[i] = (char)tolower(text[i]);
    }


#if DEBUG
    std::cout<<"toLower():"<<newStr.text<<" -> size: "<<len<<std::endl;
#endif
    return newStr;
}

mString mString::toUpper() const
{
    mString newStr = mString(text);

    for(size_t i = 0; i<len; i++)
    {
        newStr[i] = (char)toupper(text[i]);
    }

#if DEBUG
    std::cout<<"toUpper():"<<newStr<<" -> size: "<<newStr.len<<std::endl;
#endif

    return newStr;
}

bool mString::operator==(const mString& str) const
{

    if(str.len != len)
        return false;

    for(size_t i = 0; i<str.len; i++)
    {
        if(str[i] != text[i])
            return false;
    }

    return true;
}

bool mString::operator==(const char* str) const
{
    size_t n = GetLen(str);

    if(n != len)
        return false;

    for(size_t i = 0; i<n;i++)
    {
        if(str[i] != text[i])
            return false;
    }

    return true;
}

mString::~mString()
{
    delete[] text;
}
