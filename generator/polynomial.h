//
// Created by Amida on 2021/06/06.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>
#include "fraction.h"

class Polynomial {
public:
    class Monomial {
    public:
        Fraction coefficient;
        int index;
        Monomial(Fraction coefficient, int index): coefficient(coefficient), index(index){}
        Fraction substitute(int x);
        Fraction definiteIntegral(int from, int to);
        Monomial indefiniteIntegral();
    };

    std::vector<Monomial> polynomial;

    void add(Monomial m);

    Fraction substitute(int x);

    /**
     * 定積分
     * @param from
     * @param to
     * @return
     */
    Fraction definiteIntegral(int from, int to);

    /**
     * 不定積分。積分定数は0。
     * @return F
     */
    Polynomial* indefiniteIntegral();

    std::string show();

};

#endif //POLYNOMIAL_H
