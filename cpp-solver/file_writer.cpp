/* 
 * File:   file_writer.cpp
 * Author: Lasse Lybeck
 * 
 * Created on October 24, 2014, 3:50 PM
 */

#include <fstream>
#include "file_writer.h"

namespace dlx {

    file_writer::file_writer(std::string const& filename) : file_() {
        file_.open(filename);
    }

    file_writer::~file_writer() {
        file_.close();
    }

    void file_writer::println(const std::string& str) {
        file_ << str << std::endl;
    }
    
    void file_writer::println(int const& i) {
        file_ << i << std::endl;
    }
}
