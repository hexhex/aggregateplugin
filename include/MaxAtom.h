#ifndef _AGG_PLUGIN_AGGATOM_H_
#define _AGG_PLUGIN_AGGATOM_H_

#include "dlvhex/PluginInterface.h"
#include "AggAtom.h"

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Maximum Aggregate Atom.
	 */
	class MaxAtom : public AggAtom
	{
	public:

		MaxAtom();

	private:

		virtual void
		calculateAggfun(Term&) const;
	};

  }
}
