#include <fstream>
#include <ctime>

#include "UTILS.h"

int main() {
    double ptick = 0.01, ttick = 0.01,
        w = 1.7, h = 1, mar = 0.1, D = 0.9;
    double iw = w + mar, ih = h + mar;

    size_t counter = 0;
    size_t oks = 0, dots = 5000;

    std::ofstream output { "genoutput.bin", std::ios::binary };

    srand((unsigned)time(0));

    for(double phi = 0; phi < twopi; phi += ptick) {
        for(double theta = 0; theta < halfpi; theta += ttick) {
            oks = 0;
			double tgth = tan(theta);
			double vecd[] = { -cos(phi) * tgth, -sin(phi) * tgth, -1 };
			mulvec(vecd, D);
			for(size_t i = 0; i < dots; ++i) {
				double vecp[] = { doublerand(-mar, iw), doublerand(-mar, ih), D };
                sumvecs(vecp, vecd);
                if(vecp[0] >= 0 && vecp[0] <= w && vecp[1] >= 0 && vecp[1] <= h) ++oks;
			}
            writeFile(output, phi, cos(theta), (double)oks / dots);
        }
        ++counter;
        if(counter % 6 == 0) {
            std::cerr << '#';
            counter = 0;
        }
    }

    return 0;
}
