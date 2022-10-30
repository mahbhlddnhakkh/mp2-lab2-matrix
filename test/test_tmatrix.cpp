#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m1(10);
  TDynamicMatrix<int> m2(m1);
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m1(2);
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++)
      m1[i][j] = 1;
  TDynamicMatrix<int> m2(m1);
  m2[0][0] = 0;
  EXPECT_EQ(false, m1 == m2);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(4);
  m[0][0] = 4;

  EXPECT_EQ(4, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(10);
  ASSERT_ANY_THROW(m.at(-3));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(10);
  ASSERT_ANY_THROW(m.at(11));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  const size_t size = 2;
  TDynamicMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
      m1[i][j] = 0;
      m2[i][j] = 1;
    }
  m2 = m1;
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
      EXPECT_NE(1, m2[i][j]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  const size_t size1 = 2, size2 = 5;
  TDynamicMatrix<int> m1(size1), m2(size2);
  m2 = m1;
  EXPECT_EQ(size1, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  const size_t size1 = 2, size2 = 5;
  TDynamicMatrix<int> m1(size1), m2(size2);
  for (size_t i = 0; i < size1; i++)
    for (size_t j = 0; j < size1; j++)
      m1[i][j] = 1;
  m2 = m1;
  for (size_t i = 0; i < size1; i++)
    for (size_t j = 0; j < size1; j++)
      EXPECT_NE(0, m2[i][j]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  const size_t size = 2;
  TDynamicMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
      m1[i][j] = i + j;
      m2[i][j] = i + j;
    }
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(10);
  EXPECT_EQ(true, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(5), m2(10);
  EXPECT_EQ(true, m1 != m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  const size_t size = 5;
  const int scalar = 2;
  TDynamicMatrix<int> m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
      m1[i][j] = 4;
      m2[i][j] = m1[i][j] * scalar;
    }
  m1 = m1 * scalar;
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector_with_equal_size)
{
  const size_t size = 2;
  TDynamicMatrix<int> m(size);
  TDynamicVector<int> v(size), res(size);
  
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  v[0] = 1;
  v[1] = 2;

  res[0] = 5;
  res[1] = 11;

  EXPECT_EQ(res, m * v);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 10;
  TDynamicMatrix<int> m(size1);
  TDynamicVector<int> v(size2);
  ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  const size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size), m3(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
      m1[i][j] = 4;
      m2[i][j] = 5;
      m3[i][j] = m1[i][j] + m2[i][j];
    }
  EXPECT_EQ(true, (m1 + m2) == m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TDynamicMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  const size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(size), m3(size);
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
      m1[i][j] = 4;
      m2[i][j] = 5;
      m3[i][j] = m1[i][j] - m2[i][j];
    }
  EXPECT_EQ(true, (m1 - m2) == m3);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TDynamicMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  const size_t size = 2;
  TDynamicMatrix<int> m1(size), m2(size), m3(size);

  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[1][0] = 1;
  m1[1][1] = 2;

  m2[0][0] = 3;
  m2[0][1] = 2;
  m2[1][0] = 1;
  m2[1][1] = 3;

  m3[0][0] = 5;
  m3[0][1] = 8;
  m3[1][0] = 5;
  m3[1][1] = 8;

  EXPECT_EQ(m3, m1 * m2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
  const size_t size1 = 2, size2 = 4;
  TDynamicMatrix<int> m1(size1), m2(size2);
  ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, can_find_cofactor_matrix)
{
  size_t sz = 3;
  TDynamicMatrix<int> m(sz), m00(sz - 1), m10(sz - 1), m01(sz - 1), m11(sz - 1), m21(sz - 1), m12(sz - 1);
  int tmp = 1;
  for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < sz; j++)
      m[i][j] = tmp++;

  m00[0][0] = 5;
  m00[0][1] = 6;
  m00[1][0] = 8;
  m00[1][1] = 9;
  EXPECT_EQ(true, m.Cofactor(0, 0) == m00);

  m10[0][0] = 2;
  m10[0][1] = 3;
  m10[1][0] = 8;
  m10[1][1] = 9;
  EXPECT_EQ(true, m.Cofactor(1, 0) == m10);

  m01[0][0] = 4;
  m01[0][1] = 6;
  m01[1][0] = 7;
  m01[1][1] = 9;
  EXPECT_EQ(true, m.Cofactor(0, 1) == m01);

  m11[0][0] = 1;
  m11[0][1] = 3;
  m11[1][0] = 7;
  m11[1][1] = 9;
  EXPECT_EQ(true, m.Cofactor(1, 1) == m11);

  m21[0][0] = 1;
  m21[0][1] = 3;
  m21[1][0] = 4;
  m21[1][1] = 6;
  EXPECT_EQ(true, m.Cofactor(2, 1) == m21);

  m12[0][0] = 1;
  m12[0][1] = 2;
  m12[1][0] = 7;
  m12[1][1] = 8;
  EXPECT_EQ(true, m.Cofactor(1, 2) == m12);
}

TEST(TDynamicMatrix, can_find_determinant)
{
  TDynamicMatrix<int> m(3);

  m[0][0] = 1;
  m[0][1] = 3;
  m[0][2] = 3;

  m[1][0] = 2;
  m[1][1] = 7;
  m[1][2] = 11;

  m[2][0] = 3;
  m[2][1] = 4;
  m[2][2] = 2;
  EXPECT_EQ(18, m.Det());
}

TEST(TDynamicMatrix, can_transpose)
{
  size_t sz = 2;
  TDynamicMatrix<int> m1(sz), m2(sz);

  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[1][0] = 3;
  m1[1][1] = 4;

  m2[0][0] = 1;
  m2[1][0] = 2;
  m2[0][1] = 3;
  m2[1][1] = 4;

  m1.Transpose();
  EXPECT_EQ(true, m1 == m2);
}

TEST(TDynamicMatrix, can_get_invertible_matrix_with_non_zero_determinant)
{
  TDynamicMatrix<int> m1(3), m2(3);

  m1[0][0] = 2;
  m1[0][1] = 5;
  m1[0][2] = 7;

  m1[1][0] = 6;
  m1[1][1] = 3;
  m1[1][2] = 4;

  m1[2][0] = 5;
  m1[2][1] = -2;
  m1[2][2] = -3;

  m2[0][0] = 1;
  m2[0][1] = -1;
  m2[0][2] = 1;

  m2[1][0] = -38;
  m2[1][1] = 41;
  m2[1][2] = -34;

  m2[2][0] = 27;
  m2[2][1] = -29;
  m2[2][2] = 24;

  
  EXPECT_EQ(true, m1.Invertible() == m2);
}

TEST(TDynamicMatrix, cant_get_invertible_matrix_with_zero_determinant)
{
  TDynamicMatrix<int> m(3);
  int k = 1;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      m[i][j] = k++;
  ASSERT_ANY_THROW(m.Invertible());
}

TEST(TDynamicMatrix, can_divide_matrix_with_non_zero_determinant_and_equal_size)
{
  TDynamicMatrix<int> m1(3), m2(3), res(3);
  int k = 1;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      m1[i][j] = k++;
  m2[0][0] = 1;
  m2[0][1] = -1;
  m2[0][2] = 1;

  m2[1][0] = -38;
  m2[1][1] = 41;
  m2[1][2] = -34;

  m2[2][0] = 27;
  m2[2][1] = -29;
  m2[2][2] = 24;

  res[0][0] = 29;
  res[0][1] = 5;
  res[0][2] = 6;

  res[1][0] = 68;
  res[1][1] = 23;
  res[1][2] = 30;

  res[2][0] = 107;
  res[2][1] = 41;
  res[2][2] = 54;
  EXPECT_EQ(true, ((m1 / m2) == res));
}

TEST(TDynamicMatrix, cant_divide_matrix_with_zero_determinant_and_equal_size)
{
  TDynamicMatrix<int> m1(3), m2(3);
  int k1 = 3;
  int k2 = 1;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
    {
      m1[i][j] = k1++;
      m2[i][j] = k2++;
    }
  ASSERT_ANY_THROW(m1 / m2);
}

TEST(TDynamicMatrix, cant_divide_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  int k = 2;
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++)
      m1[i][j] = k++;
  m2[0][0] = 1;
  m2[0][1] = -1;
  m2[0][2] = 1;

  m2[1][0] = -38;
  m2[1][1] = 41;
  m2[1][2] = -34;

  m2[2][0] = 27;
  m2[2][1] = -29;
  m2[2][2] = 24;

  ASSERT_ANY_THROW(m1 / m2);
}

TEST(TDynamicMatrix, self_division_is_identity_matrix)
{
  TDynamicMatrix<int> m(3), E(3);

  m[0][0] = 2;
  m[0][1] = 5;
  m[0][2] = 7;

  m[1][0] = 6;
  m[1][1] = 3;
  m[1][2] = 4;

  m[2][0] = 5;
  m[2][1] = -2;
  m[2][2] = -3;

  E[0][0] = 1;
  E[1][1] = 1;
  E[2][2] = 1;

  EXPECT_EQ(E, m / m);
}