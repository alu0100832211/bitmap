#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>

using namespace cv;
int main(int argc, char** argv )
{
  if ( argc != 2 )
  {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }
  Mat image;
  image = imread( argv[1], 0 );
  if ( !image.data )
  {
    printf("No image data \n");
    return -1;
  }
  int rows = image.rows;
  int cols = image.cols;

  std::fstream ofs;
  ofs.open("sans.c", std::ofstream::out | std::ofstream::trunc );
  if(!ofs.is_open()){
    exit(EXIT_FAILURE);
  }
  ofs << "const uint8_t sans ["<< rows*cols/8 <<"] PROGMEM = {";
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int bitPos = 7;
      int bitMap = 0;
      while(bitPos >= 0){
        if(image.at<uchar>(j,i)>100)
          bitMap |= (1 << bitPos);
        bitPos--; j++;
      }
      ofs << "0x" << std::setfill('0') << std::setw(2) << std::hex << bitMap << ", ";
      //ofs << "0x" << static_cast<unsigned>(bitMap) << ", ";
      //ofs << std::hex << bitMap;
    }
    ofs << "\n";
  }
  ofs.seekp(ofs.tellp()-2);
  ofs << "};\n";
  namedWindow("Display Image", WINDOW_AUTOSIZE );
  imshow("Display Image", image);
  waitKey(0);
  return 0;
}
