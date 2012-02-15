
#include "MinAtom.h"

#include <dlvhex2/Registry.h>

namespace dlvhex {
  namespace aggregate {

	MinAtom::MinAtom() : AggAtom("min") { }
	
	MinAtom::~MinAtom() { }

	ID MinAtom::calculateAggfun(InterpretationConstPtr interp, 
								const Tuple& input) 			 const {
	
		Registry& registry = *interp.get()->getRegistry().get();
		
		int maskPos = -1;
		for (int i=0; i<input.size(); i++) {
			if (input[i] == registry.terms.getIDByString(MASKTERM.symbol)) {
				maskPos = i;
				LOG(DBG, "MinAtom::calculateAggfun: maskPos = " << maskPos);
				break;
			}
		}
		if (maskPos == -1) {
			std::stringstream errmsgSS;
			errmsgSS << "There was no occurrence of '" << MASKTERM.symbol << "'!";
			throw PluginError(errmsgSS.str());
		}
		
		std::string min = "";
		
		int pos = interp.get()->getStorage().get_first();
		do {
			const OrdinaryAtom& oatom = registry.ogatoms.getByAddress(pos);
			ID curid = oatom.tuple[maskPos]; 
			std::string cur = registry.getTermStringByID(curid);
			if (min == "" || cur < min) {
				min = cur;
				LOG(DBG, "MinAtom::calculateAggfun: min = " << min);
			}
			pos = interp.get()->getStorage().get_next(pos);
		} 
		while (pos != 0);
		
		Term t = Term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, min);
		LOG(DBG, "MinAtom::calculateAggfun: t = " << t);
		ID id = registry.storeTerm(t);
		
		return id;
	}

  }
}
