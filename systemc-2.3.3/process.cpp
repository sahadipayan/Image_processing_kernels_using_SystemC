#include "process.h"
#include <vector>

// defining a template
typedef sc_dt::sc_int<24> Pixel24bit;

void processimage::processing() {
    // declaring a 2D matrix to store all pixel values
    std::vector<std::vector<Pixel24bit> > image_matrix;
    // row contains all the pixels in a row
    std::vector<Pixel24bit> row;
    sc_dt::sc_int<24> temp_signed;

    // Loading all the pixels into the matrix
    int rows = 0;
    int current_col = 0;
    wait();
    // load the pixels untill sonein becomes 1
    while (!donein) {

	temp_signed=pixelin.read();
	// stores the pixels in a row one by one
        row.push_back(temp_signed);
	//cout << temp_unsigned << "  ";

        current_col++;
        // when coulm is exhausted, push the row pixels to matrix
        if (current_col == cols) {
            image_matrix.push_back(row);
	    // clearing the row and reseting the current column index to start new row pixels loading
            row.clear();
            current_col = 0;
            rows++;
        }
       wait();
    }
    // all pixels are loaded in a matrix
    // now in the next step, we will create window by moving it both horizontally and vertically
    // the window size is 3*3, it was initialized in header file
    // here i and j are the reference points of the wind. i and j will be created untill rows-2 and cols-2
    for (int i = 0; i < rows - 2; i++) {
        for (int j = 0; j < cols - 2; j++) {
	    //k and l are the row and column indices of the window
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
		    // making sure that ready_signal is kept false untill full window is ready. ready signal used to communicate between output and process module
		    ready_writing.write(false);
                    window[k][l] = image_matrix[i + k][j + l];
		    //cout << "contents: " <<window[k][l] << "\n";
		wait();
                }
	    wait();
            }
	    
            // calling filter
            sc_dt::sc_int<24> filtered_pixel = filter();            
	    // since the window is ready, ready_writing signal is made high
	    ready_writing.write(true);
	    wait();
	    //pushing to output module
            pixelout.write(filtered_pixel);
	    
        }
 	wait();
    }
    //since the pixels are processed, making the doneout signal high
    doneout.write(true);	

}

//to perform median filtering uncoment the following block

sc_dt::sc_int<24> processimage::filter() {
    std::vector<sc_dt::sc_int<24> > values;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            values.push_back(window[i][j]);
		wait();
        }
	wait();
    }
    sort(values.begin(), values.end());
    cout << "filtered value: " << values[values.size() / 2] << "\n";
//	cout << "\n";
   return values[values.size() / 2]; // Return the median value
//return window[k][l];
}



/*
//to perform Sobel edge detection filtering uncoment the following block
sc_dt::sc_int<24> processimage::filter() {
    // two Sobel kernels are defined for computing the horizontal x and vertical y gradients
    const int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // using the previous window computing the x and y direction gradients
    sc_dt::sc_int<24> gx = 0, gy = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gx += window[i][j] * sobel_x[i][j];
            gy += window[i][j] * sobel_y[i][j];
        }
    }

    // computing the square root of the sum of squared gradients
    sc_dt::sc_int<24> gradient = sqrt(gx * gx + gy * gy);
    
    //applying thresholding on gredient to make edge more visible  
    //comparing with 2^22 and gradient is greater than thresold return 2^24-1 (all 1)    
	if (gradient>4194304){
	return 16777215;  
	}
    //otherwise return 0
	else{
	return 0;
	} 
  
 //   return gradient;
}
*/

