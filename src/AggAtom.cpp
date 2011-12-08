
#include "AggAtom.h"

namespace dlvhex {
  namespace aggregate {

	AggAtom::AggAtom()
		: MASKTERM("mask")
	{
		addInputPredicate();
		addInputTuple();

		setOutputArity(1);
	}


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


	void
	AggAtom::calculateAggfun(Term& t) const
	{

	}

  }
}
