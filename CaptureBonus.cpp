/*
Cap Bonus
    Copyright (C) 2015 Vladimir "allejo" Jimenez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bzfsAPI.h"
#include "plugin_utils.h"

class CaptureBonus : public bz_Plugin
{
public:
    virtual const char* Name () {return "Capture Bonus";}
    virtual void Init (const char* config);
    virtual void Event (bz_EventData *eventData);
    virtual void Cleanup (void);

    virtual int calculatePointBonus (void);
};

BZ_PLUGIN(CaptureBonus)

void CaptureBonus::Init (const char* commandLine)
{
    Register(bz_eCaptureEvent);

    if (!bz_BZDBItemExists("_captureBonus"))
    {
        bz_setBZDBDouble("_captureBonus", 10);
    }
}

void CaptureBonus::Cleanup (void)
{
    Flush();
}

void CaptureBonus::Event (bz_EventData *eventData)
{
    switch (eventData->eventType)
    {
        case bz_eCaptureEvent: // This event is called each time a team's flag has been captured
        {
            bz_CTFCaptureEventData_V1* captureData = (bz_CTFCaptureEventData_V1*)eventData;

            // Data
            // ---
            //    (bz_eTeamType)  teamCapped    - The team whose flag was captured.
            //    (bz_eTeamType)  teamCapping   - The team who did the capturing.
            //    (int)           playerCapping - The player who captured the flag.
            //    (float[3])      pos           - The world position(X,Y,Z) where the flag has been captured
            //    (float)         rot           - The rotational orientation of the capturing player
            //    (double)        eventTime     - This value is the local server time of the event.

            bz_incrementPlayerWins(captureData->playerCapping, calculatePointBonus());
        }
        break;

        default: break;
    }
}

int CaptureBonus::calculatePointBonus (void)
{
    return bz_getBZDBInt("_captureBonus");
}