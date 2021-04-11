

// Opengl4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "ray.h"
#include "vec3.h"
#include <iostream>
#include <gl/glut.h>
#include <vector>
#include "object.h"
#include "tools.h"

const auto aspect_ratio=16.0 / 9.0;
const int image_width= 592;
const int image_height= 333;
const int randomTimes = 100;
const int maxdepth = 50;



unsigned char Image[image_height * image_width * 3];
std::vector<Sphere> sphereList;

vec3 write_color(std::ostream& out,color pixel_color,int randomTimes) {
    // Write the translated [0,255] value of each color component.
    auto scale = 1.0 / randomTimes;
    auto r = pixel_color.v[0];
    auto g = pixel_color.v[1];
    auto b = pixel_color.v[2];
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    return vec3(static_cast<int>(256 * clamp(r,0.0,0.999)),
        static_cast<int>(256 *clamp(g,0.0,0.999)),
        static_cast<int>(256*clamp(b,0.0,0.999)));
    /*
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';*/
}

bool listHit(const ray& r, double min, double max, hit_record& rec)
{
    hit_record cur;
    bool ifhit = false;
    auto closestmax = max;
    for (int i = 0; i < sphereList.size(); i++)
    {
        if (sphereList[i].hit(r, min, closestmax, cur))
        {
            ifhit = true;
            closestmax = cur.t;//当前交点之前
            cur.mat_ptr = cur.mat_ptr;
            rec = cur;
        }
    }
    
    return ifhit;
}


color ray_color(const ray& r,int depth){
    hit_record point;
    if (depth <= 0)
        return color(0, 0, 0);

    if (listHit(r, 0.001, 1000, point))
    {  
            ray scattered;
            color attenuation;
            bool islight;
            if (point.mat_ptr->scatter(r, point, attenuation, scattered, islight))
            {
                if (islight)
                {
                 //   ray newl(r.origin, r.origin + random_in_unit_sphere());
                //    return attenuation * ray_color(newl, depth);                
                    return attenuation;
                }
                else
                {
                    return attenuation * ray_color(scattered, depth - 1);
                   
                }
            }
            else
            {
                return color(0, 0, 0);              
            }
    }
    vec3 unit_direction = unit_vector(r.vect);
    auto t = 0.5 * (unit_direction.v[1] + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void display()
{
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       auto material_ground = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
       auto material_center = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
       auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
       auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0);
       Sphere first(Point3(0, -0.25, -1), 0.25, material_center);
       Sphere sec(Point3(0, -100.5, -1), 100.0, material_ground);
       Sphere left(Point3(-1.3, -0.25, -1.0), 0.25, material_left);
       Sphere right(Point3(1.0, -0.25, -1.0), 0.25, material_right);

       auto material_light = std::make_shared<Light>(color(255, 255, 255));
 //    Sphere light(Point3(-1, 2, 0), 0.2, material_light);

       sphereList.push_back(first);
       sphereList.push_back(sec);
       sphereList.push_back(left);
       sphereList.push_back(right);
  //   sphereList.push_back(light);


    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    Sphere m(Point3(-0.5, 0, -1.5), 0.5, material2);
    sphereList.push_back(m);

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    Sphere m1(Point3(0.7 ,0, -1.7), 0.5, material3);
    sphereList.push_back(m1);
    
    int index = 0;
    /*
    viewport的设置
    */
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;//viewer和投影面之间的距离

    auto origin = Point3(0, 0, 0);//原点--viewer，ray的射出点
    auto horizontal = vec3(viewport_width, 0, 0);//宽度向量
    auto vertical = vec3(0, viewport_height, 0);//高度向量
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);//指向画布左下角的向量

    // Render
    int idx = 0;
    /*
    i与j是对应于image空间
    */
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j =0; j<image_height;j++) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for (int z = 0; z < randomTimes; z++)
            {//加入random函数，使得光线实则在正确的像素周围抖动，最后取抖动之后的平均值
                auto u = (double(i)+random_double()) / (image_width - 1);//将image空间映射到视口空间
                auto v = (double(j)+random_double()) / (image_height - 1);
                ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
                pixel_color += ray_color(r,maxdepth);

            }
            vec3 outcolor=write_color(std::cout,pixel_color,randomTimes);
            Image[idx] = outcolor.v[0];
            Image[idx + 1] = outcolor.v[1];
            Image[idx + 2] = outcolor.v[2];
            idx += 3;
        }
    }
    std::cerr << "\nDone.\n";
    glDrawPixels(image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, Image);

    glutSwapBuffers();
}

int main(int argc,char** argv) 
{
    glutInit(&argc, argv);
    glutInitWindowSize(image_width,image_height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("RayTracer");
    glutDisplayFunc(display);
    
    glutMainLoop();

    return 0;
}
