//Class which implements a FIR filter
//by selecting the cut-off frequencies,
//the number of taps,
//and the type of the filter:
//	*High pass
//	*Low pass
//	*Stop band
//	*Pass band
//
//Created by Eduardo Sebastián
//Date: 19/11/2017

#include "stdio.h"
#include "string.h"
#include "math.h"
#include "vector"

//Class
class FIR{
	
	//Atributes
	private:
	int                 taps; //number of coefficients of the FIR filter
	std::vector<double> coeff;//coefficients of the FIR filter
	char                type; //type of the FIR filter: 'l' or 'L'= lowpass
		                  //		                   'h' or 'H'= highpass
		      		  //		                   's' or 'S'= stopband
	              		  //			           'p' or 'P'= passband			    
	std::vector<double> freq; //Normalized cut-off frequencies
	std::vector<double> buff; //buffer implementing the M(taps) delays	
	
	//Constructor
	public: FIR(int M){

		if(M<0){
		printf("\nThe number of taps can not be less than 0\n");
		taps=0;		
		}else{
		taps=M;
		}		
	
		coeff.resize(taps);
		buff.resize(taps);
		type='l';
	}

	//Methods
	public:
	int    getTaps();		  //Gets the number of taps of the filter
	double getCoeff(int i);	          //Gets the coefficient of index i
	char   getType();		  //Gets the type of the filter
	double getFreq(int i);		  //Gets the cut-off frequency i: if the filter is first order, i=0
	double getBuffer(int i);	  //Gets the buffered value of index i
	void   setTaps(int M);            //Sets the number of taps of the filter
	void   setCoeff(double x, int i); //Sets the coefficient of the position i with the value x
	void   setType(char a);		  //Sets the type of the filter
	void   setFreq(double x, int i);  //Sets the cut-off frequency of index i: if the filter is first order, i=0
	void   setBuffer(double x, int i);//Sets the value of index i of the buffer to x
	void   lowpass(double f);	  //Generates the coefficients of a low pass filter with cut-off frequency f
	void   highpass(double f);        //Generates the coefficients of a high pass filter with cut-off frequency f
	void   stopband(double f[2]);     //Generates the coefficients of a stop band filter with cut-off frequencies f
	void   passband(double f[2]);     //Generates the coefficients of a pass band filter with cut-off frequencies f
	double filter(double x);	  //Filters the scalar input x by using the coefficients of the filter and returns a scalar output
					  //If no coefficient generator method is applied, the coefficients are all zero.
};
	


//Implementation of the methods

int FIR::getTaps (){return taps;}



double FIR::getCoeff (int i){
	if (i>= this->getTaps() or i<0) {
	printf("\nThat coefficient does not exist\n");
	return 0.0;
	}else{
	return coeff[i];
	}
}


char FIR::getType(){
	if (type=='l' or type=='L'){
	printf("\nLow-pass filter\n");
	}
	if (type=='h' or type=='H'){
	printf("\nHigh-pass filter\n");
	}
	if (type=='s' or type=='S'){
	printf("\nStop-band filter\n");
	}
	if (type=='p' or type=='P'){
	printf("\nPass-band filter\n");
	}
	return type;
}

double FIR::getFreq (int i){
	if (i>= 2 or i<0) {
	printf("\nThat frequency does not exist\n");
	return 0.0;
	}else{
	return freq[i];
	}
}

double FIR::getBuffer (int i){
	if (i>= this->getTaps() or i<0) {
	printf("\nThat value does not exist\n");
	return 0.0;
	}else{
	return buff[i];
	}
}
			

void FIR::setTaps(int M){
	if (M<=0){printf("\nThat value is not possible\n");}
	else{
		taps=M;
		coeff.resize(M);
		buff.resize(M);
	}
}



void FIR::setCoeff(double x, int i){
	if (i>=this->getTaps() or i<0){
	printf("\nThat coefficient does not exist\n");
	}else{
	coeff[i]=x;
	}	
}


void FIR::setType(char a){
	if (a=='l' or a=='L' or a=='h' or a=='H' or a=='s' or a=='S' or a=='p' or a=='P'){
	type=a;
	}else{
	printf("\nThat type is not possible with this class\n");
	}
}
	

void FIR::setFreq(double x, int i){
	if (i>freq.size() or x>0.5 or x<0.0 or i<0){
	printf("\nThat frequency is not normalized or the index does not exist\n");	
	}else{
	freq[i]=x;
	}	
}


void FIR::setBuffer(double x, int i){
	if (i>=this->getTaps() or i<0){
	printf("\nThat index for the buffer does not exist\n");
	}else{
	buff[i]=x;
	}	
}


void FIR::lowpass(double f){

	freq.resize(1);
	if (f<0.0 or f>0.5){printf("\nThe frequency is not normalized\n");}
	else{
		this->setFreq(f,0);
		this->setType('l');
		int M=this->getTaps();
		int W=M/2;

		for (int i=-W; i<W; i++){
			if (i==0) {
				this->setCoeff(2*f,W);
			}else{		
				this->setCoeff((sin(2*(M_PI)*f*i)/(i*(M_PI))),i+W);
			}
		}
	}
}


void FIR::highpass(double f){

	freq.resize(1);
	if (f<0.0 or f>0.5){printf("\nThe frequency is not normalized\n");}
	else{
		this->setFreq(f,1);
		this->setType('h');
		int M=this->getTaps();

		for (int i=-int(M/2); i<int(M/2); i++){
			if (i==0) {
				this->setCoeff(1-(2*f),i+int(M/2));
			}else{		
				this->setCoeff(-sin(2*M_PI*f*i)/(i*M_PI),i+int(M/2));
			}
		}
	}
}


void FIR::stopband(double f[2]){

	freq.resize(2);
	double f1=f[0];
	double f2=f[1];

	if (f1<0.0 or f1>0.5 or f2<0.0 or f2>0.5){printf("\nThe frequencies are not normalized\n");}
	else{
		this->setFreq(f1,0);
		this->setFreq(f2,1);
		this->setType('s');
		int M=this->getTaps();
		
		for (int i=-int(M/2); i<int(M/2); i++){
			if (i==0) {
				this->setCoeff(1+((2*M_PI*f1)-(2*M_PI*f2))/M_PI,i+int(M/2));
			}else{		
				this->setCoeff(((sin(2*M_PI*f1*i)-sin(2*M_PI*f2*i))/(i*M_PI)),i+int(M/2));
			}
		}
	}
}


void FIR::passband(double f[2]){

	freq.resize(2);
	double f1=f[0];
	double f2=f[1];

	if (f1<0.0 or f1>0.5 or f2<0.0 or f2>0.5){printf("\nThe frequencies are not normalized\n");}
	else{
		this->setFreq(f1,0);
		this->setFreq(f2,1);
		this->setType('s');
		int M=this->getTaps();
		
		for (int i=-int(M/2); i<int(M/2); i++){
			if (i==0) {
				this->setCoeff(((2*M_PI*f2)-(2*M_PI*f1))/M_PI,i+int(M/2));
			}else{		
				this->setCoeff(((sin(2*M_PI*f2*i)-sin(2*M_PI*f1*i))/(i*M_PI)),i+int(M/2));
			}
		}	
	}
}

double FIR::filter(double x){

	double output=0.0;
	
	int M = this->getTaps();

	for (int i=M-1; i>0; i--){this->setBuffer(this->getBuffer(i-1),i);}
	
	this->setBuffer(x,0);
	
	for (int i=0; i<M; i++){output+=(this->getBuffer(i))*(this->getCoeff(i));}

	return output;	

}


