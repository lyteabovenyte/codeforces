#include <iostream>
#include <iomanip>

int main() {
    // Example values:
    // P(A) = priorA
    // P(B|A) = likelihoodA
    // P(B|~A) = likelihoodNotA
    double priorA = 0.01;         // e.g., prevalence
    double likelihoodA = 0.95;    // test sensitivity
    double likelihoodNotA = 0.05; // false positive rate

    // Bayes' theorem:
    // P(A|B) = P(B|A) P(A) / [ P(B|A) P(A) + P(B|~A) (1-P(A)) ]
    double numerator = likelihoodA * priorA;
    double denominator = numerator + likelihoodNotA * (1.0 - priorA);

    double posteriorA_givenB = (denominator > 0.0) ? numerator / denominator : 0.0;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "P(A|B) = " << posteriorA_givenB << "\n";
    std::cout << "P(~A|B) = " << (1.0 - posteriorA_givenB) << "\n";
    return 0;
}