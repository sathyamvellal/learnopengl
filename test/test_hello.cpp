//
// Created by Sathyam Vellal on 06/11/2017.
//

#include <iostream>

#include "hello.h"
#include "utils/logger.h"

int main(int argc, char *argv[])
{
    hello();
    log<LOG_DEBUG>(L"Foo bar %1%") % 5;

    return 0;
}