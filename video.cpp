#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
Mat frame,tempFrame;

string Int_to_String(long long n)
{
    ostringstream stream;
    stream<<n;
    return stream.str();
}

int i = 0;

int process(VideoCapture& capture) {

        while(1) {
            capture >> frame;
            resize(frame,frame,Size(360,288));
            if (frame.empty())
                break;
         
            transpose(frame, frame);
            flip(frame, frame, 0); 
            Mat cameraMatrix = (Mat_<double>(3, 3) << 332.9940853075179, 0, 132.1316529191423, 0, 312.6317086084869, 181.8092030975754, 0, 0, 1);  
            Mat distCoeffs = (Mat_<double>(5, 1) << -0.412050920679748, -0.1059357739570653, -0.0008283295005213291, 0.002197508171154389, 0.7053427088558183);  
     
            undistort(frame,tempFrame,cameraMatrix,distCoeffs);    
  
            imshow("Video", tempFrame);
            
            char key = (char)waitKey(30);
          
            switch (key) {
            
               
                
				//空格拍照
                case 32:
                    i++;
                    imwrite(Int_to_String(i) + ".png",tempFrame);
                    
                   break;
            }
        }
        return 0;
    }  



int main()
{
    VideoCapture capture(2);
  //  capture.set(CV_CAP_PROP_FRAME_WIDTH, 960);  //设置宽高，但是这里的参数必须是摄像头硬件能够提供的，并不是随便设的
    // capture.set(CV_CAP_PROP_FRAME_HEIGHT, 582);   
 
    if(!capture.isOpened()) {
        cerr << "open error \n" << endl;
        return 1;
    }

    return process(capture);
}
