#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <cmath>

class Vector
{
    ///Koordináták
    double x,y;

public:

    ///Alapértelmezett konstruktor
    Vector(): x(0), y(0) {}

    ///Paraméteres konstruktor
    /// @param double xt - x koordináta
    /// @param double yt - y koordináta
    Vector(double xt, double yt): x(xt), y(yt){}

    ///Másoló konstruktor
    /// @param const Vector& v - A másolandó vektor
    Vector(const Vector& v): x(v.x), y(v.y){}

    ///X koordináta lekérdezése
    /// @return - x koordináta
    double getX() const {return x;};

    ///Y koordináta lekérdezése
    /// @return - y koordináta
    double getY() const {return y;};

    ///Vektor + Vektor
    /// @param const Vector& - hozzáadandó vektor
    /// @return - saját és a paraméter vektor összege
    Vector operator+(const Vector&) const;

    ///Vektor - Vektor
    /// @param const Vector& - kivonandó vektor
    /// @return - saját és a paraméter vektor különbsége
    Vector operator-(const Vector&) const;

    ///Vektor szorzása skaláral
    /// @param double - Skalár amivel beszorzunk
    /// @return - Saját vektornak a skalárszorosa
    Vector operator*(double) const;

    ///Vektor szorzása vektorral
    /// @param const Vector& - Vektor amivel beszorzunk
    /// @return - Saját és a paraméter vektornak a szorzata
    Vector operator*(const Vector&) const;

    ///Értékadó operátor
    /// @param const Vector& - Aminek az értékét hozzáadjuk
    void operator=(const Vector&);

    void operator+=(const Vector&);
    void operator-=(const Vector&);

    ///Vektor hosszának kiszámítása
    /// @return - vektor hossza
    double Length() const;

    ///Vektor 1 hosszú irányvektorának kiszámítása
    /// @return - 1 hosszú irányvektor
    Vector getDirection() const;

    ///Vektor kerekítése
    /// @return - egészre kerekített vektor
    Vector Round() const;

    ///Vektor elforgatása
    /// @param double - elforgatás nagysága fokban megadva
    /// @return - elforgatott vektor
    Vector Rotate(double) const;

    ///Vektor kiírása
    ///Formátum: (x;y)
    friend std::ostream& operator<<(std::ostream&, const Vector&);
};

#endif // VECTOR_H_INCLUDED
