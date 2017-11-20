// Demo of a real-time filtering system
// The input signal is a ECG recorded 140 seconds
// FIR filters are going to eliminate the 50Hz and DC noise
// For that purpose the module FIR is employed 


#include "stdio.h"
// includes the FIR filter library
#include "FIR.h"


// The input file is the recorded data "ecg.dat"
// and after passing throughout both filters, the
// resulting signal is written in "ecg_filtered.dat"
int main (){
	const double Fs=1000;   //Sampling rate
	const double F0=2;      //Cut-off frequency of the DC filter
	const double F1=45;     //First cut-off frequency of the 50Hz FIR
	const double F2=55;     //Second cut-off freq of the 50Hz FIR
	const int    MDC=1000;  //Number of taps of the DC filter
	const int    M50=1000;  //Number of taps of the 50Hz filter
	const double f0=F0/Fs;  //F0 normalized
	const double f1=F1/Fs;  //F1 normalized
	const double f2=F2/Fs;  //F2 normalized
	double freqs[2]={f1,f2};//Array with the stop band frequencies
	FIR filterDC(MDC);      //DC filter
	FIR filter50(M50);      //50Hz filter



	filterDC.highpass(f0);
	filter50.stopband(freqs);

	double input = 0.0;
	double output = 0.0;

	FILE *fin = fopen("ecg.dat","r");
	if(fin != NULL){
		FILE *fout = fopen("ecg_filtered.dat","w");
		if(fout!= NULL){
			while(feof(fin)==0) {
				double r;
				int t;
				fscanf(fin,"%i %lf",&t,&r);
				input = (2*r-4096)/500;//Converting from raw values to actual values of the amplitude of the signal recorded
				output = filterDC.filter(input);
				output = filter50.filter(output);
				fprintf(fout,"%i %lf",t,output);
			}
		fclose(fout);
		}else{printf("\nOutput file couldnt be opened\n\n");}
	fclose(fin);	
	}else{printf("\nInput file couldnt be opened\n\n");}

	return 0;
}
