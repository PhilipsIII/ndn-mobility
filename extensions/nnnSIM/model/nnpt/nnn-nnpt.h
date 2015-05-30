/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright 2014 Waseda University, Sato Laboratory
 *   Author: Takahiro Miyamoto <mt3.mos@gmail.com>
 *           Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *			 Zhu Li <philipzhuli1990@ruri.waseda.jp>
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

#include <ns3-dev/ns3/node.h>
#include <ns3-dev/ns3/simulator.h>

#include <ostream>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include "nnn-nnpt-entry.h"
#include "../nnn-naming.h"

#include <ns3-dev/ns3/object.h>
#include <ns3-dev/ns3/ptr.h>

using boost::multi_index_container;
using namespace ::boost::multi_index;

namespace ns3
{
  namespace nnn
  {
	/**
     * @ingroup nnn
     * @defgroup nnn-nnpt NNPT
     */

    /**
     * @ingroup nnn-nnpt
     * \brief Namespace for NNPT operations
     */
    namespace nnpt
    {
      class Entry;
    }

    /**
     * @ingroup nnn-nnpt
     * @brief Class implementing NNPT structure & functionality
     */
    class NNPT : public Object
    {
    public:
      struct PtrNNNComp
      {
	bool operator () (const Ptr<const NNNAddress> &lhs , const Ptr<const NNNAddress>  &rhs) const  {
	  return *lhs < *rhs;
	}
      };

      struct oldname {};
      struct newname {};
      struct st_lease {};

      /**
       *  \brief NNPT contains multiple indices: index<oldname>, index<newname>
       *  and index<st_lease>
       */
      typedef multi_index_container<
      	nnpt::Entry,
      	indexed_by<
          ordered_unique<
            tag<st_lease>,
      	    identity<nnpt::Entry>
          >,

          ordered_unique<
            tag<oldname>,
            member<nnpt::Entry,Ptr<const NNNAddress>,&nnpt::Entry::m_oldName>,
            PtrNNNComp
          >,

          ordered_unique<
            tag<newname>,
            member<nnpt::Entry,Ptr<const NNNAddress>,&nnpt::Entry::m_newName>,
            PtrNNNComp
          >
        >
      > pair_set;

      typedef pair_set::index<oldname>::type pair_set_by_oldname;
      typedef pair_set::index<newname>::type pair_set_by_newname;
      typedef pair_set::index<st_lease>::type pair_set_by_lease;

      /**
       * \brief Interface ID
       *
       * \return interface ID
       */
      static TypeId GetTypeId ();

      /**
       * \brief Default constructor
       */
      NNPT();

      /**
       * \brief Virtual destructor
       */
      virtual
      ~NNPT();

      /**
       * \brief Add an entry in NNPT
       */
      void
      addEntry (Ptr<const NNNAddress> oldName, Ptr<const NNNAddress> newName, Time lease_expire);

      /**
       * \brief Delete an entry in NNPT by oldName
       */
      void
      deleteEntry (Ptr<const NNNAddress> oldName);

      /**
       * \brief Delete an entry in NNPT by nnptEntry
       */
      void
      deleteEntry (nnpt::Entry nnptEntry);

      /**
       * \brief Delete an entry in NNPT by oldName & newName
       */
      void
      deleteEntry (Ptr<const NNNAddress> oldName, Ptr<const NNNAddress> newName);

      /**
       * \brief Search for oldName in NNPT
       */
      bool
      foundOldName (Ptr<const NNNAddress> name);

      /**
       * \brief Search for newName in NNPT
       */
      bool
      foundNewName (Ptr<const NNNAddress> name);

      /**
       * \brief Search for the newName in name pair by
       * using oldName in NNPT
       */
      const NNNAddress&
      findPairedName (Ptr<const NNNAddress> oldName);

      /**
       * \brief Search for the oldName in the name pair
       * by using newName in NNPT
       */
      const NNNAddress&
      findPairedOldName (Ptr<const NNNAddress> newName);

      /**
       * \brief Search for the pointer of the newName in the name pair
       * by using oldName in NNPT
       */
      Ptr<const NNNAddress>
      findPairedNamePtr (Ptr<const NNNAddress> oldName);

      /**
       * \brief Search for the pointer of the oldName in the name pair
       * by using newName in NNPT
       */
      Ptr<const NNNAddress>
      findPairedOldNamePtr (Ptr<const NNNAddress> newName);

      /**
       *  \brief Search for one nnpt-entry by one NNNAddress
       */
      nnpt::Entry
      findEntry (Ptr<const NNNAddress> name);

      /**
       *  \brief Update the expire time of the nnpt-entry
       */
      void
      updateLeaseTime (Ptr<const NNNAddress> oldName, Time lease_expire);

      /**
       *  \brief Calculate the size of NNPT
       */
      uint32_t
      size ();

      /**
       *  \brief Check whether the NNPT is empty
       */
      bool
      isEmpty ();

      /**
       *  \brief Check the expire time of a NNNAddress's entry
       */
      Time
      findNameExpireTime (Ptr<const NNNAddress> name);

      /**
       *  \brief Check the expire time of an entry
       */
      Time
      findNameExpireTime (nnpt::Entry nnptEntry);

      /**
       *  \brief Clean out the expired entries in NNPT
       */
      void
      cleanExpired ();

      /**
       *  \brief Print out the NNPT
       */
      void
      Print (std::ostream &os) const;

      /**
       *  \brief Print out the NNPT by the order of oldNames
       */
      void
      printByAddress ();

      /**
       *  \brief Print out the NNPT by the order of leaseTime
       */
      void
      printByLease ();

      pair_set container;
    };

    std::ostream& operator<< (std::ostream& os, const NNPT &nnpt);

  } /* namespace nnn */
} /* namespace ns3 */

#endif /* NNN_NNPT_H_ */
