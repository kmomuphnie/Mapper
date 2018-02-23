/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "graphics.h"
#include "m2.h"
#include "map_data.h"
#include <string.h>
#include <vector>
#include "StreetsDatabaseAPI.h"
#include <math.h>

#define AREA_THRESHOLD9 3000
#define AREA_THRESHOLD8 4000
#define AREA_THRESHOLD7 8000
#define AREA_THRESHOLD6 11000
#define AREA_THRESHOLD5 20000
#define AREA_THRESHOLD4 30000
#define AREA_THRESHOLD3 45000
#define AREA_THRESHOLD2 60000
#define AREA_THRESHOLD1 550000
#include "m1.h"
using namespace std;

// got datastructure from m1
extern map_data const* my_map;

bool mouseclick = false;
bool show_find_box = false;
bool start_find = false;
bool enable_draw_start_find = false;
double mousex;
double mousey;
double findx;
double findy;

double mapdistance; 
unsigned zoomLevel;
string find_string = "";
string found_information = "";
vector<unsigned> highlight_found_Intersection;

void draw_screen();
void draw_one_way_sign (feature_data current);
void draw_street_segment_names(draw_street_segments_data current, string type, unsigned current_zoomLevel);
void draw_street_names();

//keyboard input function
void act_on_key_press(char key_pressed, int keysym);
void act_on_button_press(float x, float y, t_event_buttonPressed event);
void find_by_street_names(void (*drawscreen_ptr) (void));
void draw_subway();

void find_by_street_names(void (*drawscreen_ptr) (void)); //void (*drawscreen_ptr) (void)
void draw_find_box();
void find_intersection_from_input();
void draw_found_intersection();

string globalName1;
string globalName2;


void act_on_key_press(char key_pressed, int keysym) {
    // function to handle keyboard press event, the ASCII character is returned
    // along with an extended code (keysym) on X11 to represent non-ASCII
    // characters like the arrow keys.

    std::cout << "Key press: char is " << key_pressed << std::endl;
    draw_screen();
    
    
    
#ifdef X11 // Extended keyboard codes only supported for X11 for now
    // see more information in keysymdef.h !!!!!!!!!
    switch (keysym) {
        case XK_Left:
            start_find = false;
            std::cout << "Left Arrow" << std::endl;
            break;
        case XK_Right:
            start_find = false;
            std::cout << "Right Arrow" << std::endl;
            break;
        case XK_Up:
            start_find = false;
            std::cout << "Up Arrow" << std::endl;
            break;
        case XK_Down:
            start_find = false;
            std::cout << "Down Arrow" << std::endl;
            break;
        case XK_BackSpace:
            start_find = false;
            find_string = find_string.substr(0, find_string.length()-1);
            break;
        case XK_Shift_L:
            start_find = false;
            break;
        case XK_Return:
            start_find = true;
            if(start_find&&show_find_box)
                draw_found_intersection();
            find_string="";
            break;
        default:
            std::cout << "keysym (extended code) is " << keysym << std::endl;
            find_string += key_pressed;
            break;
    }
    
    globalName1.push_back(key_pressed);
    draw_screen();
#endif   
}
void act_on_button_press(float x, float y, t_event_buttonPressed event) {

    /* Called whenever event_loop gets a button press in the graphics *
     * area.  Allows the user to do whatever he/she wants with button *
     * clicks.                                                        */
    mouseclick = true;
//    mousex = x;
//    mousey = y;
    LatLon mouselatlon(y/DEG_TO_RAD,x/cos(my_map->get_avg_lat())/DEG_TO_RAD);
    unsigned closeintersectionID = find_closest_intersection(mouselatlon);
    mousex =  getIntersectionPosition(closeintersectionID).lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD;
    mousey =  getIntersectionPosition(closeintersectionID).lat()*DEG_TO_RAD;     
            
    cout<<event.button<<endl;
    draw_screen();
    
//    LatLon mouseclicklatlon(x/cos(my_map->get_avg_lat())/DEG_TO_RAD,y);
//    unsigned closestintersectionID = my_map->closest_intersection_point(mouseclicklatlon);
//    setcolor(t_color(255,55,0,255));
//    fillarc(my_map->get_intersections_longitude_cartesian_intersectionsID(closestintersectionID), 
//            my_map->get_intersections_latitude_cartesian_intersectionsID(closestintersectionID), 
//            mapdistance*(1/20),0,360);
    
//    std::cout << "User clicked a mouse button at coordinates ("
//            << x << "," << y << ")";
//    if (event.shift_pressed || event.ctrl_pressed) {
//        std::cout << " with ";
//        if (event.shift_pressed) {
//            std::cout << "shift ";
//            if (event.ctrl_pressed)
//                std::cout << "and ";
//        }
//        if (event.ctrl_pressed)
//            std::cout << "control ";
//        std::cout << "pressed.";
//    }
//    std::cout << std::endl;

//    if (line_entering_demo) {
//        line_pts.push_back(t_point(x, y));
//        have_rubber_line = false;
//
//        // Redraw screen to show the new line.  Could do incrementally, but this is easier.
//        drawscreen();
//    }
}

