#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <iomanip>
#include "q3tod3_map.h"

struct Vec3 {
    float x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    float dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
    Vec3 cross(const Vec3& o) const {
        return Vec3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    float length() const { return sqrt(dot(*this)); }
    Vec3 normalized() const {
        float l = length();
        if (l > 0.0f) {
            return Vec3(x / l, y / l, z / l);
        }
        return *this;
    }
};

struct Face {
    Vec3 p1, p2, p3;
    std::string tex;
    float offx, offy, rot, scalex, scaley;
};

struct Brush {
    std::vector<Face> faces;
};

struct Entity {
    std::map<std::string, std::string> props;
    std::vector<Brush> brushes;
};

std::string to_str(float val) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6) << val;
    return ss.str();
}

float signed_zero(float v) {
    if (fabs(v) < 1e-6f) {
        return (std::signbit(v) ? -0.0f : 0.0f);
    }
    return v;
}

void convert_map(std::string infile, std::string outfile) {

    std::vector<Entity> map_data;
    std::string line;
    Entity cur_ent;
    Brush cur_br;
    int level = 0;
    bool in_brush = false;

    std::ifstream in(infile);
    if (!in) {
        throw (std::make_pair(std::string("Can't open input map:"), infile));
    }

    while (getline(in, line)) {
        size_t comm = line.find("//");
        if (comm != std::string::npos) line = line.substr(0, comm);
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);
        size_t end = line.find_last_not_of(" \t");
        if (end != std::string::npos) line = line.substr(0, end + 1);
        if (line.empty()) continue;

        if (line == "{") {
            level++;
            if (level == 1) {
                cur_ent = Entity();
            }
            else if (level == 2 && !in_brush) {
                in_brush = true;
                cur_br = Brush();
            }
        }
        else if (line == "}") {
            level--;
            if (level == 1 && in_brush) {
                cur_ent.brushes.push_back(cur_br);
                in_brush = false;
            }
            else if (level == 0) {
                map_data.push_back(cur_ent);
            }
        }
        else if (in_brush) {
            Face f;
            std::stringstream ss(line);
            char ch;
            ss >> ch;
            if (ch != '(') continue;
            ss >> f.p1.x >> f.p1.y >> f.p1.z >> ch;
            if (ch != ')') continue;
            ss >> ch;
            if (ch != '(') continue;
            ss >> f.p2.x >> f.p2.y >> f.p2.z >> ch;
            if (ch != ')') continue;
            ss >> ch;
            if (ch != '(') continue;
            ss >> f.p3.x >> f.p3.y >> f.p3.z >> ch;
            if (ch != ')') continue;
            ss >> f.tex >> f.offx >> f.offy >> f.rot >> f.scalex >> f.scaley;
            cur_br.faces.push_back(f);
        }
        else if (level == 1) {
            if (line[0] != '"') continue;
            size_t end_key = line.find('"', 1);
            if (end_key == std::string::npos) continue;
            std::string key = line.substr(1, end_key - 1);
            size_t start_val = line.find('"', end_key + 1);
            if (start_val == std::string::npos) continue;
            size_t end_val = line.rfind('"');
            if (end_val == std::string::npos) continue;
            std::string val = line.substr(start_val + 1, end_val - start_val - 1);
            cur_ent.props[key] = val;
        }
    }
    in.close();

    std::ofstream out(outfile);
    if (!out) {
        throw (std::make_pair(std::string("Can't open output map:"), outfile));
    }

    out << "Version 2\n";
    for (size_t e = 0; e < map_data.size(); ++e) {
        out << "// entity " << e << "\n{\n";
        const Entity& ent = map_data[e];
        for (const auto& p : ent.props) {
            out << "\"" << p.first << "\" \"" << p.second << "\"\n";
        }
        for (size_t b = 0; b < ent.brushes.size(); ++b) {
            out << "// primitive " << b << "\n{\nbrushDef3\n{\n";
            const Brush& br = ent.brushes[b];
            for (const Face& f : br.faces) {
                Vec3 v1 = f.p2 - f.p1;
                Vec3 v2 = f.p3 - f.p1;
                Vec3 n = v1.cross(v2).normalized();
                n = -n;
                float d = -n.dot(f.p1);
                float sx = 1.0f / (f.scalex * 64.0f);
                float sy = 1.0f / (f.scaley * 64.0f);
                float ox = f.offx / 64.0f;
                float oy = f.offy / 64.0f;
                std::string s_sx = to_str(sx);
                std::string s_ox = to_str(ox);
                std::string s_sy = to_str(sy);
                std::string s_oy = to_str(oy);
                std::string proj = "( ( " + s_sx + " 0 " + s_ox + " ) ( 0 " + s_sy + " " + s_oy + " ) )";
                std::string tex_name;
                if (f.tex[0] == '_') {
                    tex_name = f.tex;
                }
                else {
                    tex_name = "textures/" + f.tex;
                }
                out << "( " << signed_zero(n.x) << " " << signed_zero(n.y) << " " << signed_zero(n.z) << " " << signed_zero(d) << " ) " << proj << " \"" << tex_name << "\" 0 0 0\n";
            }
            out << "}\n}\n";
        }
        out << "}\n";
    }
    out.close();
}
