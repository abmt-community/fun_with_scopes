#ifndef TEST_SCOPE_PIC_IMG_TEST_H
#define TEST_SCOPE_PIC_IMG_TEST_H TEST_SCOPE_PIC_IMG_TEST_H

#include <abmt/img.h>
#include <abmt/3d.h>
#include <vector>
namespace fun_with_scopes{

//@node:auto
struct virtual_scope{
    double in_x;
    double in_y;
    
    double last_x = 0;
    double last_y = 0;
    
    double param_filter = 0.99;
    
    abmt::img_gray out_img = {101,101};
    
    void tick(){
        for(auto px: out_img.roi()){
            px.color = px.color*param_filter;
        }
        //out_img.at(in_x,in_y) = 255;
        out_img.draw_line(in_x * 100, 100 - in_y*100, last_x*100, 100-last_y*100, 255);
        last_x = in_x;
        last_y = in_y;
    }
};

//@node: auto
struct draw_line{
    double out_x;
    double out_y;
    
    bool dir_fwd = true;
    int pos = 0;
    std::vector<abmt::vec2> in_line;
    
    draw_line();
    void tick();
    
};

//@node: auto
struct make_cube{
    abmt::scene out_scene;
    void init(){
        abmt::vec3 last_p = {0,0,0};
        auto add = [&](abmt::vec3 p ){
            auto ptr = std::make_shared<abmt::line3d>(abmt::line3d{last_p,p,{255,255,255,255}});
            out_scene.lines.push_back(ptr);
            last_p = p;
        };
        add({0,1,0});
        add({1,1,0});
        add({1,0,0});
        add({1,0,1});
        add({1,1,1});
        add({0,1,1});
        add({0,0,1});
        add({0,0,0});
    }
    
};

//@node:auto
struct scene_line_to_2d{
    std::vector<abmt::vec2> out_line;
    abmt::scene in_scene;
    double param_cam_z = -2.5;
    void add_point(abmt::vec3 p){
        out_line.push_back({
           p.x / (-p.z - param_cam_z) + 0.5,
           p.y / (-p.z - param_cam_z) + 0.5,
        });
    }
    void tick(){
        out_line.clear();
        
        if(in_scene.lines.size() > 0){
            add_point(in_scene.lines[0]->p1);
            for(auto l: in_scene.lines){
                add_point(l->p2);
            }
        }
    }
};





} // namespace test_scope_pic

#endif // TEST_SCOPE_PIC_IMG_TEST_H
