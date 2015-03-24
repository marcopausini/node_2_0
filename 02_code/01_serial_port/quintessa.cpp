#include "quintessa.hpp"
#include "my_library.hpp"

#define MAX_BUFF_SIZE    1024 

using namespace std;

/***************************************************************************
 * Quintessa::write32_register --                                          *
 *  							write 32-bits word into FPGA/ASIC register *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     bits  -- 32-bits word to be written                                 *
 *     address -- address of register                                      *
 * Updates                                                                 *
 *                                                                         *
 ***************************************************************************/
bool Quintessa::write32_register( unsigned int address, unsigned int bits){
	
	bool error = false;

    // create commnand line string
	std::string data_string = "mw " + int_to_hex(address, false) + " " + int_to_hex(bits,false) + "\n";
	
	// log
	log_file<<data_string;
			
	// convert C++ to C
	const char *data; 
    data = data_string.c_str();  
	
	// send command line string to serial port
	if(!send_buffer_to_serial_port( data )){error=true;}
	
	delete [] data;
	
	// rx buffer
	char rx_buffer[MAX_BUFF_SIZE];
	
	// read buffer from serial port  ended by '0:->'
	if(!read_buffer_from_serial_port( rx_buffer )){error=true;}
	

	// log
	log_file<<rx_buffer<<"\n";
//	cout<<"\nrx_buffer:"<<rx_buffer<<"\n";
	
	return(!error);
	
}


/***************************************************************************
 * Quintessa::read32_register --                                           *
 *  							read 32-bits word from FPGA/ASIC register  *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     bits  -- 32-bits word read from register                            *
 *     address -- address of register                                      *
 * Updates                                                                 *
 *                                                                         *
 ***************************************************************************/
bool Quintessa::read32_register( unsigned int address, unsigned int &bits){
	
	bool error = false;

	// create commnand line string
	std::string data_string = "mr " + int_to_hex(address, false) + "\n";
	
	// log
	log_file<<data_string;
			
	// convert C++ to C
	const char *data; 
    data = data_string.c_str();  
	
	// send command line string to serial port
	if(!send_buffer_to_serial_port( data )){error=true;}
	
	delete [] data;
	
	// rx buffer
	char rx_buffer[MAX_BUFF_SIZE];
	
	// read buffer from serial port  ended by '0:->'
	if(!read_buffer_from_serial_port( rx_buffer )){error=true;}
	
	// convert to c++ string
	std::string buffer(rx_buffer);
	
	// split words
	vector<string> v = split(buffer);
	
	// get substring that contains the value of the register 
	vector<string>::size_type i=0;
	string reg_value;
	bool found = false;
	while ( i!=v.size() && !found){
		if(v[i] == "[" + int_to_hex(address, true) + "]"){
			reg_value = v[i+1];
			found = true;
		}
		i++;
	}
	if(!found){error=true; std::cout<<"Serial port did not return string"<<"[" + int_to_hex(address, true) + "]"<<endl;}
	
	// convert string into unsigned int  
    std::stringstream ss;
	ss << std::hex << reg_value;
    ss >> bits;
	
	// log
	log_file<<rx_buffer<<"\n";
	// LOG to FILE
	// cout<<"\nrx_buffer:"<<rx_buffer<<"\n";
	// cout<<"\nreg_value="<<reg_value<<"\n";
		
	return(!error);
}

/***************************************************************************
 * Quintessa::send_command                                                 *
 *  	 send command to the ARM processor through the serial port         *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     command  -- command line (i.e., "gphy x S 1024")                    *
 * Updates                                                                 *
 *                                                                         *
 ***************************************************************************/
bool Quintessa::send_command( const std::string& command, std::string& reply){
	
	bool error = false;
	
	// log
	log_file<<command<<"\n";
			
	// convert C++ command line string to C char array
	const char *data; 
    data = command.c_str();  
	
	// send command line string to serial port
	if(!send_buffer_to_serial_port( data )){error=true;}
	
	delete [] data;
	
	// rx buffer
	char rx_buffer[MAX_BUFF_SIZE];
	
	// read buffer from serial port  ended by '0:->'
	if(!read_buffer_from_serial_port( rx_buffer )){error=true;}
	
	// convert to c++ string
	//std::string buffer(rx_buffer);
	//reply = buffer;
	reply = string(rx_buffer);
	
	// log
	log_file<<rx_buffer<<"\n";
	
	return(!error);
	
}


 
//void Quintessa::Quintessa(){}
 
/***************************************************************************
 * Quintessa::connect --                                                   *
 *   open COMM port between PC and Quintessa;                              *
 *                                                                         *
 *  Updates:                                                               *
 *	  hSerial   - Handle object to serial COMM port                        *
 *    port_name - String with COM port ID                                  *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     name -- COMM port indentifier (e.g. "COM3")                         *
 *                                                                         *
 * Returns                                                                 *
 *    bool                                                                 *
 ***************************************************************************/
 bool Quintessa::connect(std::string name ) {
    
	bool error = false;
	
	// store COM port ID (private common variable)
	port_name = name;
	
	// convert c++ string to c
	char* c_port_name = new char[port_name.length()+1];
    std::strcpy(c_port_name, port_name.c_str());
	
	if(!open_serial_port( c_port_name )){error=true;}

	delete [] c_port_name;

	if(!overwrite_serial_port_parameters()){error=true;}
	
	if(!set_serial_port_timeouts()){error=true;}
	
	return(!error);
} 

