/*
 * output.cpp
 *
 *      Author: Justin Roark
 */


#include <iostream>
#include "output.h"
using std::cout;
using std::endl;

void output::buildImage(){
	int ready_temp;
	
	while(true){
		//using a signal ready to comunicate between output and processing module. 
		// it ensures that the processing module is ready to pass a value to output module
				
		if (!done && ready){
			sc_dt::sc_int<24> tempsc;	
			tempsc = pixel.read();
			//cout << "before wait, count: " << count << ", done:" << done << ", ready:" << ready << endl;
			wait();
			//cout << "output read: " << tempsc << "\n";

			(*it)[0] = tempsc.range(7,0); //puts RGB values into Mat variable
			
			(*it)[1] = tempsc.range(15,8);
	               
			(*it)[2] = tempsc.range(23,16);
			
			//cout << "out: " << tempsc.range(7,0) << ", " << tempsc.range(15,8) << ", " << tempsc.range(23,16) << endl;
			
			count++; //we used it for debugging only
			++it;
		}
		
		wait();
	}
}

void output::setMat(int rows, int cols){
	Mat temp(rows,cols, CV_8UC3, Scalar(0,0,0)); //sets up image with correct dimensions
	I = temp;
	it = I.begin<Vec3b>();
	end = I.end<Vec3b>();
	//cout << I;
}

Mat& output::getImage(){
	return I;
}


