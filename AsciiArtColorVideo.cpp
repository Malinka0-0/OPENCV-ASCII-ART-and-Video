#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

string path = "D:\\Project\\Video_Audio\\Premiere pro\\Done\\floversmp4.mp4"; //path to img
bool SafeImgOrNot = true; // true - safe img | false - not safe img
string PathToSafeAsciiVideo = "D:\\Project\\Programing\\ASCII\\Save\\Output.mp4"; //path to safe img \\Output.mp4 - name and format
double char_size = 0.6; // char size (big size - low quality | small size -  high quality)

string AsciiChars = " ./`,:;!~+-xmo*#W&8@";
int ASCII_COEFF = 255 / (AsciiChars.length() - 1);

Mat ConverFrame(Mat frame, int frameheigth, int framewidth, int CharStepX, int CharStepY) {
    Mat newimg(frame.rows, frame.cols, CV_8UC3, Scalar(0, 0, 0));

    for (int y = 0; y < frame.cols; y += CharStepX) {
        for (int x = 0; x < frame.rows; x += CharStepY) {
            int Red = frame.at<Vec3b>(x, y)[0];
            int Blue = frame.at<Vec3b>(x, y)[2];
            int Green = frame.at<Vec3b>(x, y)[1];
            char ascii_character = AsciiChars[static_cast<int>(Red / ASCII_COEFF)];

            putText(newimg, string(1, ascii_character), Point(y, x), FONT_HERSHEY_SIMPLEX, char_size, Scalar(Red, Green, Blue), 2);
        }
    }

   
   //imshow("Processed Frame", newimg);
    return newimg;
}


int main() {

    VideoCapture video(path);

    //check opening img 
    if (!video.isOpened()) {
        cout << "Error" << endl;
        return -1;
    }

    // create new img

    Size textSize = getTextSize(string(1, AsciiChars[0]), FONT_HERSHEY_SIMPLEX, char_size, 2, nullptr);

    int char_height = textSize.height; // symbol`s height
    int char_width = textSize.width; // symbol`s width

    //change step for symbol include width and height
    int CharStepX = char_width * 0.6;
    int CharStepY = char_height * 0.6;
    //Get video size 
    int frame_width = static_cast<int>(video.get(CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(video.get(CAP_PROP_FRAME_HEIGHT));
    //Create new video for record changing frame 
    VideoWriter svideo(PathToSafeAsciiVideo, VideoWriter::fourcc('H', '2', '6', '4'), video.get(CAP_PROP_FPS), Size(frame_width, frame_height));//width - 718 heigth - 1280

    Mat frame,re;
    while (true) {
        
        video >> frame;
        if (frame.empty()) {
            break;
        }
       

        frame = ConverFrame(frame, frame_height, frame_width, CharStepX, CharStepY);
        svideo.write(frame); //recording video
        imshow("1",frame);
        waitKey(1);

    }
    video.release();
    svideo.release();
    destroyAllWindows();

    return 0;

}

