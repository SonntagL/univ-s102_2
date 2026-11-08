/**
 * @date Octobre 2026
 * @author A. Casali
 * @brief Classe myString dérivant de std::string.
 *
 * Spécificités et comportements :
 * - Surcharge des opérateurs `[]` pour lever une exception `std::out_of_range` en cas de débordement de tableau.
 * - Comportement similaire à l'accesseur `std::string::at()`.
 */

#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>     // Requis pour std::string
#include <stdexcept>  // Requis pour std::out_of_range

class myString : public std::string {
public:
    // Importe les constructeurs de la classe de base (C++11 et supérieur)
    using std::string::string;

    // Surcharge de []
    char& operator[](std::size_t index) {
        //si l'indice n'est pas valide
        if (index >= this->size())
            throw std::out_of_range("indice hors limite");
        //sinon on appele l'opérateur de base
        return std::string::operator[](index);
    }


    // Surcharge de [] si const
    const char& operator[](std::size_t index) const {
        //si l'indice n'est pas valide
        if (index >= this->size())
            throw std::out_of_range("indice hors limte");
        //sinon on appele l'opérateur de base
        return std::string::operator[](index);
    }
};
#endif // MYSTRING_H
