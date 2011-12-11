/* dlvhex-aggregateplugin -- aggregate atoms for hex-programs.
 * Copyright (C) 2007 Roman Schindlauer
 * 
 * This file is part of dlvhex-aggregateplugin.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dlvhex/PrintVisitor.h"

#include "AggPlugin.h"

#include <iostream>

namespace dlvhex {
  namespace aggregate {

	AggregatePlugin::AggregatePlugin() {
		setNameVersion(PACKAGE_TARNAME, AGGREGATEPLUGIN_MAJOR, 
			AGGREGATEPLUGIN_MINOR, AGGREGATEPLUGIN_MICRO);
	}

	~AggregatePlugin::AggregatePlugin() {

	}

	std::vector<PluginAtomPtr> AggregatePlugin::createAtoms(ProgramCtx&) const {
		std::vector<PluginAtomPtr> ret;
		ret.push_back(PluginAtomPtr(new MinAtom, PluginPtrDeleter<PluginAtom>()));
		ret.push_back(PluginAtomPtr(new MaxAtom, PluginPtrDeleter<PluginAtom>()));
		ret.push_back(PluginAtomPtr(new CountAtom, PluginPtrDeleter<PluginAtom>()));
		return ret;
	}

	void AggregatePlugin::processOptions(std::list<const char*>& pluginOptions, 
										ProgramCtx& ctx) {
	}

	void AggregatePlugin::printUsage(std::ostream& o) {
		
	}

	/*
	void
	AggregatePlugin::getAtoms(AtomFunctionMap& a)
	{
	  boost::shared_ptr<PluginAtom> min(new MinAtom);
	  boost::shared_ptr<PluginAtom> max(new MaxAtom);
	  boost::shared_ptr<PluginAtom> count(new CountAtom);
	  a["min"] = min;
	  a["max"] = max;
	  a["count"] = count;
	}
	*/

	/*
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
	*/


	AggregatePlugin theAggregatePlugin;

  } // namespace aggregate
} // namespace dlvhex

/*
extern "C"
dlvhex::aggregate::AggregatePlugin*
PLUGINIMPORTFUNCTION()
{
  dlvhex::aggregate::theAggregatePlugin.setPluginName(PACKAGE_TARNAME);
  dlvhex::aggregate::theAggregatePlugin.setVersion(AGGREGATEPLUGIN_MAJOR,
						   AGGREGATEPLUGIN_MINOR,
						   AGGREGATEPLUGIN_MICRO);

  return &dlvhex::aggregate::theAggregatePlugin;
}
*/

/* vim: set noet sw=4 ts=4 tw=80: */

// Local Variables:
// mode: C++
// End:
