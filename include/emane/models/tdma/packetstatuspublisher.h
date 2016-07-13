/*
 * Copyright (c) 2015-2016 - Adjacent Link LLC, Bridgewater, New Jersey
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of Adjacent Link LLC nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EMANEMODELSTDMAPACKETSTATUSPUBLISHER_HEADER_
#define EMANEMODELSTDMAPACKETSTATUSPUBLISHER_HEADER_

#include "emane/models/tdma/messagecomponent.h"

namespace EMANE
{
  namespace Models
  {
    namespace TDMA
    {
      /**
       * @class PacketStatusPublisher
       *
       * @brief Packet status interface used to publish statistics and
       * tables showing accepted and rejected byte counts along with
       * reasons.
       */
      class PacketStatusPublisher
      {
      public:
        /**
         * Destroys an instance.
         */
        virtual ~PacketStatusPublisher(){}

        /**
         * Inbound packet (upstream) status codes
         */
        enum class InboundAction
        {
          ACCEPT_GOOD, /**< Accepted and sent upstream*/
          DROP_BAD_CONTROL,/**< Dropped bad control message*/
          DROP_SLOT_NOT_RX,/**< Dropped received slot not rx slot*/
          DROP_SLOT_MISSED_RX,/**< Dropped received late*/
          DROP_MISS_FRAGMENT,/**< Dropped one or more fragments missing*/
          DROP_SPECTRUM_SERVICE,/**< Dropped due to Spectrum service query error*/
          DROP_SINR,/**< Dropped due to SINR*/
          DROP_REGISTRATION_ID,/**< Dropped not for this radio model*/
          DROP_DESTINATION_MAC,/**< Dropped not for this NEM*/
          DROP_TOO_LONG/**< Dropped packet propagation plus duration more than a slot*/
        };

        /**
         * OUtbound packet (downstream> status codes
         */
        enum class OutboundAction
        {
          ACCEPT_GOOD, /**< Accepted and sent downstream */
          DROP_TOO_BIG, /**< Dropped too big and fragmentation disabled */
          DROP_OVERFLOW, /**< Dropped queue overflow */
          DROP_FLOW_CONTROL /**< Dropped flow control error */
         };

        /**
         * Records status of inbound message components

         * @param src NEM message source
         * @param component MessageComponent entry
         * @param action Action status code
         */
        virtual void inbound(NEMId src,
                             const MessageComponent & component,
                             InboundAction action) = 0;

        /**
         * Records status of inbound message components
         *
         * @param src NEM message source
         * @param components MessageComponent entries
         * @param action Action status code
         */
        virtual void inbound(NEMId src,
                             const MessageComponents & components,
                             InboundAction action) = 0;

        /**
         * Records status of inbound message components
         *
         * @param src NEM message source
         * @param dst NEM message destination
         * @param priority Message priority
         * @param size Message size in bytes
         * @param action Action status code
         */
        virtual void inbound(NEMId src,
                             NEMId dst,
                             Priority priority,
                             size_t size,
                             InboundAction action) = 0;

        /**
         * Records status of outbound message components
         *
         * @param src NEM message source
         * @param dst NEM message destination
         * @param priority Message priority
         * @param size Message size in bytes
         * @param action Action status code
         */
        virtual void outbound(NEMId src,
                              NEMId dst,
                              Priority priority,
                              size_t size,
                              OutboundAction action) = 0;

        /**
         * Records status of outbound message components
         *
         * @param src NEM message source
         * @param components MessageComponent entries
         * @param action Action status code
         */
        virtual void outbound(NEMId src,
                              const MessageComponents & components,
                              OutboundAction action) = 0;

      protected:
        /**
         * Creates an instance
         */
        PacketStatusPublisher(){}
      };
    }
  }
}

#endif // EMANEMODELSTDMAPACKETSTATUSPUBLISHER_HEADER_
