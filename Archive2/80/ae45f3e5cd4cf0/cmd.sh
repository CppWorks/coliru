g++ -std=c++11 -Os -march=native -Wall -pedantic main.cpp -lboost_system -lboost_serialization && ./a.out; head ./world.save ./world2.save