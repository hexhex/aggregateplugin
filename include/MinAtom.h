#ifndef _AGG_PLUGIN_MINATOM_H_
#define _AGG_PLUGIN_MINATOM_H_

//#include <dlvhex/PluginInterface.h>
#include "AggAtom.h"

#include <dlvhex/Interpretation.hpp>

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
		virtual ID calculateAggfun(InterpretationConstPtr);
	};

  }
}

#endif

