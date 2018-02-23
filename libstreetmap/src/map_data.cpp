/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "map_data.h"
// de-constructor
map_data::~map_data() {
    //delete the point array in parks for fillpoly function
    for(unsigned i = 0;i < parks.size();i++){
        delete [] parks[i].point;
    }
    //delete the point array in beachs for fillpoly function
    for(unsigned i = 0;i < beachs.size();i++){
        delete [] beachs[i].point;
    }
    //delete the point array in lakes for fillpoly function
    for(unsigned i = 0;i < lakes.size();i++){
        delete [] lakes[i].point;
    }
    //delete the point array in islands for fillpoly function
    for(unsigned i = 0;i < islands.size();i++){
        delete [] islands[i].point;
    }
    //delete the point array in islands for fillpoly function
    for(unsigned i = 0;i < buildings.size();i++){
        delete [] buildings[i].point;
    }
    //delete the point array in greenspaces for fillpoly function
    for(unsigned i = 0;i < greenspaces.size();i++){
        delete [] greenspaces[i].point;
    }
    //delete the point array in golfcourses for fillpoly function
    for(unsigned i = 0;i < golfcourses.size();i++){
        delete [] golfcourses[i].point;
    }
    //delete the point array in rivers for fillpoly function
    for(unsigned i = 0;i < rivers.size();i++){
        delete [] rivers[i].point;
    }
    //delete the point array in shorelines for fillpoly function
    for(unsigned i = 0;i < shorelines.size();i++){
        delete [] shorelines[i].point;
    }
    //delete the point array in streams for fillpoly function
    for(unsigned i = 0;i < streams.size();i++){
        delete [] streams[i].point;
    }
    
//    //delete the point array in Lspeed for fillpoly function
//    for(unsigned i = 0;i < Lspeed.size();i++){
//        delete [] Lspeed[i].point;
//    }
//    //delete the point array in Mspeed for fillpoly function
//    for(unsigned i = 0;i < Mspeed.size();i++){
//        delete [] Mspeed[i].point;
//    }
//    //delete the point array in Hspeed for fillpoly function
//    for(unsigned i = 0;i < Hspeed.size();i++){
//        delete [] Hspeed[i].point;
//    }
    //delete the point array in motorway for fillpoly function
    for(unsigned i = 0;i < motorway.size();i++){
        delete [] motorway[i].point;
    }
    //delete the point array in trunk for fillpoly function
    for(unsigned i = 0;i < trunk.size();i++){
        delete [] trunk[i].point;
    }
    //delete the point array in primary for fillpoly function
    for(unsigned i = 0;i < primary.size();i++){
        delete [] primary[i].point;
    }
    //delete the point array in secondary for fillpoly function
    for(unsigned i = 0;i < secondary.size();i++){
        delete [] secondary[i].point;
    }
    //delete the point array in tertiary; for fillpoly function
    for(unsigned i = 0;i < tertiary.size();i++){
        delete [] tertiary[i].point;
    }
    //delete the point array in unclassified for fillpoly function
    for(unsigned i = 0;i < unclassified.size();i++){
        delete [] unclassified[i].point;
    }
    //delete the point array in residential for fillpoly function
    for(unsigned i = 0;i < residential.size();i++){
        delete [] residential[i].point;
    }
    //delete the point array in service for fillpoly function
    for(unsigned i = 0;i < service.size();i++){
        delete [] service[i].point;
    }
    //delete the point array in otherhighway for fillpoly function
    for(unsigned i = 0;i < otherhighway.size();i++){
        delete [] otherhighway[i].point;
    }
}
// constructor
map_data::map_data() {   
    //load total numbers of streets, street segments, and intersections into local variable
    unsigned totalsegmentNum = getNumberOfStreetSegments();
    unsigned totalstreetNum = getNumberOfStreets();
    unsigned totalIntersectionsNum = getNumberOfIntersections();
    unsigned totalfeatureNum = getNumberOfFeatures();
    unsigned totalwayNum = getNumberOfWays();
    unsigned totalinterestNum = getNumberOfPointsOfInterest();
    unsigned totalNodeNum = getNumberOfNodes();
    unsigned totalRelationshipNum = getNumberOfRelations();
    //change the size of storing variables
    intersection_street_segments.resize(totalIntersectionsNum);
    street_segments.resize(totalstreetNum);
    street_intersections.resize(totalstreetNum);
    segmentID_segmentlength.resize(totalsegmentNum);
    segmentID_traveltime.resize(totalsegmentNum);
    streetID_streetlength.resize(totalstreetNum);
    intersections.resize(totalIntersectionsNum);
    intersectionID_alreadyinsert.resize(totalIntersectionsNum);
    kdtree_intersections.resize(totalIntersectionsNum);
    kdtree_interests.resize(totalinterestNum);
    
    //store the nodeOSMID type to unordered map
    for (unsigned i = 0;i<totalNodeNum;i++) {
        node_OSMID_ID[getNodeByIndex(i)->id()] = i;
    }
    
    
    //store the wayOSMID type to unordered map
    for (unsigned i = 0;i<totalwayNum;i++) {
        //store the wayOSMID type to unordered map
        way_OSMID_ID[getWayByIndex(i)->id()] = i;
        for(unsigned j=0;j<getTagCount(getWayByIndex(i));j++){
            //cout<<getTagPair(getWayByIndex(i),j).first<<" "<<getTagPair(getWayByIndex(i),j).second<<endl;
            if(getTagPair(getWayByIndex(i),j).first=="highway"){
                OSMID_typestring[getWayByIndex(i)->id()]=getTagPair(getWayByIndex(i),j).second;  
            }
//            if(getTagPair(getWayByIndex(i),j).first=="name"){
//                OSMID_OSMwayname[getWayByIndex(i)->id()]=getTagPair(getWayByIndex(i),j).second;  
//            }
        }
    }

    //store data into vector: intersection_street_segments
    for(unsigned intersection = 0; intersection < totalIntersectionsNum;++intersection){
        //loop through all the intersections
        
        for(unsigned i=0; i< getIntersectionStreetSegmentCount(intersection);++i){
            //loop through all the segments which connected to the intersection
            auto const ss_id = getIntersectionStreetSegment(intersection,i);
            intersection_street_segments[intersection].push_back(ss_id);
        } 
        
        //loop through all the intersection data include position and name
        intersections[intersection].position = getIntersectionPosition(intersection);
        intersections[intersection].name = getIntersectionName(intersection);
        // set max and min for latitude and longitude
        max_lat = std::max(max_lat,intersections[intersection].position.lat());
        min_lat = std::min(min_lat,intersections[intersection].position.lat());
        max_lon = std::max(max_lon,intersections[intersection].position.lon());
        min_lon = std::min(min_lon,intersections[intersection].position.lon());
        
        // load points of intersection to r-tree
        kdtree_intersections[intersection].x[0]=intersections[intersection].position.lon();
        kdtree_intersections[intersection].x[1]=intersections[intersection].position.lat();
        kdtree_intersections[intersection].id=intersection;  
        
        // set already insert intersection to false in vector
        intersectionID_alreadyinsert[intersection] = false;
    }
    
    //calculate latitude-average after the intersection loop
    avg_lat = 0.5*(max_lat+min_lat)*DEG_TO_RAD;
    
    //second intersection loop to get cartesian value
    for(unsigned intersection = 0; intersection < totalIntersectionsNum;++intersection){
        intersections[intersection].latitude_cartesian = intersections[intersection].position.lat()*DEG_TO_RAD;
        intersections[intersection].longitude_cartesian= intersections[intersection].position.lon()*cos(avg_lat)*DEG_TO_RAD;
    }
    
    //store data into vectors
    for(unsigned segmentID=0;segmentID<totalsegmentNum;segmentID++){
        //loop though all the street segments
        StreetSegmentInfo temp = getStreetSegmentInfo(segmentID);
        unsigned tempstreetID = temp.streetID;
        //store street segments into vector
        street_segments[tempstreetID].push_back(segmentID);
        //store the intersection ids which are located on the same street
        street_intersections[tempstreetID].push_back(temp.from);
        street_intersections[tempstreetID].push_back(temp.to);
        
        //calculate the distance and speed
        //get information and make them become local variables
        LatLon point1 = getIntersectionPosition(temp.from);
        LatLon point2 = getIntersectionPosition(temp.to);
        double distance = 0.0;
        double speedLimit = 1000*temp.speedLimit/(60*60);
        
        // set data structure for save drawing information
        feature_data tempfeature_data;
        tempfeature_data.npoints = temp.curvePointCount+2;
        tempfeature_data.point = new t_point[tempfeature_data.npoints];
        
        //load data into segmentDrawingInfo vector
        float segmentFromX = point1.lon()*cos(avg_lat)*DEG_TO_RAD;
        float segmentFromY = point1.lat()*DEG_TO_RAD;
        float segmentToX = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
        float segmentToY = point2.lat()*DEG_TO_RAD;
        t_point start (segmentFromX, segmentFromY);
        t_point end (segmentToX, segmentToY);
        draw_street_segments_data insertSegmentDrawingtemp;
        insertSegmentDrawingtemp.location = t_bound_box(start, end);
        insertSegmentDrawingtemp.segmentsID = segmentID;
        insertSegmentDrawingtemp.name = getStreetName(temp.streetID);
        
        if (insertSegmentDrawingtemp.name=="<unknown>")
            insertSegmentDrawingtemp.draw = false;
        else
            insertSegmentDrawingtemp.draw = true;
        
        double RAD_TO_DEG = 1/DEG_TO_RAD;
        insertSegmentDrawingtemp.angle = atan((segmentFromY - segmentToY)/(segmentFromX - segmentToX))*RAD_TO_DEG;
        tempfeature_data.drawInfo = insertSegmentDrawingtemp;
        tempfeature_data.oneway = temp.oneWay;
        
        //calculate length of one street segment
        if(temp.curvePointCount==0){
            //if there is no curves
            distance = find_distance_between_two_points(point1, point2);
            //calculate the cartesion number from the LonTon and save the information to the allocated array
            tempfeature_data.point[0].x = point1.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
            tempfeature_data.point[0].y = point1.lat()*DEG_TO_RAD;
            tempfeature_data.point[1].x = point2.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
            tempfeature_data.point[1].y = point2.lat()*DEG_TO_RAD;
        }
        else{
            //if there is curve in the street segment
            unsigned num = temp.curvePointCount;
            LatLon temp1 = point1,temp2;
            //calculate the cartesion number from the LonTon and save the information to the allocated array
            tempfeature_data.point[0].x = point1.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
            tempfeature_data.point[0].y = point1.lat()*DEG_TO_RAD;
            for(unsigned i=1; i<=num; i++){
                temp2 = getStreetSegmentCurvePoint(segmentID,i-1);
                distance += find_distance_between_two_points(temp1, temp2);
                temp1 = temp2;
                //calculate the cartesion number from the LonTon and save the information to the allocated array
                tempfeature_data.point[i].x = temp2.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[i].y = temp2.lat()*DEG_TO_RAD;
            }
            distance += find_distance_between_two_points(point2,temp2);
            //calculate the cartesion number from the LonTon and save the information to the allocated array
            tempfeature_data.point[num+1].x = point2.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
            tempfeature_data.point[num+1].y = point2.lat()*DEG_TO_RAD;
            tempfeature_data.openfeature = true;
        }
        //store information into vectors
        segmentID_segmentlength[segmentID]=distance;
        segmentID_traveltime[segmentID]=distance/speedLimit;
        //increase street length
        streetID_streetlength[tempstreetID] += distance;
        
        tempfeature_data.name = getStreetName(temp.streetID);
        // push data structure to the Lspeed Mspeed Hspeed
        if(temp.speedLimit<40) {
            Lspeed.push_back(tempfeature_data);
        }
        else if(temp.speedLimit>60) {
            Hspeed.push_back(tempfeature_data);
        }
        else {
            Mspeed.push_back(tempfeature_data);
        }
        
        std::unordered_map<OSMID,std::string>::const_iterator got = OSMID_typestring.find (temp.wayOSMID);
        // push data structure to the OSMwayID types
        if (got == OSMID_typestring.end()) {
            otherway.push_back(tempfeature_data);
            if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    otherway_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    otherway_intersection.push_back(tempintersection_data);
                }
        } 
        else {
            //find tag is motorway insert segment data and intersection data for level
            if (got->second=="motorway") {
                motorway.push_back(tempfeature_data);
                if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    motorway_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    motorway_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="trunk") {
                trunk.push_back(tempfeature_data);
                if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    trunk_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    trunk_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="primary") {
                primary.push_back(tempfeature_data);
                if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    primary_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    primary_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="secondary") {
                secondary.push_back(tempfeature_data);
                if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    secondary_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    secondary_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="tertiary") {
                tertiary.push_back(tempfeature_data);
                if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    tertiary_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    tertiary_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="unclassified") {
                unclassified.push_back(tempfeature_data);
                if(!intersectionID_alreadyinsert[temp.from]){
                    intersectionID_alreadyinsert[temp.from]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian= point1.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    unclassified_intersection.push_back(tempintersection_data);
                }
                if(!intersectionID_alreadyinsert[temp.to]){
                    intersectionID_alreadyinsert[temp.to]=true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat()*DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    unclassified_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="residential") {
                residential.push_back(tempfeature_data);
                if (!intersectionID_alreadyinsert[temp.from]) {
                    intersectionID_alreadyinsert[temp.from] = true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian = point1.lon() * cos(avg_lat) * DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat() * DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    residential_intersection.push_back(tempintersection_data);
                }
                if (!intersectionID_alreadyinsert[temp.to]) {
                    intersectionID_alreadyinsert[temp.to] = true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon() * cos(avg_lat) * DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat() * DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    residential_intersection.push_back(tempintersection_data);
                }
            } 
            else if (got->second=="service") {
                service.push_back(tempfeature_data);
                if (!intersectionID_alreadyinsert[temp.from]) {
                    intersectionID_alreadyinsert[temp.from] = true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian = point1.lon() * cos(avg_lat) * DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat() * DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    service_intersection.push_back(tempintersection_data);
                }
                if (!intersectionID_alreadyinsert[temp.to]) {
                    intersectionID_alreadyinsert[temp.to] = true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon() * cos(avg_lat) * DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat() * DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    service_intersection.push_back(tempintersection_data);
                }
            } 
            else {
                otherhighway.push_back(tempfeature_data);
                if (!intersectionID_alreadyinsert[temp.from]) {
                    intersectionID_alreadyinsert[temp.from] = true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point1;
                    tempintersection_data.longitude_cartesian = point1.lon() * cos(avg_lat) * DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point1.lat() * DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.from);
                    otherhighway_intersection.push_back(tempintersection_data);
                }
                if (!intersectionID_alreadyinsert[temp.to]) {
                    intersectionID_alreadyinsert[temp.to] = true;
                    intersection_data tempintersection_data;
                    tempintersection_data.position = point2;
                    tempintersection_data.longitude_cartesian = point2.lon() * cos(avg_lat) * DEG_TO_RAD;
                    tempintersection_data.latitude_cartesian = point2.lat() * DEG_TO_RAD;
                    tempintersection_data.name = getIntersectionName(temp.to);
                    otherhighway_intersection.push_back(tempintersection_data);
                }
            }
        }
//        if(OSMID_OSMwayname[temp.wayOSMID]!=getStreetName(temp.streetID)&&(getStreetName(temp.streetID)!="<unknown>")){
//            cout<<OSMID_OSMwayname[temp.wayOSMID]<<endl;
//            cout<<getStreetName(temp.streetID)<<endl;
//            cout<<""<<endl;
//        }
//        //load data into segmentDrawingInfo vector
//        float segmentFromX = point1.lon()*cos(avg_lat)*DEG_TO_RAD;
//        float segmentFromY = point1.lat()*DEG_TO_RAD;
//        float segmentToX = point2.lon()*cos(avg_lat)*DEG_TO_RAD;
//        float segmentToY = point2.lat()*DEG_TO_RAD;
//        t_point start (segmentFromX, segmentFromY);
//        t_point end (segmentToX, segmentToY);
//        draw_street_segments_data insertSegmentDrawingtemp;
//        insertSegmentDrawingtemp.location = t_bound_box(start, end);
//        insertSegmentDrawingtemp.segmentsID = segmentID;
//        insertSegmentDrawingtemp.name = getStreetName(temp.streetID);
//        float RAD_TO_DEG = 1/DEG_TO_RAD;
//        insertSegmentDrawingtemp.angle = atan((segmentFromY - segmentToY)/(segmentFromX - segmentToX))/RAD_TO_DEG;
//        segmentDrawingInfo.push_back(insertSegmentDrawingtemp);
    }
    
    
    //store data into vector: streetString_streetIDs
    for(unsigned streetID = 0;streetID < totalstreetNum; ++streetID){
        //sort the street intersections first 
        sort(street_intersections[streetID].begin(), street_intersections[streetID].end());
        street_intersections[streetID].erase(unique( street_intersections[streetID].begin(), street_intersections[streetID].end()), street_intersections[streetID].end());
          
        
        //set streetstring_streetIDs unordermap
        std::string tempstreetname = getStreetName(streetID);
        streetString_streetIDs[tempstreetname].push_back(streetID);
    }
    
    // load points of interest to kd-tree
    for(unsigned i = 0; i < totalinterestNum; i++){
        kdtree_interests[i].x[0]=getPointOfInterestPosition(i).lon();
        kdtree_interests[i].x[1]=getPointOfInterestPosition(i).lat();
        kdtree_interests[i].id=i;
        //filter the types of point of interests
        string interestType = getPointOfInterestType(i);
        interest_data insertInterest;
        insertInterest.interestID = i;
        insertInterest.name = getPointOfInterestName(i);
        if ((interestType == "theatre")||(interestType == "cinema")||(interestType == "casino")){
            entertainment.push_back(insertInterest);
        }else if((interestType == "bus_station")||(interestType == "ferry_terminal")){
            transportation.push_back(insertInterest);
        }else if((interestType == "hospital")||(interestType == "pharmacy")||(interestType == "dentist")||(interestType == "doctors")||(interestType == "clinic")){
            medical.push_back(insertInterest);
        }else if((interestType == "fast_food")||(interestType == "restaurant")||(interestType == "food_court")||(interestType == "backery")){
            restaurant.push_back(insertInterest);
        }else if((interestType == "hotel")||(interestType == "motel")){
            hotel.push_back(insertInterest);
        }else if(interestType == "bank"){
            bank.push_back(insertInterest);
        }else{
            other.push_back(insertInterest);
        }
    }
    
    //build kd-tree by prepared data
    kd_Build(kdtree_intersections);
    kd_Build(kdtree_interests);
    
    // load features information 
    for(unsigned i = 0; i < totalfeatureNum; i++){
        feature_data tempfeature_data;
        // if it is park load to park vector
        if (getFeatureType(i)==1) {
            // push number of points for a park to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        parks.push_back(tempfeature_data);    
        }
        //if it is beach load to beach vector
        if (getFeatureType(i)==2) {
            // push number of points for a beach to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        beachs.push_back(tempfeature_data);    
        }
        //if it is lake load to lake vector
        if (getFeatureType(i)==3) {
            // push number of points for a lake to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        lakes.push_back(tempfeature_data);    
        }
        //if it is island load to island vector
        if (getFeatureType(i)==5) {
            // push number of points for a island to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        islands.push_back(tempfeature_data);    
        }
        //if it is building load to building vector
        if (getFeatureType(i)==7) {
            // push number of points for a building to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        buildings.push_back(tempfeature_data);    
        }
        //if it is greenspace load to greenspace vector
        if (getFeatureType(i)==8) {
            // push number of points for a greenspace to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        greenspaces.push_back(tempfeature_data);    
        }
        //if it is golfcourse load to golfcourse vector
        if (getFeatureType(i)==9) {
            // push number of points for a golfcourse to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        golfcourses.push_back(tempfeature_data);    
        }
        //if it is river load to river vector
        if (getFeatureType(i)==4) {
            // push number of points for a river to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        rivers.push_back(tempfeature_data);    
        }
        //if it is shoreline load to shoreline vector
        if (getFeatureType(i)==6) {
            // push number of points for a shoreline to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        shorelines.push_back(tempfeature_data);    
        }
        //if it is stream load to stream vector
        if (getFeatureType(i)==10) {
            // push number of points for a stream to the data structure
            tempfeature_data.npoints=getFeaturePointCount(i);
            // allocate number of points need since the function fillpoly only accept input of a array pointer
            tempfeature_data.point=new t_point[tempfeature_data.npoints];
            // calculate the cartesion number from the LonTon and save the information to the allocated array
            for(unsigned j = 0; j < tempfeature_data.npoints; j++){
                LatLon tempLatLon = getFeaturePoint(i,j);
                tempfeature_data.point[j].x = tempLatLon.lon()*cos(avg_lat)*DEG_TO_RAD;//lon
                tempfeature_data.point[j].y = tempLatLon.lat()*DEG_TO_RAD;
            }
            if ((tempfeature_data.point[0].x == tempfeature_data.point[tempfeature_data.npoints-1].x)&&(tempfeature_data.point[0].y == tempfeature_data.point[tempfeature_data.npoints-1].y)) {
                tempfeature_data.openfeature = false;
            }
            else {
                tempfeature_data.openfeature = true;
            }
        streams.push_back(tempfeature_data);    
        }        
    }
