/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright 2014 Waseda University, Sato Laboratory
 *   Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *	             Zhu Li <philipszhuli1990@ruri.waseda.jp>
 *
 *  nnn-den.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-den.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero Public License for more details.
 *
 *  You should have received a copy of the GNU Affero Public License
 *  along with nnn-den.h.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NNN_DEN_HEADER_H_
#define _NNN_DEN_HEADER_H_

#include "../nnn-pdu.h"
#include "../nnn-en-pdus.h"
#include "../../nnn-naming.h"

namespace ns3
{
  namespace nnn
  {
    /**
     * @ingroup nnn
     * @brief NNN DEN packet (wire formats are defined in wire)
     **/
    class DEN : public ENPDU
    {
    public:
      /**
       * \brief Constructor
       *
       * Creates a REN packet
       **/
      DEN ();

      /**
       * \brief Constructor
       *
       *
       * @param name NNN Address Ptr
       **/
      DEN(Ptr<NNNAddress> name);

      /**
       * \brief Constructor
       *
       * Creates a DEN packet with payload
       *
       * @param name NNN Address
       * @param payload Packet Ptr
       **/
      DEN(const NNNAddress &name);

      /**
       * @brief Copy constructor
       */
      DEN (const DEN &den_p);

      /**
       * \brief Get interest name
       *
       * Gets name of the interest.
       **/
      const NNNAddress&
      GetName () const;

      /**
       * @brief Get smart pointer to the interest name (to avoid extra memory usage)
       */
      Ptr<const NNNAddress>
      GetNamePtr () const;

      /**
       * \brief Set interest name
       *
       * @param name smart pointer to Name
       *
       **/
      void
      SetName (Ptr<NNNAddress> name);

      /**
       * \brief Another variant to set interest name
       *
       * @param name const reference to Name object
       *
       **/
      void
      SetName (const NNNAddress &name);

      /**
       * @brief Print DEN in plain-text to the specified output stream
       */
      void
      Print (std::ostream &os) const;

    private:
      // NO_ASSIGN
      DEN &
      operator = (const DEN &other) { return *this; }

    protected:
      Ptr<NNNAddress> m_name;   ///< @brief NNN Address used in the packet
    };

    inline std::ostream &
    operator << (std::ostream &os, const DEN &i)
    {
      i.Print (os);
      return os;
    }

    /**
     * @brief Class for Interest parsing exception
     */
    class DENException {};
  } //namespace nnn
} //namespace ns3

#endif // _NNN_DEN_HEADER_H_
