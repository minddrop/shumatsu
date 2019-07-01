#include <fstream>
#include <iostream>
#include <random>
#include "camera.h"
#include "float.h"
#include "hitable_list.h"
#include "sphere.h"

vec3 color(const ray& r, hitable* world) {
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 *
           vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

std::random_device seed;
std::mt19937 mt(seed());
std::uniform_real_distribution<float> urd(-0.5, 0.5);
inline float rnd() { return urd(mt); }

int main(int argc, char* argv[]) {
  const char* fileName = "./result/hitablesample.ppm";
  std::ofstream ofs(fileName);
  if (!ofs) {
    std::cout << "File is broken." << std::endl;
    return 0;
  }

  int nx = 2000;
  int ny = 1000;
  int ns = 100;
  ofs << "P3\n" << nx << " " << ny << "\n255\n";
  camera cam;
  hitable* list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable* world = new hitable_list(list, 2);

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = (float(i) + rnd()) / float(nx);
        float v = (float(j) + rnd()) / float(ny);
        ray r = cam.get_ray(u, v);
        col += color(r, world);
      }
      col /= float(ns);
      int ir = int(255.99 * col[2]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[0]);
      ofs << ir << " " << ig << " " << ib << "\n";
    }
  }

  ofs.close();
  std::cout << "Done!" << std::endl;
}
