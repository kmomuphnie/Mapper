/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "area.h"

area::area(){
//    AREA.resize(50);
//    for ( int i = 0 ; i < 50 ; i++ ){
//        AREA[i].resize(100);
//    }
//    for ( int i = 0 ; i < 50 ; i++ ){
//        for( int j = 0; j < 100 ; j++){
//            AREA[i][j].push_back(0);
//        }
//    }



    //Load map related data structures here
    for(unsigned i = 0; i < getNumberOfIntersections(); i++){
        interLatLonList.push_back(getIntersectionPosition(i));
    }
    //first is to set up the MBR(minimum Boundary rectangle)
    //find the boundary values
    LatLon initial = getIntersectionPosition(0);
    northBound = initial.lat();
    southBound = initial.lat();
    westBound  = initial.lon();
    eastBound  = initial.lon();
    
    for(unsigned i = 1; i < interLatLonList.size() ; i++){
        LatLon temp = interLatLonList[i];
        if (temp.lat() > northBound){
            northBound = temp.lat();
        }
        if (temp.lat() < southBound){
            southBound = temp.lat();
        }
        if (temp.lon() > eastBound){
            eastBound = temp.lon();
        }
        if (temp.lon() < westBound){
            westBound = temp.lon();
        }
    }
  
    latDelta = (northBound - southBound)/50;
    lonDelta = (eastBound - westBound)/100;
    //the following is to built up the map. ie, stores point in the area.
    
    
    for(unsigned i = 0; i < interLatLonList.size(); i++){
        LatLon temp = interLatLonList[i];
        int rowIndex = (temp.lat() - southBound) / latDelta;
        int colIndex = (temp.lon() - westBound ) / lonDelta;
        
        
        
        
        //comment this fking line and everything works
//        AREA[rowIndex][colIndex].push_back(i);

        
        
        //store the ID of intersection into the sub area vector.
        
    }
    
    

    
    
//    cout << "the northBound is : " << northBound << endl;
//    cout << "the southBound is : " << southBound << endl;
//    cout << "the eastBound is  : " << eastBound  << endl;
//    cout << "the westBound is  : " << westBound  << endl;   
//    cout << "total number of intersections : "<< getNumberOfIntersections() << endl;
//    cout << "intersection lag and lon example " << getIntersectionPosition(100).lat() << " and " << getIntersectionPosition(100).lon() << endl;
//    cout << "latDelta is " << latDelta << endl;
//    cout << "lonDelta is " << lonDelta << endl;
//
//    for(unsigned i = 0; i < AREA[28][53].size(); i++){
//        cout << AREA[28][53][i] << endl;
//    }
//    cout << endl;   
//    for(unsigned i = 0; i < AREA[29][56].size(); i++){
//        cout << AREA[29][56][i] << endl;
//    }
    cout << endl;
}





double area::get_northBound() const{
    return northBound;
}
double area::get_southBound() const{
    return southBound;
}
double area::get_eastBound() const{
    return eastBound;
}
double area::get_westBound() const{
    return westBound;
}
double area::get_latDelta() const{
    return latDelta;
}
double area::get_lonDelta() const{
    return lonDelta;
}
        
vector<LatLon> area::get_InterLatLonList() const{
    return interLatLonList;
}       

vector<unsigned> area::get_AREA(unsigned rowIndex, unsigned colIndex) const{
    
    return AREA[rowIndex][colIndex];
}

