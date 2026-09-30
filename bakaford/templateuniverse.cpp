/******************************************************************************
 * Bakaford/TemplateUniverse: The implementation of HoTT based on TMP.		  *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.9.30 (latest upd)                                              *
 * @Modules: { Bakaford::TemplateUniverse }                                   *
 ******************************************************************************/
#include "templateuniverse.hpp"
using namespace Bakaford::TemplateUniverse;
int main(void) {
	UniverseOf<Nat> uni;
	Nat nat0=uni.subclass(nullptr);
	Nat nat9=nat0.succ().succ().succ().succ().succ().succ().succ().succ().succ();
	Nat nat7=nat0.succ().succ().succ().succ().succ().succ().succ();
	
	std::cout << nat9.integer() << ":" << nat9.what() << "\n";
	std::cout << nat7.integer() << ":" << nat7.what() << "\n";
	
	std::cout << nat9.integer() << "+" << nat7.integer() << " == " << (nat9+nat7).integer() << ":" << (nat9+nat7).what() << "\n";
	std::cout << nat9.integer() << "*" << nat7.integer() << " == " << (nat9*nat7).integer() << ":" << (nat9*nat7).what() << "\n";
	return 0;
}

