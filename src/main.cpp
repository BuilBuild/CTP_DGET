/*
 * @Author: LeiJiulong
 * @Date: 2024-12-22 16:04:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-22 18:20:59
 * @Description: 
 */

#include <iostream>
#include <string>
#include "CTPmd.h"

int bufsize = 0;
char **ppInstrumentID  = nullptr;
int iInstrumentID = 0;

int main()
{
    CTPDataGet();
    std::cout << "src" << std::endl;
    return 0;
}

