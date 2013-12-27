/*

FF32lite from FocusFlight, a new alternative firmware
for the Naze32 controller

Original work Copyright (c) 2013 John Ihlein

This file is part of FF32lite.

Includes code and/or ideas from:

  1)BaseFlight
  2)S.O.H. Madgwick

FF32lite is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

FF32lite is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FF32lite. If not, see <http://www.gnu.org/licenses/>.

*/

///////////////////////////////////////////////////////////////////////////////

#include "board.h"

///////////////////////////////////////////////////////////////////////////////

uint8_t escCalibrating = false;
char    temp;

///////////////////////////////////////////////////////////////////////////////
// ESC Calibration
///////////////////////////////////////////////////////////////////////////////

void escCalibration(void)
{
    escCalibrating = true;

    armed = false;

    cliPrint("\nESC Calibration:\n\n");
    cliPrint("!!!! CAUTION - Remove all propellers and disconnect !!!!\n");
    cliPrint("!!!! flight battery before proceeding any further   !!!!\n\n");
    cliPrint("Type 'Y' to continue, any other character exits\n\n");

    while (cliAvailable() == false);
    temp = cliRead();
    if (temp != 'Y')
    {
    	cliPrint("ESC Calibration Canceled!!\n\n");
    	escCalibrating = false;
    	return;
    }

    ///////////////////////////////////

    cliPrint("Enter 'h' for Max Command....\n");
    cliPrint("Enter 'm' for Mid Command....\n");
    cliPrint("Enter 'l' for Min Command....\n");
    cliPrint("Enter 'x' to exit....\n\n");

    while(true)
    {
		while (cliAvailable() == false);

		temp = cliRead();

		switch (temp)
		{
			case 'h':
			    cliPrint("Applying Max Command....\n\n");
			    writeAllMotors(eepromConfig.maxThrottle);
			    break;

			case 'm':
			    cliPrint("Applying Mid Command....\n\n");
			    writeAllMotors(eepromConfig.midCommand);
			    break;

			case 'l':
			    cliPrint("Applying Min Command....\n\n");
			    writeAllMotors(MINCOMMAND);
			    break;

			case 'x':
			    cliPrint("Applying Min Command, Exiting Calibration....\n\n");
			    writeAllMotors(MINCOMMAND);
			    escCalibrating = false;
			    return;
			    break;

			case '0':
			    cliPrint("Motors at  Min Command....\n\n");
			    writeAllMotors(MINCOMMAND);
			    break;

			case '1':
				cliPrint("Motor1 at Min Throttle....\n\n");
				pwmEscWrite(0, eepromConfig.minThrottle);
				break;

			case '2':
				cliPrint("Motor2 at Min Throttle....\n\n");
				pwmEscWrite(1, eepromConfig.minThrottle);
				break;

			case '3':
				cliPrint("Motor3 at Min Throttle....\n\n");
				pwmEscWrite(2, eepromConfig.minThrottle);
				break;

			case '4':
				cliPrint("Motor4 at Min Throttle....\n\n");
				pwmEscWrite(3, eepromConfig.minThrottle);
				break;

			case '5':
				cliPrint("Motor5 at Min Throttle....\n\n");
				pwmEscWrite(4, eepromConfig.minThrottle);
				break;

			case '6':
				cliPrint("Motor6 at Min Throttle....\n\n");
				pwmEscWrite(5, eepromConfig.minThrottle);
				break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
