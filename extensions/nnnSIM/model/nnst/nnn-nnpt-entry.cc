/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright 2014 Waseda University, Sato Laboratory
 *   Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *  nnn-nnpt-entry.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-nnpt-entry.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero Public License for more details.
 *
 *  You should have received a copy of the GNU Affero Public License
 *  along with nnn-nnst-entpy.cc.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "nnn-nnpt-entry.h"

namespace ns3 {
namespace nnn {
//namespace nnpt {

NNPTEntry::NNPTEntry()
	// TODO Auto-generated constructor stub
	  :m_oldName			(NNNAddress ())
	  ,m_newName			(NNNAddress ())
	  ,m_lease_expire	(Seconds (-1))
	  ,m_renew			(Seconds (-1))
{
}

NNPTEntry::~NNPTEntry() {
	// TODO Auto-generated destructor stub
}

NNPTEntry::NNPTEntry (NNNAddress oldName, NNNAddress newName, Time lease_expire)
:m_oldName			(oldName)
,m_newName			(newName)
,m_lease_expire		(lease_expire)
,m_renew			(lease_expire - Seconds (-1))
{
}

NNPTEntry::NNPTEntry (NNNAddress oldName, NNNAddress newName, Time lease_expire, Time renew)
:m_oldName			(oldName)
,m_newName			(newName)
,m_lease_expire		(lease_expire)
{
	if(renew < m_lease_expire)		m_renew = renew;		/////////////////// inverse?????
	else 							m_renew = lease_expire - Seconds(1);
}

//} /* namespace nnpt */
} /* namespace nnn */
} /* namespace ns3 */
