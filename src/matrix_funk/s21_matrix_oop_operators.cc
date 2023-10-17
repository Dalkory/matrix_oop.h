#include "../s21_matrix_oop.h"

/*---------ОПЕРАТОРЫ ПЕРЕОПРЕДЕЛЕНИЯ----------*/

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix resultMatrix(*this);  // Создание новой матрицы на основе текущей
  resultMatrix.SumMatrix(other);  // Используем метод суммирования матриц
  return resultMatrix;  // Возвращаем полученную матрицу
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix resultMatrix(*this);
  resultMatrix.SubMatrix(other);
  return resultMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix resultMatrix(*this);
  resultMatrix.MulMatrix(other);
  return resultMatrix;
}

S21Matrix operator*(double multiplier, const S21Matrix &matrix) {
  S21Matrix resultMatrix(matrix);
  resultMatrix.MulNumber(multiplier);
  return resultMatrix;
}

S21Matrix operator*(const S21Matrix &matrix, double multiplier) {
  S21Matrix resultMatrix(matrix);
  resultMatrix.MulNumber(multiplier);
  return resultMatrix;
}

bool S21Matrix::operator==(const S21Matrix &otherMatrix) const noexcept {
  return EqMatrix(otherMatrix);
}

/*---------ОПЕРАТОРЫ ПРИСВОЕНИЯ----------*/

// Копирует
S21Matrix &S21Matrix::operator=(const S21Matrix &otherMatrix) noexcept {
  if (this == &otherMatrix) {  // Защита от самоприсвоения
    return *this;
  }

  FreeMatrixMemory();  // Освобождаем память текущей матрицы перед присвоением
  rows_ = otherMatrix.rows_;
  cols_ = otherMatrix.cols_;
  CopyFromOther(otherMatrix);  // Копирование значений матрицы
  return *this;
}

// Перемещает
S21Matrix &S21Matrix::operator=(S21Matrix &&otherMatrix) noexcept {
  if (this == &otherMatrix) {
    return *this;
  }
  FreeMatrixMemory();
  rows_ = std::exchange(otherMatrix.rows_, 0);
  cols_ = std::exchange(otherMatrix.cols_, 0);
  matrix_ = std::exchange(otherMatrix.matrix_, nullptr);
  return *this;
}

/*---------ОПЕРАТОРЫ ДЛЯ ИЗМЕНЕНИЯ СОСТОЯНИЯ ОБЪЕКТА----------*/

S21Matrix S21Matrix::operator+=(const S21Matrix &otherMatrix) {
  SumMatrix(otherMatrix);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &otherMatrix) {
  SubMatrix(otherMatrix);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &otherMatrix) {
  MulMatrix(otherMatrix);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double multiplier) {
  MulNumber(multiplier);
  return *this;
}

/*---------ОПЕРАТОРЫ ПОЛУЧЕНИЯ ЗНАЧЕНИЯ----------*/

/*     Это то как мы называем нашу S21Matrix     */

double &S21Matrix::operator()(int rowIndex, int columnIndex) {
  ValidateIndex(rowIndex, columnIndex);
  return matrix_[rowIndex][columnIndex];
}

const double &S21Matrix::operator()(int rowIndex, int columnIndex) const {
  ValidateIndex(rowIndex, columnIndex);
  return matrix_[rowIndex][columnIndex];
}