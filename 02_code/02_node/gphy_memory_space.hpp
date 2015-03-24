/****************************************
* gphy_memory_space
*		GphyMemorySpace class
*       Memory       class
*****************************************/
#ifndef _GPHY_MEMORY_SPACE_HPP_
#define _GPHY_MEMORY_SPACE_HPP_

#include <iostream>
#include <string>
#include <math.h>
#include "serial_core.hpp"
#include "comm_core.hpp"


/****************************************************************************************
* Memory class                                                                          *
*    Abstraction of FPGA/ASIC memory. Lowest layer in the Software to access HW.        *
*    Organized as array of 32-bits with no semantic meaning.                            *
*                                                                                       *
* Member functions                                                                      *
*   flush : write content of data[] to chip memory                                       *       
*   dump  : read chip memory and store into data[]                                       *    
*   write : write content of data[ind] from SW                                           *    
*   read  : read data[ind] from SW                                                       *   
*****************************************************************************************/

 class Memory {
    private:
        unsigned int* data;
        int base_address;
        // number of data words, each one stored as 4-bytes
        int N;
        //
        //CommCore *hw;
    
    public:
        // constructor
        Memory( ) {}; 
        Memory( int base_addr, int nBytes ); 
     //   Memory( Quintessa* hw, int base_addr, int nBytes );
        // ~memory -- 
        ~Memory( ) {delete data;};
        // copy constructor default
        
        //
    //    void set_hw_handle( CommCore* hw ) {hw = hw;}
                
        // move data[N] to HW memory 
        void flush ( unsigned int offset, unsigned int length);
        // move HW memory content to data[N]
        void dump  (unsigned int offset, unsigned int length);
        // write content of data[ind]
        void  write( int ind, unsigned int value);
        // write content of data[a:b] from file
        void write( std::string file );
        // read  content of data[ind]
        void read( int ind, unsigned int & value);
}; 

/*****************************************************************************************
* GphyMemorySpace class                                                                  *
*    GPHY Memory Space segmented into GPHY memories                                      *
*                                                                                        *
* Member functions                                                                       *
*	                                                                                     *
*                                                                                        *
******************************************************************************************/

class GphyMemorySpace {
	private:

	public:
		//   constructor
         GphyMemorySpace( ): 
                            GPHY_REG      (0x40080000, 0x0300), 
                            PSR_TX_MEM    (0x40081000, 0x0400),
                            PSR_RX_MEM    (0x40082000, 0x0400),
                            PSD_MEM       (0x40084000, 0x2000),
                            BAT0_MEM      (0x40088000, 0x4000),
                            BAT1_MEM      (0x4008C000, 0x4000),
                            MAT_MEM       (0x40090000, 0x4000),
                            FDP_SNR_MEM   (0x40094000, 0x2000),
                            FDP_PHASE_MEM (0x40096000, 0x0800),
                            FDP_SNGV_MEM  (0x40097000, 0x1000),
                            TDB_WAVE_MEM  (0x40098000, 0x1800),
                            AIU_MEM       (0x400A0000, 0x0400),
                            CAPT_MEM      (0x400B0000, 0x1000),
                            CLOCK_ERR     (0x400D0000, 0x0400),
                            MAC_EMU_MEM   (0x400E0000, 0x1000),
                            FPGA          (0x400F0000, 0x1000),
                            CH_EMULATOR   (0x400FE000, 0x2000)  
                        { }
        // ~gphy_memory_space (void); -- default  constructor
		// copy constructor defaultds
        
        // GPHY memories
        Memory GPHY_REG;
        Memory PSR_TX_MEM;
        Memory PSR_RX_MEM;
        Memory PSD_MEM;
        Memory BAT0_MEM;
        Memory BAT1_MEM;
        Memory MAT_MEM;
        Memory FDP_SNR_MEM;
        Memory FDP_PHASE_MEM;
        Memory FDP_SNGV_MEM;
        Memory TDB_WAVE_MEM;
        Memory AIU_MEM;
        Memory CAPT_MEM;
        Memory CLOCK_ERR;
        Memory MAC_EMU_MEM;
        Memory FPGA;
        Memory CH_EMULATOR;
};    
              
#endif
