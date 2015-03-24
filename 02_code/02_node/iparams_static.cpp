#include "iparams_static.hpp"

using namespace std;

/*****************************************************************
 * iparams_static::iparams_static -- Initialize Private Data     *
 *****************************************************************/
iparams_static::iparams_static( void ){
	// handle to hardware
	// COMM_HANDLE hw_handle = NULL;
	//
	// hw registers
	hw_register[0].address = 0xFFFFFFFF;
	hw_register[0].data    = 0xdeadbeef;
	//
	// create conversion table: parameter <=> (address, MSB, LSB)
	//
	// PROFILE_0
	// PROFILE_1
	// PROFILE_2
	// RX_BOOST_0
	table["S1"] = {0x40080020,15,0}; 
	table["HDR"] = {0x40080020,31,16}; 
	// RX_BOOST_1
	table["PAYLOAD_MAPD"] = {0x40080024,15,0}; 
	table["PAYLOAD"] 	  = {0x40080024,31,16}; 
	// FEQ_0
	// FEQ_1
	// FEQ_2
	// FEQ_3
	// NDIM_0
	// MEAS_0
	table["SC_TYPE"]   = {0x40080040,4,0}; 
	table["SC_DELTA"]  = {0x40080040,7,5}; 
	table["ALPHA"]     = {0x40080040,15,8}; 
	table["SC_START"]  = {0x40080040,28,16}; 
	table["MEAS_MODE"] = {0x40080040,30,30}; 
	table["SC_MODE"]   = {0x40080040,31,31}; 
	// MEAS_1
	table["SC_END"]      = {0x40080044,12,0}; 	
    table["MASK"]        = {0x40080044,21,16}; 	
	table["ANT_DISABLE"] = {0x40080044,23,22}; 	
	table["WITH_INIT"]   = {0x40080044,24,24}; 	
	table["MEM_LOCK"]    = {0x40080044,31,31}; 	
	table["DELTA_FERR_ALWAYS"] = {0x40080044,28,28}; 	
	table["DELTA_FERR_ENA"]    = {0x40080044,29,29}; 	
	table["DISABLE_MATRIX_INVERSION"] = {0x40080044,30,30}; 
	// MEAS_2
	table["SYM_FIRST"] = {0x400800D0,11,0}; 	
    table["SYM_DELTA"] = {0x400800D0,14,12}; 	
	table["SYM_LAST"]  = {0x400800D0,27,16};
	// MEAS_3
	table["BETA"]      = {0x40080108,7,0}; 	 	
	// LLR_SCALE_0
	// LLR_SCALE_1
	// LLR_SCALE_2
	// MAC_EMU_0
	unsigned int MAC_EMU_0 = 0x400801B8;                     
	table["xt.mac_emu_tx_frame_length"]    = {MAC_EMU_0,9,0  };
	table["xt.mac_emu_init_seed"]          = {MAC_EMU_0,12,12};
	table["xt.mac_emu_tx_pointer_payload"] = {MAC_EMU_0,25,16};
	table["xt.mac_emu_clear_cnt"]          = {MAC_EMU_0,27,27};
	table["xt.mac_emu_tx_random"]          = {MAC_EMU_0,28,28};
	table["xt.mac_emu_rx_enable"]          = {MAC_EMU_0,29,29};
	table["xt.mac_emu_tx_enable"]          = {MAC_EMU_0,30,30};
	table["xt.mac_emu_enable"]             = {MAC_EMU_0,31,31};
	// MAC_EMU_1
	unsigned int MAC_EMU_1 = 0x400801BC;
	table["xt.mac_emu_tx_length_payload"] = {MAC_EMU_1,15,0 };
	table["xt.mac_emu_ac_phase_0_tx_en" ] = {MAC_EMU_1,16,16};
	table["xt.mac_emu_ac_phase_1_tx_en" ] = {MAC_EMU_1,17,17};
	table["xt.mac_emu_ac_phase_0_rx_en" ] = {MAC_EMU_1,20,20};
	table["xt.mac_emu_ac_phase_1_rx_en" ] = {MAC_EMU_1,21,21};
	table["xt.mac_emu_ac_sync_en"       ] = {MAC_EMU_1,24,24};
	// MAC_EMU_2
	unsigned int MAC_EMU_2 = 0x400801C0;
	table["xt.mac_emu_tx_num_frames"] = {MAC_EMU_2,31,0};
	// MAC_EMU_3
	unsigned int MAC_EMU_3 = 0x400801C4;
	table["xt.mac_emu_tx_pause_frames"] = {MAC_EMU_3,31,0};
	// MAC_EMU_4
	unsigned int MAC_EMU_4 = 0x40080184;
	table["xt.mac_emu_ac_tx_delay"] = {MAC_EMU_4,31,0};
	// MAC_EMU_5
	unsigned int MAC_EMU_5 = 0x40080188;
	table["xt.mac_emu_ac_rx_delay"] = {MAC_EMU_5,31,0};
	// MAC_EMU_6
	unsigned int MAC_EMU_6 = 0x4008018C;
	table["xt.mac_emu_ac_rx_width"] = {MAC_EMU_6,31,0};
	// TDP_TX_0 
	unsigned int TDP_TX_0 = 0x400800C8;
	table["xt.trigger_tx_timer"] = {TDP_TX_0,31,0};
    // AIU_2
	unsigned int AIU_2 = 0x400800B4;
	table["xt.aiu_swap_rx_port"] = {AIU_2,1,0}; 
	table["xt.aiu_swap_tx_port"] = {AIU_2,5,4};
    // AIU_27	
	unsigned int AIU_27 = 0x40080130;
	table["xt.aiu_mux0_tx"] = {AIU_27, 15, 0};
	table["xt.aiu_mux0_rx"] = {AIU_27, 31, 16};
	// AIU_28	
	unsigned int AIU_28 = 0x40080130;
	table["xt.aiu_mux1_tx"] = {AIU_28, 15, 0};
	table["xt.aiu_mux1_rx"] = {AIU_28, 31, 16};
	// AGC_0
	table["NWIN"] = {0x40080078,2,0}; 
	table["NADAPT"] = {0x40080078,6,4};
	table["xt.agc_nset"] = {0x40080078,10,8};
	table["NDLY"] = {0x40080078,14,12};
	table["TPOWER"] = {0x40080078,23,16};
	table["xt.agc_igain"]  = {0x40080078,31,24};
	// AGC_1
	unsigned int AGC_1 = 0x4008007C;
	table["xt.agc_floor"]     = {AGC_1,23,16};
	table["xt.agc_threshold"] = {AGC_1,15,0};
	// AGC_2
	unsigned int AGC_2 = 0x40080080;
	table["xt.agc_timeout"]         = {AGC_2,15,0};
	table["xt.false_detection_1"]   = {AGC_2,23,16};
	
	// RX_FILTER
	// GENERAL
	table["TX_INIT"]   = {0x400801D8,0,0}; 	
	table["RX_INIT"]   = {0x400801D8,1,1}; 	
	table["TX_ENABLE"] = {0x400801D8,2,2}; 	
	table["RX_ENABLE"] = {0x400801D8,3,3}; 	
	table["GP2GMAC_DROP_ENA"] = {0x400801D8,30,30}; 	
	table["GPHY_CLOCK_DIV"]   = {0x400801D8,31,31}; 	
	table["DIGITAL_RX_GAIN_ENA"] = {0x400801D8,24,24}; 	
	table["TRANSMISSSION_RULE"]  = {0x400801D8,4,4};
	// RXO_DBG_#
	table["PSR_TX"] = {0x400801F0,31,0}; 	
	table["DDP_TX"] = {0x400801F4,31,0}; 	
	table["FDP_TX"] = {0x400801F8,31,0}; 	
	table["FFT_TX"] = {0x400801FC,31,0}; 
	table["TDB_TX"] = {0x40080200,31,0}; 	
	table["TDP_TX"] = {0x40080204,31,0};	
	table["MAC_EMU"] = {0x40080208,31,0}; 	
	table["AIU"]    = {0x4008020C,31,0};
	table["PSR_RX"] = {0x40080210,31,0}; 	
	table["DDP_RX"] = {0x40080214,31,0};
	table["FDP_RX"] = {0x40080218,31,0}; 	
	table["TDB_RX"] = {0x4008021C,31,0};
	table["TDP_RX"] = {0x40080220,31,0};
}

