#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

constexpr double twopi = 2 * M_PI;
constexpr double halfpi = M_PI / 2;

#define CASE(CHAR, VAR, IF, NAME) \
			case CHAR:\
				++str;\
				if(*str == '\0') str = *(++argv);\
				if(str != nullptr) {\
					std::istringstream stream(str);\
					stream >> temv;\
					if(!(IF)) warn("Invalid " #NAME " value (", temv, ')');\
					else VAR = temv;\
				}\
				else warn("No " #NAME " value after -", CHAR, " found, will be used default value");\
				break;

#define TOGGLE_CASE(CHAR, VAR) \
			case CHAR:\
				VAR = !VAR;\
				break;

#define STRING_CASE(CHAR, VAR, NAME) \
			case CHAR:\
				++str;\
				if(*str == '\0') str = *(++argv);\
				if(str != nullptr) VAR = str;\
				else warn("No " #NAME " -", CHAR, " found, will be used default value");\
				break;

void sumvecs(double dest[3], const double add[3]) {
	for(unsigned i = 0; i < 3; ++i) dest[i] += add[i];
}

void mulvec(double dest[3], double a) {
	for(unsigned i = 0; i < 3; ++i) dest[i] *= a;
}

double doublerand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template<class T, class... Args> void _warn(T arg, Args... args) {
	std::cerr << arg;
	_warn(args...);
}

template<class T> void _warn(T arg) {
	std::cerr << arg << '!' << std::endl;
}

template<class T, class... Args> void warn(T arg, Args... args) {
	std::cerr << "Warning: " << arg;
	_warn(args...);
}

template<class T> void warn(T arg) {
	std::cerr << "Warning: " << arg << '!' << std::endl;
}

#pragma inline_recursion(on)

template<class First, class... Args>
inline void writeFile(std::ostream& out, First&& first, Args&&... args) {
	out.write(reinterpret_cast<const char*>(&first), sizeof(First));
	writeFile(out, std::forward<Args>(args)...);
}

template<class First>
inline void writeFile(std::ostream& out, First&& first) {
	out.write(reinterpret_cast<const char*>(&first), sizeof(First));
}

#endif // !UTILS_H
