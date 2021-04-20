cmake_minimum_required(VERSION 3.19)
project(Console_Chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(Console_Chess main.cpp Pieces/Piece.h Pieces/Pawn.h Pieces/Knight.h Pieces/Bishop.h Pieces/Rook.h Pieces/Queen.h Pieces/King.h Pieces_I.h Board.h Chess.h Players/Player.h Players_I.h Players/HumanPlayer.h Move.h)