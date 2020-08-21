#pragma once

#define MOVE_R 1
#define MOVE_L 2
#define MOVE_SOFTDROP 4
#define MOVE_HARDDROP 8
#define MOVE_ROTATE_R 16
#define MOVE_ROTATE_L 32
#define MOVE_HOLD 64

#define BOARD_MAX_SIZE_V 255
#define BOARD_SIZE_V 20
#define BOARD_SIZE_H 10

#define GRAPH_SIZE 5

#define DISPLAYSIZE_V 720
#define DISPLAYSIZE_H 1260

#define rep(i,n) for(int i=0;i<n;++i)
#define rrep(i,n) for(int i=n;i>=0;--i)
#define REP(i,m,n) for(int i=m;i<n;++i)
#define RREP(i,m,n) for(int i=n;i>=m;--i)

#include <utility>
using pii = std::pair<int, int>;