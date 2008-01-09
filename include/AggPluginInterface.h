/* dlvhex-aggregateplugin -- aggregate atoms for hex-programs.
 * Copyright (C) 2005, 2006, 2007 Roman Schindlauer
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
 * @file   AggPluginInterface.h
 * @author Roman Schindlauer
 * @date   Fri Jul 13 16:36:09 CEST 2007
 * 
 * @brief  aggregateplugin interface declaration.
 * 
 * 
 */

#ifndef _AGGPLUGININTERFACE_H
#define _AGGPLUGININTERFACE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "dlvhex/PluginInterface.h"

#include <string>

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


/**
 * @brief Minimum Aggregate Atom.
 */
class MinAtom : public AggAtom
{
public:

    MinAtom();

private:

	virtual void
	calculateAggfun(Term&) const;
};


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


/**
 * @brief Count Aggregate Atom.
 */
class CountAtom : public AggAtom
{
public:

    CountAtom();

private:

	virtual void
	calculateAggfun(Term&) const;
};



class AggregatePlugin : public PluginInterface
{
public:

    virtual void
    getAtoms(AtomFunctionMap& a);

    void
    setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out);

};


  } // namespace aggregate
} // namespace dlvhex

#endif // _AGGPLUGININTERFACE_H


/* vim: set noet sw=4 ts=4 tw=80: */

// Local Variables:
// mode: C++
// End:
