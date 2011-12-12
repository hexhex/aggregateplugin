#ifndef _AGG_PLUGIN_COUNTATOM_H_
#define _AGG_PLUGIN_COUNTATOM_H_

#include <dlvhex/PluginInterface.h>
#include "AggAtom.h"

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Count Aggregate Atom.
	 */
	class CountAtom : public AggAtom
	{
	public:

		CountAtom();

	private:

		virtual void
		calculateAggfun(Term&) const;
	};

  }
}

#endif

