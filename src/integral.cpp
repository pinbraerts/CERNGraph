#include <fstream>
#include <ctime>

#include "UTILS.h"

int main() {
    double ptick = 0.01, ttick = 0.01, dtick = 0.1, sum = 0,
        w = 1.7, h = 1, mar = 0.1;
    double iw = w + mar, ih = h + mar;

    size_t counter = 0;
    size_t oks = 0, dots = 1000;

    std::ofstream output { "output.bin", std::ios::binary };

    srand((unsigned)time(0));

    for(double d = 0; d < 1; d += dtick) {
        double D = 3 * d + 0.3;
        std::cerr << "d: " << d << ' ';
        sum = 0;
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
                sum += (double)oks / dots * ttick * sin(theta);
            }
            ++counter;
            if(counter % 6 == 0) {
                std::cerr << '#';
                counter = 0;
            }
        }
        sum *= ptick;
        // sum *= ttick;
        sum /= twopi;
        std::cerr << '\r' << sum << std::endl;
        writeFile(output, d, sum);
    }

    return 0;
}
