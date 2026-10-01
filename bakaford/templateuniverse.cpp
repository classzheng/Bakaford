/******************************************************************************
 * Bakaford/TemplateUniverse: The implementation of HoTT based on TMP.		  *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.9.30 (latest upd)                                              *
 * @Modules: { Bakaford::TemplateUniverse }                                   *
 ******************************************************************************/
#include "templateuniverse.hpp"
using namespace Bakaford::TemplateUniverse;
int main(void) {
	try {
		UniverseOf<Nat> natuni;
		UniverseOf<Identity<Nat>> iduni;
		UniverseOf<G0> falseprop;
		UniverseOf<G1> trueprop;
		Nat nat0=natuni.subclass(nullptr);
		Nat nat9=nat0.succ().succ().succ().succ().succ().succ().succ().succ().succ();
		Nat nat7=nat0.succ().succ().succ().succ().succ().succ().succ();
		Nat nat16=nat0.succ().succ().succ().succ().succ().succ().succ().succ().succ().succ().succ().succ().succ().succ().succ().succ();
		Identity<Nat> id=iduni.subclass(nat9+nat7,nat16);
		
		std::cout << "natuni\t\t: " << natuni.what() << "\n";
		std::cout << "iduni\t\t: " << iduni.what() << "\n";
		std::cout << "falseprop\t: " << falseprop.what() << "\n";
		std::cout << "trueprop\t: " << trueprop.what() << "\n";
		std::cout << nat9.integer() << "\t\t: " << nat9.what() << "\n";
		std::cout << nat7.integer() << "\t\t: " << nat7.what() << "\n";
		std::cout << nat16.integer() << "\t\t: " << nat16.what() << "\n";
		std::cout << std::boolalpha << "uni.iselement(nat9)= " << natuni.iselement(nat9) << "\n";
		std::cout << std::boolalpha << "trueprop.iselement(trueprop.getinstead<G0>(id.reflection()))= " << trueprop.iselement(trueprop.getinstead<G0>(id.reflection())) 
				  << "; refl(" << id.what() << "(nat9+nat7,nat16)) : " << trueprop.getinstead<G0>(id.reflection()).what() << "\n\n";
		
		std::cout << nat9.integer() << "+" << nat7.integer() << " == " << (nat9+nat7).integer() << "\t: " << (nat9+nat7).what() << "\n";
		std::cout << nat9.integer() << "*" << nat7.integer() << " == " << (nat9*nat7).integer() << "\t: " << (nat9*nat7).what() << "\n";
	} catch(std::exception &e) {
		std::clog << e.what();
		return -1;
	}
	return 0;
}


