
/**
 * @date Octobre 2026
 * @author A. Casali
 * @brief Classe myVect dérivant de std::vector<T>.
 *
 * Spécificités et comportements :
 * - Surcharge des opérateurs `[]` pour lever une exception `std::out_of_range` en cas de débordement de tableau.
 * - Comportement similaire à l'accesseur `std::vector<T>::at()`.
 */

#ifndef MYVECT_H
#define MYVECT_H
#include <vector> // Requis pour std::vector
#include <stdexcept> // Requis pour std::out_of_range

template <typename T>
class myVect : public std::vector<T> {
public:

    // Importe les constructeurs de la classe de base (C++11 et supérieur)
    using std::vector<T>::vector;

    // Surcharge de []
    T& operator[](std::size_t index) {
        //si l'indice n'est pas valide
        if (index >= this->size())
            throw std::out_of_range("indice hors limite");
        //sinon on appele l'opérateur de base
        return std::vector<T>::operator[](index);
    }

    // Surcharge de [] si const
    const T& operator[](std::size_t index) const {
        //si l'indice n'est pas valide
        if (index >= this->size())
           throw std::out_of_range("indice hors limte");
        //sinon on appele l'opérateur de base
        return std::vector<T>::operator[](index);
    }
};
#endif // MYVECT_H
