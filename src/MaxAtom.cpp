
#include "MaxAtom.h"

#include <dlvhex2/Registry.h>

namespace dlvhex {
  namespace aggregate {

	MaxAtom::MaxAtom() : AggAtom("max") { }
	
	MaxAtom::~MaxAtom() { }

	ID MaxAtom::calculateAggfun(InterpretationConstPtr interp, 
								const Tuple& input) 			 const {
		
		Registry& registry = *interp.get()->getRegistry().get();
		
		int maskPos = -1;
		for (int i=0; i<input.size(); i++) {
			if (input[i] == registry.terms.getIDByString(MASKTERM.symbol)) {
				maskPos = i;
				LOG(DBG, "MaxAtom::calculateAggfun: maskPos = " << maskPos);
				break;
			}
		}
		if (maskPos == -1) {
			std::stringstream errmsgSS;
			errmsgSS << "There was no occurrence of '" << MASKTERM.symbol << "'!";
			throw PluginError(errmsgSS.str());
		}
		
		std::string max = "";
		
		int pos = interp.get()->getStorage().get_first();
		do {
			const OrdinaryAtom& oatom = registry.ogatoms.getByAddress(pos);
			ID curid = oatom.tuple[maskPos]; 
			std::string cur = registry.getTermStringByID(curid);
			if (cur > max) {
				max = cur;
				LOG(DBG, "MaxAtom::calculateAggfun: max = " << max);
			}
			pos = interp.get()->getStorage().get_next(pos);
		} 
		while (pos != 0);
		
		Term t = Term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, max);
		LOG(DBG, "MaxAtom::calculateAggfun: t = " << t);
		ID id = registry.storeTerm(t);
		
		return id;
	}

  }
}

