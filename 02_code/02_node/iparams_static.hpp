/****************************************
* iparams_static
*		iparams_static class
*****************************************/
#ifndef _IPARAMS_STATIC_HPP_
#define _IPARAMS_STATIC_HPP_

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include "serial_core.hpp"
#include "comm_core.hpp"



/*****************************************************************************************
* iparams_static class                                                                   *
*                                                                                        *
* Member functions                                                                       *
*	set_handle --                                                                        *
*   set_parameter -- write parameter value to FPGA/ASIC register                         *
*   get_parameter -- read parameter value from FPGA/ASIC register                        *
*   display_parameters_mapping -- display the list of parameters that can be read/written*
******************************************************************************************/
class iparams_static {
	private:
        // interface to interact with the hardware node
	    COMM_HANDLE hw_handle; 
        //  structure to model HW (FPGA/ASIC) register: address + data
		struct {
			unsigned int address;
			unsigned int data;
			unsigned int MSB;
			unsigned int LSB;
		} hw_register[1]; 
        // structure to create map entry
		struct par_mapping {
			unsigned int address;
			unsigned int MSB;
			unsigned int LSB;
		};               
        // conversion table: parameter <=> (address, MSB, LSB)
		std::map<string,par_mapping> table; 
		// convert parameter to hw register (address, data) 
		void set_hw_register( int );
        // convert hw register to parameter value
		bool get_hw_register( std:: string );
	public:
        // initialize the iparams_static
		iparams_static( void );
        // ~iparams_static (void); -- default  constructor
		// copy constructor defaultds
        
        // pointer to a comm serial port, i.e. to the node
		void set_handle( COMM_HANDLE this_handle){hw_handle = this_handle;}
	    // parameter (label=string, value=int) -> hw register
		bool set_parameter   (std::string, int);
        // hw_register -> parameter (label=string, value=int)
		bool get_parameter   (std::string, int&);
		// display table
		void display_parameters_mapping(void);
};

#endif
