#include <fstream>
#include <ctime>

#include "UTILS.h"

int main() {
    double ptick = 0.01, ttick = 0.01, D = 1,
        w = 1.7, h = 1, iw = 2, ih = 1.3,
        xtick = 0.01, ytick = 0.01;

    size_t oks = 0, dots = 10000;

    std::ofstream output { "imoutput.bin", std::ios::binary };

    for(double y = 0; y < h; y += ytick) {
        for(double x = 0; x < w; x += xtick) {
            size_t sum = 0;
            double vecp[] = { x, y, D };
            for(double phi = 0; phi < twopi; phi += ptick) {
                double sp = sin(phi), cp = cos(phi);
                for(double theta = 0; theta < halfpi; theta += ttick) {
                    double tgth = tan(theta);
                    double vecd[] = { -cp * tgth, -sp * tgth, -1 };
                    double temvecp[] = { vecp[0], vecp[1], vecp[2] };
                    mulvec(vecd, D);
                    sumvecs(temvecp, vecd);
                    sum += temvecp[0] >= 0 && temvecp[0] <= w && temvecp[1] >= 0 && temvecp[1] <= h;
                }
            }
            writeFile(output, x, y, sum);
        }
        std::cerr << '#';
    }
    std::cerr << std::endl;
    output.close();

    return 0;
}
