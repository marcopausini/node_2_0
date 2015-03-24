#include "header.hpp"

using namespace std;


Header::Header(string config_file){
	
	int ft =0;
	
	if (ft==6){
		h = new HeaderProbe();
	}
	else if
	(ft==0){
		h = new HeaderMsg();
	}
	h->configure_header_fields();
}


/*****************************************************************
 * HeaderCommon::HeaderCommon -- Initialize Private Data       *
 *****************************************************************/
// HeaderCommon::HeaderCommon(){ }
 
 
 unsigned short HeaderCommon::calculate_dur() {
 
 // bool hsi, bool ehi, int n_symb, unsigned char gi_id
 
 //int n_symb = (ftsf.prbsym+1)*4;
 
    // compute number of header symbols
/*	int n_hdr_symb;
	if ((common_fields.hsi==1) && (common_fields.ehi==1)) {
		n_hdr_symb = 4;
	} else  if ((common_fields.hsi==1) && (common_fields.ehi==0)) {
		n_hdr_symb = 2;
	} else if ((common_fields.hsi==0) && (common_fields.ehi==1)) {
		n_hdr_symb = 2;
	} else {
		n_hdr_symb = 1;
	}

	int num_pay_ofdm = n_symb;
	double n_pr = (double)XT_PROF->BETA;
	if (XT_PROF->N_1 > 0.0f) {
		n_pr += XT_PROF->N_1 * (((double)XT_PROF->N_FFT_TX) / ((double)XT_PROF->K_1));
	}
	if (XT_PROF->N_2 > 0.0f) {
		n_pr += XT_PROF->N_2 * (((double)XT_PROF->N_FFT_TX) / ((double)XT_PROF->K_2));
	}
	if (XT_PROF->N_3 > 0.0f) {
		n_pr += XT_PROF->N_3 * (((double)XT_PROF->N_FFT_TX) / ((double)XT_PROF->K_3));
	}
	double dur = n_pr + (((double)n_hdr_symb) * ((double)XT_PROF->N_FFT_TX) * (5.0f / 4.0f));

	if (num_pay_ofdm > 2) {
		dur = dur + (2.0f * ((double)XT_PROF->N_FFT_TX) * (5.0f / 4.0f));
		double cp = (((double)gi_id) + 1.0f) / 32.0f;
		dur = dur + ((double)(num_pay_ofdm - 2)) * ((double)XT_PROF->N_FFT_TX) * (1.0f + cp);
	} else {
		dur = dur + (((double)num_pay_ofdm) * ((double)XT_PROF->N_FFT_TX) * (5.0f / 4.0f));
	}
	dur = dur / XT_PROF->BW_TX;
	dur = dur / (0.25e-6);
*/
	double dur = 0;
	return dur;
    //return ((unsigned short)ceil(dur));
}
 
 /***************************************************************************
 * HeaderProbe::configure_header_fields --                                 *
 *                                                                         *
 * Parameters                                                              *
 *                                                                         *
 * Returns                                                                 *
 *                                                                         *
 ***************************************************************************/
void HeaderProbe::configure_header_fields(){

    common_fields.ft  = 6; // PROBE
    common_fields.dod = 1;
    common_fields.sid = 3;
    common_fields.did = 5;
    common_fields.mi  = 0;
    common_fields.dri = 1;
    common_fields.ehi = 0;
    common_fields.hsi = 0;

    fts_fields.prb_dur  = 0;
    fts_fields.prbtype  = 8;
    fts_fields.prbsym   = 3;
    fts_fields.apsdc_p  = 0;
    fts_fields.prbgi    = 7;
    fts_fields.currts   = 0;
    fts_fields.mimo_ind = 1;
    fts_fields.prb_bmat_id = 16;
    fts_fields.ace_sym     = 3;
    fts_fields.num_silent_sym = 0;
 }
 
  /***************************************************************************
 * HeaderProbe::compute_header_fields --                                 *
 *                                                                         *
 * Parameters                                                              *
 *                                                                         *
 * Returns                                                                 *
 *                                                                         *
 ***************************************************************************/
void HeaderProbe::compute_header_fields(){
    
  //  unsigned short int fts_fields.dur = calculate_dur(false, false, n_symb, ftsf.prbgi);
    //unsigned short  fts_fields.prb_dur = calculate_dur();
   
 }

 
  /***************************************************************************
 * HeaderMsg::configure_header_fields --                                 *
 *                                                                         *
 * Parameters                                                              *
 *                                                                         *
 * Returns                                                                 *
 *                                                                         *
 ***************************************************************************/
void HeaderMsg::configure_header_fields(){

    common_fields.ft  = 0; // CHECK
    common_fields.dod = 1;
    common_fields.sid = 3;
    common_fields.did = 5;
    common_fields.mi  = 0;
    common_fields.dri = 1;
    common_fields.ehi = 0;
    common_fields.hsi = 0;

    fts_fields.dur  = 10;
    
 }
