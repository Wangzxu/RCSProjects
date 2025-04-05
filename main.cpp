#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "CreateMesh.h"
#include <string>

using namespace std;

const double PI = 3.141592653589793;

int main() {
    // 初始化参数
    double radius = 1.0;
    int slices = 20;
    int stacks = 10;
    std::string filename = "F:\\C++_program\\ScatterProject\\mesh\\mesh.stl";
    cout<<"初始化参数："<<endl;
    cout<<"radius = "<<radius<<endl;
    cout<<"slices = "<<slices<<endl;
    cout<<"stacks = "<<stacks<<endl;
    ofstream fout(filename);
    fout << "radius: " << radius << "  slices: " << slices << "  stacks: " << stacks << endl;

    // 生成网格
    auto [vertices,triangles] = mesh(slices, stacks, radius, PI);
    cout<<"成功生成网格，正在写入stl文件"<<endl;

    // 写入stl文件
    writeSTL(vertices, triangles, filename);


    return 0;
}