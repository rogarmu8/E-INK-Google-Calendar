/*
 *  Copyright (C) 2019 lokthelok
 *  Copyright (C) 2016 PhracturedBlue
 *  Copyright (C) 2018 Andreas Spiess
 *  Copyright (C) 2018 MickMake
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

#include <WiFi.h>
#include <SPIFFS.h>
#include <WiFiClientSecure.h>
#include <Adafruit_Thermal.h>
#include "calEvent.h"
#include "calPrint.h"
#if __has_include(<urls.h>)
#  include "urls.h"
#  define URLS
#endif

#ifndef URLS


//Add or remove full WIFI_CONN() lines to add/remove networks from list
//Networks are connected by ordered preference, index 0 being first.

const char* script = "https://script.google.com/macros/s/Your_Script/exec";
#else
const char* script = SCRIPT_URL;
#endif

#include "main.h"
WiFiClientSecure client;

wifi_conn network;
char* getCalendarData(){
	
	network = searchWiFi();

	String response = "";
	DPRINT("Connecting to WiFi.");
	WiFi.begin(network.ssid, network.password);
	while (WiFi.status() != WL_CONNECTED) {
		DPRINT(".");
		delay(300);
	}
	client.setInsecure();

	DPRINTF("\nConnected to WiFi: %s\n",network.ssid);
	if (WiFi.status() == WL_CONNECTED)
	{
		response = FetchGCal(script);

	}
	char *cstr = new char[response.length() + 1];
	strcpy(cstr, response.c_str());
	return cstr;
}

String FetchGCal(String url)
{
	String Return1;
	String Return2;
	Return1 = WebFetch(url);
	Return2 = WebFetch(Return1);

	return(Return2);
}

String WebFetch(String url)
{
	const char *strURL;
	String Response;
	char server[80];
	bool Redirect = 0;

	strURL = url.c_str();
	DPRINT("GCAL:URL:");
  DPRINTLN(strURL);

	if (memcmp("https://", strURL, 8) == 0)
	{
		int i;
		for(i=0; i<80; i++)
		{
			if (strURL[i+8] == '/')
				break;
			server[i] = strURL[i+8];
		}
		server[i] = 0;
	}

	DPRINT("GCAL:server:");
  DPRINTLN(server);


	if (!client.connect(server, 443))
		Serial.printf("GCAL:No connection");
	else
	{
		Serial.printf("GCAL:Connect");
		// Make a HTTP request:
		client.print("GET ");
		client.print(url);
		client.println(" HTTP/1.0");

		client.print("Host: ");
		client.println(server);
		client.println("Connection: close");
		client.println();

		String header;
		while (client.connected())
		{
			String line = client.readStringUntil('\n');
			header = header + line + "\n";
			if (line.startsWith("Location: "))
			{
				Redirect = 1;
				Response = line.substring(line.indexOf("http"));
				DPRINT("GCAL:REDIRECT:");
        DPRINTLN(Response);
			}
			if (line == "\r")
				break;
		}
		DPRINT("GCAL:HEADER:");
    DPRINTLN(header);

		String body;
		while (client.available())
		{
			String line = client.readStringUntil('\n');
			body = body + line + "\n";
			if (line == "\r")
				break;
		}

		if (!Redirect)
		{
			DPRINT("GCAL:BODY:");
      DPRINTLN(body);
			Response = body;
		}

		client.stop();
	}

	return(Response);
}

wifi_conn searchWiFi(void)
{
	DPRINTF("scan start\n");
	int n = WiFi.scanNetworks();
	DPRINTF("scan done: %i\n", n);
	for(int x = 0; x < n; x++) DPRINTF("%i:%s\n",x,WiFi.SSID(x).c_str());

	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	wifi_conn available_network;
	int i,j;
	if(n > 0) {
		for(i = 0; i < NETWORK_LIST_LENGTH; i++)
		{
		DPRINTF("l");
		for(j = 0; j < n; j++)
		{
			DPRINTF("f");
			if(strcmp(networks[i].ssid,WiFi.SSID(j).c_str()) == 0)
			{
			DPRINTF("\nMatched - list: %s  found: %s\n",networks[i].ssid,WiFi.SSID(j).c_str());
			available_network = networks[i];
			return available_network;
			}
		}
		}
	}
	return available_network;
}