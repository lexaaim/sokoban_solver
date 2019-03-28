#include "deadlocks.h"

std::vector<Sokoban::DeadlockInfo> deadlocks2x2 =
{

//
//   $$
//   $?
  { {  }, { {-1, -1}, { 0, -1}, {-1,  0} }, { {-1, -1}, { 0, -1}, {-1,  0} }, { {-1, -1}, { 0, -1}, {-1,  0}, { 0,  0} }, 1 },

//
//   #$
//   $?
  { { {-1, -1} }, { { 0, -1}, {-1,  0} }, { { 0, -1}, {-1,  0} }, { { 0, -1}, {-1,  0}, { 0,  0} }, 1 },

//
//   $#
//   $?
  { { { 0, -1} }, { {-1, -1}, {-1,  0} }, { {-1, -1}, {-1,  0} }, { {-1, -1}, {-1,  0}, { 0,  0} }, 1 },

//
//   ##
//   $?
  { { {-1, -1}, { 0, -1} }, { {-1,  0} }, { {-1,  0} }, { {-1,  0}, { 0,  0} }, 1 },

//
//   $$
//   #?
  { { {-1,  0} }, { {-1, -1}, { 0, -1} }, { {-1, -1}, { 0, -1} }, { {-1, -1}, { 0, -1}, { 0,  0} }, 1 },

//
//   #$
//   #?
  { { {-1, -1}, {-1,  0} }, { { 0, -1} }, { { 0, -1} }, { { 0, -1}, { 0,  0} }, 1 },
};