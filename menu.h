#ifndef SHAPES_MENU_H
#define SHAPES_MENU_H

#include <iostream>

#include "shape.hpp"
#include "mystring.h"
#include "vector.h"
#include "paper.h"
#include "shape.hpp"

///Névtér ami a menüvezérlést valósítja meg
namespace Menu
{
    ///Menü opcióinak kiírása
    /// @param int shapeCount - Betölött alakzatok száma
    /// @param std::ostream& os - Kimenet
    void DrawMain(int shapeCount, std::ostream& os = std::cout);

    ///Index bekérése
    /// @param Paper& paper - Alakzatok tárolója
    /// @param std::ostream& os - Kimenet
    /// @param std::istream& input - Bemenet
    int GetIndex(Paper& paper, std::ostream& os = std::cout, std::istream& input = std::cin);

    ///Alakzat kiválasztása
    /// @param Paper& paper - Alakzatok tárolója
    /// @param std::ostream& os - Kimenet
    /// @param std::istream& input - Bemenet
    Shape* Selector(Paper& paper, std::ostream& os = std::cout, std::istream& input = std::cin);

    ///Válasz bekérése
    /// @param mString& question - Kérdés
    /// @param std::ostream& os - Kimenet
    /// @param std::istream& input - Bemenet
    template<typename T>
    T GetParameter(const mString& question, std::ostream& os = std::cout, std::istream& input = std::cin);

    ///Menü végrehajtó függvény
    /// @param std::istream& input - Bemenet
    /// @param std::ostream& value_out - Adatok kimenete
    /// @param std::ostream& interface_out - Interface elemek kimenete
    void menu(std::istream& input = std::cin, std::ostream& value_out = std::cout, std::ostream& interface_out = std::cout);
}

#endif //SHAPES_MENU_H
