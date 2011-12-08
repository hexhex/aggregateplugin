
#include "MinAtom.h"

namespace dlvhex {
  namespace aggregate {

	MinAtom::MinAtom()
		: AggAtom()
	{

	}

	void
	MinAtom::calculateAggfun(Term& t) const
	{
		// hack: start with variable
		Term min("X");

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
				if (min.isVariable())
					min = a.getArgument(pos);
				else
				if (a.getArgument(pos).getString() < min.getString())
					min = a.getArgument(pos);
			}

			cur++;
		}

		t = min;
	}

  }
}
