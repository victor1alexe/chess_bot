cmake_minimum_required(VERSION 3.23)
project(CrazyHouse)

set(CMAKE_CXX_STANDARD 20)

add_executable(CrazyHouse
        main.cpp
        table.c++
        move.c++
        player.c++
        ./protocol/protocol.c++
        ./pieces/piece.c++
        ./pieces/pawn.c++
        ./pieces/rook.c++
        ./pieces/knight.c++
        ./pieces/bishop.c++
        ./pieces/queen.c++
        ./pieces/king.c++
        )
