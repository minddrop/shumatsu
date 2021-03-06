#include <fstream>
#include <iostream>
#include "vec3.h"

int main() {
  const char *fileName = "./out.ppm";
  std::ofstream ofs(fileName);
  if (!ofs) {
    std::cout << "File is broken." << std::endl;
    return 0;
  }

  int nx = 200;
  int ny = 100;
  ofs << "P3\n" << nx << " " << ny << "\n255\n";

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      ofs << ir << " " << ig << " " << ib << "\n";
    }
  }
  ofs.close();
  return 0;
}
