#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#include <iostream>
#include <cctype>

using namespace std;

///karaktertömb hosszának kiszámítása
int GetLen(const char*);

///String osztály
class mString
{
    ///Karaktereket tartalmazó karaktertömbre mutató pointer
    char* text;
    ///Karaktertömb hossza a záró '\0' kivételével
    size_t len = 0;

public:

    ///Alapértelmezett konstruktor
    mString();

    ///Paraméteres konstruktor
    /// @param const char* t - karakter tömb amit beletesz a string-be
    mString(const char* t);

    ///Másoló konstruktor
    /// @param const mString& - string amit lemásol
    mString(const mString&);

    ///A szöveg hossza
    /// @return - Szöveg hossza a lezáró '\0' nélkül
    int Length() const;

    ///Szöveg lekérdezése karaktertömbként
    /// @return - a szöveg karaktertömbje
    char* getText() const;

    void operator=(const mString&);
    void operator=(const char*);

    mString operator+(const mString&) const;
    mString operator+(const char*) const;
    mString operator+(const char) const;

    void operator+=(const mString&);
    void operator+=(const char);
    void operator+=(const char*);

    bool operator==(const mString&) const;
    bool operator==(const char*) const;

    char operator[](size_t) const;
    char& operator[](size_t);

    ///Szöveg kisbetűssé alakítása
    /// @return - kisbetűs szöveg
    mString toLower() const;

    ///Szöveg nagybetűssé alakítása
    /// @return - nagybetűs szöveg
    mString toUpper() const;

    ///Szöveg feldarabolása egy karakter mentén
    /// @param char - elválasztó karakter
    /// @param mString*& - a végeredmény tárolására szánt mString tömb
    /// @return - a feldarabolt szövegek száma
    int Split(char,mString*&) const;

    ///Szöveg kivágása
    /// @param size_t startIndex - kezdő index (inkluzív)
    /// @param size_t endIndex - záró index (inkluzív)
    /// @return - a két index közti szöveg nélküli szöveg (az index helyein is törli a betűket)
    mString RemoveAt(size_t startIndex, size_t endIndex) const;

    ///Szöveg kiírása
    friend ostream& operator<<(ostream&, const mString&);

    ///Szöveg beolvasása
    friend istream& operator>> (istream&, mString&);

    ///Szöveg törlése
    void clear();
    ~mString();

};


#endif // MYSTRING_H_INCLUDED
