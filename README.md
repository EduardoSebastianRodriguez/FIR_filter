# FIR_filter
This repository contains a library in C++ which implements real time FIR filters. 
-----------------------------------------------------------------------
Elements of the repository:

   + 'FIR.h': library which implements the FIR library
   + 'HOWTO.txt': document with the instructions of use of the library
   + 'DEMO.cpp': demo which shows the performance of the library by filtering an ECG
   + 'ecg.dat': file of the ECG recorded, works as the input of the demo
   + 'ecg_filtered': file of the ECG filtered by our FIR filters, is the output of the demo
   + 'DOCUMENTATION.txt': compendium of the atributes, constructor and methods of the class contained in the library
   + 'Python plotting codes and figures': folder which contains Python codes for plotting the input and output of the demo
                                          with the resulting figures: ECG, the ECG filtered, a zoomed heartbeat and a zoomed
                                          filtered heartbeat.
    
    
 The module implements real time FIR filters, which are one of the most widespread digital filters.
 The module does both the generation of the coefficients of the filter and the filtering operation.
 In the case of the filtering, the input is not an array but a single scalar value, returning another
 single scalar value. This means the class works either with a saved signal or in a real time system,
 in which the computer recieves one single real value at specific instants of time, giving as an output
 the corresponding filtered real value from passing troughout the filter.
 
 Descriptions of the behaviour, structure and demo are provided in 'HOWTO.txt' and 'DOCUMENTATION.txt'
 
 Have a nice day!
 
 Eduardo
