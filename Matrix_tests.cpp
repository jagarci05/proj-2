#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE

TEST(test_matrix_init_and_size) {
  Matrix m;
  Matrix_init(&m, 6, 7);
  ASSERT_EQUAL(Matrix_width(&m), 6);
  ASSERT_EQUAL(Matrix_height(&m), 7);
}

TEST(test_matrix_at_and_fill) {
  Matrix m;
  Matrix_init(&m, 2, 2);
  Matrix_fill(&m, 69);

  for (int r = 0; r < Matrix_height(&m); ++r) {
    for (int c = 0; c < Matrix_width(&m); ++c) {
      ASSERT_EQUAL(*Matrix_at(&m, r, c), 69);
    }
  }
}

TEST(test_matrix_at_const) {
  Matrix m;
  Matrix_init(&m, 2, 2);
  *Matrix_at(&m, 0, 0) = 99;

  const Matrix *pm = &m;
  ASSERT_EQUAL(*Matrix_at(pm, 0, 0), 99);
}

TEST(test_matrix_fill_border) {
  Matrix m;
  Matrix_init(&m, 4, 3);
  Matrix_fill(&m, 7);
  Matrix_fill_border(&m, 0);

  ASSERT_EQUAL(*Matrix_at(&m, 0, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&m, 0, 3), 0);
  ASSERT_EQUAL(*Matrix_at(&m, 2, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&m, 2, 3), 0);

  ASSERT_EQUAL(*Matrix_at(&m, 1, 1), 7);
}

TEST(test_matrix_max) {
  Matrix m;
  Matrix_init(&m, 2, 2);
  Matrix_fill(&m, 5);
  *Matrix_at(&m, 0, 1) = 9;
  ASSERT_EQUAL(Matrix_max(&m), 9);
}

TEST(test_matrix_min_value_in_row) {
  Matrix m;
  Matrix_init(&m, 3, 1);
  *Matrix_at(&m, 0, 0) = 10;
  *Matrix_at(&m, 0, 1) = 7;
  *Matrix_at(&m, 0, 2) = 8;
  ASSERT_EQUAL(Matrix_min_value_in_row(&m, 0, 0, 3), 7);
}

TEST(test_matrix_column_of_min_value_in_row) {
  Matrix m;
  Matrix_init(&m, 3, 1);
  *Matrix_at(&m, 0, 0) = 4;
  *Matrix_at(&m, 0, 1) = 1;
  *Matrix_at(&m, 0, 2) = 1; // tie → leftmost column should win
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&m, 0, 0, 3), 1);
}

TEST(test_matrix_print) {
  Matrix m;
  Matrix_init(&m, 2, 2);
  *Matrix_at(&m, 0, 0) = 1;
  *Matrix_at(&m, 0, 1) = 2;
  *Matrix_at(&m, 1, 0) = 3;
  *Matrix_at(&m, 1, 1) = 4;

  ostringstream out;
  Matrix_print(&m, out);

  ostringstream expected;
  expected << "2 2\n";
  expected << "1 2 \n";
  expected << "3 4 \n";

  ASSERT_EQUAL(expected.str(), out.str());
}

TEST_MAIN() // Do NOT put a semicolon here