//iparams_static::~iparams_static(void){}


/***************************************************************************
 * iparams_static::set_parameter -- write parameter to FPGA/ASIC register  *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     name  -- name of parameter                                          *
 *     value -- value of the parameter                                     *
 *                                                                         *
 * Returns                                                                 *
 *    boolean exit code                                                    *
 ***************************************************************************/
bool iparams_static::set_parameter(string name, int value){
	
	if (get_hw_register( name )){
		set_hw_register( value );
		return true;
	}
	else{
		return false; 
	}
}

/***************************************************************************
 * iparams_static::get_parameter -- read parameter from FPGA/ASIC register *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     name  -- name of parameter                                           *
 *     value -- value of the parameter                                     *
 *                                                                         *
 * Returns                                                                 *
 *    boolean exit code                                                    *
 ***************************************************************************/
bool iparams_static::get_parameter(string name, int &value){
	
	if (get_hw_register( name )){
		unsigned int nBits = hw_register[0].MSB-hw_register[0].LSB+1;
		unsigned int all_ones = ((unsigned int)(pow(2, nBits)-1));
		//
		value = ( hw_register[0].data >> hw_register[0].LSB ) & all_ones;
		return true;
	}
	else{
		return false; 
	}
}

/***************************************************************************
 * iparams_static::get_hw_register --                                      *
 *  read from FPGA/ASIC the register (32-bits) where parameter is mapped   *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     name  -- name of parameter                                          *                                  
 *                                                                         *
 * Returns                                                                 *
 *    boolean exit code                                                    *
 *                                                                         *
 * Updates                                                                 *
 *    private data hw_register                                             *
 ***************************************************************************/
