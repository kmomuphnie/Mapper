/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "map_data.h"

// constructor
map_data::map_data(){
    unsigned totalsegmentNum = getNumberOfStreetSegments();
    unsigned totalstreetNum = getNumberOfStreets();
    unsigned totalIntersectionsNum = getNumberOfIntersections();
    
    intersection_street_segments.resize(totalIntersectionsNum);
    street_segments.resize(totalstreetNum);
    street_intersections.resize(totalstreetNum);
    for(unsigned intersection = 0; intersection < totalIntersectionsNum;++intersection){
        for(unsigned i=0; i< getIntersectionStreetSegmentCount(intersection);++i){
            auto const ss_id = getIntersectionStreetSegment(intersection,i);
            intersection_street_segments[intersection].push_back(ss_id);
        }
    }
    for(unsigned segmentID=0;segmentID<totalsegmentNum;segmentID++){
        StreetSegmentInfo temp = getStreetSegmentInfo(segmentID);
        unsigned tempstreetID = temp.streetID;
            street_segments[tempstreetID].push_back(segmentID);
            street_intersections[tempstreetID].push_back(temp.from);
            street_intersections[tempstreetID].push_back(temp.to);
            
            LatLon point1 = getIntersectionPosition(temp.from);
            LatLon point2 = getIntersectionPosition(temp.to);
            double distance=0.0;
            double speedLimit=1000*temp.speedLimit/(60*60);
            if(temp.curvePointCount==0){
                //if there is no curves
                distance = find_distance_between_two_points(point1, point2);
            }
            else{
                //if there is curve in the street segment
                unsigned num = temp.curvePointCount;
                LatLon temp1=point1,temp2;
                for(unsigned i=1; i<=num; i++){
                    temp2 = getStreetSegmentCurvePoint(segmentID,i-1);
                    distance += find_distance_between_two_points(temp1, temp2);
                    temp1=temp2;
                }
                distance+=find_distance_between_two_points(point2,temp2);
            }
            segmentID_segmentlength.push_back(distance);
            segmentID_traveltime.push_back(distance/speedLimit);
        }
    for(unsigned streetID=0;streetID<totalstreetNum;streetID++){
        sort(  street_intersections[streetID].begin(), street_intersections[streetID].end()  );
    street_intersections[streetID].erase(  unique( street_intersections[streetID].begin(), street_intersections[streetID].end() ), street_intersections[streetID].end()  );
    }
    
    for(unsigned streetID=0;streetID<totalstreetNum;++streetID){
        std::string tempstreetname = getStreetName(streetID);
        auto it = streetnameID.find(tempstreetname);
        //if find
        if(it!=streetnameID.end()){
            streetnameID_streetID[it->second].push_back(streetID);
        }
        //if did not find
        else {
            streetnameID[tempstreetname]=streetnameIDNum;
            streetnameID_streetID.push_back(std::vector<unsigned>());
            streetnameID_streetID[streetnameIDNum].push_back(streetID);
            streetnameIDNum++;
        }
    }
    
}
    


std::vector<unsigned>map_data::get_all_segments_from_intersectionID (unsigned inputintersectionID) const{
    return intersection_street_segments[inputintersectionID];
}

std::vector<unsigned>map_data::get_all_segments_streetID (unsigned inputstreetID) const{
    return street_segments[inputstreetID];
}

std::vector<unsigned>map_data::get_all_intersections_streetID (unsigned inputstreetID) const{
    return street_intersections[inputstreetID];
}

std::vector<unsigned>map_data::get_all_streetID_streetString (std::string inputstreetString) const{
    return streetnameID_streetID[streetnameID.at(inputstreetString)];
}

double map_data::get_segmentlength_segmentID(unsigned inputsegmentID) const{
    return segmentID_segmentlength[inputsegmentID];
}

double map_data::get_traveltime_segmentID(unsigned inputsegmentID) const{
    return segmentID_traveltime[inputsegmentID];
}