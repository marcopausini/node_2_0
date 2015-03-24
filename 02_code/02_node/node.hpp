/****************************************
* node
*		iparams_static class
*****************************************/
#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "quintessa.hpp"


/*****************************************************************************************
* Node class                                                                             *
*       G.9963 transceiver   
*                                                                                      *
* Member functions                                                                       *
*   
*                                                                                        *
*                                                                                        *
******************************************************************************************/
class Node {
	public:

        // initialize the node
		 //Node( void );
        // ~node (void); -- default  constructor
       // ~Node ( void );
		// copy constructor defaultds
        //
		void set_log_file(std::string directory);
		// connect PC to quintessa board through serial COM port <name>
        bool connect( std::string name );
        // close communication between PC and quintessa board
        void disconnect( ){quintessa.disconnect(); log_file<<"disconnect\n";}; 
        // resume connection using previous COM port <name>
		bool resume( ){quintessa.resume();log_file<<"resume connection\n";}
		// write parameter value to corresponding hw register
		//bool set_parameter   (std::string, int);
        // read parameter value from corresponding hw register
		//bool get_parameter   (std::string, int&);
		
	private:
       
	    // output log stream
		std::ofstream log_file;
		
        // Quintessa Object
		Quintessa quintessa;
		
		// Table with mapping between GPHY parameters and GPHY registers (in GPHY_REG memory space)
		//RegisterMap gphy_reg;
		
		// GPHY memory space
		//GphyMemorySpace GPHY_memory;
		
			
};

#endif
