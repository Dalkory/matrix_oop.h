#include "../s21_matrix_oop.h"

/*---------ВЫЧИСЛЕНИЯ НА МАТРИЦАХ----------*/

void S21Matrix::MatrixOperation(
    const S21Matrix &other, std::function<double(double, double)> operation) {
  ValidateDimensionsAreEqual(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = operation(matrix_[i][j], other.matrix_[i][j]);
    }
  }
}

double S21Matrix::CalculateDeterminant() const {
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
      // Заполняем матрицу значениями исключая строку и столбец на которые
      // указывает j.
      CreateMinor(minorMatrix, 0, j);
      // Расчитываем детерминант для этой матрицы и умножаем на значение
      // элемента из исходной матрицы знак элемента определяется порядковым
      // номером элемента (-1)^j.
      result += matrix_[0][j] * pow(-1, j) * minorMatrix.CalculateDeterminant();
      minorMatrix.FreeMatrixMemory();
    }
  }
  return result;
}

void S21Matrix::CreateCofactorMatrix(S21Matrix &cofactorMatrix) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
      CreateMinor(minorMatrix, i, j);
      // Значение в матрице кофакторов — это детерминант минора,
      // умноженный на (-1)^(i+j)
      cofactorMatrix.matrix_[i][j] =
          pow(-1, (i + j)) * minorMatrix.Determinant();
      minorMatrix.FreeMatrixMemory();
    }
  }
}

void S21Matrix::CreateMinor(S21Matrix &minorMatrix, int row, int col) const {
  int minorRow = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row) {  // Проверим, не совпадает ли текущая строка с удаленной
      int minorCol = 0;
      for (int j = 0; j < cols_; j++) {
        if (j !=
            col) {  // Проверим, не совпадает ли текущий столбец с удаленным
          minorMatrix.matrix_[minorRow][minorCol] =
              matrix_[i][j];  // Копируем элемент в минор, если он не находится
                              // в удаленной строке или столбце
          minorCol++;
        }
      }
      minorRow++;
    }
  }
}

/*---------ВАЛИДАЦИЯ И ПРОВЕРКА----------*/

void S21Matrix::ValidateIndex(int row, int col) const {
  // Если индекс меньше ноля либо превышает допустимый размер - выдаем
  // исключение
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Индекс вне диапазона");
}

void S21Matrix::ValidateDimensionsAreEqual(const S21Matrix &other) const {
  // Если размеры различаются, выдаем исключение
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Матрицы разных размеров");
}

void S21Matrix::ValidateSquare() const {
  // Если количество строк и столбцов не совпадают, выдаем исключение
  if (rows_ != cols_) throw std::logic_error("Матрица должна быть квадратной");
}

/*---------РАБОТА С ДАННЫМИ----------*/

void S21Matrix::CopyMatrixValues(S21Matrix &newMatrix, int rowCount,
                                 int colCount) {
  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < colCount; j++) {
      newMatrix.matrix_[i][j] = matrix_[i][j];  // Копируем значение элемента
    }
  }
}

void S21Matrix::CopyFromOther(const S21Matrix &other) {
  InitializeMatrix();
  // Копируем значения из другой матрицы
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

/*---------ИНИЦИАЛИЗАЦИЯ И ОСВОБОЖДЕНИЕ ПАМЯТИ----------*/

void S21Matrix::SetRowsCols(int rowCount, int colCount) {
  if (rowCount < 1 || colCount < 1)
    throw std::invalid_argument(
        "Количество столбцов и строк в матрице не может быть меньше 1");
  rows_ = rowCount;
  cols_ = colCount;
  InitializeMatrix();
}

void S21Matrix::InitializeMatrix() {
  matrix_ = new double *[rows_];
  for (int t = 0; t < rows_; ++t) {
    matrix_[t] = nullptr;
  }
  try {
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = 0;
      }
    }
  } catch (const std::bad_alloc &e) {
    FreeMatrixMemory();
    throw e;
  }
}

void S21Matrix::FreeMatrixMemory() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}
