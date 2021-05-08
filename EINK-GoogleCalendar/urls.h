/*
 *  Copyright (C) 2019 lokthelok
 *  Copyright (C) 2016 PhracturedBlue
 *
 *  This file is part of CalendarPrinter.
 * 
 *  CalendarPrinter is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//Credentials and Sensitive Information
//Ensure this is not committed for security!

//WiFi Credentials
#define NETWORK_LIST { \
	WIFI_CONN("MOVISTAR_649E", "dV9ufTX9Tfgs7pLcWR2C"), \
	WIFI_CONN("SSID2", "PASSWORD2"), \
	WIFI_CONN("SSID3", "PASSWORD3"), \
	NULL, \
	}
#define NETWORK_LIST_LENGTH 3

//Google Scripts
// CalendarPrinter Script URL
#define SCRIPT_URL "https://script.google.com/macros/s/YOUR_SCRIPT/exec"