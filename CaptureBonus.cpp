/*
 * Copyright (C) 2015-2018 Vladimir "allejo" Jimenez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "bzfsAPI.h"

const int DEBUG_VERBOSITY = 4;

// Define plugin name
const std::string PLUGIN_NAME = "Capture Bonus";

// Define plugin version numbering
const int MAJOR = 1;
const int MINOR = 0;
const int REV = 0;
const int BUILD = 5;

class CaptureBonus : public bz_Plugin
{
public:
    virtual const char* Name ();
    virtual void Init (const char* config);
    virtual void Event (bz_EventData *eventData);
    virtual void Cleanup (void);

private:
    bool penalizeSelfCapture();
    int calculatePointBonus();
};

BZ_PLUGIN(CaptureBonus)

const char* CaptureBonus::Name(void)
{
    static std::string pluginName;

    if (pluginName.empty())
    {
        pluginName = bz_format("%s %d.%d.%d (%d)", PLUGIN_NAME.c_str(), MAJOR, MINOR, REV, BUILD);
    }

    return pluginName.c_str();
}

void CaptureBonus::Init (const char* commandLine)
{
    Register(bz_eCaptureEvent);

    bz_registerCustomBZDBInt("_captureBonus", 10);
}

void CaptureBonus::Cleanup (void)
{
    Flush();

    bz_removeCustomBZDBVariable("_captureBonus");
}

void CaptureBonus::Event (bz_EventData *eventData)
{
    switch (eventData->eventType)
    {
        case bz_eCaptureEvent:
        {
            bz_CTFCaptureEventData_V1* captureData = (bz_CTFCaptureEventData_V1*)eventData;

            int playerID = captureData->playerCapping;
            int bonusPoints = calculatePointBonus();


            // A self-cap happened but only deduct points if we're configured to do so
            if (captureData->teamCapped == bz_getPlayerTeam(playerID) && penalizeSelfCapture())
            {
                bz_incrementPlayerLosses(playerID, bonusPoints);
                bz_sendTextMessagef(BZ_SERVER, playerID, "You were deducted %d points for capturing your own flag!", bonusPoints);

                return;
            }

            bz_incrementPlayerWins(playerID, bonusPoints);
            bz_sendTextMessagef(BZ_SERVER, playerID, "You were awarded %d points for capturing the flag!", bonusPoints);
        }
        break;

        default:
            break;
    }
}

bool CaptureBonus::penalizeSelfCapture()
{
    return bz_getBZDBBool("_penalizeSelfCapture");
}

int CaptureBonus::calculatePointBonus()
{
    return bz_getBZDBInt("_captureBonus");
}
