
#include "CountAtom.h"

namespace dlvhex {
  namespace aggregate {

	CountAtom::CountAtom()
		: AggAtom()
	{
	}


	void
	CountAtom::calculateAggfun(Term& t) const
	{
		t = Term(this->projection.size());
	}

  }
}
