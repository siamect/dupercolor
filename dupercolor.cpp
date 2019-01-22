#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;

int main(int argc, char** argv){
double red_factor = atof(argv[1]); 
double green_factor = atof(argv[2]); 
double blue_factor = atof(argv[3]); 
int file_number = atoi(argv[4]);

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  char infile[255];
  char outfile[255];
  sprintf(infile,"/home/martin/Videos/%i.mp4",file_number);
  sprintf(outfile,"/home/martin/Videos/%i_c.mp4",file_number);
  VideoCapture cap(infile); 
    
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
     
  // Default resolution of the frame is obtained.The default resolution is system dependent. 
   
  // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
  VideoWriter video(outfile,CV_FOURCC('D', 'I', 'V', 'X'),30, Size(2560,1440)); 
  namedWindow("Frame",CV_WINDOW_NORMAL);
  namedWindow("Frame out",CV_WINDOW_NORMAL);
  Mat frame; 

  while(1)
  { 
    cap >> frame;
  
    // If the frame is empty, break immediately
    if (frame.empty())
      break;
     
    /// mess with the frame

	Mat frame_out = Mat::zeros (frame.rows, frame.cols, frame.type() );

	
	Mat bgr[3];   //destination array
	split(frame,bgr);//split source 
	 
	bgr[0] = bgr[0] * blue_factor;
	bgr[1] = bgr[1] * green_factor;
	bgr[2] = bgr[2] * red_factor;
	
	merge(bgr, 3,frame_out);
   ///end of mess 

    // Write the frame into the file 'outcpp.avi'
    video.write(frame_out);
    
    // Display the resulting frame    
    imshow( "Frame out", frame_out );
    imshow( "Frame", frame);
  
    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 'b' ) break;
  }
 
  // When everything done, release the video capture and write object
  cap.release();
  video.release();
 
  // Closes all the windows
  destroyAllWindows();
  return 0;
}
