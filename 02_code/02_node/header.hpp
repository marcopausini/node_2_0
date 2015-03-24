/****************************************
* header
*		header classes
*****************************************/
#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include <iostream>
#include <string>


/*****************************************************************************************
* header_common class                                                                    *
*   abstract base class to build upon each header frame type dependent class             *
*                                                                                        *
* Member functions                                                                       *
******************************************************************************************/
class HeaderCommon {
	private:
       
    protected:
     // header common fields
        struct {
            unsigned char ft;
            unsigned char dod;
            unsigned char sid;
            unsigned char did;
            unsigned char mi;
            unsigned char dri;
            unsigned char ehi;
            unsigned char hsi;
        } common_fields;
        
        // header bytes encoding header fields
        unsigned char bytes[21];
        
        //
        unsigned short calculate_dur();
        
	public:
        // constructor
       // void HeaderCommon( ){}
        // default  de-constructor
		// copy constructor defaults
        
        // abstract function to configure common and fts fields via (file/console)
        virtual void configure_header_fields() = 0;
        
        // compute DUR and other dependent parameters
        void compute_header_fields();
        
       
};

/*****************************************************************************************
* header interface class                                                                    *
*   *
*                                                                                        *
* Member functions                                                                       *
******************************************************************************************/
class Header{
	private:
		HeaderCommon *h;
	public:
		Header( std::string config_file );
};

/*****************************************************************************************
* header PROBE class                                                                    *
*                *
*                                                                                        *
* Member functions                                                                       *
******************************************************************************************/

class HeaderProbe: public HeaderCommon  {
    private:
        // frame type specific fields
        struct {
            unsigned int prb_dur;
            unsigned char prbtype;
            unsigned char prbsym;
            unsigned char apsdc_p;
            unsigned char prbgi;
            unsigned char currts;
            unsigned char mimo_ind;
            unsigned char prb_bmat_id;
            unsigned char ace_sym;
            unsigned char num_silent_sym;
        } fts_fields;
        
	public:
        // default constructor 
        // default  de-constructor
		// copy constructor defaults
        
		// not sure where to put it
		void compute_header_fields();
		
        // 
        void configure_header_fields();  
};

/*****************************************************************************************
* header PROBE class                                                                    *
*                *
*                                                                                        *
* Member functions                                                                       *
******************************************************************************************/

class HeaderMsg: public HeaderCommon  {
    private:
        // frame type specific fields
        struct {
            unsigned int  dur;
        } fts_fields;
        
	public:
        // default constructor 
        // default  de-constructor
		// copy constructor defaults
        
		
        // 
        void configure_header_fields();  
};


#endif
