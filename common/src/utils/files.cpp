//
// Created by Sathyam Vellal on 10/03/2018.
//

#include <string>
#include <fstream>
#include <sstream>

#include "utils/logger.h"

#include "utils/files.h"

void extract(std::string& contents, const std::string& filename)
{
    log<LOG_VERBOSE>("Opening file %1% ...") % filename.c_str();
    std::ifstream fileInput;
    fileInput.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fileInput.open(filename);
    log<LOG_VERBOSE>("Reading file to buffer ...");
    std::stringstream buffer;
    buffer << fileInput.rdbuf();
    log<LOG_VERBOSE>("Writing buffer to string ...");
    contents = buffer.str();
    log<LOG_VERBOSE>("Closing file %1% ...") % filename.c_str();
    fileInput.close();
}