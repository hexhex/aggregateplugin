#ifndef _AGG_PLUGIN_MAXATOM_H_
#define _AGG_PLUGIN_MAXATOM_H_

//#include <dlvhex/PluginInterface.h>
#include "AggAtom.h"

#include <dlvhex/Interpretation.hpp>

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Maximum Aggregate Atom.
	 */
	class MaxAtom : public AggAtom {
	public:
		MaxAtom();
		~MaxAtom();
	private:
		virtual ID calculateAggfun(InterpretationConstPtr) const;
	};

  }
}

#endif 
