#include <iostream>
#include <string>
#include <fstream>
#include "quintessa.hpp"

#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {

/*************************/
// VARIABLES DECLARATION
/************************/

	std::this_thread::sleep_for(std::chrono::seconds(10));
	
	// Quintessa object
	Quintessa quintessa;
	
	// logs directory
	std::string logs_dir = "X:\\orion\\work\\mpausini\\dsn\\system\\mimo_node\\04_logs\\";
	
	// COM port ID
	std::string COM_port="COM3";
	
	bool error;
	unsigned int address[2];
    unsigned int data;
    unsigned int data_read;
    int index;
    std::string key;
	
	
/******************************************************************************/
// CONNECT/DISCONNECT/RESUME
/******************************************************************************/
	
	// connect
	cout << "\nConnect to Quintessa, through COM port: "<< COM_port;
	if (!quintessa.connect( COM_port )){return(1);}
	else{std::cout<<" - OK\n";}
    
    // display private members of quintessa
    quintessa.display_private_values();
	
	//disconnect
	//cout << "\nDisconnect to Quintessa:\n";
	//quintessa.disconnect();
	
	//resume
    //cout << "\n\nResume connection to Quintessa"<<endl<<endl;
	//if (!quintessa.resume( )){return(1);}

/******************************************************************************/
// WRITE REGISTER
/******************************************************************************/
	address[0] = 0x40080048;
    data    = 0xF0BA2799;
    
	cout<<"\nWrite Register: "<<"0x"<<std::hex<<address[0]<<" "<<"0x"<<data<<endl;

	if (!quintessa.write32_register(address[0],data)){return(1);}
	else{cout<<"OK\n";}
	



/******************************************************************************/
// READ REGISTER
/******************************************************************************/

	cout<<"\nRead Register: ";
	if (!quintessa.read32_register(address[0],data_read)){return(1);}
	else{
		cout<<"0x"<<std::hex<<address[0]<<" "<<"0x"<<data_read<<endl;
		cout<<"OK\n";}
	
	
/******************************************************************************/
// SEND COMMAND
/******************************************************************************/
	std::string command; // = "mr 40080048\n";
	std::string reply;
 //  std::ifstream file("X:\\orion\\work\\mpausini\\dsn\\system\\node_tools\\config\\pb25_fpga\\init_tx_conf.thxt");
    std::ifstream file("X:\\orion\\work\\mpausini\\dsn\\system\\node_tools\\config\\pb25_fpga\\test_config.txt");
/*
	while (std::getline(file, command)){
		command = command + "\n";
		cout<<"\nSend Command: "<<command;
		if(!quintessa.send_command(command,reply)){return(1);}
		else{cout<<"reply: "<<reply;};
	}
*/	
	
/******************************************************************************/
// FINISH
/******************************************************************************/

    //disconnect
	cout << "\nDisconnect to Quintessa.\n";
	quintessa.disconnect();
	
    cout<<"Press a key to end"<<endl;
    cin>>key;

	return 0;
}
