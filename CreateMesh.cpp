//
//
// Created by w'z'x on 2025/4/5.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

struct Vec3 {
    double x, y, z;
};

struct Triangle {
    int v1, v2, v3;
};

struct TriangleNum{
    int v1, v2, v3;
};
tuple<vector<Vec3> , vector<Triangle>> mesh(int slices, int stacks, double radius, double PI) {
    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;


    // 添加顶部极点（唯一一个）
    vertices.push_back({0, 0, radius});

    // 添加中间层顶点（不包含极点）
    for (int i = 1; i < stacks; ++i) {
        double phi = PI * i / stacks;
        for (int j = 0; j <= slices; ++j) {
            double theta = 2 * PI * j / slices;
            Vec3 v{
                radius * std::sin(phi) * std::cos(theta),
                radius * std::sin(phi) * std::sin(theta),
                radius * std::cos(phi)
            };
            vertices.push_back(v);
        }
    }

    // 添加底部极点（唯一一个）
    vertices.push_back({0, 0, -radius});

    // 顶部三角形
    for (int j = 0; j < slices; ++j) {
        int top = 0;
        int a = 1 + j;
        int b = 1 + (j + 1);
        triangles.push_back({top, b, a});
    }

    // 中间部分
    for (int i = 0; i < stacks - 2; ++i) {
        for (int j = 0; j < slices; ++j) {
            int row = i * (slices + 1);
            int nextRow = (i + 1) * (slices + 1);
            int a = 1 + row + j;
            int b = 1 + nextRow + j;
            int c = 1 + row + (j + 1);
            int d = 1 + nextRow + (j + 1);

            triangles.push_back({a, b, c});
            triangles.push_back({b, d, c});
        }
    }

    // 底部三角形
    int bottom = (int)vertices.size() - 1;
    int lastRowStart = 1 + (stacks - 2) * (slices + 1);
    for (int j = 0; j < slices; ++j) {
        int a = lastRowStart + j;
        int b = lastRowStart + (j + 1);
        triangles.push_back({a, b, bottom});
    }
    return make_tuple(vertices, triangles);
}

void writeSTL(const std::vector<Vec3>& vertices, const std::vector<Triangle>& triangles, const std::string& filename) {
    std::ofstream fout(filename,std::ios::app);
//    fout << "solid mesh\n";
    vector<TriangleNum> trianglesWithNum;
    for (const auto& tri : triangles) {
        TriangleNum triNum;

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

//        fout << " facet normal " << normal.x << " " << normal.y << " " << normal.z << "\n";
//        fout << "  outer loop\n";
//        triNum.v1 = pointNum;
//        fout << "vertex "<<pointNum++ <<"  "<< a.x << " " << a.y << " " << a.z << "\n";
//        triNum.v2 = pointNum;
//        fout << "vertex " << pointNum++<<"  "<< b.x << " " << b.y << " " << b.z << "\n";
//        triNum.v3 = pointNum;
//        fout << "vertex " << pointNum++<<"  "<< c.x << " " << c.y << " " << c.z << "\n";
//        trianglesWithNum.push_back(triNum);
//        fout << "  endloop\n";
//        fout << " endfacet\n";
    }
    for(int i = 1; i <= vertices.size(); ++i) {
         Vec3 c = vertices[i - 1];
        fout << "vertex " << i<<"  ："<< c.x << " " << c.y << " " << c.z << "\n";
    }
    for (int i = 1; i <= triangles.size(); ++i) {
        Triangle triangle  = triangles[i - 1];
         fout<< " trangls "<< i<<"  ："<< triangle.v1 << " " << triangle.v2 << " " << triangle.v3 << "\n";
    }
//    fout << "endsolid mesh\n";

    std::cout << "STL 网格文件已保存为 "<<filename<<"\n";
}



