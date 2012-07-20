// Neuroclick is a program that emulates mouse clicks with eye blinks. 
// The source code (C) can be found below (most parts come from the example provided with the API). 
// I haven't had the time yet to use a lot but it seems like it is ca. 90% accurate.
//
// Tested on Windows 7 x64 with multiscreen.
//
// Copyright (C)2012
//               - Neurosky team <http://neurosky.com>
//               - Franck Dernoncourt <http://francky.me>
//
// Home Page: http://francky.me/software.php#Neuroclick2012
// Version: 0.2 (20120721)
//
// This program is licensed under the Creative Commons
// Attribution-Noncommercial-No Derivative Works 3.0 Unported license
// <http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode>
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
////
// Ideas to investigate:
// * Being able to drag and drop would be great. However I am definitely not sure whether the eye blinking detection's accuracy and frequency would allow a smooth drag-and-drop.
// * How bad is it to blink as many times as we use mouse clicks?
// * Distinguishing left-click from right-click is currently impossible due to the fact that there is only one sensor, which mostly detects the left blinking (seems the left eye is the closest to the sensor).
// * Is there any way to avoid that the program eats 100% CPU of a core?
// * I find the headset quite incomfortable (it hurts my forehead) even though I find it not excessively intrusive.
//
//Any feedback/comments/ideas are welcome! --> franck.dernoncourt@gmail.com



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "thinkgear.h"

/**
* Prompts and waits for the user to press ENTER.
*/
void
	wait() {
		printf( "\n" );
		printf( "Press the ENTER key...\n" );
		fflush( stdout );
		getc( stdin );
}

