/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   area.h
 * Author: cuidongf
 *
 * Created on February 2, 2018, 2:32 PM
 */
#ifndef AREA_H
#define AREA_H

#include "m1.h"
#include "StreetsDatabaseAPI.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include "map_data.h"
#include <list> 



using namespace std;

class area{
    private:
//        vector< vector < vector<unsigned> > > AREA;
        vector<unsigned> AREA[50][100];

        //matrix 50x100, 5000 sub areas. each is a vector contains the ID of points within that area
        vector<LatLon> interLatLonList;
        double northBound;
        double southBound;
        double westBound;
        double eastBound;
        double latDelta;
        double lonDelta;
        
        
        
    public:
       
        
        
        double get_northBound() const;
        double get_southBound() const;
        double get_eastBound() const;
        double get_westBound() const;
        double get_latDelta() const;
        double get_lonDelta() const;
        
        vector<LatLon> get_InterLatLonList() const;
        vector<unsigned> get_AREA(unsigned rowIndex, unsigned colIndex) const;
        
        area();
};


#endif /* AREA_H */

