
#include "AggAtom.h"

#include <dlvhex2/Term.h>
#include <dlvhex2/Registry.h>
#include <dlvhex2/Interpretation.h>

namespace dlvhex {
  namespace aggregate {

	AggAtom::AggAtom(std::string atomname) : PluginAtom(atomname, 0), 
			MASKTERM(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "mask"),
			numberMaskTermAllowed(1)
	{

		addInputPredicate();
		addInputTuple();

		setOutputArity(1);
	}

	void AggAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
		
		Registry &registry = *getRegistry();		

		InterpretationConstPtr interp = this->projectInput(query.interpretation, 
														   query.input);
		ID resultID = this->calculateAggfun(interp, query.input);
		std::string resultStr;
		std::stringstream resultSS;
		
		if (resultID.isIntegerTerm())
			resultSS << resultID.address;
		else if (resultID.isConstantTerm())
			resultSS << registry.getTermStringByID(resultID); 
		else
			assert(false);
		
		resultSS >> resultStr;
		Term result(resultID.kind, resultStr); 

		Tuple tuple;
		tuple.push_back(registry.storeTerm(result));
		answer.get().push_back(tuple);
	}
	
	InterpretationConstPtr AggAtom::projectInput(const InterpretationConstPtr interp, 
												 const Tuple& mask) {
		Registry& registry = *getRegistry();
		
		// filter all occurrences of predicate mask[0]
		PredicateMask pm;
		pm.setRegistry(getRegistry());
		assert(mask[0].isConstantTerm());
		pm.addPredicate(mask[0]);
		pm.updateMask();

		InterpretationPtr interp2(new Interpretation(getRegistry()));
		interp2.get()->add(*interp.get()); 
		interp2.get()->bit_and(*pm.mask().get());
		
		// filter "mask" information
		int pos = interp2.get()->getStorage().get_first();
		do 
		{
			LOG(DBG, "AggAtom::projectInput: pos = " << pos);
			const OrdinaryAtom& oatom = registry.ogatoms.getByAddress(pos);
			LOG(DBG, "AggAtom::projectInput: oatom = " << oatom);
			const Tuple& tuple = oatom.tuple; 
			
			int masktermCount = 0;
			
			for (int i=0; i<mask.size(); i++) 
			{
				// TODO change symbol comparison to ID comparison
				std::string maskSymbol = registry.getTermStringByID(mask[i]);
				std::string tupleSymbol = registry.getTermStringByID(tuple[i]);
				
				LOG(DBG, "AggAtom::projectInput: tuple[" << i << "] = " 
					<< tupleSymbol << ", " << "mask[" << i << "] = " << maskSymbol);
				
				if (maskSymbol.compare(MASKTERM.symbol) == 0) 
				{	
					if (masktermCount >= numberMaskTermAllowed) 
					{
						LOG(DBG, "AggAtom::projectInput: Too many maskterms encountered, throwing PluginError!");
						std::stringstream errmsgSS;
						errmsgSS << "Only " << numberMaskTermAllowed;
						if (numberMaskTermAllowed == 1)
							errmsgSS << " use";
						else
							errmsgSS << " uses";
						errmsgSS << " of '" << MASKTERM.symbol << "' allowed!";
						throw PluginError(errmsgSS.str());
					}
					else
						masktermCount++;
				} 
				
				// remove atoms that don't match non-maskterm-terms
				if ((maskSymbol.compare(MASKTERM.symbol) != 0) && 
				    (maskSymbol.compare(tupleSymbol) != 0)         )
				{
					LOG(DBG, "AggAtom::projectInput: clearing fact!");
					interp2.get()->clearFact(pos);
				}
			}
			pos = interp2.get()->getStorage().get_next(pos);
			
			LOG(DBG, "AggAtom::projectInput: masktermCount = " << masktermCount);
			assert (masktermCount <= numberMaskTermAllowed); // TODO
		}
		while (pos != 0);
		
		LOG(DBG, "AggAtom::projectInput: interp2 = " << *interp2);
		
		return interp2;
	}
	
  }
}
