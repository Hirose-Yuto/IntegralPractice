//
// Created by Amida on 2021/06/06.
//

#include <math.h>
#include <random>
#include "generator.h"

std::vector<std::string> Generator::Q_and_A() {
    std::tuple<Polynomial, int, int> Q_range = randomlyGenerate();
    Polynomial Q = std::get<0>(Q_range);
    int from = std::get<1>(Q_range);
    int to = std::get<2>(Q_range);
    Fraction A = Q.definiteIntegral(from, to);

    // 答え4桁防止
    while(A.numerator > 1000 || A.denominator > 1000) {
        Q_range = randomlyGenerate();
        Q = std::get<0>(Q_range);
        from = std::get<1>(Q_range);
        to = std::get<2>(Q_range);
        A = Q.definiteIntegral(from, to);
    }

    std::vector<std::string> result;
    result.push_back("\\integralProblem{" + std::to_string(from) + "}{" + std::to_string(to) + "}{" + Q.show() + "}");
    result.push_back("\\integralAnswer{" + std::to_string(from) + "}{" + std::to_string(to) + "}{" + Q.show() + "}{"+ A.show() + "}");
    return result;
}

std::tuple<Polynomial, int, int> Generator::randomlyGenerate() {
    int num_of_items = get(NumOfItems);
    int from = 0;
    int to = 0;

    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    // 0.0以上1.0未満の値を等確率で発生させる
    std::uniform_real_distribution<> dist(0.0, 1.0);

    while(from == to) {
        from = (dist(engine) - 0.5)*7;
        to = (dist(engine) - 0.5)*7;
    }

    Polynomial p;
    for(int i = num_of_items; i >= 0; i--) {
        int numerator = get(Numerator);
        int denominator = get(Denominator);
        Polynomial::Monomial m = Polynomial::Monomial(Fraction(numerator, denominator), i);
        p.add(m);
    }

    return std::make_tuple(p, from, to);
}

int Generator::get(const Variables v) {
    std::tuple<int, int> from_to = this->rangeOfProbability[v];
    int from = std::get<0>(from_to);
    int to = std::get<1>(from_to);
    std::function<double(int)> fn = this->probability_not_normalized[v];

    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    // 0.0以上1.0未満の値を等確率で発生させる
    std::uniform_real_distribution<> dist(0.0, 1.0);

    double r = dist(engine) * *this->SumOf_probability_not_normalized[v];
    double partial_sum = 0;
    for(int i = from; i <= to; i++) {
        partial_sum += fn(i);
        if(r <= partial_sum) {
            return i;
        }
    }
    return to;
}

void Generator::calculateSumOf_probability_not_normalized(const Variables v){
    double sum = 0;
    std::tuple<int, int> from_to = this->rangeOfProbability[v];
    int from = std::get<0>(from_to);
    int to = std::get<1>(from_to);
    std::function<double(int)> fn = this->probability_not_normalized[v];
    for(int i = from; i <= to; i++) {
        sum += fn(i);
    }
    *this->SumOf_probability_not_normalized[v] = sum;
}

double Generator::numOfItems_probability_not_normalized(int x) {
    double f[5] = {1.0, 2.0, 8.0, 3.0, 2.0};
    return f[x];
}

double Generator::numeratorOfCoefficient_probability_not_normalized(int x) {
    if(x <= 12) {
        return 1.0;
    } else {
        return pow(2, -(x-12));
    }
}

double Generator::denominatorOfCoefficient_probability_not_normalized(int x) {
    return pow(2, -x);
}
