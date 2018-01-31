/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   map_data.h
 * Author: wangha78
 *
 * Created on January 31, 2018, 3:44 PM
 */

#ifndef MAP_DATA_H
#define MAP_DATA_H
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <StreetsDatabaseAPI.h>
#include "m1.h"
using namespace std;
class map_data{
    private:
        std::vector<std::vector<unsigned> > intersection_street_segments;
    public:
        std::vector<unsigned> get_all_segments_from_intersectionID (unsigned inputintersectionID) const;
        map_data();
};
#endif /* MAP_DATA_H */
