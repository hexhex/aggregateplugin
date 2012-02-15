#ifndef _AGG_PLUGIN_AGGATOM_H_
#define _AGG_PLUGIN_AGGATOM_H_

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/Term.h>

namespace dlvhex {
  namespace aggregate {

	/**
	 * @brief Base class for Aggregate Atoms.
	 */
	class AggAtom : public PluginAtom
	{
	public:
		AggAtom(std::string atomname);

		virtual void retrieve(const Query& query, Answer& answer) throw (PluginError);

	protected:

		/**
		 * @brief Constant mask term for projecting the input extension.
		 */
		const Term MASKTERM;
		const int numberMaskTermAllowed;

	private:

		/**
		 * @brief Virtual base class for all aggregate functions.
		 */
		virtual ID calculateAggfun(InterpretationConstPtr, const Tuple&) const = 0;

		/**
		 * @brief Reduction of input predicate extension to non-masked arguments.
		 */
		InterpretationConstPtr projectInput(const InterpretationConstPtr, const Tuple&);
	};

  }
}	

#endif