/**
* Program which prints ThinkGear EEG_POWERS values to stdout.
*/
int
	main( void ) {

		// http://andre.stechert.org/urwhatu/2006/01/error_c2143_syn.html
		// It's no surprise that Microsoft's compiler wants the variables at the beginnig of the function: Standard C wants them there.
		// At least, this is what C89 defines. C99 allows variable declarations also in the middle of a function.
		//char *comPortName =  (char*)malloc(sizeof(char) * (20));
		char *comPortName = NULL;
		//char *portNumber = NULL;
		char *portNumber = (char*)malloc(sizeof(char) * (2 + 1));
		//char comPortName[256] = "hello";
		//char portNumber[256] = "hello";
		char *comPortBase = NULL;
		int   dllVersion = 0;
		int   connectionId = 0;
		int   packetsRead = 0;
		int   errCode = 0;
		int comPortFound = 0;
		size_t length = 0;
		int i = 0;
		int j = 0;
		int x = 0;
		int y = 0;
		INPUT input;
		POINT cursorPos;

		/* Print driver version number */
		dllVersion = TG_GetDriverVersion();
		printf( "ThinkGear DLL version: %d\n", dllVersion );

		/* Get a connection ID handle to ThinkGear */
		connectionId = TG_GetNewConnectionId();
		if( connectionId < 0 ) {
			fprintf( stderr, "ERROR: TG_GetNewConnectionId() returned %d.\n", 
				connectionId );
			wait();
			exit( EXIT_FAILURE );
		}

		/* Set/open stream (raw bytes) log file for connection */
		errCode = TG_SetStreamLog( connectionId, "streamLog.txt" );
		if( errCode < 0 ) {
			fprintf( stderr, "ERROR: TG_SetStreamLog() returned %d.\n", errCode );
			wait();
			exit( EXIT_FAILURE );
		}

		/* Set/open data (ThinkGear values) log file for connection */
		errCode = TG_SetDataLog( connectionId, "dataLog.txt" );
		if( errCode < 0 ) {
			fprintf( stderr, "ERROR: TG_SetDataLog() returned %d.\n", errCode );
			wait();
			exit( EXIT_FAILURE );
		}

		/* Attempt to connect the connection ID handle to serial ports between COM1 and "COM16" */
		for(i=0; i < 17 && comPortFound == 0; i++)
		{

			comPortBase = "\\\\.\\COM";

			//portNumber = "1";
			portNumber = itoa(i, portNumber, 10);
			//comPortName = "ok";
			fprintf( stderr, portNumber);
			//comPortName = strcat(comPortName, portNumber);
			//comPortBase = "\\\\.\\COM1";
			length = strlen(comPortBase);
			//comPortBase = (char *)realloc (comPortBase, (length + 1)*sizeof (char)); 
			comPortName = (char *)realloc (comPortName, (length + strlen(portNumber))*sizeof (char)); 
			strcpy(comPortName,comPortBase);

			for(j=0; j<strlen(portNumber); j++)
			{
				comPortName[length+j] = portNumber[j];
			}

			comPortName[length+strlen(portNumber)] = '\0';
			//comPortBase = strcat(comPortBase, portNumber);

			fprintf( stdout, "ok");

			//comPortName = "ok";
			fprintf( stdout, comPortBase);
			fprintf( stdout, comPortName);
			//length = strlen(comPortName);

			//strcmp (comPortName, ) != 0);


			//comPortName = "\\\\.\\COM11";
			fprintf( stdout, "trying to connect on");
			fprintf( stdout, comPortName);
			fprintf( stdout, "\n");
			errCode = TG_Connect( connectionId, 
				comPortName, 
				TG_BAUD_9600, 
				TG_STREAM_PACKETS );
			if( errCode < 0 ) {
				fprintf( stderr, "ERROR: TG_Connect() returned %d.\n", errCode );

				if(errCode == -1) printf("FAILED (Invalid connection ID)\n");
				if(errCode == -2) printf("FAILED (0 bytes on the stream)\n");
				if(errCode == -3) printf("FAILED (I/O error occured)\n");

				//wait();
				//exit( EXIT_FAILURE ); 
			} else {

				//we try to read one packet, to check the connection.
				printf("Connection available...\n");
				Sleep(10000);
				errCode = TG_ReadPackets(connectionId,1);
				if(errCode >= 0)
				{	

					printf("OK\n");
					comPortFound = 1;
				}
				else
				{
					if(errCode == -1) printf("FAILED (Invalid connection ID)\n");
					if(errCode == -2) printf("FAILED (0 bytes on the stream)\n");
					if(errCode == -3) printf("FAILED (I/O error occured)\n");
				}


			}
		} 

		//To get eyeblinks, you will need to first call the following function:
		TG_EnableBlinkDetection(connectionId, 1 );

		if (comPortFound == 1) {
			printf( "connection established");
		} else {
			printf( "connection could not be established");
			wait();
			exit( EXIT_FAILURE ); 
		}




		/* Read 10 ThinkGear Packets from the connection, 1 Packet at a time */
		packetsRead = 0;
		while (1){
			//while( packetsRead < 10000 ) {

			/* Attempt to read a Packet of data from the connection */
			errCode = TG_ReadPackets( connectionId, 1 );


			/* If TG_ReadPackets() was able to read a complete Packet of data... */
			if( errCode == 1 ) {
				packetsRead++;
				printf( ".");

				/* If attention value has been updated by TG_ReadPackets()... */
				if( TG_GetValueStatus(connectionId, TG_DATA_ATTENTION) != 0 ) {

					/* Get and print out the updated attention value */
					fprintf( stdout, "New attention value: %f\n",
						TG_GetValue(connectionId, TG_DATA_ATTENTION) );
					fflush( stdout );

				} /* end "If attention value has been updated..." */


				/* If eye blinking value has been updated by TG_ReadPackets()... */
				if( TG_GetValueStatus(connectionId, TG_DATA_BLINK_STRENGTH) != 0 ) {

					/* Get and print out the updated eye blinking value */
					fprintf( stdout, "New eye blinking value: %f\n",
						TG_GetValue(connectionId, TG_DATA_BLINK_STRENGTH) );
					fflush( stdout );

					// Get mouse position: 
					// * http://msdn.microsoft.com/en-us/library/ms648380(v=vs.85).aspx#_win32_Using_the_Keyboard_to_Move_the_Cursor 
					// * http://msdn.microsoft.com/en-us/library/ms648390%28VS.85%29.aspx
					// * http://stackoverflow.com/questions/2396576/how-to-get-the-cursor-position

					GetCursorPos(&cursorPos);
					x = (int) cursorPos.x;
					y = (int) cursorPos.y;
					//x = 10;
					//y = 20;

					// http://stackoverflow.com/questions/4540282/using-mouse-with-sendinput-in-c
					input.type = INPUT_MOUSE;
					input.mi.mouseData=0;
					input.mi.dx = x*(65536.0f/GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
					input.mi.dy = y*(65536.0f/GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels
					input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
					SendInput(1,&input,sizeof(input));

				} /* end "If attention value has been updated..." */



			} /* end "If a Packet of data was read..." */

			// Posted by Friedemann Wolpert on July 04, 2012 @ 11:45 PM
			// Regarding your 100% CPU Problem
			if( errCode == 0 ) {
				printf( "z");
				Sleep(200);   // maybe #include Windows.h  
			}
			//
			//  
		} /* end "Read 10 Packets of data from connection..." */

		/* Clean up */
		TG_FreeConnection( connectionId );

		/* End program */
		wait();
		return( EXIT_SUCCESS );
}