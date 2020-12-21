/*
 * @Date: 2020-12-20 21:15:14
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-21 22:09:39
 */
#include <iostream>
#include "tv.h"

int main()
{
    using std::cout;
    using std::endl;
    Tv s42;
    cout << "Initial settings for 42\" TV:\n";
    cout << "TV is off" << endl;
    s42.chanup();
    Remote grey;
    grey.display_state();
    s42.toggle_remote(grey);

    s42.onoff();
    cout << "\nAdjusted settings for 42\" TV:\n";
    s42.settings();
    s42.toggle_remote(grey);
    cout << "\nAfter toggling the Remote state:\n";
    grey.display_state();


    
    // grey.volup(s42);
    // grey.volup(s42);
    // cout << "\n42\" settings after using remote:\n";
    // s42.settings();

    
    return 0;
}
