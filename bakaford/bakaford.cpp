#include <bits/stdc++.h>
#include "bakaford.hpp"

using namespace Bakaford;

static std::string bracketToString(const CliffordBracket<> &b) {
    std::stringstream oss;
    oss << "[" << b.arg[0] << "," << b.arg[1] << "," << b.arg[2] << "]";
    if (b.invflag) oss << "^(" << b.invflag << ")";
    return oss.str();
}

int main() {
    // Create two brackets: lhs = [1,2,3], rhs = [4,5,6]
    CliffordBracket<> lhs(1, 2, 3);
    CliffordBracket<> rhs(4, 5, 6);

    // ensure invflag is initialized (the class leaves it uninitialized by default)
    lhs.invflag = 0;
    rhs.invflag = 0;

    // Expand per the identity in your comment
    auto products = lhs.expand(rhs);

    std::cout << "Expanding " << bracketToString(lhs)
              << " with " << bracketToString(rhs) << " yields:\n\n";

    for (size_t i = 0; i < products.size(); ++i) {
        const auto &prod = products[i]; // each prod is a vector of CliffordBracket (the numerator factors)
        std::cout << " Term " << (i + 1) << ": ";
        for (size_t j = 0; j < prod.size(); ++j) {
            if (j) std::cout << " ";
            std::cout << bracketToString(prod[j]);
        }
        std::cout << "\n";
    }

    return 0;
}
