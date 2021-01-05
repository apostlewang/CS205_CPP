/*
 * @Date: 2020-12-26 18:48:31
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2021-01-05 20:28:45
 */
#include "include/cnn.hpp"
#include<opencv2/opencv.hpp>
#include <fstream>
#include <cassert>
#include <omp.h>
using namespace cv;
using namespace std;
Image_data::Image_data(int num_channels, int num_r, int num_c, float* data){
    this->num_channels = num_channels;
    this->num_r = num_r;
    this->num_c = num_c;
    this->data = data;
}
Image_data::~Image_data(){
     delete[] data;
}

float* Image_data::flatten() const{
    return data;
}

float Image_data::operator() (int channel, int r, int c)const{
    if(r < 0 || r > num_r-1 || c < 0 || c > num_c-1){
        return 0;
    }  
    else
    {
        int idx = channel*num_c*num_r + r*num_c + c;
        return data[idx];
    }   
}

Conv::Conv(conv_param param){
    pad = param.pad;
    stride = param.stride;
    kernel_size = param.kernel_size;
    in_channels = param.in_channels;
    out_channels = param.out_channels;
    p_weight = param.p_weight;
    p_bias = param.p_bias;
    
}

Image_data Conv::get_output(const Image_data &in){ 
    int in_size_r = in.num_r;
    int in_size_c = in.num_c;
    int out_size_r = (in_size_r+pad*2-kernel_size)/stride+1;
    int out_size_c = (in_size_c+pad*2-kernel_size)/stride+1;
    float *out_data = new float[out_channels*out_size_r*out_size_c];
    #pragma omp parallel for
    for (int o = 0; o < out_channels; o++){ 
        float bias = p_bias[o];
        float kernels[in_channels*kernel_size*kernel_size];
        for (int i = 0; i < in_channels; i++){
            for (int k = 0; k < kernel_size*kernel_size; k++){  
                int idx = o*kernel_size*kernel_size*in_channels + i*kernel_size*kernel_size + k;
                kernels[i*kernel_size*kernel_size+k] = p_weight[idx];
            }   
        }
        for (int r = 0; r < out_size_r; r++){
            for (int c = 0; c < out_size_c; c++){
                float sum = bias;         
                int init_r = r*stride-pad;
                int init_c = c*stride-pad;
                for (int i = 0; i < in_channels; i++){
                    for (int k1 = 0; k1 < kernel_size; k1++){
                        for (int k2 = 0; k2 < kernel_size; k2++){
                            sum += in(i,init_r+k1,init_c+k2)*kernels[i*kernel_size*kernel_size+k1*kernel_size+k2];    
                        }
                    }
                }
                //relu
                if(sum < 0)
                    sum = 0;
                out_data[o*out_size_c*out_size_r+r*out_size_c+c] = sum;
            }    
        }   
    }
    Image_data out = Image_data(out_channels, out_size_r, out_size_c, out_data);
    return out;
}

Image_data Conv::get_output_faster(const Image_data &in){ 
    int in_size_r = in.num_r;
    int in_size_c = in.num_c;
    int out_size_r = (in_size_r+pad*2-kernel_size)/stride+1;
    int out_size_c = (in_size_c+pad*2-kernel_size)/stride+1;
    float *out_data = new float[out_channels*out_size_r*out_size_c];
    #pragma omp parallel for
    for (int o = 0; o < out_channels; o++){ 
        float bias = p_bias[o];
        float kernels[in_channels*kernel_size*kernel_size];
        for (int i = 0; i < in_channels; i++){
            for (int k = 0; k < kernel_size*kernel_size; k++){  
                int idx = o*kernel_size*kernel_size*in_channels + i*kernel_size*kernel_size + k;
                kernels[i*kernel_size*kernel_size+k] = p_weight[idx];
            }   
        }
        for (int r = 0; r < out_size_r; r++){
            for (int c = 0; c < out_size_c; c++){
                float sum = bias;         
                int init_r = r*stride-pad;
                int init_c = c*stride-pad;
                for (int i = 0; i < in_channels; i++){
                    for (int k1 = 0; k1 < kernel_size; k1++){
                        for (int k2 = 0; k2 < kernel_size; k2++){
                            sum += in(i,init_r+k1,init_c+k2)*kernels[i*kernel_size*kernel_size+k1*kernel_size+k2];    
                        }
                    }
                }
                //relu
                if(sum < 0)
                    sum = 0;
                out_data[o*out_size_c*out_size_r+r*out_size_c+c] = sum;
            }    
        }   
    }
    Image_data out = Image_data(out_channels, out_size_r, out_size_c, out_data);
    return out;
}

Image_data maxPool2x2(const Image_data &in){
    int num_channels = in.num_channels;
    int in_size_c = in.num_c;
    int in_size_r = in.num_r;
    int out_size_r = in.num_r/2;
    int out_size_c = in.num_c/2;
    float * out_data = new float[out_size_c*out_size_r*num_channels];
    for (size_t i = 0; i < num_channels; i++){
        for (size_t r = 0; r < out_size_r; r++){
            for (size_t c = 0; c < out_size_c; c++){
                float e00 = in(i,2*r,2*c);
                float max = e00;
                float e01 = in(i,2*r,2*c+1);
                if(e01 > max){
                    max = e01;
                }
                float e10 = in(i,2*r+1,2*c);
                if(e10 > max){
                    max = e10;
                }
                float e11 = in(i,2*r+1,2*c+1);
                if(e11 > max){
                    max = e11;
                }
                out_data[r*out_size_c+c+i*out_size_c*out_size_r] = max;
            }
        }
    }
    Image_data out = Image_data(num_channels, out_size_r, out_size_c, out_data);
    return out;
}
