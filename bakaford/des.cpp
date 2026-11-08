#include <iostream>
#include "des.hpp"

int main() {  // VibeCoding
    using namespace Bakaford;

    const realtype pi = std::acos(-1.0L);
    const realtype e  = std::exp(1.0L);

    Drofakab<realtype> solver;

    // Candidate operations: add a constant, or multiply by a coefficient.
    solver.patternadd.push_back(
        [](Quantity<realtype> value, Quantity<realtype> constant) {
            return value + constant;
        }
    );

    solver.patternadd.push_back(
        [](Quantity<realtype> value, Quantity<realtype> constant) {
            return value - constant;
        }
    );

    solver.patternadd.push_back(
        [](Quantity<realtype> value, Quantity<realtype> constant) {
            return value * constant;
        }
    );

    solver.patternadd.push_back(
        [](Quantity<realtype> value, Quantity<realtype> constant) {
            return value / constant;
        }
    );

    solver.patternadd.push_back(
        [](Quantity<realtype> value, [[maybe_unused]] Quantity<realtype> constant) {
            return value.sqr();
        }
    );

    solver.patternadd.push_back(
        [](Quantity<realtype> value, [[maybe_unused]] Quantity<realtype> constant) {
            return value.sqrt();
        }
    );

    // Constants available to the addition and multiplication patterns.
    solver.addits.push_back(Quantity<realtype>(pi, "pi"));
    solver.addits.push_back(Quantity<realtype>(e, "e"));
    solver.addits.push_back(Quantity<realtype>(9.0L, "9"));
    solver.coefs.push_back(Quantity<realtype>(pi, "pi"));
    solver.coefs.push_back(Quantity<realtype>(e, "e"));
    solver.coefs.push_back(Quantity<realtype>(9.0L, "9"));

    // Example target: pi, starting from zero.
    const Quantity<realtype> target(1.14514L, "114.5");
    const Quantity<realtype> initial(e, "e", 1);

    const auto result = solver.run(target, initial, 1.0L, 0.01L, 1e-5, 1);

	using namespace std;
    std::cout << "Target: " << target.data << '\n'
              << "Result: " << result.data << '\n'
              << "Expression: " << result.desc << '\n'
              << sqrt(sqrt(e))-(sqrt(e)/((e)/((sqrt(e)/sqrt(e))/(sqrt(e)+e))));
}
