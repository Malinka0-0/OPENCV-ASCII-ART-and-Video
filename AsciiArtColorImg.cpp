#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>é
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

string path = "<your path>"; //path to img
bool SafeImgOrNot = true; // true - safe img | false - not safe img
string PathToSafeAsciiImg = "<your path>\\Output.png"; //path to safe img \\Output.png - name and format img
double char_size = 0.3; // char size (big size - low quality | small size -  high quality)


int main() {

    Mat img = imread(path);

    //check opening img 
    if (img.empty()) {
        cout << "Error" << endl;
        return -1;
    }
    cout << "Size original " << img.size() << endl;


    imshow("1", img);

    // create new img
    Mat newimg(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));

    string AsciiChars = " ./`,:;!~+-xmo*#W&8@";
    int ASCII_COEFF = 255 / (AsciiChars.length() - 1);


    Size textSize = getTextSize(string(1, AsciiChars[0]), FONT_HERSHEY_SIMPLEX, char_size, 2, nullptr);

    int char_height = textSize.height; // symbol`s height
    int char_width = textSize.width; // symbol`s width

    //change step for symbol include width and height
    int CharStepX = char_width * 0.6;
    int CharStepY = char_height * 0.6;

    // create new img for 

    for (int y = 0; y < img.cols; y += CharStepX) {
        for (int x = 0; x < img.rows; x += CharStepY) {
            int Red = img.at<Vec3b>(x, y)[0];
            int Blue = img.at<Vec3b>(x, y)[2];
            int Green = img.at<Vec3b>(x, y)[1];
            char ascii_character = AsciiChars[static_cast<int>(Red / ASCII_COEFF)];

            putText(newimg, string(1, ascii_character), Point(y, x), FONT_HERSHEY_SIMPLEX, char_size, Scalar(Red, Green, Blue), 2);
        }
    }



    // flip(newimg, newimg, 0);
    //Mat flipimg;
    //Point2f pc(img.cols / 2, newimg.rows / 2);
    //warpAffine(newimg, flipimg, getRotationMatrix2D(pc, -90, 1.0), img.size());

    if (SafeImgOrNot) {
        imwrite(PathToSafeAsciiImg, newimg);
    }

    imshow("Display Window", newimg);
    waitKey(0);
    return 0;

}

