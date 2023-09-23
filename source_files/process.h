/*
 * process.h
 *
 *  Created on: Oct 2, 2012
 *      Author: justin
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <systemc>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace sc_core;
using std::cout;
using std::endl;

typedef sc_dt::sc_int<24> Pixel24bit;
SC_MODULE(processimage){
	SC_HAS_PROCESS(processimage);

	sc_in<sc_dt::sc_int<24> > pixelin;
	sc_out<sc_dt::sc_int<24> > pixelout;
	sc_out<bool> ready_writing;//ready_writing signal used to communicate between output and process module
	sc_in<bool> donein;
	sc_out<bool> doneout;
	sc_in_clk clk;
	sc_fifo<sc_dt::sc_int<24> >* fifo1, *fifo2;
	sc_dt::sc_int<24> window[3][3];
	int count;
	int cols;

	void processing();

	sc_dt::sc_int<24> filter();
		
	processimage(sc_module_name nm, int col) : sc_module(nm) {
		fifo1 = new sc_fifo<sc_dt::sc_int<24> >(col);
		fifo2 = new sc_fifo<sc_dt::sc_int<24> >(col);
		SC_CTHREAD(processing, clk.pos());
		doneout.initialize(false);
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				window[i][j] = 0;
			}
		}
		cols = col;
		count = 0;
		ready_writing.initialize(false);
	}
};

#endif /* PROCESS_H_ */
