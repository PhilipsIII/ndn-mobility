/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright 2015 Waseda University, Sato Laboratory
 *   Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *  nnn-pdu-buffer.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-pdu-buffer.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero Public License for more details.
 *
 *  You should have received a copy of the GNU Affero Public License
 *  along with nnn-pdu-buffer.h.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PDU_BUFFER_H_
#define PDU_BUFFER_H_

#include <ns3-dev/ns3/traced-value.h>
#include <ns3-dev/ns3/trace-source-accessor.h>
#include <ns3-dev/ns3/object.h>
#include <ns3-dev/ns3/ptr.h>

#include "../nnn-pdus.h"
#include "../nnn-naming.h"
#include "../../utils/trie/trie.h"
#include "../../utils/trie/counting-policy.h"
#include "../../utils/trie/trie-with-policy.h"

#include "nnn-pdu-buffer-queue.h"

namespace ns3
{
  namespace nnn
  {
	/**
     * @ingroup nnn
     * @defgroup nnn-pdu-buffer PDUBuffer
     */

   /**
    * @ingroup nnn-pdu-buffer
    * @brief Class implementing PDUBuffer functionality
    */
    class PDUBuffer : public Object,
    protected ns3::nnn::nnnSIM::trie_with_policy<
      NNNAddress,
      ns3::nnn::nnnSIM::smart_pointer_payload_traits<PDUQueue>,
      ns3::nnn::nnnSIM::counting_policy_traits
    >
    {
    public:
      typedef ns3::nnn::nnnSIM::trie_with_policy<
	  NNNAddress,
	  ns3::nnn::nnnSIM::smart_pointer_payload_traits<PDUQueue>,
	  ns3::nnn::nnnSIM::counting_policy_traits
      > super;

      /**
       * \brief Interface ID
       *
       * \return interface ID
       */
      static TypeId GetTypeId (void);

      /**
       * @brief Default constructor
       */
      PDUBuffer ();

      PDUBuffer (Time retx);

      /**
       * \brief Virtual destructor
       */
      virtual
      ~PDUBuffer ();

      /**
       * \brief Add PDU's NNNAddress to the buffer
       */
      void
      AddDestination (const NNNAddress &addr);

      /**
       * \brief Add PDU's <Ptr>NNNAddress to the buffer
       */
      void
      AddDestination (Ptr<NNNAddress> addr);

      /**
       * \brief Remove PDU's NNNAddress from the buffer
       */
      void
      RemoveDestination (const NNNAddress &addr);

      /**
       * \brief Remove PDU's <Ptr>NNNAddress from the buffer
       */
      void
      RemoveDestination (Ptr<NNNAddress> addr);

      /**
       *  \brief Check in the buffer whether Destination NNNAddress
       *  exists or not and find out what it is
       */
      bool
      DestinationExists (const NNNAddress &addr);

      /**
       *  \brief Check in the buffer whether Destination <Ptr>NNNAddress
       *  exists or not and find out what it is
       */
      bool
      DestinationExists (Ptr<NNNAddress> addr);

      /**
       *  \brief Push the SO PDU to the NNNAddress added in the buffer
       */
      void
      PushSO (const NNNAddress &addr, Ptr<const SO> so_p);

      /**
       *  \brief Push the SO PDU to the <Ptr>NNNAddress added in the buffer
       */
      void
      PushSO (Ptr<NNNAddress> addr, Ptr<const SO> so_p);

      /**
       *  \brief Push the DO PDU to the NNNAddress added in the buffer
       */
      void
      PushDO (const NNNAddress &addr, Ptr<const DO> do_p);

      /**
       *  \brief Push the DO PDU to the <Ptr>NNNAddress added in the buffer
       */
      void
      PushDO (Ptr<NNNAddress> addr, Ptr<const DO> do_p);

      /**
       *  \brief Push the DU PDU to the NNNAddress added in the buffer
       */
      void
      PushDU (const NNNAddress &addr, Ptr<const DU> du_p);

      /**
       *  \brief Push the DU PDU to the <Ptr>NNNAddress added in the buffer
       */
      void
      PushDU (Ptr<NNNAddress> addr, Ptr<const DU> du_p);

      /**
       *  \brief Create a queue for PDUs with the same NNNAddress
       */
      std::queue<Ptr<Packet> >
      PopQueue (const NNNAddress &addr);

      /**
       *  \brief Create a queue for PDUs with the same <Ptr>NNNAddress
       */
      std::queue<Ptr<Packet> >
      PopQueue (Ptr<NNNAddress> addr);

      /**
       *  \brief get the size of queue of PDUs with the same NNNAddress
       */
      uint
      QueueSize (const NNNAddress &addr);

      /**
       *  \brief get the size of queue of PDUs with the same <Ptr>NNNAddress
       */
      uint
      QueueSize (Ptr<NNNAddress> addr);

      void
      SetReTX (Time rtx);

      Time
      GetReTX () const;

    private:
      Time m_retx;
    };

    std::ostream& operator<< (std::ostream& os, const PDUBuffer &buffer);

  } /* namespace nnn */
} /* namespace ns3 */

#endif /* PDU_BUFFER_H_ */