void draw_find_box(){
    double dimensionX = get_visible_world().top_right().x;
    double dimensionY = get_visible_world().bottom_left().y;
    double height = get_visible_world().get_height();
    double width = get_visible_world().get_width();
    setcolor(WHITE);
    fillrect(dimensionX-width*0.30, dimensionY, dimensionX, dimensionY+height*0.03);
    t_bound_box createFind (dimensionX-width*0.30, dimensionY, dimensionX, dimensionY+height*0.03);
    setcolor(DARKGREY);
    setlinewidth(7);
    setfontsize(10);
    settextrotation(0);
    drawtext_in(createFind, find_string);
    return;
}

void find_intersection_from_input(){
    //cout<<find_string<<endl;
    unsigned start = 0;
    while(find_string.at(start) == ' ')
        find_string.erase(start,1);
    
    size_t andIndex = find_string.find('&');
    if (andIndex == -1)
        return;
    
    andIndex -= 1;
    while ((find_string.at(andIndex)==' ')) {
        find_string.erase(andIndex,1);
        andIndex -=1;        
    }
    
    andIndex = find_string.find('&');
    andIndex +=1;
    while ((find_string.at(andIndex)==' ')&&(andIndex < find_string.length())) { 
        find_string.erase(andIndex,1);
    }
    cout<<find_string<<endl;
    andIndex = find_string.find('&');
    string firstStreet = find_string.substr(0,andIndex);
    string secondStreet = find_string.substr(andIndex+1,find_string.length()-andIndex-1);
    found_information = firstStreet + " & " + secondStreet;
    highlight_found_Intersection = find_intersection_ids_from_street_names(firstStreet, secondStreet);
    return;
}

void draw_found_intersection(){
    find_intersection_from_input();
    if (highlight_found_Intersection.size()==0){
        cout<<"No intersection found!"<<endl;
        enable_draw_start_find = false;
    }else{
        enable_draw_start_find = true;
//        setcolor(t_color(255, 55, 0, 255));
//        for(unsigned i =0; i< highlight_found_Intersection.size(); i++){
//            findx =  getIntersectionPosition(highlight_found_Intersection[i]).lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD;
//            findy =  getIntersectionPosition(highlight_found_Intersection[i]).lat()*DEG_TO_RAD;
//            if ((sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 300) > 0.0000004) {
//                fillarc(findx, findy, sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 300, 0, 360);
//            } else {
//                fillarc(findx, findy,0.0000004, 0, 360);
//            }
//        }
//        draw_find_box();
    }
    draw_screen();
    return;
}

void find_by_street_names(void (*drawscreen_ptr) (void)){
    find_string = "";
    if(show_find_box){
        show_find_box = false;
        found_information = "";
        enable_draw_start_find = false;
    }else
        show_find_box = true;
    
    if(show_find_box)
        draw_find_box();
    
    drawscreen_ptr();
 return;  
}

void start_search(void (*drawscreen_ptr) (void)){
    bool turn_on = true;
    bool turn_off = false;
    set_keypress_input(turn_on);
    //clear the string
    globalName1.clear();
    
    
    
    
    
    return;
}




void draw_map(){
    // it would gives title to our map in the map windows
    init_graphics("Some Map",t_color(243,242,242,255));
    
    // it would give a range to our map in that windows
    set_visible_world(my_map->get_min_lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD,my_map->get_min_lat()*DEG_TO_RAD,my_map->get_max_lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD,my_map->get_max_lat()*DEG_TO_RAD);
    
    set_drawing_buffer(OFF_SCREEN);
    
    create_button("Window", "Search", start_search);
    create_button("Search", "Find", find_by_street_names);
    create_button("Find", "Subway", NULL);
    // enable keyboard input
    set_keypress_input(false);
    // this is a loop that would continue check mouse and keyboard then draw something onto the map windows
    event_loop(act_on_button_press,nullptr,act_on_key_press,draw_screen);
    

    // close the map window
    close_graphics();
}