//    cout<<motorway.size()<<endl; 3 5 1 8 9 7 2 4 10 6 0
//    cout<<trunk.size()<<endl;
//    cout<<primary.size()<<endl;
//    cout<<secondary.size()<<endl;
//    cout<<tertiary.size()<<endl;
//    cout<<unclassified.size()<<endl;
//    cout<<residential.size()<<endl;
//    cout<<service.size()<<endl;
//    cout<<otherhighway.size()<<endl;
//    for(unsigned i =0;i<totalIntersectionsNum;i++){
//        if(intersectionID_alreadyinsert[i]==false){
//            intersection_data tempintersection_data;
//            tempintersection_data.position = getIntersectionPosition(i);
//            tempintersection_data.latitude_cartesian = getIntersectionPosition(i).lat()* DEG_TO_RAD;
//            tempintersection_data.longitude_cartesian = getIntersectionPosition(i).lon() * cos(avg_lat) * DEG_TO_RAD;
//            tempintersection_data.name = getIntersectionName(i);
//            noway_intersection.push_back(tempintersection_data);
//        }
//    }
    //store subway information
    for (unsigned i = 0; i < totalRelationshipNum; i++) {
        const OSMRelation* temprelation = getRelationByIndex(i);
        for (unsigned j = 0; j < getTagCount(temprelation); j++) {
            if (getTagPair(temprelation, j).second == "subway") {
                std::vector<OSMRelation::Member> tempsubwaymember = temprelation->members();
                unsigned subwayidx = subwaypointscartision.size();
                subwaypointscartision.resize(subwaypointscartision.size() + 1);
                for (unsigned k = 0; k < tempsubwaymember.size(); k++) {
                    if (tempsubwaymember[k].tid.type() == 2) {
                        unsigned wayIDfromOSMID = way_OSMID_ID[tempsubwaymember[k].tid];
                        unsigned wayidx = subwaypointscartision[subwayidx].size();
                        subwaypointscartision[subwayidx].resize(subwaypointscartision[subwayidx].size() + 1);
                        const std::vector<OSMID> relation_way_nodeOSMID = getWayByIndex(wayIDfromOSMID)->ndrefs();
                        for (unsigned l = 0; l < relation_way_nodeOSMID.size(); l++) {
                            unsigned nodeIDfromOSMID = node_OSMID_ID[relation_way_nodeOSMID[l]];
                            LatLon tempnodelatlon = getNodeByIndex(nodeIDfromOSMID)->coords();
                            t_point tempt_point;
                            tempt_point.x = tempnodelatlon.lon() * cos(avg_lat) * DEG_TO_RAD;
                            tempt_point.y = tempnodelatlon.lat() * DEG_TO_RAD;
                            subwaypointscartision[subwayidx][wayidx].push_back(tempt_point);
                        }
                    }
                }
            }
        }
    }
    
}
    

