#ifndef _AGG_PLUGIN_AGGATOM_H_
#define _AGG_PLUGIN_AGGATOM_H_

#include "dlvhex/PluginInterface.h"

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Base class for Aggregate Atoms.
	 */
	class AggAtom : public PluginAtom
	{
	public:
		AggAtom();

		virtual void
		retrieve(const Query& query, Answer& answer) throw (PluginError);

	protected:

		/**
		 * @brief Extension of input predicate after masking.
		 */
		AtomSet projection;

		/**
		 * @brief Constant mask term for projecting the input extension.
		 */
		const Term MASKTERM;

	private:

		/**
		 * @brief Virtual base class for all aggregate functions.
		 */
		virtual void
		calculateAggfun(Term&) const;

		/**
		 * @brief Reduction of input predicate extension to non-masked arguments.
		 */
		void
		projectInput(const AtomSet&, const Tuple&);
	};

  }
}	

#endif
