#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

class ImageData {
public:
    int width;
    int height;
    vector<int> data;

    ImageData(int width_, int height_, vector<int> data_) {
        width = width_;
        height = height_;
        data = move(data_);
    }
};

ImageData LoadImage(const string &imgPath) {
    Mat img = imread(imgPath);
    int width = img.cols;
    int height = img.rows;
    vector<int> data;
    cout << imgPath << " >> " << width << " x " << height << endl;

    MatIterator_<Vec3i> iter, end;
    for (iter = img.begin<Vec3i>(), end = img.end<Vec3i>(); iter != end; ++iter) {
        auto rgb = *iter;
        data.push_back(rgb[0]);
        data.push_back(rgb[1]);
        data.push_back(rgb[2]);
        data.push_back(255);
    }
    return ImageData(width, height, data);
}

void SaveImage(const string &imgPath, ImageData img) {
    const int width = img.width;
    const int height = img.height;
    vector<int> data = img.data;
    Mat newImg = Mat(height, width, CV_8UC3);

    MatIterator_<Vec3i> iter, end;
    int index = 0;
    for (iter = newImg.begin<Vec3i>(), end = newImg.end<Vec3i>(); iter != end; ++iter) {
        auto &rgb = *iter;
        rgb[0] = data[index++];
        rgb[1] = data[index++];
        rgb[2] = data[index++];
        index += 1;
    }

    vector<int> params;
    params.push_back(1);
    params.push_back(100);

    imwrite(imgPath, newImg, params);
}

int main(int argc, char **argv) {
    ImageData iptImg = LoadImage(argv[1]);
    SaveImage("out.jpg", iptImg);
    return 0;
}