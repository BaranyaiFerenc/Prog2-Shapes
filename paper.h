#ifndef NHF_PAPER_H
#define NHF_PAPER_H

#include <iostream>

#include "shape.hpp"
#include "vector.h"
#include "mystring.h"


///Heterogén tároló a Shape osztály tárolásához
class Paper
{
    ///Alakzatok pointereit tároló tömb pointere
    Shape** shapes;

    ///Alakzatok száma
    size_t shapeCount;

public:
    ///Alapértelmezett konstruktor
    Paper();

    ///Alakzat hozzáadása a tömbhöz
    /// @param - Hozzáadandó elem pointere
    void AddShape(Shape*);

    ///Alakzat eltávolítása a tömbből
    /// @param const size_t - törlendő elem indexe
    void RemoveShape(const size_t);

    ///Alakzatok számának lekérdezése
    /// @return - Alakzatok száma
    size_t GetShapeCount() const;

    ///Alakzatok keresése és kiírása az origó körüli egyéskörben
    /// @param const double r - Egységkör sugara
    /// @param std::ostream& os - Kimenet típusa
    void GetShapesInCircle(const double r, std::ostream& os = std::cout) const;

    ///Olyan alakzatok keresés és kiírása amikben benne van egy adott pont
    /// @param const Vector& - Ezzel a pontal rendelkező alakzatokat keresi
    /// @param std::ostream& os - Kimenet típusa
    void GetShapesWithPoint(const Vector& v,std::ostream& os = std::cout) const;

    ///Alakzat bekérése index szerint
    /// @param const size_t - Index
    /// @return - Az index helyén lévő alakzat pointer
    Shape* GetShape(const size_t);

    ///Tömb kiürítése
    void Clear();

    ///Destruktor
    ~Paper();

    ///Osztály által tartalmazott alakzatok kiírása szabványos formátumban
    /// @param std::ostream& - kimenet típusa
    /// @param const Paper& - kiírandó objektum
    friend std::ostream& operator<<(std::ostream&, const Paper&);

    ///Osztályba való beolvasás
    /// @param std::ostream& - bemenet típusa
    /// @param const Paper& - objektum amibe beolvasunk
    friend std::istream& operator>>(std::istream&, Paper&);
};

#endif //NHF_PAPER_H
