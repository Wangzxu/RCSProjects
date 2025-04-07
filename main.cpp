#include "main.h"

using namespace std;

const double PI = 3.141592653589793;

int main() {
    // 初始化参数
    double radius = 2.0;
    int slices = 800;
    int stacks = 800;
    std::string filename = "F:\\C++_program\\ScatterProject\\mesh\\mesh.stl";
    cout<<"初始化参数："<<endl;
    cout<<"radius = "<<radius<<endl;
    cout<<"slices = "<<slices<<endl;
    cout<<"stacks = "<<stacks<<endl;
    ofstream fout(filename);
    fout << "radius: " << radius << "  slices: " << slices << "  stacks: " << stacks << endl;

    Vec3 k_inc = {0, 0, -1};      // z 方向入射
    Vec3 E_inc = {1, 0, 0};       // x 极化
    Vec3 H_inc = (k_inc.cross(E_inc) ); // 入射磁场方向
    cout << "入射波矢 k_inc : (" << k_inc.x << ", " << k_inc.y << ", " << k_inc.z << ") "
            <<"极化 ：( "<<E_inc.x << ", " << E_inc.y << ", " << E_inc.z << ") " << endl;
    fout << "入射波矢 k_inc : (" << k_inc.x << ", " << k_inc.y << ", " << k_inc.z << ") "
            <<"极化 ：( "<<E_inc.x << ", " << E_inc.y << ", " << E_inc.z << ") " << endl;

    // 假设 theta 是俯仰角（0~π），phi 是方位角（0~2π）
    double theta =0;
    double phi = 0;
    cout<<"theta = "<<theta<<endl;
    cout<<"phi = "<<phi<<endl;

    // 设置入射波频率和速度
    double f = 10e9;  // 10 GHz 雷达频率
    double c = 3e8;   // 光速 (m/s)
    double k0 = 2 * M_PI * f / c;
    cout<<"f = "<<f<<endl;
    cout<<"c = "<<c<<endl;
    cout<<"k0 = "<<k0<<endl;

    // 生成网格
    auto [vertices,triangles] = mesh(slices, stacks, radius, PI);
    cout<<"成功生成网格，正在写入stl文件"<<endl;

    // 写入stl文件
    writeSTL(vertices, triangles, filename);


    Vec3 a(0.0, 0.0, 0.0);
    Vec3 b(0.1, 0.0, 1.0);
    Vec3 c1(0.0, 0.1, 1.0);
    vector<Vec3> vertices1;
    vertices1.push_back(a);
    vertices1.push_back(b);
    vertices1.push_back(c1);
    Triangle triangle{0,1,2};
    vector<Triangle>triangles1;
    triangles1.push_back(triangle);
    // 计算RCS
    caculateRCS(triangles,vertices,k_inc,H_inc,theta,phi,k0);
    // caculateRCS(triangles1,vertices1,k_inc,H_inc,theta,phi,k0);
    return 0;
}