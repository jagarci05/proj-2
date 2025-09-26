#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Image.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char*argv[]) {
  if (argc != 4 && argc != 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string file_name_in = argv[1];
  string file_name_out = argv[2];
  int width = stoi(argv[3]);
  int height = 0;

  ifstream going_in(file_name_in);
  if (!going_in.is_open()) {
    cout << "Error opening file: " << file_name_in << endl;
    return 1;
  }

  Image img;
  Image_init(&img, going_in);
  going_in.close();

  int width_0 = Image_width(&img);
  int height_0 = Image_height(&img);

  if (argc == 5) {
    height = stoi(argv[4]);
  } else {
    height = height_0; 
  }

  if (width <= 0 || width > width_0 || height <= 0 || height > height_0) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  while (Image_width(&img) > width) {
    Matrix energy;
    compute_energy_matrix(&img, &energy);
    Matrix cost;
    compute_vertical_cost_matrix(&energy, &cost);
    vector<int> seam = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(&img, seam);
  }

  while (Image_height(&img) > height) {
    rotate_left(&img);
    Matrix energy;
    compute_energy_matrix(&img, &energy);
    Matrix cost;
    compute_vertical_cost_matrix(&energy, &cost);
    vector<int> seam = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(&img, seam);
    rotate_right(&img);
  }

  ofstream going_out(file_name_out);
  if (!going_out.is_open()) {
    cout << "Error opening file: " << file_name_out << endl;
    return 1;
  }

  Image_print(&img, going_out);
  going_out.close();

  return 0;
}