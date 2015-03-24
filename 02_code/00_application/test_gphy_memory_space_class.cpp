#include <iostream>
#include <string>
#include "node.hpp"

int main(int argc, char *argv[]) {

/*************************/
// VARIABLES DECLARATION
/************************/
	// Serial Comm Ports: [0]:Tx; [1]:Rx
	int comm_ports_id[2] = {4,3};
    CommCore * comm_ports[2];
	static char logs_dir[256] = "X:\\orion\\work\\mpausini\\dsn\\system\\mimo_node\\04_logs\\";
	bool error_tx;
	bool error_rx;
	unsigned int value;
    unsigned int data;
    int index;
    string key;
	
/******************************************************************************/
// INITIALIZE SERIAL PORT
/******************************************************************************/
    SerialCore quintessa;
	
/******************************************************************************/
// INITIALIZE NODE
/******************************************************************************/
	
	
	cout << "\n\nInitialize Node:\n\n";
	
	// create node object
	Node node;  
    
    // display private members of quintessa
  //  node.quintessa.display_private_values();
    
    
    //
    // test read and write method
    //
    index = 10;
    data = 0xAB7F;
    //
    node.GPHY_memory.GPHY_REG.read( index, value );
    cout << "initial value at index "<<index<<" is: "<< value<<"\n"; 
    //
    cout << "write value "<< data <<" at index "<<index<<"\n"; 
    node.GPHY_memory.GPHY_REG.write( index, data );
    //
	node.GPHY_memory.GPHY_REG.read( index, value );
    cout << "value at index "<<index<<" is: "<< value<<"\n"; 
	//
	index = 0xFFFFFF;
    data = 0xBBBB;
    //
    node.GPHY_memory.GPHY_REG.read( index, value );
    cout << "initial value at index "<<index<<" is: "<< value<<"\n"; 
    //
    cout << "write value "<< data <<" at index "<<index<<"\n"; 
    node.GPHY_memory.GPHY_REG.write( index, data );
    //
	node.GPHY_memory.GPHY_REG.read( index, value );
    cout << "value at index "<<index<<" is: "<< value<<"\n"; 
	//
	
	//
	// test connection to hardware
	//
	cout<<"connect node with the quintessa board, through comm port:"<< comm_ports_id[0] <<endl;
	error_tx = node.connect( comm_ports_id[0] );
	
	
    //
    // test flush and dump
    //
    //node.GPHY_memory.GPHY_REG.flush(  0x0000, 0xF );
    
    cout<<"Press a key to end"<<endl;
    cin>>key;

	return 0;
}
