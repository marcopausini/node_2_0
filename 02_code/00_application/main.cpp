#include <iostream>
#include <string>
#include <fstream>
#include "node.hpp"
#include "header.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	/*************************/
	// VARIABLES DECLARATION
	/************************/
	
	std::string key;
	
	// COM port ID
	std::string COM_port[2]={"COM4", "COM3"};
	
	
	/******************************************************
	* FRAME
	*******************************************************/
	Header header("this is not a valid file");
    cout<<"Press a key to end"<<endl;
    cin>>key;
	return 0;
	/******************************************************************************/
	// CONNECT/DISCONNECT/RESUME
	/******************************************************************************/
	
	// create nodes
	Node node[2];
	
	// assing log directory
	node[0].set_log_file("X:\\orion\\work\\mpausini\\dsn\\system\\mimo_node\\04_logs\\node_COM4\\");
	node[1].set_log_file("X:\\orion\\work\\mpausini\\dsn\\system\\mimo_node\\04_logs\\node_COM3\\");
	
	for(int i=0;i<2;i++){
	
	
	
	// connect
	cout << "\nConnect Node to Quintessa, through COM port: "<< COM_port[i];
	if (!node[i].connect( COM_port[i] )){return(1);}
	else{std::cout<<" - OK\n";}
    
   
	//disconnect
	cout << "\nDisconnect from Quintessa:\n";
	node[i].disconnect();
	
	//resume
    cout << "\n\nResume connection to Quintessa"<<endl<<endl;
	if (!node[i].resume( )){return(1);}


	/******************************************************************************/
	// FINISH
	/******************************************************************************/

    //disconnect
	cout << "\nDisconnect from Quintessa.\n";
	node[i].disconnect();
	
	}
	
    cout<<"Press a key to end"<<endl;
    cin>>key;

	return 0;
}
