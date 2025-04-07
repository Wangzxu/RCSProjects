/**
 * @file CreateMesh
 * @brief CreateMesh class definition
 * @version 1.0
 * @author Www
 * @date 2025/4/5
 */
#ifndef CREATEMESH_H
#define CREATEMESH_H
#include "model.h"
std::tuple<std::vector<Vec3> ,std:: vector<Triangle>> mesh(int slices, int stacks, double radius, double PI);
void writeSTL(const std::vector<Vec3>& vertices, const std::vector<Triangle>& triangles, const std::string& filename);

#endif //CREATEMESH_H
