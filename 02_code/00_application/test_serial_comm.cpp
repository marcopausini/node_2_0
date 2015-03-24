#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

int main(int argc, char *argv[]) {

/*************************/
// VARIABLES DECLARATION
/************************/
	// Serial Comm Ports: [0]:Tx; [1]:Rx
	int com_ports[2] = {4,3};
	
	bool error_tx;
	bool error_rx;
	int value;
	string key;
	
/******************************************************************************/
// Open SERIAL PORT
/******************************************************************************/

	cout << "\n\nOpen Serial Ports: ";
	
	// from internet: HANLDE is a pointer to a struct that Windows doesn't want you to directly manipulate. 
	// It's a struct that is meant to be passed to, and manipulated by, only operating system functions.
	// defined as a pointer to void
	
	HANDLE hSerial;
	
	hSerial = CreateFile("COM3",
            GENERIC_READ|GENERIC_WRITE,//access ( read and write)
            0,    //(share) 0:cannot share the COM port                        
            0,    //security  (None)                
            OPEN_EXISTING,// creation : open_existing
            FILE_ATTRIBUTE_NORMAL, //otherwise: FILE_FLAG_OVERLAPPED
            0    // no templates file for COM port...
            );

	if(hSerial==INVALID_HANDLE_VALUE){
	
		if(GetLastError()==ERROR_FILE_NOT_FOUND){
			//serial port does not exist. Inform user.
			cout << "\nERROR Serial port not found\n";
		}
		else if (GetLastError()==ERROR_ACCESS_DENIED){
			// COM port already opened  by other application
			cout << "\nERROR Serial COM port already opened\n";
		}
		else{
			//some other error occurred. Inform user.
			cout << "\nERROR opening serial ports\n";
		}
		cout << "Press [KEY] to finish...\n";
		cin>> key;
		return (1);
	}
	
	else{cout <<"OK\n";}
	
/******************************************************************************/
// Set SERIAL PORT Parameters
/******************************************************************************/
	
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		//error getting state
		cout<<"\nERROR reading Serial Port State\n";
		return(1);
	}
	else{
		cout<<"\nSerial Port State:";
		cout<<"\nByteSize="<< (int) dcbSerialParams.ByteSize;
		cout<<"\nBaudRate="<< (int) dcbSerialParams.BaudRate;
		cout<<"\nStopBits="<< (int) dcbSerialParams.StopBits;
		cout<<"\nParity="<< (int) dcbSerialParams.Parity;
	}
	
	
	dcbSerialParams.BaudRate=230400;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	
	cout << "\n\nSet Serial Port Parameters.";
	cout<<"\nByteSize="<< (int) dcbSerialParams.ByteSize;
	cout<<"\nBaudRate="<< (int) dcbSerialParams.BaudRate;
	cout<<"\nStopBits="<< (int) dcbSerialParams.StopBits;
	cout<<"\nParity="<< (int) dcbSerialParams.Parity;
	
	if(!SetCommState(hSerial, &dcbSerialParams)){
		//error setting serial port state
		cout<<"\nERROR setting Serial Port State\n";
		return(1);
	}

	
/******************************************************************************/
// Set SERIAL PORT Timeouts
/******************************************************************************/
	cout << "\n\nSet Serial Port Timeouts: ";
		
    COMMTIMEOUTS timeouts={0};
	
	// Specify time-out between charactor for receiving.
	timeouts.ReadIntervalTimeout = 1;
	// Specify value that is multiplied by the requested number of bytes to be read. 
	timeouts.ReadTotalTimeoutMultiplier = 1;
	// Specify value is added to the product of the ReadTotalTimeoutMultiplier member
	timeouts.ReadTotalTimeoutConstant = 1;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	timeouts.WriteTotalTimeoutConstant = 1;

	if(!SetCommTimeouts(hSerial, &timeouts)){
	//error occureed. Inform user
		cout<<"\nERROR setting Serial Port TimeOuts\n";
		return(1);
	}


/******************************************************************************/
// Write String to SERIAL PORT 
/******************************************************************************/

	const char * data = "mw 40080080 F0CD0181\n"; 
	
	int dwSize = strlen( data );
	
	DWORD dwBytesWritten = 0;
	
	cout << "\n\nSend Data: ";
	
	for(int n=0;n<100;n++){
	if (!WriteFile (hSerial,   // handle to file to write to
					&data[0],      // pointer to data to write to file
					dwSize,    // number of bytes to write
					&dwBytesWritten,  // pointer to number of bytes written
					NULL) )
	{
		cout<<"\nERROR Sending Data\n";
	}   
	else{
		cout<<"\nBytes Written="<<dwBytesWritten<<"\nBytes Sent="<<dwSize;
	} 
	}
	
/******************************************************************************/
// Close SERIAL PORT
/******************************************************************************/
	cout << "\n\nClose Serial Ports.";
	CloseHandle(hSerial);
	
	cout << "\nPress [KEY] to finish.\n";
	cin>> key;
	return 0;
}
