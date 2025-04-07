/**
 * @file RCS
 * @brief RCS class definition
 * @version 1.0
 * @author Www
 * @date 2025/4/6
 */
#include "RCS.h"

struct triangleInfo {
  Vec3 normal;
   double area;
   Vec3 center;
   triangleInfo() = default;
   triangleInfo(Vec3 normal, float area, Vec3 center){
     this->normal = normal;
     this->area = area;
     this->center = center;
   }
   void setCenter(Vec3 center){
     this->center = center;
   }

};
/**
* 计算三角形的一些基本信息
*/
triangleInfo computeTriangleInfo(const Triangle tri,const std::vector<Vec3>& vertices) {
    triangleInfo result;
    Vec3 a = vertices[tri.v1];
    Vec3 b = vertices[tri.v2];
    Vec3 c = vertices[tri.v3];
    // 计算法向量
    Vec3 ab{b.x - a.x, b.y - a.y, b.z - a.z};
    Vec3 ac{c.x - a.x, c.y - a.y, c.z - a.z};
    Vec3 normal{
        ab.y * ac.z - ab.z * ac.y,
        ab.z * ac.x - ab.x * ac.z,
        ab.x * ac.y - ab.y * ac.x
    };
    Vec3 normal1 = normal.normalize();
    result.normal = normal1;
    // 计算面积
    result.area =ab.cross(ac).norm()*0.5;
    // 计算中心
    result.setCenter(Vec3{
        (a.x + b.x + c.x) / 3.0,
        (a.y + b.y + c.y) / 3.0,
        (a.z + b.z + c.z) / 3.0
      });
    return result;
}

double caculateRCS(const std::vector<Triangle>& triangles, const std::vector<Vec3>& vertices,const Vec3 k_inc, const Vec3 H_inc
                                                                                                                    ,const double theta, const double phi,const double k0){
    std::complex<double> E_scat_theta = 0.0;
    std::complex<double> E_scat_phi = 0.0;

    // 确保入射磁场正确归一化 (H_inc = (k_inc × E_inc)/η)
    const double eta = 377.0; // 自由空间波阻抗
    Vec3 H_inc_normalized = H_inc * (1.0/eta);

    double sum = 0.0;
    for (auto& tri : triangles) {
        triangleInfo info =  computeTriangleInfo(tri,vertices);
        // 只考虑可见面片
        if (info.normal.dot(k_inc) > 0) continue;
//        if (info.normal.dot(k_inc) < 0) continue;


        // 等效电流 Js = 2 n × H_inc
        Vec3 Js_pre = info.normal.cross(H_inc_normalized);
        Vec3 Js = Js_pre * 2.0;

        // 散射方向单位向量
        Vec3 r_hat = {sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)};

        // 相位项 e^(j k r̂·r')
        double phase = k0 * r_hat.dot(info.center);
        std::complex<double> exp_phase = std::exp(std::complex<double>(0, phase));

        // 面片贡献累加
        // θ方向单位向量（垂直极化）
        Vec3 theta_hat = {
            cos(theta) * cos(phi),
            cos(theta) * sin(phi),
            -sin(theta)
        };

        // φ方向单位向量（水平极化）
        Vec3 phi_hat = {
            -sin(phi),
            cos(phi),
            0
        };
        E_scat_theta += (Js.dot(theta_hat)) * exp_phase * info.area;
        E_scat_phi   += (Js.dot(phi_hat)) * exp_phase * info.area;
        sum += std::abs(info.area * info.normal.dot(k_inc));
//        std::cout << "Tri Center: " << info.center.x << ", " << info.center.y << ", " << info.center.z
//          << " | Js: " << Js.x << ", " << Js.y << ", " << Js.z << std::endl;
//       std::cout<< " | Phase: " << phase
//          << " | Contrib: " << (Js.dot(theta_hat)) * exp_phase * info.area << std::endl;

//        std::cout << "Js = (" << Js.x << ", " << Js.y << ", " << Js.z << ")\n";
//        std::cout << "theta_hat = (" << theta_hat.x << ", " << theta_hat.y << ", " << theta_hat.z << ")\n";
//        std::cout << "dot = " << Js.dot(theta_hat) << std::endl;

    }
    double E_abs2 = std::norm(E_scat_theta) + std::norm(E_scat_phi);
    double RCS = (4 * M_PI * E_abs2);
    std::cout << "RCS = " << RCS*1e+7 << std::endl;
    std::cout<<"area_sum: "<<sum;
    return RCS;
}