//get information functions
//detailed descriptions are listed in the header file
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
    //later would be used//return streetnameID_streetID[streetnameID.at(inputstreetString)];
    if (streetString_streetIDs.find(inputstreetString)!=streetString_streetIDs.end()) {
      return streetString_streetIDs.at(inputstreetString);  
    }
    else {
        std::vector<unsigned> empty;
        empty.resize(0);
        return empty;
    }
    
}

double map_data::get_segmentlength_segmentID(unsigned inputsegmentID) const{
    return segmentID_segmentlength[inputsegmentID];
}

double map_data::get_traveltime_segmentID(unsigned inputsegmentID) const{
    return segmentID_traveltime[inputsegmentID];
}

double map_data::get_streetlength_streetID(unsigned inputstreetID) const{
    return streetID_streetlength[inputstreetID];
}

unsigned map_data::closest_interest_point(LatLon my_position) const{ 
    return kd_Search(kdtree_interests,my_position.lon(),my_position.lat());
}

unsigned map_data::closest_intersection_point(LatLon my_position) const{
    return kd_Search(kdtree_intersections,my_position.lon(),my_position.lat());
}

//return intersections longitude by intersectionsID

double map_data::get_intersections_longitude_cartesian_intersectionsID(unsigned inputintersectionID)const {
    return intersections[inputintersectionID].longitude_cartesian;
}
//return intersections latitude by intersectionsID

