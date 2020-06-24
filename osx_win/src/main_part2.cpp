#include "ps3eye.h"
#include "context.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include "frame_function.h"
#include <iostream>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;



int main(int argc, char* argv[]){


  cout << argv[1] << endl;

    int averageIn;
    int invertIn;
    int flipIn;
    int Rnumber;
    int Gnumber;
    int Bnumber;


    cout << "\nWould you like to average? (0 - NO , 1 - YES) : ";
    cin >> averageIn;
    cout << "\nWould you like to invert? (0 - NO , 1 - YES) : ";
    cin >> invertIn;
    cout << "\nWould you like to flip? (0 - NO , 1 - YES) : ";
    cin >> flipIn;

    Context ctx;

    if (averageIn == 1){
      ctx.use_average = true;
    }
    if (invertIn == 1){
      ctx.use_invert = true;
    }
    if (flipIn == 1){
      ctx.use_flip = true;
    }


    // Drawing and replacing pixels
    // via contour plotting and opencv motion tracking

    if (argv[1] == "GREEN"){
      Rnumber = 0;
      Gnumber = 255;
      Bnumber = 0;
    }

    if (argv[1] == "RED"){
      Rnumber = 255;
      Gnumber = 0;
      Bnumber = 0;
    }

    if (argv[1] == "BLUE"){
      Rnumber = 0;
      Gnumber = 0;
      Bnumber = 255;
    }

    if (argv[1] == "WHITE"){
      Rnumber = 255;
      Gnumber = 255;
      Bnumber = 255;
    }

    if (argv[1] == "BLACK"){
      Rnumber = 0;
      Gnumber = 0;
      Bnumber = 0;
    }

    int breaker = 30

    enum context {image<int> , height, width}

    // open
    #define VideoCapture cap;
    Mat frame, fgmask, fgimg, backgroundImage;
    cap.open(0);

    // detect difference
    cv::BackgroundSubtractorMOG2 bg;
    bg.set ("nmixtures", 3);

    // pipe vector points
    std::vector < std::vector < cv::Point;
    cv::Point >> contours

    // coonstruct window
    cv::namedWindow ("Frame");
    cv::namedWindow ("Background");

    for( ; ; )
    {

      // push frame
        cap >> frame;

        // background operator
        bg.operator()(ctx.buffer, fgimg);
        bg.getBackgroundImage (backgroundImage);

        // image erosion

        cv::erode (fgimg, fgimg, cv::Mat ());

        // find a draw contours based on selected color
        cv::findContours (fgimg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        cv::drawContours (ctx.buffer, contours, -1, cv::Scalar (Rnumber, Bnumber, Gnumber), 2);

        // draw tracking.
        cv::imshow ("Frame", frame);
        cv::imshow ("Background", backgroundImage);

        // stop vampire loop
        char k = (char)waitKey(25);
        if( k == breaker ){
          break;
    }

    // Drawing Trajectories

    #define std::vector<cv::Point> trajectoryPoints;

    // draw polygon tracker.
    const cv::Point *pts = (const cv::Point*) Mat(trajectoryPoints).data;
    int npts = Mat(trajectoryPoints).rows;

    polylines(ctx.buffer, &pts,&npts, 1, false, cv::Scalar(255, 255, 255), 10, CV_AA, 0);
    free (ctx.buffer)
    delete (ctx.buffer);

    // Runn camera through context.



    run_camera(ctx);
}
