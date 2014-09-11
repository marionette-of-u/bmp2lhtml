#include <iostream>
#include <fstream>
#include <algorithm>
#include "tty_legacy_bmp.hpp"

std::string int2hex_str(int a){
    std::string r;
    for(int i = 0; i < 2; a /= 16, ++i){
        int x = a % 16;
        if(x < 10){
            r.push_back('0' + x);
        }else{
            r.push_back('A' + (x - 10));
        }
    }
    std::reverse(r.begin(), r.end());
    return r;
}

int main(int argc, char *argv[]){
    if(argc != 3 && argc != 4){
        std::cout << "usage: bmp2lhtml result.txt src.bmp [c]" << std::endl;
        return 0;
    }

    const char *c = "#";
    if(argc == 4){
        c = argv[3];
    }

    try{
        std::ofstream ofile(argv[1]);
        if(ofile.fail()){
            throw;
        }

        tt_legacy::bmp bmp(argv[2]);

        for(int i = 0; i < bmp.height(); ++i){
            for(int j = 0; j < bmp.width(); ++j){
                tt_legacy::bmp::dot x = bmp.clr(j, i);
                std::string r = int2hex_str(x.r), g = int2hex_str(x.g), b = int2hex_str(x.b);
                if(r[0] == r[1] && g[0] == g[1] && b[0] == b[1]){
                    ofile << "<font color=\"#" << r[0] << g[0] << b[0] << "\">" << c << "</font>";
                }else{
                    ofile << "<font color=\"#" << r << g << b << "\">" << c << "</font>";
                }
            }
            if(i != bmp.height() - 1){
                ofile << "<br>";
            }
        }
    }catch(...){
        std::cerr << "error...\n";
        return -1;
    }

    return 0;
}