void draw_screen() {
    // have to clean up the screen before draw the new thing
    
    clearscreen();
    //draw intersection point to the map
    unsigned tempNUMintersections = getNumberOfIntersections(); 
    
    double diffx=get_visible_world().bottom_left().x-get_visible_world().top_right().x;
    double diffy=get_visible_world().bottom_left().y-get_visible_world().top_right().y;
    mapdistance = sqrt(diffx*diffx+diffy*diffy)*EARTH_RADIUS_IN_METERS; 
    if(mapdistance > AREA_THRESHOLD1)
        zoomLevel = 1;
    else if (mapdistance > AREA_THRESHOLD2)
        zoomLevel = 2;
    else if (mapdistance > AREA_THRESHOLD3)
        zoomLevel = 3;
    else if (mapdistance > AREA_THRESHOLD4)
        zoomLevel = 4;
    else if (mapdistance > AREA_THRESHOLD5)
        zoomLevel = 5;
    else if (mapdistance > AREA_THRESHOLD6)
        zoomLevel = 6;
    else if (mapdistance > AREA_THRESHOLD7)
        zoomLevel = 7;
    else if (mapdistance > AREA_THRESHOLD8)
        zoomLevel = 8;
    else
        zoomLevel = 9;
    
    
    
 
    //draw lakes
    auto templakestemps = my_map->get_lakes_data();
    for (unsigned i = 0; i < templakestemps.size(); i++) {
        setcolor(t_color(170, 218, 253, 255));
        if (templakestemps[i].openfeature) {
            setlinewidth(0.5);
            for (unsigned j = 0; j < templakestemps[i].npoints - 1; j++) {
                drawline(templakestemps[i].point[j].x, templakestemps[i].point[j].y, templakestemps[i].point[j + 1].x, templakestemps[i].point[j + 1].y);
                //fillpoly(temprivertemps[i].point,temprivertemps[i].npoints);
            }
        } else {
            fillpoly(templakestemps[i].point, templakestemps[i].npoints);
        }
    }
    
    //draw islands
    auto tempislandstemps = my_map->get_islands_data();
    for (unsigned i = 0;i < tempislandstemps.size();i++) {
        setcolor(t_color(220,220,220,255));
        if (tempislandstemps[i].openfeature) {
            setlinewidth(0.5);
            for (unsigned j = 0; j < tempislandstemps[i].npoints - 1; j++) {
                drawline(tempislandstemps[i].point[j].x, tempislandstemps[i].point[j].y, tempislandstemps[i].point[j + 1].x, tempislandstemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(tempislandstemps[i].point, tempislandstemps[i].npoints);
        }
    }
    
    //draw parks
    auto tempparktemps = my_map->get_parks_data();
    for (unsigned i = 0;i < tempparktemps.size();i++) {
        //setcolor(t_color(199,233,192,255));
        setcolor(t_color(193,236,178,255));
        if (tempparktemps[i].openfeature) {
            setlinewidth(0.5);
            for (unsigned j = 0; j < tempparktemps[i].npoints - 1; j++) {
                drawline(tempparktemps[i].point[j].x, tempparktemps[i].point[j].y, tempparktemps[i].point[j + 1].x, tempparktemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(tempparktemps[i].point, tempparktemps[i].npoints);
        }
    }  
    
    //draw greenspaces
    auto tempgreenspacetemps = my_map->get_greenspaces_data();
    for (unsigned i = 0;i < tempgreenspacetemps.size();i++) {
        setcolor(t_color(228,244,229,255));
        if (tempgreenspacetemps[i].openfeature) {
            setlinewidth(0.5);
            for (unsigned j = 0; j < tempgreenspacetemps[i].npoints - 1; j++) {
                drawline(tempgreenspacetemps[i].point[j].x, tempgreenspacetemps[i].point[j].y, tempgreenspacetemps[i].point[j + 1].x, tempgreenspacetemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(tempgreenspacetemps[i].point, tempgreenspacetemps[i].npoints);
        }
    }
    
    //draw beachs
    auto tempbeachstemps = my_map->get_beachs_data();
    for (unsigned i = 0;i < tempbeachstemps.size();i++) {
        setcolor(t_color(250,242,202,255));
        if (tempbeachstemps[i].openfeature) {
            setlinewidth(0.5);
            for (unsigned j = 0; j < tempbeachstemps[i].npoints - 1; j++) {
                drawline(tempbeachstemps[i].point[j].x, tempbeachstemps[i].point[j].y, tempbeachstemps[i].point[j + 1].x, tempbeachstemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(tempbeachstemps[i].point, tempbeachstemps[i].npoints);
        }
    }
    
    //draw golfcourses
    auto tempgolfcoursetemps = my_map->get_golfcourses_data();
    for (unsigned i = 0;i < tempgolfcoursetemps.size();i++) {
        setcolor(t_color(191,218,189,255));
        if (tempgolfcoursetemps[i].openfeature) {
            setlinewidth(0.5);
            for (unsigned j = 0; j < tempgolfcoursetemps[i].npoints - 1; j++) {
                drawline(tempgolfcoursetemps[i].point[j].x, tempgolfcoursetemps[i].point[j].y, tempgolfcoursetemps[i].point[j + 1].x, tempgolfcoursetemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(tempgolfcoursetemps[i].point, tempgolfcoursetemps[i].npoints);
        }
    }
    
    //draw rivers
    auto temprivertemps = my_map->get_rivers_data();
    for (unsigned i = 0;i < temprivertemps.size();i++) {
        setcolor(t_color(170,218,253,255));
        if (temprivertemps[i].openfeature) {
            setlinewidth(2);
            for (unsigned j = 0; j < temprivertemps[i].npoints - 1; j++) {
                drawline(temprivertemps[i].point[j].x, temprivertemps[i].point[j].y, temprivertemps[i].point[j + 1].x, temprivertemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(temprivertemps[i].point, temprivertemps[i].npoints);
        }
    }
      
    
    
    //draw shorelines
    auto shorelines = my_map->get_shorelines_data();
    for (unsigned i = 0;i < shorelines.size();i++) {
        setcolor(t_color(0,0,0,255));
        if (shorelines[i].openfeature) {
            setlinewidth(1);
            for (unsigned j = 0; j < shorelines[i].npoints - 1; j++) {
                drawline(shorelines[i].point[j].x, shorelines[i].point[j].y, shorelines[i].point[j + 1].x, shorelines[i].point[j + 1].y);
            }
        } else {
            fillpoly(shorelines[i].point, shorelines[i].npoints);
        }
    }
    
    //draw streams
    if (mapdistance < AREA_THRESHOLD8) {
        auto streams = my_map->get_streams_data();
        for (unsigned i = 0; i < streams.size(); i++) {
            setcolor(t_color(170, 218, 253, 255));
            if (streams[i].openfeature) {
                setlinewidth(0.0000001);
                for (unsigned j = 0; j < streams[i].npoints - 1; j++) {
                    drawline(streams[i].point[j].x, streams[i].point[j].y, streams[i].point[j + 1].x, streams[i].point[j + 1].y);
                }
            } else {
                fillpoly(streams[i].point, streams[i].npoints);
            }
        }
    }
    if (mapdistance < AREA_THRESHOLD9) {
        //draw buildings
        auto tempbuildingtemps = my_map->get_buildings_data();
        for (unsigned i = 0; i < tempbuildingtemps.size(); i++) {
            setcolor(t_color(255, 226, 197, 255));
            if (tempbuildingtemps[i].openfeature) {
                setlinewidth(0.0000001);
                for (unsigned j = 0; j < tempbuildingtemps[i].npoints - 1; j++) {
                    drawline(tempbuildingtemps[i].point[j].x, tempbuildingtemps[i].point[j].y, tempbuildingtemps[i].point[j + 1].x, tempbuildingtemps[i].point[j + 1].y);
                }
            } else {
                fillpoly(tempbuildingtemps[i].point, tempbuildingtemps[i].npoints);
            }
        }
    }
    
//    //draw Lspeed
//    auto Lspeed = my_map->get_Lspeed_data();
//    for (unsigned i = 0;i < Lspeed.size();i++) {
//        setcolor(t_color(255,255,255,255));
//        setlinewidth(0.5);
//        for(unsigned j = 0;j<Lspeed[i].npoints - 1;j++){
//            drawline(Lspeed[i].point[j].x,Lspeed[i].point[j].y,Lspeed[i].point[j+1].x,Lspeed[i].point[j+1].y);
//        }
//    } 
//    //draw Mspeed
//    auto Mspeed = my_map->get_Mspeed_data();
//    for (unsigned i = 0;i < Mspeed.size();i++) {
//        setcolor(t_color(255,255,255,255));
//        setlinewidth(2);
//        for(unsigned j = 0;j<Mspeed[i].npoints - 1;j++){
//            drawline(Mspeed[i].point[j].x,Mspeed[i].point[j].y,Mspeed[i].point[j+1].x,Mspeed[i].point[j+1].y);
//        }
//    } 
//    //draw Hspeed
//    auto Hspeed = my_map->get_Hspeed_data();
//    for (unsigned i = 0;i < Hspeed.size();i++) {
//        setcolor(t_color(255,235,167,255));
//        setlinewidth(4);
//        for(unsigned j = 0;j<Hspeed[i].npoints - 1;j++){
//            drawline(Hspeed[i].point[j].x,Hspeed[i].point[j].y,Hspeed[i].point[j+1].x,Hspeed[i].point[j+1].y);
//        }
//    } 
    //draw otherhighway & otherway
    if (mapdistance < AREA_THRESHOLD8) {
        auto otherhighway = my_map->get_otherhighway_data();
        for (unsigned i = 0; i < otherhighway.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < otherhighway[i].npoints - 1; j++) {
                drawline(otherhighway[i].point[j].x, otherhighway[i].point[j].y, otherhighway[i].point[j + 1].x, otherhighway[i].point[j + 1].y);
                draw_one_way_sign(otherhighway[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if(j==(otherhighway[i].npoints-1)/2){
//                    draw_street_segment_names(otherhighway[i].drawInfo,"otherhighway",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                }
            }
        }
        auto otherway = my_map->get_otherway_data();
        for (unsigned i = 0; i < otherway.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < otherway[i].npoints - 1; j++) {
                drawline(otherway[i].point[j].x, otherway[i].point[j].y, otherway[i].point[j + 1].x, otherway[i].point[j + 1].y);
                draw_one_way_sign(otherway[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if(j==(otherhighway[i].npoints-1)/2){
//                    draw_street_segment_names(otherhighway[i].drawInfo,"otherhighway",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                }
            }
        }
    }
    //draw service
    if (mapdistance < AREA_THRESHOLD7) {
        auto service = my_map->get_service_data();
        for (unsigned i = 0; i < service.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < service[i].npoints - 1; j++) {
                drawline(service[i].point[j].x, service[i].point[j].y, service[i].point[j + 1].x, service[i].point[j + 1].y);
                draw_one_way_sign(service[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if (j==(service[i].npoints-1)/2){
//                    draw_street_segment_names(service[i].drawInfo,"service",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                }
            }
        }
    }
    //draw residential
    if (mapdistance < AREA_THRESHOLD6) {
        auto residential = my_map->get_residential_data();
        for (unsigned i = 0; i < residential.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < residential[i].npoints - 1; j++) {
                drawline(residential[i].point[j].x, residential[i].point[j].y, residential[i].point[j + 1].x, residential[i].point[j + 1].y);
                draw_one_way_sign(residential[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if (j==(residential[i].npoints-1)/2){
//                    draw_street_segment_names(residential[i].drawInfo,"residential",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                }
            }
        }
    }
    //draw unclassified
    if (mapdistance < AREA_THRESHOLD5) {
        auto unclassified = my_map->get_unclassified_data();
        for (unsigned i = 0; i < unclassified.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < unclassified[i].npoints - 1; j++) {
                drawline(unclassified[i].point[j].x, unclassified[i].point[j].y, unclassified[i].point[j + 1].x, unclassified[i].point[j + 1].y);
                draw_one_way_sign(unclassified[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                 if (j==(unclassified[i].npoints-1)/2){
//                    draw_street_segment_names(unclassified[i].drawInfo,"unclassified",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                 }  
            }
        }
    }
    //draw tertiary
    if (mapdistance < AREA_THRESHOLD4) {
        auto tertiary = my_map->get_tertiary_data();
        for (unsigned i = 0; i < tertiary.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < tertiary[i].npoints - 1; j++) {
                drawline(tertiary[i].point[j].x, tertiary[i].point[j].y, tertiary[i].point[j + 1].x, tertiary[i].point[j + 1].y);
                draw_one_way_sign(tertiary[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if (j==(tertiary[i].npoints-1)/2){
//                    draw_street_segment_names(tertiary[i].drawInfo,"tertiary",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                }
            }
        }
    }
    
    if (mapdistance < AREA_THRESHOLD3) {
        //draw secondary
        auto secondary = my_map->get_secondary_data();
        for (unsigned i = 0; i < secondary.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(2);
            for (unsigned j = 0; j < secondary[i].npoints - 1; j++) {
                drawline(secondary[i].point[j].x, secondary[i].point[j].y, secondary[i].point[j + 1].x, secondary[i].point[j + 1].y);
                draw_one_way_sign(secondary[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if (j==(secondary[i].npoints-1)/2){
//                    draw_street_segment_names(secondary[i].drawInfo,"secondary",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(2);
//                }
            }
        }
    }
    
    if (mapdistance < AREA_THRESHOLD2) {
        //draw primary
        int primary_lineWidth;
        
        if (mapdistance > AREA_THRESHOLD4)
            primary_lineWidth = 8;
        else if (mapdistance > AREA_THRESHOLD6)
            primary_lineWidth = 6;
        else if (mapdistance > AREA_THRESHOLD8)
            primary_lineWidth = 4;
        else
            primary_lineWidth = 2;
        
        auto primary = my_map->get_primary_data();
        for (unsigned i = 0; i < primary.size(); i++) {
            setcolor(t_color(255, 255, 255, 255));
            setlinewidth(primary_lineWidth);
            for (unsigned j = 0; j < primary[i].npoints - 1; j++) {
                drawline(primary[i].point[j].x, primary[i].point[j].y, primary[i].point[j + 1].x, primary[i].point[j + 1].y);
                draw_one_way_sign(primary[i]);
                setcolor(t_color(255, 255, 255, 255));
                setlinewidth(2);
//                if (j==(primary[i].npoints-1)/2){
//                    draw_street_segment_names(primary[i].drawInfo,"primary",zoomLevel);
//                    setcolor(t_color(255, 255, 255, 255));
//                    setlinewidth(primary_lineWidth);
//                }
            }
        }
    }
    if (mapdistance < AREA_THRESHOLD1) {
        //draw trunk
        int trunk_lineWidth;
        if(mapdistance > AREA_THRESHOLD3)
            trunk_lineWidth = 10;
        else if (mapdistance > AREA_THRESHOLD6)
            trunk_lineWidth = 8;
        else 
            trunk_lineWidth = 6;
        
        auto trunk = my_map->get_trunk_data();
        for (unsigned i = 0; i < trunk.size(); i++) {
            setcolor(t_color(255, 235, 167, 255));
            setlinewidth(trunk_lineWidth);
            for (unsigned j = 0; j < trunk[i].npoints - 1; j++) {
                drawline(trunk[i].point[j].x, trunk[i].point[j].y, trunk[i].point[j + 1].x, trunk[i].point[j + 1].y);
                draw_one_way_sign(trunk[i]);
                setcolor(t_color(255, 235, 167, 255));
                setlinewidth(trunk_lineWidth);
//                if ((j==(trunk[i].npoints-1)/2)&&(i%40==0)){
//                    draw_street_segment_names(trunk[i].drawInfo,"trunk",zoomLevel);
//                    setcolor(t_color(255, 235, 167, 255));
//                    setlinewidth(trunk_lineWidth);
//                }
            }
        }
    }
    //draw motorway & intersection
    auto motorway = my_map->get_motorway_data();
    int motor_lineWidth;
        if(mapdistance > AREA_THRESHOLD3)
            motor_lineWidth = 12;
        else if (mapdistance > AREA_THRESHOLD6)
            motor_lineWidth = 10;
        else 
            motor_lineWidth = 8;
        
    for (unsigned i = 0; i < motorway.size(); i++) {
        setcolor(t_color(255, 235, 167, 255));
        setlinewidth(motor_lineWidth);
        for (unsigned j = 0; j < motorway[i].npoints - 1; j++) {
            drawline(motorway[i].point[j].x, motorway[i].point[j].y, motorway[i].point[j + 1].x, motorway[i].point[j + 1].y);
            draw_one_way_sign(motorway[i]);
            setcolor(t_color(255, 235, 167, 255));
            setlinewidth(motor_lineWidth);
//            if ((j==(motorway[i].npoints-1)/2)&&(i%40==0)){
//                draw_street_segment_names(motorway[i].drawInfo,"motorway",zoomLevel);
//                setcolor(t_color(255, 235, 167, 255));
//                setlinewidth(motor_lineWidth);
//            }
        }
    }
    
    auto motowayintersection = my_map->get_motorway_intersection_data();
    for (unsigned i = 0;i<motowayintersection.size();i++) {
        double x = motowayintersection[i].longitude_cartesian;
        double y = motowayintersection[i].latitude_cartesian;
        setcolor(t_color(254, 159, 109, 255));
        if ((sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 800) > 0.0000004) {
            fillarc(x, y, sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 800, 0, 360);
        } else {
            fillarc(x, y, 0.0000004, 0, 360);
        }
        //fillarc(x, y, 0.0000005, 0, 360);
    }
    setcolor(t_color(255, 255, 255, 255));
    setfontsize(10);
    settextrotation(111);
    //void drawtext(float xc, float yc, const std::string& text, float boundx=FLT_MAX, float boundy=FLT_MAX);
//    // draw intersection
//    for (unsigned i = 0; i < tempNUMintersections; ++i) {
//        double x = my_map->get_intersections_longitude_cartesian_intersectionsID(i);
//        double y = my_map->get_intersections_latitude_cartesian_intersectionsID(i);
////        float const width = 0.000001;
////        float const height = 0.000001;
//        setcolor(t_color(254, 159, 109, 255));
//        fillarc(x, y, 0.0000005, 0, 360);
//        //fillrect(x, y, x + width, y + height);
//        //fillarc(my_map->get_intersections_longitude_cartesian_intersectionsID(i), my_map->get_intersections_latitude_cartesian_intersectionsID(i), 0.00001, 0,360);
//    }
    
    draw_street_names();
   
    // draw mouse
    if (mouseclick) {
        setcolor(t_color(255, 55, 0, 255));
        if ((sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 300) > 0.0000004) {
            fillarc(mousex, mousey, sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 300, 0, 360);
        } else {
            fillarc(mousex, mousey,0.0000004, 0, 360);
        }
    }
     if(show_find_box)
        draw_find_box();
    
     if (enable_draw_start_find){
          setcolor(MAGENTA);
        for(unsigned i =0; i< highlight_found_Intersection.size(); i++){
            findx =  getIntersectionPosition(highlight_found_Intersection[i]).lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD;
            findy =  getIntersectionPosition(highlight_found_Intersection[i]).lat()*DEG_TO_RAD;
            if ((sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 300) > 0.0000004) {
                fillarc(findx, findy, sqrt(get_visible_world().get_height() * get_visible_world().get_height() + get_visible_world().get_width() * get_visible_world().get_width()) / 300, 0, 360);
            } else {
                fillarc(findx, findy,0.0000004, 0, 360);
            }
        }
        double dimensionX = get_visible_world().top_right().x;
        double dimensionY = get_visible_world().bottom_left().y;
        double height = get_visible_world().get_height();
        double width = get_visible_world().get_width();
        setcolor(WHITE);
        fillrect(dimensionX-width*0.30, dimensionY, dimensionX, dimensionY+height*0.03);
        t_bound_box createFind (dimensionX-width*0.30, dimensionY, dimensionX, dimensionY+height*0.03);
        setcolor(FIREBRICK);
        setlinewidth(7);
        setfontsize(10);
        settextrotation(0);
        drawtext_in(createFind,found_information);
     }

    
    
    
    
    
    
    
        //draw search bar
    {
        set_coordinate_system(GL_SCREEN);
        setcolor(t_color(255, 0, 0));
        setlinestyle(SOLID);
        //drawrect (10, 10, 400, 150);
        // Specifying FLT_MAX for the size limits on the text (in world coordinates) so
        // it will always be drawn.
        //drawtext (55, 33, "Screen coord");
        //drawtext (200, 80, "Search");
        draw_surface(load_png_from_file("/homes/c/cuidongf/ece297/work/mapper/libstreetmap/resources/micon.png"), 10, 10);    
        drawtext(150,40, globalName1);
        
        set_coordinate_system(GL_WORLD);
        
    }
    

    copy_off_screen_buffer_to_screen();
    
}

void draw_street_names(){
//    auto motorway = my_map->get_motorway_data();
//    int time = 0;
//    if(zoomLevel >= 1) {
//        for (unsigned i = 0; i < motorway.size(); i++) {
//            for (unsigned j = 0; j < motorway[i].npoints - 1; j++) {
//                if ((j==(motorway[i].npoints-1)/2)&&(time%10==0))
//                    draw_street_segment_names(motorway[i].drawInfo,"motorway",zoomLevel);
//                time++;
//            }
//        }
//    }
//    else if (zoomLevel >= 2 ) {
//        
//    }
//    else if (zoomLevel >= 3) {
//        
//    }
//    else if (zoomLevel >= 4) {
//        
//    }
//    else if (zoomLevel >= 5) {
//        
//    }
//    else if (zoomLevel >= 6) {
//        
//    }
//    else if (zoomLevel >= 7) {
//        
//    }
//    else if (zoomLevel >= 8) {
//        
//    }
//    else{
//        
//    }
//    
//    return;
}

void draw_one_way_sign (feature_data current){
    string oneWaySign = "->";
    setlinewidth(8);
    setcolor(LIGHTSKYBLUE);
    settextattrs(10,current.drawInfo.angle);
//    StreetSegmentInfo temp = getStreetSegmentInfo(current.drawInfo.segmentsID);
//    unsigned fromID = temp.from;
//    unsigned toID = temp.to;
//    LatLon from = getIntersectionPosition(fromID);
//    LatLon to = getIntersectionPosition(toID);
    if(current.oneway == true)
        drawtext(current.drawInfo.location.get_xcenter(),current.drawInfo.location.get_ycenter(),oneWaySign);
    return;
}

void draw_street_segment_names(draw_street_segments_data current, string type, unsigned current_zoomLevel){
//    if (((type == "motorway")||(type == "trunk"))&&(current.draw == true)){
//        if(current_zoomLevel == 0){
//            setcolor(RED);
//            setlinewidth(7);
//            settextattrs(10,current.angle);
//            drawtext(current.location.get_xcenter(),current.location.get_ycenter(),current.name);
//            setlinewidth(1);
//        }else{
//            setcolor(RED);
//            setlinewidth(7);
//            settextattrs(7,current.angle);
//            drawtext(current.location.get_xcenter(),current.location.get_ycenter(),current.name);
//            setlinewidth(1);
//        }
//        
//    }else{
//        setlinewidth(3);
//        if(current.draw == true){
//            setcolor(BLACK);
//            settextattrs(7,current.angle);
//            drawtext(current.location.get_xcenter(),current.location.get_ycenter(),current.name);
//            setlinewidth(1);
//        }
//    }
//    
    
    if ((type == "motorway")||(type == "trunk"))
        setcolor(BLACK);
    else if ((type == "primary")||(type == "secondary"))
        setcolor(MEDIUMPURPLE);
    else 
        setcolor(DARKGREY);
    
    
    if (current_zoomLevel <= 1){
        if ((type == "motorway")||(type == "trunk"))
            settextattrs(4,current.angle);
        else if ((type == "primary")||(type == "secondary"))
            settextattrs(2,current.angle);
        else 
            settextattrs(1,current.angle);
    }else if(current_zoomLevel < 3){
        if ((type == "motorway")||(type == "trunk"))
            settextattrs(12,current.angle);
        else if ((type == "primary")||(type == "secondary"))
            settextattrs(4,current.angle);
        else 
            settextattrs(2,current.angle);
    }else if (current_zoomLevel < 6){
        if ((type == "motorway")||(type == "trunk"))
            settextattrs(10,current.angle);
        else if ((type == "primary")||(type == "secondary"))
            settextattrs(6,current.angle);
        else 
            settextattrs(3,current.angle);
    }else if (current_zoomLevel < 9){
         if ((type == "motorway")||(type == "trunk"))
            settextattrs(8,current.angle);
        else if ((type == "primary")||(type == "secondary"))
            settextattrs(6,current.angle);
        else 
            settextattrs(4,current.angle);
    }        
    
    if(current.draw == true){
         drawtext(current.location.get_xcenter(),current.location.get_ycenter(),current.name);
         setlinewidth(1);
    }
    
    return;
}

void draw_subway(){
    setcolor(RED);
    setlinewidth(6);
    std::vector< std::vector< std::vector<t_point> > > subway = my_map->get_subway_data();
    for (unsigned i = 0;i<subway.size();i++){
        for(unsigned j = 0;j<subway[i].size();j++){
            for(unsigned k = 0;k<subway[i][j].size()-1;k++){
                drawline(subway[i][j][k].x,subway[i][j][k].y,subway[i][j][k+1].x,subway[i][j][k+1].y);
            }
        }
    }
}
