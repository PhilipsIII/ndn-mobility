/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright 2014 Waseda University, Sato Laboratory
 *   Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *  nnn-nnpt.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-nnpt.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero Public License for more details.
 *
 *  You should have received a copy of the GNU Affero Public License
 *  along with nnn-nnpt.h.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NNN_NNPT_H_
#define NNN_NNPT_H_

#include <ns3-dev/ns3/simple-ref-count.h>
#include <ns3-dev/ns3/node.h>
#include <ns3-dev/ns3/simulator.h>

#include <ostream>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include "nnn-nnpt-entry.h"
#include "../nnn-naming.h"


using boost::multi_index_container;
using namespace ::boost::multi_index;


namespace ns3 {
namespace nnn {

struct pair {};
struct lease {};

typedef multi_index_container<
	NNPTEntry,
	indexed_by<
		// sort by NamesContainer::operator<
		ordered_unique<
			tag<lease>,
			identity<NNPTEntry>
		>,

		// sort by less<string> on NamesContainerEntry
		ordered_unique<
			tag<pair>,
			member<NNPTEntry,NamesContainerEntry,&NNPTEntry::m_oldName>
		>
	>
> pair_set;

typedef pair_set::index<pair>::type pair_set_by_name;
typedef pair_set::index<lease>::type pair_set_by_lease;

class NNPT : public SimpleRefCount<NNPT>
{

public:
	static TypeId GetTypeId ();

	NNPT();

	virtual
	~NNPT();

//	void
//	addEntry (NamesContainerEntry oldName, NamesContainerEntry newName);

	void
	addEntry (NamesContainerEntry oldName, NamesContainerEntry newName, Time lease_expire);

	void
	addEntry (NamesContainerEntry oldName, NamesContainerEntry newName, Time lease_expire, Time renew);

	void
	addEntry (NNPTEntry nnptEntry);

	void
	deleteEntry (NamesContainerEntry oldName);

	void
	deleteEntry (NNPTEntry nnptEntry);

	void
	deleteEntry (NamesContainerEntry oldName, NamesContainerEntry newName);

	bool
	foundName (NamesContainerEntry name);

	NNPTEntry
	findEntry (NamesContainerEntry name);

	NamesContainerEntry
	findNewestName ();

	void
	updateLeaseTime (NamesContainerEntry oldName, Time lease_expire);

	void
	updateLeaseTime (NamesContainerEntry oldName, Time lease_expire, Time renew);

	uint32_t
	size ();

	bool
	isEmpty ();

	Time
	findNameExpireTime (NamesContainerEntry name);

	Time
	findNameExpireTime (NNPTEntry nnptEntry);

	void
	cleanExpired ();

	void
	printByAddress ();

	void
	printByLease ();

	void
	informEntry (NamesContainerEntry oldName, NamesContainerEntry newName, Time lease_expire);

	pair_set container;

};

} /* namespace nnn */
} /* namespace ns3 */

#endif /* NNN_NNPT_H_ */
