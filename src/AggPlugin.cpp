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

#include "AggPlugin.h"

#include "MinAtom.h"
#include "MaxAtom.h"
#include "CountAtom.h"

namespace dlvhex {
  namespace aggregate {

	AggregatePlugin::AggregatePlugin() {
		setNameVersion(PACKAGE_TARNAME, AGGREGATEPLUGIN_VERSION_MAJOR, 
			AGGREGATEPLUGIN_VERSION_MINOR, AGGREGATEPLUGIN_VERSION_MICRO);
		LOG(DBG, "AggregatePlugin::AggregatePlugin");
	}

	AggregatePlugin::~AggregatePlugin() {

	}

	std::vector<PluginAtomPtr> AggregatePlugin::createAtoms(ProgramCtx&) const {
		LOG(DBG, "AggregatePlugin::createAtoms");
		std::vector<PluginAtomPtr> ret;
		ret.push_back(PluginAtomPtr(new MinAtom, PluginPtrDeleter<PluginAtom>()));
		ret.push_back(PluginAtomPtr(new MaxAtom, PluginPtrDeleter<PluginAtom>()));
		ret.push_back(PluginAtomPtr(new CountAtom, PluginPtrDeleter<PluginAtom>()));
		return ret;
	}

	AggregatePlugin theAggregatePlugin;

  } // namespace aggregate
} // namespace dlvhex

IMPLEMENT_PLUGINABIVERSIONFUNCTION

extern "C"
void *PLUGINIMPORTFUNCTION() {
	return reinterpret_cast<void*>(& dlvhex::aggregate::theAggregatePlugin);
}

/* vim: set noet sw=4 ts=4 tw=80: */

// Local Variables:
// mode: C++
// End:
