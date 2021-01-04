/*
 * @Date: 2020-12-26 18:48:31
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-28 15:29:49
 */
#include "cnn.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <cassert>
using namespace cv;
using namespace std;
Image_data::Image_data(int num_channels, int num_r, int num_c, float* data){
    this->num_channels = num_channels;
    this->num_r = num_r;
    this->num_c = num_c;
    this->data = data;
}
Image_data::~Image_data(){
    //delete []data;
}
void Image_data::save_info(string name) const{
    ofstream outfile(name+".txt", ios::trunc);

    outfile << "The number of channels are: " << num_channels << endl;
    outfile << "The number of rows in each channel: " << num_r << endl; 
    outfile << "The number of columns in each channel: " << num_c << endl;
    for (size_t i = 0; i < num_channels; i++)
    {
        outfile << "The data of channel " << i << ":" << endl;
        for (size_t r = 0; r < num_r; r++)
        {
            outfile << "row" << r << ":" << endl;
            for (size_t c = 0; c < num_c; c++)
            {
                outfile << data[i*num_c*num_r+r*num_c+c]<< ",";
            }
            outfile << endl;         
        }
    }
    outfile.close();
    
}
float* Image_data::flatten(){
    return data;
}
void Image_data::show_channels(int channel) const{
    assert(channel >= 0 && channel < num_channels);
    float one_channel[num_r*num_c];
    for (int i = 0; i < num_r*num_c; i++)
    {
        one_channel[i] = data[channel*num_c*num_r + i];
        //cout << one_channel[i]<< endl;
    }
    Mat single = Mat(num_c,num_r,CV_32FC1,one_channel);
    imshow("single", single);
    waitKey(0);
}
float Image_data::operator() (int channel, int r, int c)const{
    if(r < 0 || r > num_r-1 || c < 0 || c > num_c-1){
        //cout << "r= "<< r <<"c= "<< c <<"pad" << endl;
        return 0;
    }  
    else
    {
        int idx = channel*num_c*num_r + r*num_c + c;
        //int idx = channel+(r*num_c+c)*num_channels;
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

void Conv::save_info(string name) const{
    ofstream outfile(name+".txt", ios::trunc);
    outfile << "pad: " << pad << endl;
    outfile << "stride: " << stride << endl; 
    outfile << "in_channels: " << in_channels << endl;
    outfile << "out_channels: " << out_channels << endl;
    for (size_t o = 0; o < out_channels; o++)
    {
        for (size_t i = 0; i < in_channels; i++)
        {
            outfile << "kernel for o" << o << "i" << i <<":" << endl;
            for (int k1 = 0; k1 < kernel_size; k1++){
                for (int k2 = 0; k2 < kernel_size; k2++){
                    int idx = o*kernel_size*kernel_size*in_channels + i*kernel_size*kernel_size + k1*kernel_size+k2;         
                    outfile << p_weight[idx] << ", ";
                }
                outfile << endl;
            }
        }
    }

    outfile.close();
}
Image_data Conv::get_output(Image_data in, string save_file_name){
    ofstream outfile(save_file_name, ios::trunc);
    int in_size_r = in.num_r;
    int in_size_c = in.num_c;
    int out_size_r = (in_size_r+pad*2-kernel_size)/stride+1;
    int out_size_c = (in_size_c+pad*2-kernel_size)/stride+1;
    //cout << out_size_c << endl;
    float *out_data = new float[out_channels*out_size_r*out_size_c];

    for (int o = 0; o < out_channels; o++){ 
        float bias = p_bias[o];
        float kernels[in_channels*kernel_size*kernel_size];
        for (int i = 0; i < in_channels; i++){
            outfile << "out_channel: " << o << endl;
            outfile << "in_channel: " << i << endl;   
            for (int k = 0; k < kernel_size*kernel_size; k++){  
                //int idx = i*kernel_size*kernel_size*out_channels + o*kernel_size*kernel_size + k;
                int idx = o*kernel_size*kernel_size*in_channels + i*kernel_size*kernel_size + k;
                kernels[i*kernel_size*kernel_size+k] = p_weight[idx];
            }
            outfile << "the kernel: " << endl;
            for (int k1 = 0; k1 < kernel_size; k1++){
                for (int k2 = 0; k2 < kernel_size; k2++){
                    int idx = o*kernel_size*kernel_size*in_channels + i*kernel_size*kernel_size + k1*kernel_size+k2;         
                    outfile << p_weight[idx] << ", ";
                }
                outfile << endl;
            }     
        }
        for (int r = 0; r < out_size_r; r++){
            for (int c = 0; c < out_size_c; c++){
                float sum = bias;
                outfile << "r" << r << "c" << c << endl;           
                int init_r = r*stride-pad;
                int init_c = c*stride-pad;
                for (int i = 0; i < in_channels; i++){
                    for (int k1 = 0; k1 < kernel_size; k1++){
                        for (int k2 = 0; k2 < kernel_size; k2++){
                            if(!(i==0&&k1==0&&k2==0))
                                outfile << "+";
                            outfile << in(i,init_r+k1,init_c+k2) << "*" << kernels[i*kernel_size*kernel_size+k1*kernel_size+k2];
                            sum += in(i,init_r+k1,init_c+k2)*kernels[i*kernel_size*kernel_size+k1*kernel_size+k2];    
                        }
                        outfile << endl;
                        
                    }
                }
                outfile << "+" << bias << "=" << sum << endl;
                outfile << endl;
                if(sum < 0)
                    sum = 0;
                out_data[o*out_size_c*out_size_r+r*out_size_c+c] = sum;
            }    
        }
        
        
    }
    Image_data out = Image_data(out_channels, out_size_r, out_size_c, out_data);
    return out;
}

Image_data maxPool2x2(Image_data in){
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
