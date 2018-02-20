/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "graphics.h"
#include "m2.h"
#include "map_data.h"
#include "StreetsDatabaseAPI.h"
#include <math.h>
using namespace std;

// got datastructure from m1
extern map_data const* my_map;

void draw_screen();

void draw_map(){
    // it would gives title to our map in the map windows
    init_graphics("Some Map",t_color(243,242,242,255));
    
    // it would give a range to our map in that windows
    set_visible_world(my_map->get_min_lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD,my_map->get_min_lat()*DEG_TO_RAD,my_map->get_max_lon()*cos(my_map->get_avg_lat())*DEG_TO_RAD,my_map->get_max_lat()*DEG_TO_RAD);
    
    // this is a loop that would continue check mouse and keyboard then draw something onto the map windows
    event_loop(nullptr,nullptr,nullptr,draw_screen);
    
    // close the map window
    close_graphics();
}

void draw_screen() {
    // have to clean up the screen before draw the new thing
    clearscreen();
    
    //draw intersection point to the map
//    unsigned tempNUMintersections = getNumberOfIntersections(); 
//    for (unsigned i = 0; i < tempNUMintersections; ++i) {
//        double x = my_map->get_intersections_longitude_cartesian_intersectionsID(i);
//        double y = my_map->get_intersections_latitude_cartesian_intersectionsID(i);
//        float const width = 0.000001;
//        float const height = 0.000001;
//        setcolor(t_color(254,159,109,255));
//        fillrect(x, y, x + width, y + height);
//        //fillarc(my_map->get_intersections_longitude_cartesian_intersectionsID(i), my_map->get_intersections_latitude_cartesian_intersectionsID(i), 0.00001, 0,360);
//    }
    
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
    auto streams = my_map->get_streams_data();
    for (unsigned i = 0;i < streams.size();i++) {
        setcolor(t_color(170,218,253,255));
        if (streams[i].openfeature) {
            setlinewidth(0.0000001);
            for (unsigned j = 0; j < streams[i].npoints - 1; j++) {
                drawline(streams[i].point[j].x, streams[i].point[j].y, streams[i].point[j + 1].x, streams[i].point[j + 1].y);
            }
        } else {
            fillpoly(streams[i].point, streams[i].npoints);
        }
    }    
    
    //draw buildings
    auto tempbuildingtemps = my_map->get_buildings_data();
    for (unsigned i = 0;i < tempbuildingtemps.size();i++) {
        setcolor(t_color(255,226,197,255));
        if (tempbuildingtemps[i].openfeature) {
            setlinewidth(0.0000001);
            for (unsigned j = 0; j < tempbuildingtemps[i].npoints - 1; j++) {
                drawline(tempbuildingtemps[i].point[j].x, tempbuildingtemps[i].point[j].y, tempbuildingtemps[i].point[j + 1].x, tempbuildingtemps[i].point[j + 1].y);
            }
        } else {
            fillpoly(tempbuildingtemps[i].point, tempbuildingtemps[i].npoints);
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
    //draw otherhighway
    auto otherhighway = my_map->get_otherhighway_data();
    for (unsigned i = 0; i < otherhighway.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < otherhighway[i].npoints - 1; j++) {
            drawline(otherhighway[i].point[j].x, otherhighway[i].point[j].y, otherhighway[i].point[j + 1].x, otherhighway[i].point[j + 1].y);
        }
    }
    //draw service
    auto service = my_map->get_service_data();
    for (unsigned i = 0; i < service.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < service[i].npoints - 1; j++) {
            drawline(service[i].point[j].x, service[i].point[j].y, service[i].point[j + 1].x, service[i].point[j + 1].y);
        }
    }
    //draw residential
    auto residential = my_map->get_residential_data();
    for (unsigned i = 0; i < residential.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < residential[i].npoints - 1; j++) {
            drawline(residential[i].point[j].x, residential[i].point[j].y, residential[i].point[j + 1].x, residential[i].point[j + 1].y);
        }
    }
    //draw unclassified
    auto unclassified = my_map->get_unclassified_data();
    for (unsigned i = 0; i < unclassified.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < unclassified[i].npoints - 1; j++) {
            drawline(unclassified[i].point[j].x, unclassified[i].point[j].y, unclassified[i].point[j + 1].x, unclassified[i].point[j + 1].y);
        }
    }
    //draw tertiary
    auto tertiary = my_map->get_tertiary_data();
    for (unsigned i = 0; i < tertiary.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < tertiary[i].npoints - 1; j++) {
            drawline(tertiary[i].point[j].x, tertiary[i].point[j].y, tertiary[i].point[j + 1].x, tertiary[i].point[j + 1].y);
        }
    }
    //draw secondary
    auto secondary = my_map->get_secondary_data();
    for (unsigned i = 0; i < secondary.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < secondary[i].npoints - 1; j++) {
            drawline(secondary[i].point[j].x, secondary[i].point[j].y, secondary[i].point[j + 1].x, secondary[i].point[j + 1].y);
        }
    }
    //draw primary
    auto primary = my_map->get_primary_data();
    for (unsigned i = 0; i < primary.size(); i++) {
        setcolor(t_color(255, 255, 255, 255));
        setlinewidth(2);
        for (unsigned j = 0; j < primary[i].npoints - 1; j++) {
            drawline(primary[i].point[j].x, primary[i].point[j].y, primary[i].point[j + 1].x, primary[i].point[j + 1].y);
        }
    }
    //draw trunk
    auto trunk = my_map->get_trunk_data();
    for (unsigned i = 0; i < trunk.size(); i++) {
        setcolor(t_color(255, 235, 167, 255));
        setlinewidth(4);
        for (unsigned j = 0; j < trunk[i].npoints - 1; j++) {
            drawline(trunk[i].point[j].x, trunk[i].point[j].y, trunk[i].point[j + 1].x, trunk[i].point[j + 1].y);
        }
    }
    //draw motorway
    auto motorway = my_map->get_motorway_data();
    for (unsigned i = 0; i < motorway.size(); i++) {
        setcolor(t_color(255, 235, 167, 255));
        setlinewidth(4);
        for (unsigned j = 0; j < motorway[i].npoints - 1; j++) {
            drawline(motorway[i].point[j].x, motorway[i].point[j].y, motorway[i].point[j + 1].x, motorway[i].point[j + 1].y);
        }
    }
    setcolor(t_color(255, 255, 255, 255));
    setfontsize(10);
    settextrotation(111);
    //void drawtext(float xc, float yc, const std::string& text, float boundx=FLT_MAX, float boundy=FLT_MAX);
}