#ifndef _AGG_PLUGIN_COUNTATOM_H_
#define _AGG_PLUGIN_COUNTATOM_H_

#include "AggAtom.h"

#include <dlvhex2/Interpretation.h>

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Count Aggregate Atom.
	 */
	class CountAtom : public AggAtom {
	public:
		CountAtom();
		~CountAtom();
	private:
		virtual ID calculateAggfun(InterpretationConstPtr, const Tuple&) const;
	};

  }
}

#endif

