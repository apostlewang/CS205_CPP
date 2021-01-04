/*
 * @Date: 2020-11-30 10:30:04
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2021-01-04 13:37:26
 */
#include<opencv2/opencv.hpp>
#include<cmath>
#include"cnn.hpp"
#include"face_binary_cls.hpp"
using namespace std;
using namespace cv;

int main(){
    //128*128*3
    string filename = "bg/00.jpg";
    cout << "The input image: " << filename << endl;
    Mat image = imread("./samples/"+filename);
    Mat3f image_f(image); 
    //bgr data
    image_f = image_f/255;
    float *conv0_in = new float[128*128*3];
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
    Image_data in0 = Image_data(3,128,128,conv0_in);

    in0.save_info(filename+"in0");
    Conv conv0 = Conv(conv_params[0]);
    conv0.save_info("conv0");
    Image_data out0 = conv0.get_output(in0,"1.txt");
    out0.save_info(filename+"out0");
    
    Image_data out0_pool = maxPool2x2(out0);
    out0_pool.save_info(filename+"out0_pool");
    Conv conv1 = Conv(conv_params[1]);
    conv1.save_info("conv1");
    Image_data out1 = conv1.get_output(out0_pool);
    out1.save_info(filename+"out1");
    Image_data out1_pool = maxPool2x2(out1);
    out1_pool.save_info(filename+"out1_pool");
    Conv conv2 = Conv(conv_params[2]);
    conv2.save_info("conv2");
    Image_data out2 = conv2.get_output(out1_pool);
    out2.save_info(filename+"out2");
    // for (size_t i = 0; i < 32; i++)
    // {
    //     out2.show_channels(i);
    // }
    fc_param fc = fc_params[0];
    int out_features = fc.out_features;
    int in_features = fc.in_features;
    float fc_out[out_features];
    float* conv2_out = out2.flatten();

    for (int o = 0; o < 2; o++) {
        float sum = 0;
        for (int i = 0; i < 2048; i++) {
            float w_oi = fc0_weight[o*2048+i];
            //float w_oi = fc0_weight[i*out_features+o];
            sum += w_oi*conv2_out[i];
        }
        float bias = fc0_bias[o];
        sum += bias;
        fc_out[o] = sum;
    }

    float e1 = exp(fc_out[0]);
    float e2 = exp(fc_out[1]);
    cout << "The confidence for face: "<< e2/(e1+e2) << endl;
    cout << "The confidence for backgroud: "<< e1/(e1+e2) << endl;
    return 0;

}
