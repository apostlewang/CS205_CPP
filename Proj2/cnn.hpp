/*
 * @Date: 2020-12-26 18:48:02
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-28 14:40:11
 */
#include <string>
using namespace std;
typedef struct conv_param {
    int pad;
    int stride;
    int kernel_size;
    int in_channels;
    int out_channels;
    float* p_weight;
    float* p_bias;
} conv_param;

typedef struct fc_param {
    int in_features;
    int out_features;
    float* p_weight;
    float* p_bias;
} fc_param;

class Image_data{
    private:
        int num_channels;
        int num_r;
        int num_c;
        float* data;
    public:
        Image_data(int num_channels, int num_r, int num_c, float* data);
        ~Image_data();
        float operator() (int channel, int r, int c) const;
        void show_channels(int channel) const;    
        void save_info(string name) const;
        float* flatten();
        friend class Conv;
        friend Image_data maxPool2x2(Image_data in);

};

class Conv{
    private:
        int pad;
        int stride;
        int kernel_size;
        int in_channels;
        int out_channels;
        float* p_weight;
        float* p_bias;
        //Image_data in;

    public:
        Conv(conv_param param);
        Image_data get_output(Image_data in, string save_file_name = "temp.txt");
        float operator() (int in_channel, int out_channel, int r, int c) const;
        void save_info(string name) const;
};

