#include <iostream>
#include <string>
#include "iparams_static.hpp"
#include "serial_core.hpp"
#include "comm_core.hpp"

int main(int argc, char *argv[]) {

/*************************/
// VARIABLES DECLARATION
/************************/
	// Serial Comm Ports: [0]:Tx; [1]:Rx
	int com_ports[2] = {4,3};
	static char logs_dir[256] = "X:\\orion\\work\\mpausini\\dsn\\system\\mimo_node\\04_logs\\";
	bool error_tx;
	bool error_rx;
	int value;
	
/******************************************************************************/
// INITIALIZE SERIAL PORT
/******************************************************************************/

	cout << "\n\nInitialize Serial Ports: ";
	
	COMM_HANDLE theTxHandle =  (COMM_HANDLE)new SerialCore(com_ports[0], logs_dir, error_tx);
	COMM_HANDLE theRxHandle =  (COMM_HANDLE)new SerialCore(com_ports[1], logs_dir, error_rx);
	
	if (error_tx || error_rx) {
		cout << "\nERROR opening COM/TCP ports\n";
		cout << "Press [ENTER] to finish...\n";
		getch();
		return (1);
	}
	else{cout <<"OK\n";}
	
	// create iparams object
	iparams_static iparams[2];  
	
	//
	iparams[0].set_handle( theTxHandle );
	iparams[1].set_handle( theRxHandle );
	
	// display parameters mapping
	iparams[0].display_parameters_mapping();
	
	iparams[1].get_parameter("TPOWER",value);
	cout<<hex<<"TPOWER "<<value<<"\n";
	iparams[1].get_parameter("IGAIN",value);
	cout<<hex<<"IGAIN "<<value<<"\n";
	iparams[1].get_parameter("NOEXIST",value);
	cout<<hex<<"NOEXIST "<<value<<"\n";
	// set parameters values
	iparams[1].set_parameter("TPOWER",10);
	iparams[1].set_parameter("IGAIN",-4);
	iparams[1].set_parameter("NOEXIST",0xFF);
	iparams[1].get_parameter("TPOWER",value);
	cout<<hex<<"TPOWER "<<value<<dec<<(signed int)value<<"\n";
	iparams[1].get_parameter("IGAIN",value);
	cout<<"IGAIN "<<(signed char)value<<dec<<(signed int)value<<hex<<value<<"\n";
	iparams[1].get_parameter("NOEXIST",value);
	cout<<hex<<"NOEXIST "<<value<<"\n";
	
	return 0;
}
