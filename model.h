/**
 * @file model
 * @brief model class definition
 * @version 1.0
 * @author Www
 * @date 2025/4/6
 */
#ifndef MODEL_H
#define MODEL_H
#include<cmath>
struct Vec3 {
    double x, y, z;
    Vec3() = default;
    Vec3(double _x, double _y, double _z) {
        x = _x, y = _y, z = _z;
    }
    // 赋值运算符重载
    Vec3& operator=(Vec3& other)  {
        if (this != &other) { // 防止自我赋值
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
    // 向量加法
    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    // 向量减法
    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    // 向量数乘
    Vec3 operator*(double s) const {
        return Vec3(x * s, y * s, z * s);
    }

    // 向量数除
    Vec3 operator/(double s) const {
        return Vec3(x / s, y / s, z / s);
    }

    // 点积
    double dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // 叉积
    Vec3 cross(const Vec3& v) const {
        return Vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // 单位化
    Vec3 normalize() const {
        double len = std::sqrt(x * x + y * y + z * z);
        return (len == 0) ? Vec3(0, 0, 0) : *this / len;
    }

    // 取模
    double norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }


};

struct Triangle {
    int v1, v2, v3;
};
#endif //MODEL_H
