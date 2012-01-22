
#include "CountAtom.h"

#include <dlvhex/Interpretation.hpp>
#include <boost/lexical_cast.hpp>

namespace dlvhex {
  namespace aggregate {

	CountAtom::CountAtom() : AggAtom("count") { }

	CountAtom::~CountAtom() { }

	ID CountAtom::calculateAggfun(InterpretationConstPtr interp, const Tuple& input) const {
	
		int count = interp.get()->getStorage().count();
		LOG(DBG, "CountAtom::calculateAggfun: count = " << count);
		ID id = ID::termFromInteger(count); 
		LOG(DBG, "CountAtom::calculateAggfun: id = " << id);
		return id;
	}

  }
}
