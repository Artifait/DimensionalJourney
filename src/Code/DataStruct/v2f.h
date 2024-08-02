#pragma once
#include <cmath>
#include "olcPixelGameEngine.h"

namespace DJ
{
	class v2f
	{
    public:
        v2f() : x(0.f), y(0.f) {}
        v2f(float x, float y) : x(x), y(y) {}

        v2f operator+(const v2f& other) const { return v2f(x + other.x, y + other.y); }
        v2f operator-(const v2f& other) const { return v2f(x - other.x, y - other.y); }
        v2f operator*(float scalar)     const { return v2f(x * scalar, y * scalar); }
        v2f operator*(const v2f& other) const { return v2f(x * other.x, y * other.y); }
        v2f operator/(float scalar)     const { return v2f(x / scalar, y / scalar); }
        v2f operator/(v2f scalar)       const { return v2f(x / scalar.x, y / scalar.y); }
        v2f operator%(v2f scalar)       const { return v2f((int)x % (int)scalar.x, (int)y % (int)scalar.y); }


        v2f& operator=(const v2f& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
            }
            return *this;
        }
        v2f& operator+=(const v2f& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        v2f& operator-=(const v2f& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        v2f& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        v2f& operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const v2f& rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!=(const v2f& rhs) const { return !(*this == rhs); }
        bool operator<(const v2f& rhs) const { return y < rhs.y || (y == rhs.y && x < rhs.x); }
        bool operator>(const v2f& rhs) const { return y > rhs.y || (y == rhs.y && x > rhs.x); }

        float Mag() const { return std::sqrt(x * x + y * y); }
        float Mag2() const { return x * x + y * y; }
        v2f GetFloor() const { return v2f(std::floor(x), std::floor(y)); }

        void Norm() {
            float length = Mag();
            if (length != 0.f) {
                x /= length;
                y /= length;
            }
        }
        v2f GetNorm() const {
            v2f result(x, y);
            result.Norm();
            return result;
        }

        static float dot(const v2f& v1, const v2f& v2) 
        { return v1.x * v2.x + v1.y * v2.y; }
        static float cross(const v2f& v1, const v2f& v2) 
        { return v1.x * v2.y - v1.y * v2.x; }
        static v2f lerp(const v2f& v1, const v2f& v2, float t) 
        { return v1 * (1.f - t) + v2 * t; }

        float x, y;


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
        v2f(const olc::vf2d& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}
        v2f(const olc::vi2d& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

        operator olc::vf2d() const { return olc::vf2d(x, y); }
        operator olc::vi2d() const { return olc::vi2d(x, y); }

        v2f& operator=(const olc::vf2d& v) {
            x = static_cast<float>(v.x);
            y = static_cast<float>(v.y);
            return *this;
        }
        v2f& operator=(const olc::vi2d& v) {
            x = static_cast<float>(v.x);
            y = static_cast<float>(v.y);
            return *this;
        }
#endif
	};
}
namespace std {
    template <>
    struct hash<DJ::v2f> {
        size_t operator()(const DJ::v2f& v) const {
            return hash<float>()(v.x) ^ hash<float>()(v.y);
        }
    };
}