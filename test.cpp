#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"3\n"
                  "3 2\n"
                  "4 2\n"
                  "5 2";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "2\n");
}
/*
TEST_CASE("file 017", ""){
    BENCHMARK("Can cover with 0 len"){
        std::ifstream input( "../017", std::ofstream::in);
        std::stringstream output;
        parseFile(input,output);
        input.close();
        REQUIRE(output.str() == "0\n");
    };
}
*/
TEST_CASE("test 2", ""){
    std::stringstream input, output;
    input<<"5\n"
           "13 4\n"
           "15 1\n"
           "11 5\n"
           "12 3\n"
           "10 3";
    parseFile(input,output);
    REQUIRE(output.str() == "3\n");
}

TEST_CASE("arrive at the same time", ""){
    std::stringstream input, output;
    input<<"2\n"
           "1 4\n"
           "1 1";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n");
}

TEST_CASE("one arrive when another finished", ""){
    std::stringstream input, output;
    input<<"2\n"
           "1 4\n"
           "5 1";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n");
}

TEST_CASE("gap", ""){
    std::stringstream input, output;
    input<<"2\n"
           "1 4\n"
           "6 4";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n");
}

TEST_CASE("overlap", ""){
    std::stringstream input, output;
    input<<"2\n"
           "1 4\n"
           "3 4";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n");
}

TEST_CASE("inclusion", ""){
    std::stringstream input, output;
    input<<"2\n"
           "1 4\n"
           "2 1";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n");
}
