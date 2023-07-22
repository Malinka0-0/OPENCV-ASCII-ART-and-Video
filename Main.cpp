#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

string path = "<your path>"; //path to img
bool SafeImgOrNot = true; // true - safe img | false - not safe img
string PathToSafeAsciiImg = "<your path>\\Output.png"; //path to safe img \\Output.png - name and format img
double char_size = 0.3; // char size (big size - low quality | small size -  high quality)

int main() {

    Mat img = imread(path, IMREAD_GRAYSCALE);
    //check opening img 
    if (img.empty()) {
        cout << "Error" << endl;
        return -1;
    }
    cout << "Size original " << img.size() << endl;
   

    // create new img
    Mat newimg(img.rows, img.cols, CV_8UC1, Scalar(0));
   
    string AsciiChars = " ./`,:;!~+-xmo*#W&8@";
    int ASCII_COEFF = 255 / (AsciiChars.length() - 1); //Діапазон значень 


    Size textSize = getTextSize(string(1, AsciiChars[0]), FONT_HERSHEY_SIMPLEX, char_size, 2, nullptr);

    int char_height = textSize.height; // symbol`s height
    int char_width = textSize.width; // symbol`s width

    //change step for symbol include width and height
    int CharStepX = char_width * 0.6;
    int CharStepY = char_height * 0.6;

    // create new img for 
    for (int x = 0; x < img.cols; x += CharStepX) {
        for (int y = 0; y < img.rows; y += CharStepY) {
    
            putText(newimg, string(1, AsciiChars[static_cast<int>(img.at<uchar>(y, x) / ASCII_COEFF)]), Point(x, y), FONT_HERSHEY_SIMPLEX, char_size, Scalar(img.at<uchar>(y, x)), 2);
        }
    }

    if (SafeImgOrNot) {
        imwrite(PathToSafeAsciiImg, newimg); 
    }
    imshow("Display Window", newimg);
    waitKey(0);
    return 0;
       
}
