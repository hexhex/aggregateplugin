#ifndef _AGG_PLUGIN_MINATOM_H_
#define _AGG_PLUGIN_MINATOM_H_

//#include <dlvhex/PluginInterface.h>
#include "AggAtom.h"

#include <dlvhex2/Interpretation.h>

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Minimum Aggregate Atom.
	 */
	class MinAtom : public AggAtom {
	public:
		MinAtom();
		~MinAtom();
	private:
		virtual ID calculateAggfun(InterpretationConstPtr, const Tuple&) const;
	};

  }
}

#endif

