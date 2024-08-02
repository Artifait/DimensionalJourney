
#pragma once
#include <cmath>
#include "olcPixelGameEngine.h"
#include "v2f.h"

namespace DJ
{
    class v2i
    {
    public:
        v2i() : x(0), y(0) {}
        v2i(int x, int y) : x(x), y(y) {}

        v2i operator+(const v2i& other) const { return v2i(x + other.x, y + other.y); }
        v2i operator-(const v2i& other) const { return v2i(x - other.x, y - other.y); }
        v2i operator*(int scalar)     const { return v2i(x * scalar, y * scalar); }
        v2i operator*(const v2i& other) const { return v2i(x * other.x, y * other.y); }
        v2f operator/(float scalar)     const { return v2f(x / scalar, y / scalar); }
        v2f operator/(v2i scalar)       const { return v2f(x / scalar.x, y / scalar.y); }
        v2i operator%(v2i scalar)       const { return v2i((int)x % (int)scalar.x, (int)y % (int)scalar.y); }


        v2i& operator=(const v2i& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
            }
            return *this;
        }
        v2i& operator+=(const v2i& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        v2i& operator-=(const v2i& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        v2i& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        static v2i GetFloorFrom(const v2f& rhs) { return v2i(floor(rhs.x), floor(rhs.y)); }

        bool operator==(const v2i& rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!=(const v2i& rhs) const { return !(*this == rhs); }
        bool operator<(const v2i& rhs) const { return y < rhs.y || (y == rhs.y && x < rhs.x); }
        bool operator>(const v2i& rhs) const { return y > rhs.y || (y == rhs.y && x > rhs.x); }


        int x, y;


#ifdef SFML_VECTOR2_HPP
        v2f(const sf::Vector2f& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}
        v2f(const sf::Vector2i& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

        operator sf::Vector2f() const { return sf::Vector2f(x, y); }
        operator sf::Vector2i() const { return sf::Vector2i(x, y); }

        v2f& operator=(const sf::Vector2f& v) {
            x = static_cast<float>(v.x);
            y = static_cast<float>(v.y);
            return *this;
        }
        v2f& operator=(const sf::Vector2i& v) {
            x = static_cast<float>(v.x);
            y = static_cast<float>(v.y);
            return *this;
        }
#endif
#if defined(OLC_PGE_DEF) && !defined(OLC_IGNORE_VEC2D)
        v2i(const olc::vi2d& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

        operator olc::vi2d() const { return olc::vi2d(x, y); }

        v2i& operator=(const olc::vi2d& v) {
            x = static_cast<int>(v.x);
            y = static_cast<int>(v.y);
            return *this;
        }
#endif
    };
}
namespace std {
    template <>
    struct hash<DJ::v2i> {
        size_t operator()(const DJ::v2i& v) const {
            return hash<int>()(v.x) ^ hash<int>()(v.y);
        }
    };
}