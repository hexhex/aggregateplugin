
#include "AggAtom.h"

#include <dlvhex/Term.hpp>
#include <dlvhex/Registry.hpp>
#include <dlvhex/Interpretation.hpp>

namespace dlvhex {
  namespace aggregate {

	// SABINE: OK
	AggAtom::AggAtom(std::string atomname) : PluginAtom(atomname, 0), 
		MASKTERM(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "mask") {

		addInputPredicate();
		addInputTuple();

		setOutputArity(1);
	}

	void AggAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
		
		Registry &registry = *getRegistry();		

		InterpretationConstPtr interp = this->projectInput(query.interpretation, query.input);

		Term &result = this->calculateAggfun(interp);

		Tuple tuple;
		tuple.push_back(registry.storeTerm(result));
		answer.get().push_back(tuple);
	}

	/*
	void
	AggAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
	{
		Tuple inputTuple = query.getInputTuple();

		//
		// we don't need the predicate name at the beginning of the input tuple any more,
		// the interpretation is already filtered
		//
		inputTuple.erase(inputTuple.begin());

		this->projectInput(query.getInterpretation(), inputTuple);

		//	RawPrintVisitor rpv(std::cerr);
		//	this->projection.accept(rpv);

		Term res;
		this->calculateAggfun(res);

		Tuple out;

		out.push_back(res);

		answer.addTuple(out);
	}
	*/
	
	InterpretationConstPtr AggAtom::projectInput(const InterpretationConstPtr interp, const Tuple& mask) {

		//this->projection.clear();

		PredicateMask pm;
		pm.setRegistry(getRegistry());

		assert(mask[0].isConstantTerm());
		LOG(DBG, "AggAtom::projectInput: mask = " << mask[0]);
		pm.addPredicate(mask[0]);
		pm.updateMask();

		InterpretationPtr interp2(new Interpretation(getRegistry()));
		interp2.get()->add(*interp.get()); 
		interp2.get()->bit_and(*pm.mask().get());

		return interp2;
		
		/*
		#warning use TrueBits once it's merged into dlvhex-refactoring		
		for (Storage::enumerator en = interp.getStorage().first();
			 en++; en != interp.getStorage().end()) {

			IDAddress adr = *en;
			pm.addPredicate();

		}
		*/
	}
	

	/*
	void
	AggAtom::projectInput(const AtomSet& i, const Tuple& mask)
	{
		this->projection.clear();

		AtomSet::const_iterator cur = i.begin();
		AtomSet::const_iterator last = i.end();

		//
		// go through all atoms of the interpretation
		//
		while (cur != last)
		{
			Atom a = *cur;

			if (a.getArity() != mask.size())
				throw PluginError("Aggregate mask does not correspond to predicate arity!");

			bool drop(0);

			Tuple newarg;

			newarg.push_back(a.getPredicate());

			for (Tuple::size_type pos = 0; pos < mask.size(); pos++)
			{
				if (mask[pos].getUnquotedString() == AggAtom::MASKTERM.getUnquotedString())
				{
					newarg.push_back(a.getArgument(pos+1));
				}
				else
				if (mask[pos] != a.getArgument(pos+1))
					drop = 1;
			}

			if (!drop)
			{
				AtomPtr ap(new Atom(newarg));
				this->projection.insert(ap);
			}

			cur++;
		}
	}
	*/

	Term& AggAtom::calculateAggfun(InterpretationConstPtr interp) const {

	}

  }
}
