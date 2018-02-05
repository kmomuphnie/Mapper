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

//including libraries which are used in this program
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <StreetsDatabaseAPI.h>
#include "m1.h"

//------------------------RTREE LIBRARY HEADERS-------------------------//
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/foreach.hpp>
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef std::pair<point, unsigned> value;
//------------------------RTREE LIBRARY HEADERS-------------------------//



using namespace std;
class map_data{
    //private data variables
    private: 
        //r-tree intersection
        bgi::rtree< value, bgi::rstar<8> > rt;
        //r-tree interest
        bgi::rtree< value, bgi::rstar<8> > rtForPOI;
        
        //store all street names and their IDs
        std::unordered_map<std::string,std::vector<unsigned> > streetString_streetIDs;
        //later would be used//std::map<std::string,unsigned> streetnameID;
        
        //vector which stores unsigned variables. these unsigned are entire street segments
        std::vector<std::vector<unsigned> > street_segments;
        
        //vector which stores vectors.
        //vector is the entire intersections in the program
        //stored vector is the street segments which connected to every intersection
        std::vector<std::vector<unsigned> > intersection_street_segments;
        
        //stored all the intersections located on a street into a vector. Organize them into another vector. 
        std::vector<std::vector<unsigned> > street_intersections;
        
        //Not sure whether it is needed or not
        //std::vector<std::vector<unsigned> > streetnameID_streetID;
        
        //store the length of every street segments. (ordered by id number)
        std::vector<double> segmentID_segmentlength;
        
        //store the length of every street.(ordered by id number)
        std::vector<double> streetID_streetlength;
        
        //store the fastest speed to travel through one street segment.
        std::vector<double> segmentID_traveltime;
    //public functions   
    public:
        
        //constructor of a class
        map_data();
        
        //return all street segments which are connected to the street
        std::vector<unsigned> get_all_segments_streetID (unsigned inputstreetID)  const;
        
        //return all street segments which are connected to one intersection point
        std::vector<unsigned> get_all_segments_from_intersectionID (unsigned inputintersectionID) const;
        
        //return all intersections on a particular street
        std::vector<unsigned> get_all_intersections_streetID (unsigned inputstreetID)  const;
        
        //return all street id which are corresponding to one street name
        std::vector<unsigned> get_all_streetID_streetString (std::string inputstreetString) const;
        
        //return the length of one street segment in meters
        double get_segmentlength_segmentID (unsigned inputsegmentID ) const;
        
        //return the length of one street in meters
        double get_streetlength_streetID (unsigned inputstreetID ) const;
        
        //return the shortest travel time of one street segment 
        double get_traveltime_segmentID (unsigned inputsegmentID ) const;
        
        //return r-tree interest close point
        unsigned closest_interest_point(LatLon my_position) const;
        
        //return r-tree intersection close point
        unsigned closest_intersection_point(LatLon my_position) const;
        
};
#endif /* MAP_DATA_H */
