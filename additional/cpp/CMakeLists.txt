cmake_minimum_required(VERSION 3.10)

project(test)

add_executable(test
    solve.h
    test_solve.cpp
    catch.cpp
    catch.hpp
)