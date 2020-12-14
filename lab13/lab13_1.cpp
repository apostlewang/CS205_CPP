/*
 * @Date: 2020-12-07 17:03:48
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-07 17:15:36
 */

/****************************************************
*
* FileName: maxTemplate.cpp
* Purpose: Demonstrate the use of function templates
*
********************************************************/
#include <iostream>
#include <string>
using namespace std;
//Make a template out of the prototype
template<typename T>
T Max(T one, T two);
int main()
{
    int i_one = 3, i_two = 5;
    cout << "The max of " << i_one << " and " << i_two << " is "
    << Max(i_one, i_two) << endl;
    float i_one_f = 3.2f, i_two_f = 5.1f;
    cout << "The max of " << i_one_f << " and " << i_two_f << " is "
    << Max(i_one_f, i_two_f) << endl;
    string i_one_s = "aa", i_two_s = "bb";
    cout << "The max of " << i_one_s << " and " << i_two_s << " is "
    << Max(i_one_s, i_two_s) << endl;
    //Test your template on float and string types
    return 0;
}
//Make a template out of this function. Don't forget the return type.
template<typename T>
T Max(T one, T two)
{
    T biggest;
    if (one < two)
    {
    biggest = two;
    }
    else
    {
    biggest = one;
    }
    return biggest;
}