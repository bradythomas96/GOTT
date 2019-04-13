//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef SPINNAKER_GENAPI_IPORT_H
#define SPINNAKER_GENAPI_IPORT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"

#ifdef _WIN32
#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        /**
        *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
        */
        /*@{*/

        /**
        *  @defgroup IPort_h IPort Interface
        */
        /*@{*/

        //*************************************************************
        // IPort interface
        //*************************************************************

        /**
        * @brief Interface for ports
        */
        interface SPINNAKER_API_ABSTRACT IPort : virtual public IBase
        {
            /**
            * Reads a chunk of bytes from the port
            */
            virtual void Read(void *pBuffer, int64_t Address, int64_t Length) = 0;

            /**
            * Writes a chunk of bytes to the port
            */
            virtual void Write(const void *pBuffer, int64_t Address, int64_t Length) = 0;
        };

        /*@}*/
        /*@}*/
    }
}

#ifdef _WIN32
#pragma warning ( pop )
#endif

#endif // ifndef SPINNAKER_GENAPI_IPORT_H
