#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HPVTUtility.h"
#include "HPVTControl.h"
void *sample_main(void *arg) {
    char filename[64];
    struct timeval tv_now;
    struct tm *time_st;
    timerclear(&tv_now);
    while (1) {
        sleep(5);
        gettimeofday(&tv_now, NULL);
        cv::Mat img;
        time_st = localtime(&tv_now.tv_sec);
        if (HPVTCreateCVImageFromVideo(320, 180, &img) < 0) {
            printf("Error!");
            continue;
        }
        sprintf(filename, "%02d%02d%02d.jpg", time_st->tm_hour, time_st->tm_min, time_st->tm_sec);
        std::vector<int> params(2);
        params[0] = CV_IMWRITE_JPEG_QUALITY;
        params[1] = 90;
        cv::imwrite(filename, img, params);
        img.release();
    }
    return NULL;
}
void HPVTLoadPlugin(void) {
    HPVTInitialize();
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, sample_main, NULL);
}
void HPVTUnloadPlugin(void) {
    HPVTDestroy();
}
