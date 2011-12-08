
#include "MaxAtom.h"

namespace dlvhex {
  namespace aggregate {

	MaxAtom::MaxAtom()
		: AggAtom()
	{

	}

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
	}

  }
}

