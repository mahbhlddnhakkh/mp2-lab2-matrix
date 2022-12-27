#include "TDTriangleMatrix.h"

#include <gtest.h>

TEST(TDTriangleMatrix, can_create_dtriangle_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDTriangleMatrix<int> m(5));
}

TEST(TDTriangleMatrix, cant_create_too_large_dtriangle_matrix)
{
  ASSERT_ANY_THROW(TDTriangleMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDTriangleMatrix, throws_when_create_dtriangle_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDTriangleMatrix<int> m(-5));
}

TEST(TDTriangleMatrix, can_create_copied_dtriangle_matrix)
{
  TDTriangleMatrix<int> m(5);

  ASSERT_NO_THROW(TDTriangleMatrix<int> m1(m));
}

TEST(TDTriangleMatrix, copied_dtriangle_matrix_is_equal_to_source_one)
{
  TDTriangleMatrix<int> m1(10);
  TDTriangleMatrix<int> m2(m1);
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDTriangleMatrix, copied_dtriangle_matrix_has_its_own_memory)
{
  TDTriangleMatrix<int> m1(3, 1);
  TDTriangleMatrix<int> m2(m1);
  m2[0][0] = 0;
  EXPECT_EQ(false, m1 == m2);
}

TEST(TDTriangleMatrix, can_get_size)
{
  TDTriangleMatrix<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDTriangleMatrix, can_set_and_get_element)
{
  TDTriangleMatrix<int> m(4);
  m[0][0] = 4;

  EXPECT_EQ(4, m[0][0]);
}

TEST(TDTriangleMatrix, throws_when_set_element_with_negative_index)
{
  TDTriangleMatrix<int> m(10);
  ASSERT_ANY_THROW(m.at(-3));
}

TEST(TDTriangleMatrix, throws_when_set_element_with_too_large_index)
{
  TDTriangleMatrix<int> m(10);
  ASSERT_ANY_THROW(m.at(11));
}

TEST(TDTriangleMatrix, can_assign_dtriangle_matrix_to_itself)
{
  TDTriangleMatrix<int> m(5);
  ASSERT_NO_THROW(m = m);
}

TEST(TDTriangleMatrix, can_assign_dtriangle_matrices_of_equal_size)
{
  const size_t size = 2;
  TDTriangleMatrix<int> m1(size, 0), m2(size, 1);
  m2 = m1;
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < i; j++)
      EXPECT_NE(1, m2[i][j]);
}

TEST(TDTriangleMatrix, compare_equal_dtriangle_matrices_return_true)
{
  const size_t size = 2;
  TDTriangleMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < i; j++)
    {
      m1[i][j] = i + j;
      m2[i][j] = i + j;
    }
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDTriangleMatrix, compare_dtriangle_matrix_with_itself_return_true)
{
  TDTriangleMatrix<int> m(10);
  EXPECT_EQ(true, m == m);
}

TEST(TDTriangleMatrix, dtriangle_matrices_with_different_size_are_not_equal)
{
  TDTriangleMatrix<int> m1(5), m2(10);
  EXPECT_EQ(true, m1 != m2);
}

TEST(TDTriangleMatrix, can_dtriangle_multiply_matrix_by_scalar)
{
  const size_t size = 5;
  const int scalar = 2;
  TDTriangleMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < i; j++)
    {
      m1[i][j] = 4;
      m2[i][j] = m1[i][j] * scalar;
    }
  m1 = m1 * scalar;
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDTriangleMatrix, can_multiply_dtriangle_matrix_by_vector_with_equal_size)
{
  const size_t size = 3;
  TDTriangleMatrix<int> m(size);
  TDynamicVector<int> v(size), res(size);

  m(0, 0) = 1;
  m(1, 0) = 2;
  m(2, 0) = 3;
  m(1, 1) = 4;
  m(2, 1) = 6;
  m(2, 2) = 5;

  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  res[0] = 1;
  res[1] = 10;
  res[2] = 30;

  EXPECT_EQ(res, m * v);
}

TEST(TDTriangleMatrix, cant_multiply_dtriangle_matrix_by_vector_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 10;
  TDTriangleMatrix<int> m(size1);
  TDynamicVector<int> v(size2);
  ASSERT_ANY_THROW(m * v);
}

TEST(TDTriangleMatrix, can_add_dtriangle_matrices_with_equal_size)
{
  const size_t size = 5;
  TDTriangleMatrix<int> m1(size), m2(size), m3(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < i; j++)
    {
      m1[i][j] = 4;
      m2[i][j] = 5;
      m3[i][j] = m1[i][j] + m2[i][j];
    }
  EXPECT_EQ(true, (m1 + m2) == m3);
}

TEST(TDTriangleMatrix, cant_add_dtriangle_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TDTriangleMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDTriangleMatrix, can_subtract_dtriangle_matrices_with_equal_size)
{
  const size_t size = 5;
  TDTriangleMatrix<int> m1(size), m2(size), m3(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < i; j++)
    {
      m1[i][j] = 4;
      m2[i][j] = 5;
      m3[i][j] = m1[i][j] - m2[i][j];
    }
  EXPECT_EQ(true, (m1 - m2) == m3);
}

TEST(TDTriangleMatrix, cant_subtract_dtriangle_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TDTriangleMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDTriangleMatrix, can_multiply_dtriangle_matrices_with_equal_size)
{
  const size_t size = 3;
  TDTriangleMatrix<int> m1(size), m2(size), m3(size);

  m1(0, 0) = 1;
  m1(1, 0) = 2;
  m1(2, 0) = 3;
  m1(1, 1) = 4;
  m1(2, 1) = 6;
  m1(2, 2) = 5;

  m2(0, 0) = 5;
  m2(1, 0) = 22;
  m2(2, 0) = 2;
  m2(1, 1) = 4;
  m2(2, 1) = 3;
  m2(2, 2) = 6;

  m3(0, 0) = 5;
  m3(1, 0) = 98;
  m3(2, 0) = 157;
  m3(1, 1) = 16;
  m3(2, 1) = 39;
  m3(2, 2) = 30;

  EXPECT_EQ(m3, m1 * m2);
}

TEST(TDTriangleMatrix, cant_multiply_dtriangle_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TDTriangleMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 * m2);
}