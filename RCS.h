/**
 * @file RCS
 * @brief RCS class definition
 * @version 1.0
 * @author Www
 * @date 2025/4/6
 */
#ifndef RCS_H
#define RCS_H
#include "model.h"
#include <vector>
#include <cmath>
#include <complex>
#include <iostream>
#include <fstream>

double caculateRCS(const std::vector<Triangle>& triangles, const std::vector<Vec3>& vertices,const Vec3 k_inc, const Vec3 H_inc
                                                                                                                    ,const double theta, const double phi,const double k0);

#endif //RCS_H