bool iparams_static::get_hw_register( string name ){
	
	// convert (name, value) to (hw_register.address, hw_register.data, hw_register.MSB hw_register.LSB)
	if (table.count(name)>0){
		
		// find table entry with key "name"
		std::map<string,par_mapping>::iterator it=table.find(name);
		
		// assign address
		hw_register[0].address = it->second.address;
		
		// assign data
		hw_handle->read_address(hw_register[0].address, hw_register[0].data);
		
		// get MSB and LSB
		hw_register[0].MSB=it->second.MSB;
		hw_register[0].LSB=it->second.LSB;
		
		return true;
	}
	else {
		cout<<name<<" is not mapped\n";
		return false;
	}
	
}

/***************************************************************************
 * iparams_static::set_hw_register --                                      *
 *       update hw_register.data with <value> and write into FPGA/ASIC reg *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     value  -- value to be written in position [MSB:LSB]                 *
 *                                                                         *
 * Updates                                                                 *
 *    private data hw_register.data                                        *
 ***************************************************************************/
void iparams_static::set_hw_register( int value ){
	
	unsigned int  nBits = hw_register[0].MSB-hw_register[0].LSB+1;

	// create bits to be written in the register
	unsigned int all_ones = ((unsigned int)(pow(2, nBits)-1));
	unsigned int bits = ((unsigned int)value) & all_ones;
	// shifts bits in the corresponding position
	bits = (bits << hw_register[0].LSB); 
	// create bit mask
	unsigned int mask = ~( all_ones << hw_register[0].LSB );
	
	// update bits [MSB:LSB] and assign data
	hw_register[0].data = (hw_register[0].data & mask) | bits;
    
    // update register content
	hw_handle->write_address(hw_register[0].address, hw_register[0].data);

}

/***************************************************************************
 * iparams_static::display_parameters_mapping                              *
 *                                                                         * 
 ***************************************************************************/
void iparams_static::display_parameters_mapping(void){
	
	for (std::map<string,par_mapping>::iterator it=table.begin(); it!=table.end(); ++it)
    std::cout << it->first << " => " <<hex<<"0x"<< it->second.address <<" "<<dec<< it->second.MSB << " "<< it->second.LSB <<'\n';
	//std::cout<<table["ex0"].MSB<<"\n";
	//std::cout<<table["ex1"]<<"\n";
}

 
