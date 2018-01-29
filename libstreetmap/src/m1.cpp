/* 
 * Copyright 2018 University of Toronto
 *
 * Permission is hereby granted, to use this software and associated 
 * documentation files (the "Software") in course work at the University 
 * of Toronto, or for personal use. Other uses are prohibited, in 
 * particular the distribution of the Software either publicly or to third 
 * parties.
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "m1.h"
#include "StreetsDatabaseAPI.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
        
        
bool load_map(std::string map_path) {
    bool load_successful = false; //Indicates whether the map has loaded successfully
    
    if(!loadStreetsDatabaseBIN(map_path)){
        return false;
    }
    
    
    //
    //Load your map related data structures here
    //
    
    
        load_successful = true; //Make sure this is updated to reflect whether
                            //loading the map succeeded or failed

    return load_successful;
}

void close_map() {
    //Clean-up your map related data structures here  
    cout << "Closing map" << endl;
    closeStreetDatabase();
   
}


//Returns street id(s) for the given street name
//If no street with this name exists, returns a 0-length vector.

std::vector<unsigned> find_street_ids_from_name(std::string street_name){
    std::vector<unsigned> result;
    
    string temp;
    unsigned  totalStreetNum = getNumberOfStreets();
    
    StreetIndex i = 0;//0 is <unknown> but cant reach total StreetNum
    //several cases:
    //a. no such street.  b. more than one street have the same name
    for( i = 0; i < totalStreetNum ; i++){
        temp = getStreetName(i);
        if(temp == street_name){
            result.push_back(i);
//          cout << i << endl;
        }    
    }
    

    return result;
    
////below are testing code which should be used  in test main
//    string test1= getStreetName(14);
//    cout << "test1   is  "<< test1<< endl;
//    std::vector<unsigned> test;
//    test =  find_street_ids_from_name(test1);
//    for(int i = 0; i < test.size(); i++){
//        cout << " " << test[i] << endl;
//    }
   
    
}

//Returns the street segments for the given intersection 
std::vector<unsigned> find_intersection_street_segments(unsigned intersection_id){
    
    std::vector<unsigned> streetSegmentList;
//    unsigned numStreetSegment = getIntersectionStreetSegmentCount(intersection_id);
//    for(unsigned i = 0; i < numStreetSegment; i++){
//        streetSegmentList.push_back(getIntersectionStreetSegment(intersection_id, i));
//    }
//    
    return streetSegmentList;
    
//    //below are testing code which should be used  in test main
//    cout << "This is a test using intersection ID 66" <<endl;
//    string intersection_name = getIntersectionName(66);
//    cout << "Intersection name is " << intersection_name << endl;
//    std::vector<unsigned> test = find_intersection_street_segments(66);
//    cout << "the following ID are the street segment ID that this intersection connected"<<endl;
//    
//    for(int i = 0; i < test.size(); i++){
//        cout << " " << test[i] << endl;
//    }
//    cout << endl;
//    
//    for(int j = 0; j < test.size();j++){
//        cout << "for Street segment ID " << test[j] << ", it";
//        StreetSegmentInfo testInfo = getStreetSegmentInfo(test[j]);
//        cout << " from intersection "<< testInfo.from <<"to intersection " << testInfo.to << endl;
//    }
    
    
}




//Returns the street names at the given intersection (includes duplicate street 
//names in returned vector)
std::vector<std::string> find_intersection_street_names(unsigned intersection_id){
    vector<string> streetNameList;
    
    vector<unsigned> streetSegmentList;
    unsigned numStreetSegment = getIntersectionStreetSegmentCount(intersection_id);
    for(unsigned i = 0; i < numStreetSegment; i++){
        streetSegmentList.push_back(getIntersectionStreetSegment(intersection_id, i));
    }
    //store the streetSegment IDs of the given intersection into a vector
    
    vector<StreetSegmentInfo> streetSegInfoList;
    for(unsigned j = 0; j < numStreetSegment; j++){
        streetSegInfoList.push_back(getStreetSegmentInfo(streetSegmentList[j]));
    }
    //store the SS info into a vector
      
    for(unsigned j = 0; j < numStreetSegment; j++){
        streetNameList.push_back(getStreetName(streetSegInfoList[j].streetID));
    }
  
    return streetNameList;
    
//    //this is the test code which should be used in test Main
//    cout << endl;
//    vector<string> streetNameList = find_intersection_street_names(66);
//    cout << " This is a test for finding street name around an intersection:  " << endl;
//    for(int i = 0; i < streetNameList.size(); i++){
//        cout << streetNameList[i] << endl;
//    }
//    cout << endl;
   
    
    
}


//Returns true if you can get from intersection1 to intersection2 using a single 
//street segment (hint: check for 1-way streets too)
//corner case: an intersection is considered to be connected to itself
bool are_directly_connected(unsigned intersection_id1, unsigned intersection_id2){
    
    if(intersection_id1 == intersection_id2){
        //the same intersection
        return true;
    }
    
    vector<unsigned>SSIDList1 =  find_intersection_street_segments(intersection_id1);
    vector<unsigned>SSIDList2 =  find_intersection_street_segments(intersection_id2);
    
    
    //comparing two vectors to find common element
    for(unsigned i = 0; i < SSIDList1.size(); i++){
        for(unsigned j = 0; j < SSIDList2.size();j++){
            if(SSIDList1[i] == SSIDList2[j]){
                StreetSegmentInfo temp = getStreetSegmentInfo(SSIDList1[i]);
                //check the oneway situation
                if(temp.oneWay){
                    if((temp.from == intersection_id1) && (temp.to == intersection_id2)){
                        return true;
                    }
                }else{
                    return true;
                }

            }
        
        
        }    
    }   
    return false;
    
//            //below are testing code which should be used  in test main
//    cout << "This is a test using intersection ID 66" <<endl;
//    string intersection_name = getIntersectionName(66);
//    cout << "Intersection name is " << intersection_name << endl;
//    std::vector<unsigned> test = find_intersection_street_segments(66);
//    cout << "the following ID are the street segment ID that this intersection connected"<<endl;
//    
//    for(int i = 0; i < test.size(); i++){
//        cout << " " << test[i] << endl;
//    }
//    cout << endl;
//    
//    for(int j = 0; j < test.size();j++){
//        cout << "for Street segment ID " << test[j] << ", it";
//        StreetSegmentInfo testInfo = getStreetSegmentInfo(test[j]);
//        cout << " from intersection "<< testInfo.from <<" to intersection " << testInfo.to << endl;
//        
//        if(are_directly_connected(testInfo.from, testInfo.to)){
//            cout << testInfo.from << " and " << testInfo.to << " are directly connected intersections"<< endl;
//        }    
//    }
//    
//    if(are_directly_connected(666, 6666)){
//        cout << "directly connected intersections"<< endl;
//    }else{
//        cout << "666 and 6666 are not directly connected intersections " << endl;
//    }
//    cout << endl;
}





//Returns all intersections reachable by traveling down one street segment 
//from given intersection (hint: you can't travel the wrong way on a 1-way street)
//the returned vector should NOT contain duplicate intersections
std::vector<unsigned> find_adjacent_intersections(unsigned intersection_id){
    std::vector<unsigned> adjIDList;
    
    vector<unsigned>SSIDList =  find_intersection_street_segments(intersection_id);
    for(unsigned i = 0; i < SSIDList.size(); i++){
        StreetSegmentInfo temp = getStreetSegmentInfo(SSIDList[i]);
        
        if(temp.oneWay){//if is one way street segment
            if(temp.from == intersection_id){//put the destination into the list
                adjIDList.push_back(temp.to);
            }
        }else{//if is not one way
            if(temp.from == intersection_id){//put the destination into the list
                adjIDList.push_back(temp.to);
            }
            if(temp.to == intersection_id){//put the destination into the list
                adjIDList.push_back(temp.from);
            }
        }
    }
    
    //sort the adjIDList first then erase the duplicate
    
    sort(adjIDList.begin(), adjIDList.end()  );
    adjIDList.erase(  unique( adjIDList.begin(), adjIDList.end() ), adjIDList.end()  );
    
    
    return adjIDList;
    
//        //below are testing code which should be used  in test main
//    cout << "This is a test using intersection ID 66" <<endl;
//    string intersection_name = getIntersectionName(66);
//    cout << "Intersection name is " << intersection_name << endl;
//    std::vector<unsigned> test = find_intersection_street_segments(66);
//    cout << "the following ID are the street segment ID that this intersection connected"<<endl;
//    
//    for(int i = 0; i < test.size(); i++){
//        cout << " " << test[i] << endl;
//    }
//    cout << endl;
//    
//    for(int j = 0; j < test.size();j++){
//        cout << "for Street segment ID " << test[j] << ", it";
//        StreetSegmentInfo testInfo = getStreetSegmentInfo(test[j]);
//        cout << " from intersection "<< testInfo.from <<" to intersection " << testInfo.to << endl;
//    }
//    cout << endl;
//    cout <<" the following are the adjacent intersections' IDs of intersection 66 " <<endl;
//    vector<unsigned> adjIDList = find_adjacent_intersections(66);
//    for(int i = 0; i< adjIDList.size(); i++){
//        cout << adjIDList[i]<<endl;
//    }
//    cout << endl;
    
}







//Returns all street segments for the given street
std::vector<unsigned> find_street_street_segments(unsigned street_id){
    std::vector<unsigned> SSList;
    
    
    unsigned totalSSNum = getNumberOfStreetSegments();
    
    for(unsigned i = 0; i < totalSSNum; i++){
        StreetSegmentInfo temp = getStreetSegmentInfo(i);
        if(temp.streetID == street_id){//SS is belong to the street specified
            SSList.push_back(i);
        }
    }
    return SSList;
    
//    //below are testing code which should be used  in test main
//    string test1= getStreetName(14);
//    cout << "test1   is  "<< test1<< endl;
//    std::vector<unsigned> test;
//    test =  find_street_ids_from_name(test1);
//    for(int i = 0; i < test.size(); i++){
//        cout << " " << test[i] << endl;
//    }
//    vector<unsigned> SSList = find_street_street_segments(14);
//    for(unsigned i = 0 ; i < SSList.size(); i++){
//        cout << "SS ID is " << SSList[i]<< endl;
//    }
//    cout << endl;
}




//Returns all intersections along the a given street
std::vector<unsigned> find_all_street_intersections(unsigned street_id){
    std::vector<unsigned> interList;
    
    //this is the list of all the street segment of a given street
    vector<unsigned> SSList = find_street_street_segments(street_id);
    for(unsigned i = 0; i< SSList.size(); i++){
        StreetSegmentInfo temp = getStreetSegmentInfo(SSList[i]);
        interList.push_back(temp.from);
        interList.push_back(temp.to);     
    }
    
    //sort the interList first then erase the duplicate
    sort(  interList.begin(), interList.end()  );
    interList.erase(  unique( interList.begin(), interList.end() ), interList.end()  );
    
 
    return interList;
    
//    //below are testing code which should be used  in test main
//    string test1= getStreetName(14);
//    cout << "test1   is  "<< test1<< endl;
//    std::vector<unsigned> test;
//    test =  find_street_ids_from_name(test1);
//    for(int i = 0; i < test.size(); i++){
//        cout << " " << test[i] << endl;
//    }
//    vector<unsigned> interList = find_all_street_intersections(14);
//    for(unsigned i = 0 ; i < interList.size(); i++){
//        cout << "intersection ID is " << interList[i]<< endl;
//    }
//    cout << endl;

}



//Return all intersection ids for two intersecting streets
//This function will typically return one intersection id.
//However street names are not guarenteed to be unique, so more than 1 intersection id
//may exist
std::vector<unsigned> find_intersection_ids_from_street_names(std::string street_name1, 
                                                              std::string street_name2){
    std::vector<unsigned> interList;
    
    // it looks like we have a probelm here
    vector<unsigned> find_all_street_intersections(unsigned street_id)
    
    
    
    
    return interList;
}

//Returns the distance between two coordinates in meters
double find_distance_between_two_points(LatLon point1, LatLon point2){
    double distance=0.0;
    double avgLat=(point1.lat()+point2.lat())/2*DEG_TO_RAD;
    double lan1=point1.lat()*DEG_TO_RAD,
           lon1=point1.lon()*DEG_TO_RAD,
           lan2=point2.lat()*DEG_TO_RAD,
           lon2=point2.lon()*DEG_TO_RAD;
    double x1=lon1*cos(avgLat),
            y1=lan1;
    double x2=lon2*cos(avgLat),
            y2=lan2;
    double diffx=x1-x2;
    double diffy=y1-y2;
    distance=sqrt(diffx*diffx+diffy*diffy)*EARTH_RADIUS_IN_METERS;
    return distance;
    
    //below are testing code which should be used  in test main
    //need to include the LatLon.h
//    #include <LatLon.h>
//    double lan1=6.78,lon1=9.56;
//    double lan2=6.78,lon2=10.66;
//    cout<<"test case: first position: ("<<lan1<<","<<lon1<<") Second position: ("<<lan2<<","<<lon2<<")."<<endl;
//    LatLon a(lan1,lon1);
//    LatLon b(lan2,lon2);
//    double distance=find_distance_between_two_points(a,b);
//    cout<<"distance between two points is: "<<distance<<endl;
}

//Returns the length of the given street segment in meters
double find_street_segment_length(unsigned street_segment_id){     
    StreetSegmentInfo street_segment = getStreetSegmentInfo(street_segment_id);
    LatLon point1 = getIntersectionPosition(street_segment.from);
    LatLon point2 = getIntersectionPosition(street_segment.to);
    double distance=0.0;
    if(street_segment.curvePointCount==0){
        //if there is no curves
        distance = find_distance_between_two_points(point1, point2);
        return distance;
    }else{ 
        //if there is curve in the street segment
        int num = street_segment.curvePointCount;
        LatLon temp1=point1,temp2;
        for(unsigned int i=1; i<=num; i++){
            temp2 = getStreetSegmentCurvePoint(street_segment_id,i-1);
            distance+=find_distance_between_two_points(temp1, temp2);
            temp1=temp2;
        }
        distance+=find_distance_between_two_points(point2,temp2);
    }
    return distance;
}

//Returns the length of the specified street in meters
double find_street_length(unsigned street_id){
    
    
    return 0.0;
}

//Returns the travel time to drive a street segment in seconds 
//(time = distance/speed_limit)
double find_street_segment_travel_time(unsigned street_segment_id){
    //not sure it is correct or not
    double distance=find_street_segment_length(street_segment_id);
    StreetSegmentInfo street =getStreetSegmentInfo(street_segment_id);
    double speedLimit=street.speedLimit;
    double time = distance/speedLimit;
    return time;
    return 0.0;
}

//Returns the nearest point of interest to the given position
unsigned find_closest_point_of_interest(LatLon my_position){
    return 1;
}

//Returns the the nearest intersection to the given position
unsigned find_closest_intersection(LatLon my_position){
    return 1;
}
