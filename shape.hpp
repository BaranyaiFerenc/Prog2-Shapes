#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <iostream>
#include "vector.h"
#include "mystring.h"

#include "shape.hpp"


class Shape
{
    ///Alakzat közepe
    Vector center;
    ///Alakzat egyik csúcsa
    Vector vertex;

public:
    ///Paraméteres konstruktor
    /// @param Vector c - az alakzat középpontja
    /// @param Vector v - az alakzat egyik csúcsa
    Shape(Vector c, Vector v):center(c), vertex(v){}

    ///Alakzat elmozgatása
    /// @param const Vector& - elmozgatás vektora
    void Move(const Vector&);

    ///Alakzat forgatása
    /// @param const double - forgatás foka
    void Rotate(const double);

    ///Alakzat átméretezése
    /// @param const double - Növelés nagysága
    void Scale(const double);

    ///Visszatér az alakzat középpontjával
    /// @return - Az alakzat közepe
    Vector GetCenter() const{return center;}

    ///Visszatér az alakzat megadott pontjával
    /// @return - Az alakzat egy pontja
    Vector GetVertex() const{return vertex;}

    ///Meghatározza hogy az alakzat benne van-e az origó körüli egységkörben
    /// @param double - Egységkör sugara
    /// @return - Benne van-e az egységkörben az alakzat
    virtual bool insideCircle(double) const;

    ///Meghatározza hogy egy pont benne van-e az alakzatban
    /// @param const Vector& - A pont koordinátái
    /// @return - benne van-e a pont az alakzatban
    virtual bool pointInside(const Vector&) const = 0;

    ///Alakzat területének kiszámolása
    /// @return - Az alakzat területe
    virtual double GetArea() const = 0;

    ///Alakzat kerületének kiszámolása
    /// @return - Az alakzat kerülete
    virtual double GetPerimeter() const = 0;

    ///Alakzat pontjainak lekérdezése relatív az origóhoz
    /// @param int& n - A kiszámoltok pontok számát ebbe írja vissza
    /// @return - Az alakzat csúcsai
    virtual Vector* GetVertices(int& n) const = 0;

    ///Alakzat nevének kiírása
    /// @param std::ostream& - kimenet típusa
    virtual void Write(std::ostream&) const = 0;

    virtual ~Shape(){}

    ///Alakzat szabványos kiírása (<név> <cx> <cy> <vx> <vy>)
    /// @param std::ostream& - kimenet típusa
    /// @param const Shape* - kiírandó alakzat pointere
    friend std::ostream& operator<<(std::ostream&, const Shape*);

    ///Alakzat szabványos beolvasása (<név> <cx> <cy> <vx> <vy>)
    /// @param std::ostream& - bemenet típusa
    /// @param const Shape* - alakzat pointere amibe a beolvasás történik
    friend std::istream& operator>>(std::istream&, Shape*&);
};


class Triangle: public Shape
{

public:
    Triangle(Vector c, Vector v):Shape(c,v){}

    Vector* GetVertices(int&) const override;

    bool pointInside(const Vector&) const override;

    double GetArea() const override;
    double GetPerimeter() const override;

    double GetSide() const;

    void Write(std::ostream&) const override;


    ///Háromszög adatainak részletes kiírása
    /// @param std::ostream& - kimenet típusa
    /// @param const Triangle& - kiírandó háromszög
    friend std::ostream& operator<<(std::ostream&, const Triangle&);

};


class Square: public Shape
{

public:
    Square(Vector c, Vector v): Shape(c,v){}
    Vector* GetVertices(int&) const override;

    bool pointInside(const Vector&) const override;

    double GetArea() const override;
    double GetPerimeter() const override;

    double GetSide() const;

    void Write(std::ostream&) const override;

    ///Négyzet adatainak részletes kiírása
    /// @param std::ostream& - kimenet típusa
    /// @param const Square& - kiírandó négyzet
    friend std::ostream& operator<<(std::ostream&, const Square&);

};

class Circle: public Shape
{
    ///Kör csúcsainak száma
    size_t vertCount;

public:
    ///Kör konstruktora
    /// @param Vector c - kör középpontja
    /// @param Vector v - kör egyik pontja
    /// @param int n - kör pontjainak száma
    Circle(Vector c, Vector v, int n = 36);

    Vector* GetVertices(int&) const override;

    /// Mivel a körnek nem véges számú a ponthalmaza ezért ehez külön függvény készült
    bool insideCircle(double) const override;

    bool pointInside(const Vector&) const override;

    double GetArea() const override;
    double GetPerimeter() const override;

    ///Sugár kiszámítása
    /// @return - kör sugara
    double GetRadius() const;

    void Write(std::ostream&) const override;

    ///Kör adatainak részletes kiírása
    /// @param std::ostream& - kimenet típusa
    /// @param const Square& - kiírandó kör
    friend std::ostream& operator<<(std::ostream&, const Circle&);
};

#endif // SHAPE_H_INCLUDED
