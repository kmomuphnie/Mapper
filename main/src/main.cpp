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
#include <iostream>
#include <string>
#include <StreetsDatabaseAPI.h>
#include "m1.h"
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <LatLon.h>

using namespace std;
//Program exit codes
constexpr int SUCCESS_EXIT_CODE = 0;        //Everyting went OK
constexpr int ERROR_EXIT_CODE = 1;          //An error occured
constexpr int BAD_ARGUMENTS_EXIT_CODE = 2;  //Invalid command-line usage

//The default map to load if none is specified
std::string default_map_path = "/cad2/ece297s/public/maps/toronto_canada.streets.bin";

int main(int argc, char** argv) {

    std::string map_path;
    if(argc == 1) {
        //Use a default map
        map_path = default_map_path;
    } else if (argc == 2) {
        //Get the map from the command line
        map_path = argv[1];
    } else {
        //Invalid arguments
        std::cerr << "Usage: " << argv[0] << " [map_file_path]\n";
        std::cerr << "  If no map_file_path is provided a default map is loaded.\n";
        return BAD_ARGUMENTS_EXIT_CODE;
    }
  
    //Load the map and related data structures
    bool load_success = load_map(map_path);
    if(!load_success) {
        std::cerr << "Failed to load map '" << map_path << endl;
        return ERROR_EXIT_CODE;
    }

    std::cout << "Successfully loaded map '" << map_path << endl;

    
    
    
    
    
    //You can now do something with the map data
    
  
     
    //first is to set up the MBR(minimum Boundary rectange)
    //find the boundary values
//    LatLon initial = getIntersectionPosition(0);
//    float northBound = initial.lat();
//    float southBound = initial.lat();
//    float westBound  = initial.lon();
//    float eastBound  = initial.lon();
//    for(unsigned i = 1; i < getNumberOfIntersections() ; i++){
//        LatLon temp = getIntersectionPosition(i);
//        if (temp.lat() > northBound){
//            northBound = temp.lat();
//        }
//        if (temp.lat() < southBound){
//            southBound = temp.lat();
//        }
//        if (temp.lon() > eastBound){
//            eastBound = temp.lon();
//        }
//        if (temp.lon() < westBound){
//            westBound = temp.lon();
//        }
//    }
  
    //vector<LatLon> interLatLonList;
//    for(unsigned i = 0; i < getNumberOfIntersections(); i++){
//        interLatLonList.push_back(getIntersectionPosition(i));
//    }
    //vector<unsigned> AREA[50][100];//matrix 50x100, 5000 sub areas. each is a vector contains the ID of points within that area
//    double latDelta = (northBound - southBound)/50;
//    double lonDelta = (eastBound - westBound)/100;
//    //the following is to built up the map. ie, stores point in the area.
//    for(unsigned i = 0; i < getNumberOfIntersections(); i++){
//        LatLon temp = getIntersectionPosition(i);
//        int rowIndex = (temp.lat() - southBound) / latDelta;
//        int colIndex = (temp.lon() - westBound ) / lonDelta;
//        AREA[rowIndex][colIndex].push_back(i);//store the ID of intersection into the sub area vector.
//    }
//    
//    
//    cout << "the northBound is : " << northBound << endl;
//    cout << "the southBound is : " << southBound << endl;
//    cout << "the eastBound is  : " << eastBound  << endl;
//    cout << "the westBound is  : " << westBound  << endl;   
//    cout << "total number of intersections : "<< getNumberOfIntersections() << endl;
//    cout << "intersection lag and lon example " << getIntersectionPosition(100).lat() << " and " << getIntersectionPosition(100).lon() << endl;
//    cout << "latDelta is " << latDelta << endl;
//    cout << "lonDelta is " << lonDelta << endl;
//    for(int i = 0; i < AREA[28][53].size(); i++){
//        cout << AREA[28][53][i] << endl;
//    }
    
    

            
            
    
    
    
    
    //Clean-up the map data and related data structures
    close_map(); 

    return SUCCESS_EXIT_CODE;
}
