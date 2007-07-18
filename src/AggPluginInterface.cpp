/* dlvhex-aggregateplugin -- aggregate atoms for hex-programs.
 * Copyright (C) 2007 Roman Schindlauer
 * 
 * dlvhex-aggregateplugin is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * dlvhex-aggregateplugin is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * dlvhex-aggregateplugin; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * @file   AggPluginInterface.cpp
 * @author Roman Schindlauer
 * @date   Fri Jul 13 16:36:09 CEST 2007
 * 
 * @brief  aggregateplugin interface definition.
 * 
 * 
 */


#include "AggPluginInterface.h"
#include "dlvhex/PrintVisitor.h"



AggAtom::AggAtom()
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
			if (mask[pos].getUnquotedString() == "mask")
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



MinAtom::MinAtom()
	: AggAtom()
{
}

void
MinAtom::calculateAggfun(Term& t) const
{
	// hack: start with variable
	Term min("X");

	AtomSet::const_iterator cur = projection.begin();
	AtomSet::const_iterator last = projection.end();

	//
	// go through all atoms of the interpretation
	//
	while (cur != last)
	{
		Atom a = *cur;

		for (Tuple::size_type pos = 1; pos <= a.getArity(); pos++)
		{
			// first term - no comparison possible
			if (min.isVariable())
				min = a.getArgument(pos);
			else
			if (a.getArgument(pos).getString() < min.getString())
				min = a.getArgument(pos);
		}

		cur++;
	}

	t = min;
}


MaxAtom::MaxAtom()
	: AggAtom()
{
}

void
MaxAtom::calculateAggfun(Term& t) const
{
	// hack: start with variable
	Term max("X");

	AtomSet::const_iterator cur = projection.begin();
	AtomSet::const_iterator last = projection.end();

	//
	// go through all atoms of the interpretation
	//
	while (cur != last)
	{
		Atom a = *cur;

		for (Tuple::size_type pos = 1; pos <= a.getArity(); pos++)
		{
			// first term - no comparison possible
			if (max.isVariable())
				max = a.getArgument(pos);
			else
			if (a.getArgument(pos).getString() > max.getString())
				max = a.getArgument(pos);
		}

		cur++;
	}

	t = max;
}



CountAtom::CountAtom()
	: AggAtom()
{
}


void
CountAtom::calculateAggfun(Term& t) const
{
	t = Term(this->projection.size());
}




void
AggregatePlugin::getAtoms(AtomFunctionMap& a)
{
	a["min"] = new MinAtom;
	a["max"] = new MaxAtom;
	a["count"] = new CountAtom;
}


void
AggregatePlugin::setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out)
{
	if (doHelp)
	{
		out << "some-plugin: " << std::endl << std::endl;
		out << " --myswitch=FOO       Use FOO as bar." << std::endl;
		out << " --anotherone         Turn off light." << std::endl;
		return;
	}

	std::vector<std::vector<std::string>::iterator> found;

	//
	// go through options that were left from dlvhex-main()
	//
	for (std::vector<std::string>::iterator it = argv.begin();
			it != argv.end();
			it++)
	{
		std::string::size_type o;

		o = it->find("--myswitch=");

		if (o != std::string::npos)
		{
			std::string option = it->substr(o + 11); // length of parameter = 11

			//
			// do something with this option
			//

			// remember to delete it from list:
			found.push_back(it);
		}

		o = it->find("--anotherone");

		//
		// process second switch...
		//
	}

	//
	// delete all found options, dlvhex would complain about them!
	// 
	for (std::vector<std::vector<std::string>::iterator>::const_iterator it = found.begin();
		it != found.end(); ++it)
	{
		argv.erase(*it);
	}
}


AggregatePlugin theAggregatePlugin;

extern "C"
AggregatePlugin*
PLUGINIMPORTFUNCTION()
{
    theAggregatePlugin.setVersion(AGGREGATEPLUGIN_MAJOR,
                                  AGGREGATEPLUGIN_MINOR,
                                  AGGREGATEPLUGIN_MICRO);

    return &theAggregatePlugin;
}


/* vim: set noet sw=4 ts=4 tw=80: */

// Local Variables:
// mode: C++
// End:
