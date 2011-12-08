#ifndef _AGG_PLUGIN_AGGATOM_H_
#define _AGG_PLUGIN_AGGATOM_H_

#include "dlvhex/PluginInterface.h"
#include "AggAtom.h"

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Minimum Aggregate Atom.
	 */
	class MinAtom : public AggAtom
	{
	public:

		MinAtom();

	private:

		virtual void
		calculateAggfun(Term&) const;
	};

  }
}