double map_data::get_intersections_latitude_cartesian_intersectionsID(unsigned inputintersectionID)const {
    return intersections[inputintersectionID].latitude_cartesian;
}

// got max and min and average for longitude and latitude
double map_data::get_max_lat()const{
    return max_lat;
}
double map_data::get_max_lon()const{
    return max_lon;
}
double map_data::get_min_lat()const{
    return min_lat;
}
double map_data::get_min_lon()const{
    return min_lon;
}
double map_data::get_avg_lat()const{
    return avg_lat;
}

// get parks_data vector
std::vector<feature_data> map_data::get_parks_data()const{
    return parks;
}
// get beachs_data vector
std::vector<feature_data> map_data::get_beachs_data()const{
    return beachs;
}
// get lakes_data vector
std::vector<feature_data> map_data::get_lakes_data()const{
    return lakes;
}
// get lakes_data vector
std::vector<feature_data> map_data::get_islands_data()const{
    return islands;
}
// get buildings_data vector
std::vector<feature_data> map_data::get_buildings_data()const{
    return buildings;
}

// get greenspaces_data vector
std::vector<feature_data> map_data::get_greenspaces_data()const{
    return greenspaces;
}

// get golfcourses_data vector
std::vector<feature_data> map_data::get_golfcourses_data()const{
    return golfcourses;
}

