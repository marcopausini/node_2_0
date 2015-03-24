/****************************************
* Quintessa
*		Quintessa class
*****************************************/
#ifndef _QUINTESSA_HPP_
#define _QUINTESSA_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <string>
#include <cstring>
#include <cctype>
#include "windows.h"

/*****************************************************************************************
* Quintessa class                                                                             *
*       Quintessa    
*                                                                                      *
* Member functions                                                                       *
*   connect: create connection betweeen node app running on pc and software running on
   the microprocessor on the hardware board 
*                                                                                        *
*                                                                                        *
******************************************************************************************/
class Quintessa {
	private:
        // COM port ID
        std::string port_name;
		
		// output log stream
		std::ofstream log_file;
		
		// open serial port
		bool open_serial_port(char*);
		// overwrite serial port parameters
		bool overwrite_serial_port_parameters();
		// set serial port timeouts
		bool set_serial_port_timeouts();
		
		//  send buffer of characters to serial port 
		bool send_buffer_to_serial_port( const char* buffer);
		// receive buffer of characters from serial port until <prompt> is received
        bool read_buffer_from_serial_port( char* buffer);
		
		// from internet: HANLDE is a pointer to a struct that Windows doesn't want you to directly manipulate. 
		// It's a struct that is meant to be passed to, and manipulated by, only operating system functions. Defined as a pointer to void
		HANDLE hSerial;
		
		DCB dcbSerialParams;
		COMMTIMEOUTS timeouts;
		
	public:
    
        // assign default directory
        // Quintessa( void ) { a=10; }
        // ~Quintessa (void); -- default  constructor
		// copy constructor defaultds
     
		// set serial port id
		// void set_port_name( std::string name ) {port_name = name;}
		// set logs directory
		void set_log_file(std::string directory);
        // open communication port object between PC and quintessa board, and create pointer to the object
        bool connect(std::string name);
        // close communication port object between PC and quintessa board, and delete pointer to the object
        void disconnect( );
        // resume
        bool resume();
        // dsiplay private varibales values
        void display_private_values( void ){std::cout<<"COM port:"<< port_name<<"\n";}
		// write 32-bits to register
		bool write32_register( unsigned int address, unsigned int bits );
		// read 32-bits from register
	    bool read32_register( unsigned int address, unsigned int & bits );
		// send command
		bool send_command( const std::string& command, std::string& reply);
};

#endif
