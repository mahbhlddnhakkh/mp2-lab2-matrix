#include "TUTriangleMatrix.h"

#include <gtest.h>

TEST(TUTriangleMatrix, can_create_utriangle_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TUTriangleMatrix<int> m(5));
}

TEST(TUTriangleMatrix, cant_create_too_large_utriangle_matrix)
{
  ASSERT_ANY_THROW(TUTriangleMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TUTriangleMatrix, throws_when_create_utriangle_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TUTriangleMatrix<int> m(-5));
}

TEST(TUTriangleMatrix, can_create_copied_utriangle_matrix)
{
  TUTriangleMatrix<int> m(5);

  ASSERT_NO_THROW(TUTriangleMatrix<int> m1(m));
}

TEST(TUTriangleMatrix, copied_utriangle_matrix_is_equal_to_source_one)
{
  TUTriangleMatrix<int> m1(10);
  TUTriangleMatrix<int> m2(m1);
  EXPECT_EQ(true, m1 == m2);
}

TEST(TUTriangleMatrix, copied_utriangle_matrix_has_its_own_memory)
{
  TUTriangleMatrix<int> m1(3, 1);
  TUTriangleMatrix<int> m2(m1);
  m2(0, 0) = 0;
  EXPECT_EQ(false, m1 == m2);
}

TEST(TUTriangleMatrix, can_get_size)
{
  TUTriangleMatrix<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TUTriangleMatrix, can_set_and_get_element)
{
  TUTriangleMatrix<int> m(4);
  m(0, 0) = 4;

  EXPECT_EQ(4, m(0, 0));
}

TEST(TUTriangleMatrix, throws_when_set_element_with_negative_index)
{
  TUTriangleMatrix<int> m(10);
  ASSERT_ANY_THROW(m.at(-3, 0));
}

TEST(TUTriangleMatrix, throws_when_set_element_with_too_large_index)
{
  TUTriangleMatrix<int> m(10);
  ASSERT_ANY_THROW(m.at(11, 0));
}

TEST(TUTriangleMatrix, can_assign_utriangle_matrix_to_itself)
{
  TUTriangleMatrix<int> m(5);
  ASSERT_NO_THROW(m = m);
}

TEST(TUTriangleMatrix, can_assign_utriangle_matrices_of_equal_size)
{
  const size_t size = 2;
  TUTriangleMatrix<int> m1(size, 0), m2(size, 1);
  m2 = m1;
  for (size_t i = 0; i < size; i++)
    for (size_t j = i; j < size; j++)
      EXPECT_NE(1, m2(i, j));
}

TEST(TUTriangleMatrix, compare_equal_utriangle_matrices_return_true)
{
  const size_t size = 2;
  TUTriangleMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = i; j < size; j++)
    {
      m1(i, j) = i + j;
      m2(i, j) = i + j;
    }
  EXPECT_EQ(true, m1 == m2);
}

TEST(TUTriangleMatrix, compare_utriangle_matrix_with_itself_return_true)
{
  TUTriangleMatrix<int> m(10);
  EXPECT_EQ(true, m == m);
}

TEST(TUTriangleMatrix, dtriangle_matrices_with_different_size_are_not_equal)
{
  TUTriangleMatrix<int> m1(5), m2(10);
  EXPECT_EQ(true, m1 != m2);
}

TEST(TUTriangleMatrix, can_utriangle_multiply_matrix_by_scalar)
{
  const size_t size = 5;
  const int scalar = 2;
  TUTriangleMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = i; j < size; j++)
    {
      m1(i, j) = 4;
      m2(i, j) = m1(i, j) * scalar;
    }
  m1 = m1 * scalar;
  EXPECT_EQ(true, m1 == m2);
}

TEST(TUTriangleMatrix, can_multiply_utriangle_matrix_by_vector_with_equal_size)
{
  const size_t size = 3;
  TUTriangleMatrix<int> m(size);
  TDynamicVector<int> v(size), res(size);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 1) = 4;
  m(1, 2) = 6;
  m(2, 2) = 5;

  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  res[0] = 14;
  res[1] = 26;
  res[2] = 15;

  EXPECT_EQ(res, m * v);
}

TEST(TUTriangleMatrix, cant_multiply_utriangle_matrix_by_vector_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 10;
  TUTriangleMatrix<int> m(size1);
  TDynamicVector<int> v(size2);
  ASSERT_ANY_THROW(m * v);
}

TEST(TUTriangleMatrix, can_add_utriangle_matrices_with_equal_size)
{
  const size_t size = 5;
  TUTriangleMatrix<int> m1(size), m2(size), m3(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = i; j < size; j++)
    {
      m1(i, j) = 4;
      m2(i, j) = 5;
      m3(i, j) = m1(i, j) + m2(i, j);
    }
  EXPECT_EQ(true, (m1 + m2) == m3);
}

TEST(TUTriangleMatrix, cant_add_utriangle_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TUTriangleMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TUTriangleMatrix, can_subtract_utriangle_matrices_with_equal_size)
{
  const size_t size = 5;
  TUTriangleMatrix<int> m1(size), m2(size), m3(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = i; j < size; j++)
    {
      m1(i, j) = 4;
      m2(i, j) = 5;
      m3(i, j) = m1(i, j) - m2(i, j);
    }
  EXPECT_EQ(true, (m1 - m2) == m3);
}

TEST(TUTriangleMatrix, cant_subtract_utriangle_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TUTriangleMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TUTriangleMatrix, can_multiply_utriangle_matrices_with_equal_size)
{
  const size_t size = 3;
  TUTriangleMatrix<int> m1(size), m2(size), m3(size);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 1) = 4;
  m1(1, 2) = 6;
  m1(2, 2) = 5;

  m2(0, 0) = 5;
  m2(0, 1) = 22;
  m2(0, 2) = 2;
  m2(1, 1) = 4;
  m2(1, 2) = 3;
  m2(2, 2) = 6;

  m3(0, 0) = 5;
  m3(0, 1) = 30;
  m3(0, 2) = 26;
  m3(1, 1) = 16;
  m3(1, 2) = 48;
  m3(2, 2) = 30;

  EXPECT_EQ(m3, m1 * m2);
}

TEST(TUTriangleMatrix, cant_multiply_utriangle_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TUTriangleMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 * m2);
}