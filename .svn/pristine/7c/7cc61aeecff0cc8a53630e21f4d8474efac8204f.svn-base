/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   m1_perf_find_street_ids_from_name.cpp
 * Author: hanqinto
 * 
 * Created on February 2, 2018, 8:54 PM
 */
#include <algorithm>
#include <set>
#include <unittest++/UnitTest++.h>
#include "m1.h"
#include "unit_test_util.h"
#include "StreetsDatabaseAPI.h"

using ece297test::relative_error;

struct MapFixture {
    MapFixture() {
        //Load the map
        load_map("/cad2/ece297s/public/maps/toronto_canada.streets.bin");
    }

    ~MapFixture() {
        //Clean-up
        close_map();
    }
};

SUITE(street_queries_perf_public_toronto_cananda){
    
    
    
    TEST_FIXTURE(MapFixture,street_ids_from_name_perf){
        std::vector<unsigned> expected;
        std::vector<unsigned> actual;
        
        //functionality test
        //14 function tests-compare the return results with expected ones
        //focus on streets with multiple id numbers
        expected = {959,1414,10087};
        actual = find_street_ids_from_name("Admiral Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {5576,5577};
        actual = find_street_ids_from_name("Ballacaine Drive");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {255,5752};
        actual = find_street_ids_from_name("Grosvenor Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {5565};
        actual = find_street_ids_from_name("High Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {16528,16541};
        actual = find_street_ids_from_name("High Street West");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {186,1078};
        actual = find_street_ids_from_name("Highway 410");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {205,208,209,309};
        actual = find_street_ids_from_name("Highway 401 Westbound");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {154,155,190,212,213,217,1535,6855};
        actual = find_street_ids_from_name("Highway 401");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {20088};
        actual = find_street_ids_from_name("Baggott Lane");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {1313,5191,6621,7411,12215};
        actual = find_street_ids_from_name("Fourteenth Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {3362,3431,3978,14340};
        actual = find_street_ids_from_name("Franklin Avenue");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {200,246,396,5799,5802,8978};
        actual = find_street_ids_from_name("Gardiner Expressway");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {8358,18027};
        actual = find_street_ids_from_name("Gatehead Road");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        expected = {941,1912,3219,5467,6508,7284,9883,18954};
        actual = find_street_ids_from_name("George Street");
        std::sort(actual.begin(), actual.end());
        CHECK_EQUAL(expected, actual);
        
        {//Time Test for find_street_ids_from_name
            std::vector<unsigned> results;
            ECE297_TIME_CONSTRAINT(250);
            for(unsigned i = 0; i < 100000; i++){
                //run 10 different tests for 100000 times and compare its running time with the time limit
                results = find_street_ids_from_name("Grosvenor Street");
                results = find_street_ids_from_name("Buckhorn Avenue");
                results = find_street_ids_from_name("Bur Oak Avenue");
                results = find_street_ids_from_name("Burbank Drive");
                results = find_street_ids_from_name("Calvin Avenue");
                results = find_street_ids_from_name("Cambridge Crescent");
                results = find_street_ids_from_name("Canada Drive");
                results = find_street_ids_from_name("Dixie Road");
                results = find_street_ids_from_name("Dollery Gate");
                results = find_street_ids_from_name("Douglas Avenue");
            }
        }
    }
}


