
#include "MaxAtom.h"

#include <dlvhex2/Term.h>
#include <dlvhex2/Registry.h>
//#include <dlvhex2/Interpretation.h>
//#include <bm.h>

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
			errmsgSS << "There was no occurrence of " << MASKTERM.symbol << "!";
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
	
	/*
	void 
	MaxAtom::calculateAggfun(Term& t) const
	{
		// hack: start with variable
		Term max("X");

		AtomSet::const_iterator cur = projection.begin();
		AtomSet::const_iterator last = projection.end();

		//
		// go through all atoms of the interpretation
		//
		while (cur != last)
		{
			Atom a = *cur;

			for (Tuple::size_type pos = 1; pos <= a.getArity(); pos++)
			{
				// first term - no comparison possible
				if (max.isVariable())
					max = a.getArgument(pos);
				else
				if (a.getArgument(pos).getString() > max.getString())
					max = a.getArgument(pos);
			}

			cur++;
		}

		t = max;
	} */

  }
}