// get rivers_data vector
std::vector<feature_data> map_data::get_rivers_data()const{
    return rivers;
}

// get shorelines_data vector
std::vector<feature_data> map_data::get_shorelines_data()const{
    return shorelines;
}

// get streams_data vector
std::vector<feature_data> map_data::get_streams_data()const{
    return streams;
}

// get Lspeed_data vector
std::vector<feature_data> map_data::get_Lspeed_data()const{
    return Lspeed;
}

// get Mspeed_data vector
std::vector<feature_data> map_data::get_Mspeed_data()const{
    return Mspeed;
}

// get Hspeed_data vector
std::vector<feature_data> map_data::get_Hspeed_data()const{
    return Hspeed;
}

// get motorway_data vector
std::vector<feature_data> map_data::get_motorway_data()const{
    return motorway;
}
// get trunk_data vector
std::vector<feature_data> map_data::get_trunk_data()const{
    return trunk;
}
// get primary_data vector
std::vector<feature_data> map_data::get_primary_data()const{
    return primary;
}
// get secondary_data vector
std::vector<feature_data> map_data::get_secondary_data()const{
    return secondary;
}
// get tertiary_data vector
std::vector<feature_data> map_data::get_tertiary_data()const{
    return tertiary;
}
// get unclassified_data vector
std::vector<feature_data> map_data::get_unclassified_data()const{
    return unclassified;
}
// get residential_data vector
std::vector<feature_data> map_data::get_residential_data()const{
    return residential;
}
// get service_data vector
std::vector<feature_data> map_data::get_service_data()const{
    return service;
}
// get otherhighway_data vector
std::vector<feature_data> map_data::get_otherhighway_data()const{
    return otherhighway;
}
// get otherway_data vector
std::vector<feature_data> map_data::get_otherway_data()const{
    return otherway;
}

