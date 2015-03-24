#include "gphy_memory_space.hpp"

/*****************************************************************
 * gphy_memory_space::gphy_memory_space -- Initialize Private Data*
 *****************************************************************/

 
 /*****************************************************************
 * memory::memory -- Initialize Private Data*
 *****************************************************************/ 
Memory::Memory( int base_addr, int nBytes  ){

    base_address = base_addr; 
    // each entry is 32-bits = 4 bytes
    N = nBytes/4;
    // allocate the memory and initialize it 
    data = new unsigned int[N];
    for (int n=0; n<N; n=n+1){
        data[n]=0xdeadbeef;
    }
 }  
 
/***************************************************************************
 * Memory::write -- write value into data[ind]  *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     ind   -- array index                                          *
 *     value -- value to be written                                     *
 *                                                                         *
 * Returns                                                                 *
 *    void                                                    *
 ***************************************************************************/
 void Memory::write( int ind, unsigned int value ){
    
    if (ind < N) {data[ind]=value;}
    else {std::cout<<"Index: "<<ind<<"out of range\n";}    
 }
 
 /***************************************************************************
 * Memory::read -- read value from data[ind]  *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     ind   -- array index                                          *
 *     value -- value to be written                                     *
 *                                                                         *
 * Returns                                                                 *
 *    void                                                    *
 ***************************************************************************/
 void Memory::read( int ind, unsigned int &value ){
    
    if (ind < N) {value = data[ind];}
    else {std::cout<<"Index: "<<ind<<"out of range\n";value = 0xdeadbeef;}    
 }
 
 /***************************************************************************
 * Memory::flush --                                                        *
 *      write data[offset/4 + (0:length/4-1)] to memory chip at address    *
 *      addr = base + offset                                               *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     offset   -- offset address within memory [Bytes]                      *
 *     length -- number of bytes to be transferred                 *
 *                                                                         *
 * Returns                                                                 *
 *    void                                                    *
 ***************************************************************************/
 void Memory::flush( unsigned int offset, unsigned int length){
    
    // number of 32-bits words to be transferred to memory
    unsigned int N =  length >> 2;
    // first index od data[] array
    unsigned int first_index = offset >> 2; // shit of 2 position equal to dived by 4
    
    // write memory buffer
    for (unsigned int n=first_index; n<first_index+N; n++){
        // memory address
        unsigned int addr = base_address + (n<<2);
        // write to hw
      //  std::cout<<"quintessa.a="<<hw->a<<std::endl;
       // quintessa.comm_port->write_address(addr, data[n]);
     //  hw->a = 8;
        // update address
        addr = addr+4;
    }
 }
 
 
