#pragma once
/*
* OutputGECERmt.h - GECE driver code for ESPixelStick RMT Channel
*
* Project: ESPixelStick - An ESP8266 / ESP32 and E1.31 based pixel driver
* Copyright (c) 2015, 2025 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*   This is a derived class that converts data in the output buffer into
*   pixel intensities and then transmits them through the configured serial
*   interface.
*
*/
#include "ESPixelStick.h"
#if defined(SUPPORT_OutputType_GECE) && defined(ARDUINO_ARCH_ESP32)

#include "OutputGECE.hpp"
#include "OutputRmt.hpp"

class c_OutputGECERmt : public c_OutputGECE
{
public:
    // These functions are inherited from c_OutputCommon
    c_OutputGECERmt (c_OutputMgr::e_OutputChannelIds OutputChannelId,
                     gpio_num_t outputGpio,
                     uart_port_t uart,
                     c_OutputMgr::e_OutputType outputType);
    virtual ~c_OutputGECERmt ();

    // functions to be provided by the derived class
    void    Begin ();                                         ///< set up the operating environment based on the current config (or defaults)
    bool    SetConfig (ArduinoJson::JsonObject& jsonConfig);  ///< Set a new config in the driver
    uint32_t Poll ();                                        ///< Call from loop (),  renders output data
#if defined(ARDUINO_ARCH_ESP32)
    bool    RmtPoll ();
#endif // defined(ARDUINO_ARCH_ESP32)
    void    GetStatus (ArduinoJson::JsonObject& jsonStatus);
    void    SetOutputBufferSize (uint32_t NumChannelsAvailable);
    void    PauseOutput (bool State);

private:

    c_OutputRmt Rmt;

}; // c_OutputGECERmt

#endif // defined(SUPPORT_OutputType_GECE) && defined(ARDUINO_ARCH_ESP32)
