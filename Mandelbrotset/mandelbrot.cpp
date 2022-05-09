#include "color.h"
#include <iostream>
#include "complex_number.h"
#include <png++/png.hpp>
#include <cmath>
#include <string>
#include <iomanip>

int MAXITS = 2000;

using std::cin, std::stod, std::endl, std::cout, png::image, png::rgb_pixel;

struct boarders{
    double R;
    double I;
};

png::image< png::rgb_pixel > whiteimg(png::image< png::rgb_pixel > &result){
    for(png::uint_32 y = 0; y < result.get_height(); ++y)
    {
        for(png::uint_32 x = 0; x < result.get_width(); ++x)
        {
            result[y][x] = png::rgb_pixel(255, 255, 255);
        }
    }
    return result;
}

int steps(const complex_number c){
    complex_number z(0);
    int count = 0;
    while((z.rez()*z.rez() + z.imz()*z.imz() < 4) && (count < MAXITS)){
        z = z*z + c;
        count++;
    }
    return count;
}

int main(int argc, char **argv){
    int h = std::stoi(argv[1]), w = std::stoi(argv[2]);
    boarders low, mid, up;

    mid.R = stod(argv[4]);
    mid.I = stod(argv[5]);
    double diff = stod(argv[6]);

    image< rgb_pixel > result(w, h);
    std::string keypressed = "n";

    std::string filename = argv[3];
    cout << h << "x" << w << endl << filename << endl;
    

    while(keypressed != "q"){
        cout << std::setprecision(25) << complex_number(low.R, low.I) << endl 
             << complex_number(up.R, up.I) << endl; 
        cout << "mid: " << complex_number(mid.R, mid.I) << endl << "diff: " << diff << endl << "-------" << endl;
        
        if(keypressed.find("+") != std::string::npos){
            diff *= 0.6;
        }
        if(keypressed.find("-") != std::string::npos){
            diff *= 1.4;
        }
        if(keypressed.find("w") != std::string::npos){
            mid.I -= 0.2 * diff/2;
        }
        
        if(keypressed.find("s") != std::string::npos){
            mid.I += 0.2 * diff/2;
        }
        if(keypressed.find("a") != std::string::npos){
            mid.R -= 0.2 * diff/2;
        }
        if(keypressed.find("d") != std::string::npos){
            mid.R += 0.2 * diff/2;
        }
        low.R = mid.R - diff/2;
        low.I = mid.I - diff/2;
        up.R = mid.R + diff/2;
        up.I = mid.I + diff/2;

        double stwh = ((up.I - low.I)/h);    
        double stww = ((up.R - low.R)/w);    

        int count = 0;

#pragma omp parallel for
        for(png::uint_32 y = 0; y < result.get_height(); ++y){
            for(png::uint_32 x = 0; x < result.get_width(); ++x){

                count = steps(complex_number(low.R + x*stww, low.I + y*stwh));

                if(count < MAXITS){result.set_pixel(x, y, (color_map(count%MAXITS, MAXITS)));}
                if(count >= MAXITS) result.set_pixel(x, y, rgb_pixel(0,0,0)); 
            }
        }
        result.write(filename);
        cout << ">>> ";
        cin >> keypressed;
    }

    return 0;
}
