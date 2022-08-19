/*
 * Copyright (c) 2022 - Adjacent Link LLC, Bridgewater, New Jersey
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
 * * Neither the name of Adjacent Link, LLC nor the names of its
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


#ifndef EMANESINRTABLE_HEADER_
#define EMANESINRTABLE_HEADER_

#include "emane/types.h"
#include "emane/statisticregistrar.h"
#include "emane/configurationinfo.h"
#include "emane/registrar.h"

#include <uuid.h>

namespace EMANE
{
 /**
  *
  * @class SINRTable
  *
  * @brief Manages SINR Table
  *
  */
  class SINRTable
  { 
    public:
     /**
      * Creates a SINRTable instance
      *
      * @param nemId NEM id
      */
      SINRTable(NEMId nemId);
    
     /**
      * Destroys an instance
      *
      */
      ~SINRTable();


     void initialize(EMANE::Registrar & registrar);

     void configure(const EMANE::ConfigurationUpdate & update);

     /**
      * Updates sinr metrics
      *
      * @param src                     src NEM
      * @param rxAntennaId             rx antenna Id
      * @param frequencyHz             frequency in Hz
      * @param fRxPower_mW             rx power in milli watts
      * @param fNoiseFloor_mW          nosie floor milli watts
      * @param freceiverSensitivity_mW receiver sensitivity milli watts
      *
      */
     void update(NEMId src,
                 AntennaIndex rxAntennaId,
                 std::uint64_t frequencyHz,
                 double fRxPower_mW,
                 double fNoiseFloor_mW,
                 double fReceiverSensitivity_mW);

     /**
      * Clear all sinr table entries for a given antenna
      *
      * @param rxAntennaId             rx antenna Id
      *
      */
     void reset(AntennaIndex rxAntennaId);

     /**
      * Clear all sinr table entries
      *
      */
     void resetAll();


   private:
     class Implementation;

     std::unique_ptr<Implementation> pImpl_;

     SINRTable(const SINRTable &) = delete;

     SINRTable & operator=(const SINRTable &) = delete;
  };
}

#endif // EMANESINRTABLE_HEADER_
