#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serial_core.hpp"
#include "comm_core.hpp"

#define COMM_PORT                 this->handle

#define XT_REG_AGC_0              0x40080078
#define XT_REG_AGC_1              0x4008007C
#define XT_REG_RXO_AGC_0		  0x40080230
#define XT_REG_RXO_AGC_1		  0x40080234

using namespace std;


class agc {
	private:		
	public:
		void set_gain( COMM_HANDLE, int );
		int  read_power_ant0( COMM_HANDLE );
		int  read_power_ant1( COMM_HANDLE );
};


int main(int argc, char *argv[]) {

/*************************/
// VARIABLES DECLARATION
/************************/
	agc iAgc;  // AGC object
	int iGain =0; // agc gain
	int iAtt  =0; // value external attenuator
	int Ptx[2], Prx[2]; // tx and rx power
	char keyboard_char; // read character from keyboard
	bool valid_answer;   
	bool again;   
	int com_tx = 4;
	int com_rx = 3;
	static char logs_dir[256] = "X:\\orion\\work\\mpausini\\dsn\\system\\mimo_node\\04_logs\\";
	bool error_tx;
	bool error_rx;
	unsigned int data;

/******************************************************************************/
// INITIALIZE SERIAL PORT
/******************************************************************************/

	cout << "\n\nInitialize Serial Ports: ";
	
	COMM_HANDLE theTxHandle =  (COMM_HANDLE)new SerialCore(com_tx, logs_dir, error_tx);
	COMM_HANDLE theRxHandle =  (COMM_HANDLE)new SerialCore(com_rx, logs_dir, error_rx);
	
	if (error_tx || error_rx) {
		cout << "\nERROR opening COM/TCP ports\n";
		cout << "Press [ENTER] to finish...\n";
		getch();
		return (1);
	}
	else{cout <<"OK\n";}
	

/******************************************************************************/
// Configure Tone Transmission
/******************************************************************************/
cout << "\nConfigure tone transmission\n";

// config tx
//theTxHandle->write_address(0x400800C0, 0x80000011); // FFT_CLK_DIV = 1
//theTxHandle->write_address(0x400801D8, 0xC0000000); // GPHY_CLOCK_DIV = 1

theTxHandle->write_address(0x400F0000, 0x00000003); //Enable TX AFE A and AFE B

// config rx
//theRxHandle->write_address(0x400800C0, 0x80000011);
//theRxHandle->write_address(0x400801D8, 0xC0000000);
//theRxHandle->write_address(0x400F0000, 0x0000000C);


	

/******************************************************************************/
// ITERATE AGC GAIN
/******************************************************************************/
    valid_answer = false;
    
    while (!valid_answer){
    
	    cout << "\nSelect Measurement\n";
		cout << "Auto ('A')  : automatic loop in gain range [-18:1:50]\n";
		cout << "Manual ('M'): select gain manually\n" ;
		cin >> keyboard_char;
		
		if (keyboard_char == 'M'){
			valid_answer = true; // 
			again = true;
			while (again){
				// select action
				cout <<"Menu: ('G'):set gain; ('A'):set attenuation; ('R'): read power measurements; ('Q'): quit => ";
				cin >> keyboard_char;
				switch (keyboard_char) {
					case 'G':
						cout <<"Enter gain value [dB]. Range = [-18:42]: ";
						cin >> iGain;
						iAgc.set_gain( theRxHandle, iGain );
						again = true;
						break;
					case 'A':
						cout <<"Enter attenuation value [dB]: ";
						cin >> iAtt;
						again = true;
						break;
					case 'R':
						Prx[0] = iAgc.read_power_ant0( theRxHandle );
						Prx[1] = iAgc.read_power_ant1( theRxHandle );
						Ptx[0] = Prx[0] - iGain + iAtt;
						Ptx[1] = Prx[1] - iGain + iAtt;
						cout <<"[iGain="<<iGain<<" iAtt="<<iAtt<<" Prx[0]="<<Prx[0]<<" Prx[1]="<<Prx[1]<<" => Ptx[0]="<<Ptx[0]<<" Ptx[1]="<<Ptx[1]<<"\n";
						again = true;
						break;
					case 'Q':
						again = false;
						break;
					default:
						cout <<"Invalid answer\n";
						again = true;
				}				
			}
		}
		else if (keyboard_char == 'A'){
			valid_answer = true;
			//
			cout <<"AGC range: [-18 20] dB. Set External Attenuator to 15 dB\n";
			cout << "Press a key when ready";
			cin >> keyboard_char;
			iAtt = 15;
			for (iGain=-18; iGain<20;iGain=iGain+1){
				iAgc.set_gain( theRxHandle, iGain );
				Sleep(100);
				Prx[0] = iAgc.read_power_ant0( theRxHandle );
				Prx[1] = iAgc.read_power_ant1( theRxHandle );
				Ptx[0] = Prx[0] - iGain + iAtt;
				Ptx[1] = Prx[1] - iGain + iAtt;
				cout <<"[iGain="<<iGain<<" Prx[0]="<<Prx[0]<<" Prx[1]="<<Prx[1]<<" => Ptx[0]="<<Ptx[0]<<" Ptx[1]="<<Ptx[1]<<"\n";
			}
			cout <<"AGC range: [10 45] dB. Set External Attenuator to 40 dB\n";
			cout << "Press a key when ready";
			cin >> keyboard_char;
			iAtt = 40;
			for (iGain=10; iGain<45;iGain=iGain+1){
				iAgc.set_gain( theRxHandle, iGain );
				Sleep(100);
				Prx[0] = iAgc.read_power_ant0( theRxHandle );
				Prx[1] = iAgc.read_power_ant1( theRxHandle );
				Ptx[0] = Prx[0] - iGain + iAtt;
				Ptx[1] = Prx[1] - iGain + iAtt;
				cout <<"[iGain="<<iGain<<" Prx[0]="<<Prx[0]<<" Prx[1]="<<Prx[1]<<" => Ptx[0]="<<Ptx[0]<<" Ptx[1]="<<Ptx[1]<<"\n";
			}
			cout << "Measurement done. Press any key to quit.";
			cin >> keyboard_char;
		}
		else{
			valid_answer = false;
			cout <<"\nInvalid Character\n";
		}
		
	}
	
	cout << "\nDisable Tone\n";
	theTxHandle->write_address(0x400F0000, 0x00000000); //Disable TX AFE A and AFE B
    
}

void agc::set_gain( COMM_HANDLE node_handle, int iGain ){
	std::cout << iGain << "\n";
	// APB - Set IGAIN/TPOWER
	unsigned int temp_value;
	node_handle->read_address(XT_REG_AGC_0, temp_value);
//	unsigned int tpower_val = ((unsigned int)tpower) & 0xFF;
	unsigned int igain_val = ((unsigned int)iGain) & 0xFF;
	temp_value = (temp_value & 0x00FFFFFF) | (igain_val << 24);
	node_handle->write_address(XT_REG_AGC_0, temp_value);
}

int agc::read_power_ant0( COMM_HANDLE node_handle){
	
	unsigned int temp_value;
	node_handle->read_address(XT_REG_RXO_AGC_0, temp_value);
	char power = (char)((temp_value >> 0) & 0xFF);
	return ((int)power);
}

int agc::read_power_ant1( COMM_HANDLE node_handle){
	
	unsigned int temp_value;
	node_handle->read_address(XT_REG_RXO_AGC_1, temp_value);
	char power = (char)((temp_value >> 0) & 0xFF);
	return ((int)power);
}

