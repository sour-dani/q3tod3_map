#ifndef Q3TOD3_MAP_H
#define Q3TOD3_MAP_H
#include <string>

struct Vec3;
struct Face;
struct Brush;
struct Entity;
std::string to_str(float val);
float signed_zero(float v);
void convert_map(std::string infile, std::string outfile);
#endif // Q3TOD3_MAP_H
