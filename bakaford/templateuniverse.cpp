/******************************************************************************
 * Bakaford/TemplateUniverse: The implementation of HoTT based on TMP.		  *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.9.26 (latest upd)                                              *
 * @Modules: { Bakaford::TemplateUniverse }                                   *
 ******************************************************************************/
#include "templateuniverse.hpp"
using namespace Bakaford::TemplateUniverse;
int main(void) {
	[[maybe_unused]] Universe<G0> uni;
	Nat zero=Nat{};
	Nat nine=Nat{}.succ().succ().succ().succ().succ().succ().succ().succ().succ();
	Nat seven=Nat{}.succ().succ().succ().succ().succ().succ().succ();
	std::cout << nine.integer() << ":" << nine.what() << "\n";
	std::cout << seven.integer() << ":" << seven.what() << "\n";
	Nat sum=nine.church(Nat::successor,seven), prod=nine.church(seven.churchnum(),zero);
	std::cout << sum.integer() << ":" << sum.what() << "\n";
	std::cout << prod.integer() << ":" << prod.what() << "\n";
	return 0;
}

