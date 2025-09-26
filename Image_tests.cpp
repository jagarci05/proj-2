#include "Image.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE

TEST(test_image_init_and_size) {
  Image img;
  Image_init(&img, 3, 2);
  ASSERT_EQUAL(Image_width(&img), 3);
  ASSERT_EQUAL(Image_height(&img), 2);
}

TEST(test_image_fill_and_get_pixel) {
  Image img;
  Image_init(&img, 2, 2);

  Pixel red = {255, 0, 0};
  Image_fill(&img, red);

  for (int r = 0; r < Image_height(&img); ++r) {
    for (int c = 0; c < Image_width(&img); ++c) {
      Pixel p = Image_get_pixel(&img, r, c);
      ASSERT_EQUAL(p.r, 255);
      ASSERT_EQUAL(p.g, 0);
      ASSERT_EQUAL(p.b, 0);
    }
  }
}

TEST(test_image_set_and_get_pixel) {
  Image img;
  Image_init(&img, 1, 1);

  Pixel maize = {251, 206, 51};
  Image_set_pixel(&img, 0, 0, maize);

  Pixel got = Image_get_pixel(&img, 0, 0);
  ASSERT_EQUAL(got.r, 251);
  ASSERT_EQUAL(got.g, 206);
  ASSERT_EQUAL(got.b, 51);
}

TEST(test_image_copy_independence) {
  Image img1;
  Image_init(&img1, 2, 2);
  Pixel blue = {0, 0, 255};
  Image_fill(&img1, blue);

  Image img2 = img1; // copy
  Pixel white = {255, 255, 255};
  Image_set_pixel(&img2, 0, 0, white);

  Pixel p1 = Image_get_pixel(&img1, 0, 0);
  Pixel p2 = Image_get_pixel(&img2, 0, 0);

  ASSERT_NOT_EQUAL(p1.r, p2.r); // confirm copy is independent
}

TEST(test_image_print_ppm) {
  Image img;
  Image_init(&img, 2, 1);

  Pixel black = {0, 0, 0};
  Pixel white = {255, 255, 255};
  Image_set_pixel(&img, 0, 0, black);
  Image_set_pixel(&img, 0, 1, white);

  ostringstream out;
  Image_print(&img, out);

  ostringstream expected;
  expected << "P3\n2 1\n255\n";
  expected << "0 0 0 255 255 255 \n";

  ASSERT_EQUAL(expected.str(), out.str());
}

TEST(test_image_init_from_stream) {
  istringstream in(
      "P3\n"
      "2 1\n"
      "255\n"
      "10 20 30 40 50 60\n");
  Image img;
  Image_init(&img, in);

  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 1);

  Pixel p1 = Image_get_pixel(&img, 0, 0);
  Pixel p2 = Image_get_pixel(&img, 0, 1);

  ASSERT_EQUAL(p1.r, 10);
  ASSERT_EQUAL(p1.g, 20);
  ASSERT_EQUAL(p1.b, 30);

  ASSERT_EQUAL(p2.r, 40);
  ASSERT_EQUAL(p2.g, 50);
  ASSERT_EQUAL(p2.b, 60);
}

TEST_MAIN() // Do NOT put a semicolon here