void Quintessa::disconnect( ) {
    
//	cout << "\nClose Serial Ports.";
	CloseHandle(hSerial);   
} 

 bool Quintessa::resume( ) {
    
	bool error = false;
	
	// convert c++ string to c
	char* c_port_name = new char[port_name.length()+1];
    std::strcpy(c_port_name, port_name.c_str());
	
	if(!open_serial_port(c_port_name)){error=true;}
	
	delete [] c_port_name;
	return(!error);
} 

bool Quintessa::open_serial_port(char* name){
	
	bool error = false;
	
	hSerial = CreateFile(name,
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
		error = true;
	}
	return(!error);
}

bool Quintessa::overwrite_serial_port_parameters(){
	
	bool error = false;
	
	dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		//error getting state
		cout<<"\nERROR reading Serial Port State\n";
		error=true;
		return(!error);
	}
	else{
	/*	cout<<"\nSerial Port State:";
		cout<<"\nByteSize="<< (int) dcbSerialParams.ByteSize;
		cout<<"\nBaudRate="<< (int) dcbSerialParams.BaudRate;
		cout<<"\nStopBits="<< (int) dcbSerialParams.StopBits;
		cout<<"\nParity="<< (int) dcbSerialParams.Parity;
		*/
	}
	
	
	dcbSerialParams.BaudRate=230400;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	
	/*cout << "\n\nSet Serial Port Parameters.";
	cout<<"\nByteSize="<< (int) dcbSerialParams.ByteSize;
	cout<<"\nBaudRate="<< (int) dcbSerialParams.BaudRate;
	cout<<"\nStopBits="<< (int) dcbSerialParams.StopBits;
	cout<<"\nParity="<< (int) dcbSerialParams.Parity;
	*/
	if(!SetCommState(hSerial, &dcbSerialParams)){
		//error setting serial port state
		cout<<"\nERROR setting Serial Port State\n";
		error = true;
		return(!error);
	}
	
	return(!error);
}

bool Quintessa::set_serial_port_timeouts(){
	
	bool error = false;
		
    timeouts={0};
	
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
		error = true;
	}
	
	return(!error);
}


/***************************************************************************
 *  *
 *  *
 *  *
 *  *
 *  *
 *  *
 *  *
 *  *
 *  *
 *  *
 ***************************************************************************/
bool Quintessa::send_buffer_to_serial_port( const char* buffer){
	
	bool error = false;

    //
	// send string through serial port
	//
	int dwSize = strlen( buffer );
	DWORD dwBytesWritten = 0;
	if (!WriteFile (hSerial,   // handle to file to write to
					&buffer[0],      // pointer to data to write to file
					dwSize,    // number of bytes to write
					&dwBytesWritten,  // pointer to number of bytes written
					NULL) )
	{
		cout<<"\nERROR Sending Data\n";
		error = true;
	}   
	else{
		if (dwSize!=dwBytesWritten){
			cout<<"\nBytes Sent not the same of Bytes Written\n";
			error=true;
		}
	}
	
	return(!error);	
}

/***************************************************************************
 * Quintessa::read_buffer_from_serial_port 	                               *
 *  read buffer of characters from serial port until the string "0:->" is found *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     buffer  -- buffer of characters to store the serial port data       *
 *	                                                                       *
 * Comments:                                                               *
 *     instead of char* would have been nicer to use std::string           *
 ***************************************************************************/
bool Quintessa::read_buffer_from_serial_port( char* buffer ){
	
	bool error = false;
	
	//
	// receive data from serial port
	//
	char  inputData [MAX_BUFF_SIZE];
	DWORD read_char = 0;
	char in_char;
	char sequence[4];
	bool stop = false;
	int n=0;
	int timeout = 0;
	while (!stop) {
		read_char = 0;
		ReadFile(hSerial, &in_char, 1, &read_char, NULL);
		if (read_char){ 
				std::cout<<" "<<timeout;
				// reset timeout
				timeout = 0;
				// store new char
				inputData[n] = in_char;
				// retrieve last 4 characters
				if (n>=3){
					sequence[0] = inputData[n-3];
					sequence[1] = inputData[n-2];
					sequence[2] = inputData[n-1];
					sequence[3] = inputData[n-0];
				}
				// Wait until characters sequence '0:->' is received
				stop = (sequence[0] == '0') && (sequence[1] == ':') && (sequence[2] == '-') && (sequence[3] == '>');
				// update counter
				n++;
		}
		else{
			Sleep(10);
			timeout++;
			if(timeout==100){break;}
		}
		if (n>=MAX_BUFF_SIZE){
		error=true; std::cout<<"\nERROR: buffer received from serial port too large.\n"; 
		break;
		}
	}
    // terminate string
    inputData[n] = '\0';
	strcpy( buffer, inputData );
	
	
	
	return(!error);	
}


/***************************************************************************
 * Quintessa::set_log_file 	                               *
 * 
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *	                                                                       *
 * Comments:                                                               *
 ***************************************************************************/
void Quintessa::set_log_file(string directory){
	 
	// create filename string
	string filename = directory + "\\quintessa.txt";
	
	// open
	log_file.open(filename, std::ofstream::out | std::ofstream::app);
	
	
}

