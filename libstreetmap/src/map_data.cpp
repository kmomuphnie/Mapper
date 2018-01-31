/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "map_data.h"

// constructor
map_data::map_data(){
    intersection_street_segments.resize(getNumberOfIntersections());
    for(unsigned intersection = 0; intersection < getNumberOfIntersections();++intersection){
        for(unsigned i=0; i< getIntersectionStreetSegmentCount(intersection);++i){
            auto const ss_id = getIntersectionStreetSegment(intersection,i);
            intersection_street_segments[intersection].push_back(ss_id);
        }
    }
}

std::vector<unsigned>map_data::get_all_segments_from_intersectionID (unsigned inputintersectionID) const{
    return intersection_street_segments[inputintersectionID];
}