/* 
 * File:   file_writer.h
 * Author: Lasse Lybeck
 *
 * Created on October 24, 2014, 3:50 PM
 */

#ifndef FILE_WRITER_H
#define	FILE_WRITER_H

#include <fstream>

namespace dlx {

    class file_writer {
    public:
        file_writer(std::string const&);
        file_writer(const file_writer& orig) = delete;
        virtual ~file_writer();
        void println(std::string const&);
        void println(int const&);
    private:
        std::ofstream file_;
    };

}

#endif	/* FILE_WRITER_H */

