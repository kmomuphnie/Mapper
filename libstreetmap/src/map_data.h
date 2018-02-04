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
#include <map>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <StreetsDatabaseAPI.h>
#include "m1.h"


using namespace std;
class map_data{
    private:
        unsigned streetnameIDNum=0;
        std::unordered_map<std::string,std::vector<unsigned> > streetString_streetIDs;
        //later would be used//std::map<std::string,unsigned> streetnameID;
        std::vector<std::vector<unsigned> > street_segments;
        std::vector<std::vector<unsigned> > intersection_street_segments;
        std::vector<std::vector<unsigned> > street_intersections;
        std::vector<std::vector<unsigned> > streetnameID_streetID;
        std::vector<double> segmentID_segmentlength;
        std::vector<double> streetID_streetlength;
        std::vector<double> segmentID_traveltime;
        
        
    public:
        std::vector<unsigned> get_all_segments_streetID (unsigned inputstreetID)  const;
        std::vector<unsigned> get_all_segments_from_intersectionID (unsigned inputintersectionID) const;
        std::vector<unsigned> get_all_intersections_streetID (unsigned inputstreetID)  const;
        std::vector<unsigned> get_all_streetID_streetString (std::string inputstreetString) const;
        double get_segmentlength_segmentID (unsigned inputsegmentID ) const;
        double get_streetlength_streetID (unsigned inputstreetID ) const;
        double get_traveltime_segmentID (unsigned inputsegmentID ) const;
        map_data();
};
#endif /* MAP_DATA_H */