// get subway data
std::vector< std::vector< std::vector<t_point> > > map_data::get_subway_data()const{
    return subwaypointscartision;
}


// get motorway_data vector
std::vector<intersection_data> map_data::get_motorway_intersection_data()const{
    return motorway_intersection;
}
// get trunk_data vector
std::vector<intersection_data> map_data::get_trunk_intersection_data()const{
    return trunk_intersection;
}
// get primary_data vector
std::vector<intersection_data> map_data::get_primary_intersection_data()const{
    return primary_intersection;
}
// get secondary_data vector
std::vector<intersection_data> map_data::get_secondary_intersection_data()const{
    return secondary_intersection;
}
// get tertiary_data vector
std::vector<intersection_data> map_data::get_tertiary_intersection_data()const{
    return tertiary_intersection;
}
// get unclassified_data vector
std::vector<intersection_data> map_data::get_unclassified_intersection_data()const{
    return unclassified_intersection;
}
// get residential_data vector
std::vector<intersection_data> map_data::get_residential_intersection_data()const{
    return residential_intersection;
}
// get service_data vector
std::vector<intersection_data> map_data::get_service_intersection_data()const{
    return service_intersection;
}
// get otherhighway_data vector
std::vector<intersection_data> map_data::get_otherhighway_intersection_data()const{
    return otherhighway_intersection;
} 

// get entertainment_data vector
std::vector<interest_data> map_data::get_entertainment_data()const{
    return entertainment;
}

//get transportation_data vector
std::vector<interest_data> map_data::get_transportation_data()const{
    return transportation;
}

//get education_data vector
std::vector<interest_data> map_data::get_education_data()const{
    return education;
}

//get medical_data vector
std::vector<interest_data> map_data::get_medical_data()const{
    return medical;
}

//get restaurant_data vector
std::vector<interest_data> map_data::get_restaurant_data()const{
    return restaurant;
}

//get hotel_data vector
std::vector<interest_data> map_data::get_hotel_data()const{
    return hotel;
}

//get other_data vector
std::vector<interest_data> map_data::get_other_data()const{
    return other;
}

//get segmentDrawingInfo vector
std::vector<draw_street_segments_data> map_data::get_segmentDrawingInfo_data()const{
    return segmentDrawingInfo;
}