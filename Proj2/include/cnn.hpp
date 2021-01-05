/*
 * @Date: 2020-12-26 18:48:02
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2021-01-05 17:11:44
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
        float* flatten() const;
        friend class Conv;
        friend Image_data maxPool2x2(const Image_data &in);
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
    public:
        Conv(conv_param param);
        Image_data get_output(const Image_data &in);
        Image_data get_output_faster(const Image_data &in);
};

