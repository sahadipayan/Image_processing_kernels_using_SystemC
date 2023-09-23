# Image_processing_kernels_using_SystemC
Implementation of a high-level design of image processing kernels using SystemC and OpenCV

**********************************************Fire hirerarchy*********************************************
File Structure ---->
	|task2 
	    |------> source_files
	    |------> systemc-2.3.3 (You have to be inside this folder for running the codes for task 2 )  
	    |------> Results (All the input and output images of tasks are stored here)
	    |------> readme.txt  for instruction

**********************************************System Requirement******************************************
We had following system setup to run this code:
1. Ubuntu 16.04.7 LTS
2. SystemC 2.3.3
3. OpenCV 3.4.4 

**************************************run the codes for Task 2******************************************

The folder "systemc-2.3.3" contain all the necessary files.

step 1: At first find the process.cpp in folder named "systemc-2.3.3". Open the file. There are implementation of two different filters: median filtering and sobel filtering.
Make sure desired filtering is uncommented and the other one is commented. Save the file.

Step 2: Open Makefile and change the directory in line 3 your systemC directory

Step 3: make sure that SystemC installatation is in in usr/local/systemc-2.3.3. otherwise go to the CMakeLists.txt in folder "systemc-2.3.3" and change the proper directory in line 10

step 4: find the directory where your install OpenCV "build" folder is located. Go to the CMakeLists.txt and change the directory in line 13 accordignly

Step 5: set your directory to "/systemc-2.3.3/build"

Step 6: open terminal in the current directory

step 7: write "cmake .."

step 8: write "make". it will create a executable file named "SystemCOpenCV" in the folder

step 9: write "./SystemCOpenCV " followed by input image name. For example, "./SystemCOpenCV cube.jpg".
In the folder there are several sample images for test. The output image will be saved with name "processed.jpg".





