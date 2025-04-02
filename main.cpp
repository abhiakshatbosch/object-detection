#include "nanodetlib.h"

int main() {
    bool useGPU = false;
    char* path_video = "/home/csb3kor/workspace/OD-Nanodet/sample/demo-tiny.mp4";
    char* path_model_param = "/home/csb3kor/workspace/OD-Nanodet/model/nanodet.param";
    char* path_model_bin = "/home/csb3kor/workspace/OD-Nanodet/model/nanodet.bin";
    NanoDet detector = NanoDet(path_model_param, path_model_bin, useGPU);
    cv::Mat image;
    cv::VideoCapture cap(path_video); 

    if( !cap.isOpened() ) {
        fprintf(stderr, "Could Not Read Video.\n");
        return 0;
    }

    int height = detector.input_size[0];
    int width = detector.input_size[1];

    while (true) {
        cap >> image;
        object_rect effect_roi;
        cv::Mat resized_img;
        resize_uniform(image, resized_img, cv::Size(width, height), effect_roi);
        auto results = detector.detect(resized_img, 0.4, 0.5);
        cv::Mat result_frame = draw_bboxes(image, results, effect_roi);
        cv::imshow("dst", result_frame);
        cv::waitKey(1);
    }
    return 0;
}