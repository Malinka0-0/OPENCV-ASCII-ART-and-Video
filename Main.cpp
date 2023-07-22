#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

string Path = "C:\\Users\\Administrator\\Downloads\\videoplayback.mp4"; //path to img
bool SafeVideoOrNot = true; // true - safe img | false - not safe img
string PathToSafeAsciiVideo = "D:\\Project\\Programing\\ASCII\\Save\\Output.mp4"; //path to safe img \\Output.png - name and format
double Char_size = 0.5; // char size (big size - low quality | small size -  high quality)

string AsciiChars = " ./`,:;!~+-xmo*#W&8@";
int ASCII_COEFF = 255 / (AsciiChars.length() - 1);

Mat ConverFrame(Mat frame, int char_height, int char_width,int CharStepX, int CharStepY) {
    Mat newimg(frame.rows,frame.cols, CV_8UC1, Scalar(0));
    for (int x = 0; x < frame.cols; x += CharStepX) {
        for (int y = 0; y < frame.rows; y += CharStepY) {

            putText(newimg, string(1, AsciiChars[static_cast<int>(frame.at<uchar>(y, x) / ASCII_COEFF)]), Point(x, y), FONT_HERSHEY_SIMPLEX, Char_size, Scalar(frame.at<uchar>(y, x)), 2);
        }
    }
    return newimg;
}
int main() {
    // Opem video file 
    VideoCapture video(Path);

    // Перевірка, чи вдалося відкрити відеофайл
    if (!video.isOpened()) {
        cout << "Error" << endl;
        return -1;
    }
    
    Size textSize = getTextSize(string(1, AsciiChars[0]), FONT_HERSHEY_SIMPLEX, Char_size, 2, nullptr);

    int char_height = textSize.height; // symbol`s height
    int char_width = textSize.width; // symbol`s width

    //change step for symbol include width and height
    int CharStepX = char_width * 0.6;
    int CharStepY = char_height * 0.6;

    int frame_width = static_cast<int>(video.get(CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(video.get(CAP_PROP_FRAME_HEIGHT));
    VideoWriter svideo(PathToSafeAsciiVideo, VideoWriter::fourcc('H', '2', '6', '4'), video.get(CAP_PROP_FPS), Size(frame_width, frame_height));

    Mat frame;
    while (true) {
        video >> frame;
        if (frame.empty()) {
            break;
        }
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        frame = ConverFrame(frame, char_height, char_width, CharStepX, CharStepY);
        svideo.write(frame);
       
        
        //imshow("Processed Frame", frame );
        waitKey(0);

    }

    
    video.release();
    svideo.release();
    destroyAllWindows();

    return 0;
}
