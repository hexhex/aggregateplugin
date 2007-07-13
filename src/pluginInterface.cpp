/* dlvhex-aggregateplugin -- aggregate atoms for hex-programs.
 * Copyright (C) 2005, 2006, 2007 Roman Schindlauer
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
 * @file   PluginInterface.h
 * @author Roman Schindlauer
 * @date   Fri Jul 13 16:36:09 CEST 2007
 * 
 * @brief  aggregateplugin interface definition.
 * 
 * 
 */


#include "PluginInterface.h"

minAtom::minAtom()
{
	//
	// let's say, this atom has one constant input parameter...
	//
	addInputConstant();

	//
	// ...and one predicate...
	//
	addInputPredicate();

	//
	// ...and the output is unary.
	//
	setOutputArity(1);
}


void
minAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
{
	//
	// dlvhex will call this function for evaluating the external
	// atom. Whatever is done inside here, is up to the user.
	//

	//
	// let's get the constant of the first input argument:
	//

	std::string in;

	in = query.getInputTuple()[0].getUnquotedString();

	//
	// and the second one, it's a predicate name:
	//

	std::string pred = query.getInputTuple()[1].getUnquotedString();

	//
	// take the interpretation:
	//

	AtomSet i = query.getInterpretation();

	//
	// do something with i, pred and in...
	//

	//
	// ...and prepare the atom's output:
	//

	std::vector<Tuple> out;

	//
	// fill the answer object...
	//

	answer.addTuples(out);
}



void
AggregatePlugin::getAtoms(AtomFunctionMap& a)
{
	a["min"] = new minAtom;
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
