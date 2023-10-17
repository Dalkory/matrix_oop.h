#include "../s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool isEqual = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) isEqual = false;
  for (int i = 0; isEqual && i < rows_; i++) {
    for (int j = 0; isEqual && j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1.0e-07) isEqual = false;
    }
  }
  return isEqual;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  // Здесь мы используем функцию высшего порядка MatrixOperation, которая служит
  // оберткой для применения определенной математической операции (подаваемой
  // как функция) к двум матрицам. В данном случае, эта операция - сложение.
  MatrixOperation(other, [](double a, double b) { return a + b; });
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  MatrixOperation(other, [](double a, double b) { return a - b; });
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument("Недопустимые размеры матриц для умножения");
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      res(i, j) = 0;
      for (int k = 0; k < cols_; k++) {
        res(i, j) += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  // Создаем новую матрицу с перевернутыми размерами: количество строк
  // становится количеством столбцов и наоборот.
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < transposed.rows_; i++) {
    for (int j = 0; j < transposed.cols_; j++) {
      transposed.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transposed;
}

S21Matrix S21Matrix::CalcComplements() const {
  // Сначала проверяем, является ли матрица квадратной, так как определение
  // алгебраических дополнений применимо только к квадратным матрицам.
  ValidateSquare();
  if (rows_ == 1) throw std::logic_error("Размерность должна быть больше 1");
  S21Matrix calccomplements(rows_, cols_);
  CreateCofactorMatrix(calccomplements);
  return calccomplements;
}

double S21Matrix::Determinant() const {
  ValidateSquare();
  return CalculateDeterminant();
}

S21Matrix S21Matrix::InverseMatrix() {
  const double determinant = Determinant();
  if (fabs(determinant) < 1.0e-7)
    throw std::logic_error("Определитель не может быть равен 0");
  // Расчет обратной матрицы: берем матрицу алгебраических дополнений,
  // транспонируем ее и делим каждый элемент на определитель.
  S21Matrix inversed = CalcComplements().Transpose();
  inversed.MulNumber(1.0 / determinant);
  return inversed;
}