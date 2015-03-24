#include "node.hpp"

using namespace std;

/*****************************************************************
 * node::node -- Initialize Private Data                         *
 *****************************************************************/
// Node::Node( void ){}
 
 /*****************************************************************
 * node::~node -- 
 *****************************************************************/
 //Node::~Node( void ){}
 
 /***************************************************************************
 * Node::connect --                                                        *
 *   open COMM port between PC and Quintessa using Quintessa methods       *
 *                                                                         *
 *  Updates:                                                               *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *     name -- COMM port indentifier (e.g. "COM3")                         *
 *                                                                         *
 * Returns                                                                 *
 *    bool                                                                 *
 ***************************************************************************/
 bool Node::connect( std::string name ) {
     
	bool error = false;
	
	log_file<<"connect to "<<name<<"\n";
	if(!quintessa.connect(name)){error=true;}
	
    return (!error);
} 

void Node::set_log_file(string directory){
	
	// create filename string
	string filename = directory + "\\node.txt";
	// open
	log_file.open(filename, std::ofstream::out | std::ofstream::app);
	
	// quintessa log file
	quintessa.set_log_file( directory );
	//
	
}

 /***************************************************************************
 * Node:: --                                                     *
 *        *
 *                                                                         *
 *  Updates:                                                               *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Parameters                                                              *
 *                                                                         *
 * Returns                                                                 *
 *    void                                                                 *
 ***************************************************************************/
    
