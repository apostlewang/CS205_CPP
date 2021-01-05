/*
 * @Date: 2020-11-30 10:30:04
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2021-01-05 20:07:58
 */
#include<opencv2/opencv.hpp>

#include<cmath>
#include <chrono>
#include"cnn.hpp"
#include <iomanip>
#include"include/face_binary_cls.hpp"
using namespace std;
using namespace cv;
#define TIME_START start=std::chrono::steady_clock::now();
#define TIME_END(NAME) end=std::chrono::steady_clock::now(); \
             duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();\
             cout<<(NAME)<<": duration = "<<duration<<"ms"; \

void judge(string filename);

int main(){
    judge("bg.jpg");
    judge("face.jpg");
    for (int i = 0; i < 10; i++)
    {
        string index = "0"+to_string(i);
        string filename = index+".jpg";
        judge(filename);
    }
    return 0;
}

void judge(string filename){
    //Parameters
    Conv conv0 = Conv(conv_params[0]);
    Conv conv1 = Conv(conv_params[1]);
    Conv conv2 = Conv(conv_params[2]);
    fc_param fc = fc_params[0];
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto duration = 0L;
    //cout << "The input image: " << filename << endl;
    TIME_START 
/***************IO and preprocessing*********************/
    Mat image = imread("./samples/"+filename);
    Mat3f image_f(image); 
    image_f = image_f/255;
    float *conv0_in = new float[3*128*128];
    for (size_t i = 0; i < 128; i++)
    {
        for (size_t j = 0; j < 128; j++)
        {   
            //red
            conv0_in[0*128*128+128*i+j] = image_f(i,j)[0];
            //green
            conv0_in[1*128*128+128*i+j] = image_f(i,j)[1];
            //blue
            conv0_in[2*128*128+128*i+j] = image_f(i,j)[2];
        }     
    }
    Image_data in0(3,128,128,conv0_in);
/***************CONV0*********************/
    const Image_data &out0 = conv0.get_output(in0);
    const Image_data &out0_pool = maxPool2x2(out0);
/***************CONV1*********************/
    const Image_data &out1 = conv1.get_output(out0_pool);
    const Image_data &out1_pool = maxPool2x2(out1);
/***************CONV2*********************/
    const Image_data &out2 = conv2.get_output(out1_pool);
/***************FC*********************/
    int out_features = fc.out_features;
    int in_features = fc.in_features;
    float fc_out[out_features];
    float* conv2_out = out2.flatten();

    for (int o = 0; o < 2; o++) {
        float sum = 0;
        for (int i = 0; i < 2048; i++) {
            float w_oi = fc.p_weight[o*2048+i];
            sum += w_oi*conv2_out[i];
        }
        float bias = fc.p_bias[o];
        sum += bias;
        fc_out[o] = sum;
    }
/***************SOFTMAX*********************/
    float e1 = exp(fc_out[0]);
    float e2 = exp(fc_out[1]);
    TIME_END(filename)
    cout <<  setiosflags(ios::fixed) << setprecision(6) << ", face score: "<< e2/(e1+e2) << endl;
}
