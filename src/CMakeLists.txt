add_library(tictactoe TicTacToe.cpp)

add_executable(mikroprojekt3 main.cpp)

target_link_libraries(mikroprojekt3 PRIVATE tictactoe)
