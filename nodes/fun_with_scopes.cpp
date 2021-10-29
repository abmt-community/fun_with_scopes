#include "fun_with_scopes.h"

using namespace std;
using namespace fun_with_scopes;

draw_line::draw_line(){
    in_line = {{0,0},{1,0},{1,1},{0,1}};   
}

void draw_line::tick(){
    if(pos +1 > in_line.size()){
        pos = 0;
    }
    out_x = in_line[pos].x;
    out_y =  in_line[pos].y;
    
    pos++;
}