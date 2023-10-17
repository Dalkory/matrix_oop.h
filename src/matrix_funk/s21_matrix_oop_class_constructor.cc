#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_{}, cols_{}, matrix_{} {}

S21Matrix::S21Matrix(int rowCount, int colCount) {
  if (rowCount < 1 || colCount < 1)
    throw std::invalid_argument(
        "Количество столбцов и строк в матрице не может быть меньше 1");
  rows_ = rowCount;
  cols_ = colCount;
  InitializeMatrix();
}

S21Matrix::~S21Matrix() { FreeMatrixMemory(); }

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  // Проверка на самокопирование
  if (&other == this)
    throw std::logic_error("Нельзя копировать объект в самого себя");
  CopyFromOther(other);  // Копирование значений матрицы из другого объекта
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  matrix_ = other.matrix_;  // Перемещение указателя на матрицу
  rows_ = other.rows_;  // Перемещение количества строк
  cols_ = other.cols_;  // Перемещение количества столбцов
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rowCount) {
  S21Matrix resizedMatrix(rowCount, cols_);
  double cutoffEdge = rows_;
  if (rowCount < rows_)
    cutoffEdge = rowCount;  // Определение границы копирования
  CopyMatrixValues(resizedMatrix, cutoffEdge,
                   cols_);  // Копирование значений в новую матрицу
  *this = resizedMatrix;
}

void S21Matrix::SetCols(int colCount) {
  S21Matrix resizedMatrix(rows_, colCount);
  double cutoffEdge = cols_;
  if (colCount < cols_)
    cutoffEdge = colCount;  // Определение границы копирования
  CopyMatrixValues(resizedMatrix, rows_,
                   cutoffEdge);  // Копирование значений в новую матрицу
  *this = resizedMatrix;
}