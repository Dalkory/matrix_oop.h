#ifndef S21_MATRIX_S21_MATRIX_OOP_H_
#define S21_MATRIX_S21_MATRIX_OOP_H_

#include <cmath>
#include <functional>
#include <iostream>  // нужен для main в test

// Объявляем пользовательский класс "Matrix"
class S21Matrix {
 public:
  // Конструкторы и деструктор
  S21Matrix();  // Дефолтный (пустой) конструктор
  S21Matrix(int rows, int cols);  // Конструктор с параметрами
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other);  // Конструктор перемещения
  ~S21Matrix();                  // Деструктор

  // Перегрузка операторов
  S21Matrix& operator=(const S21Matrix& other) noexcept;  // Присваивание
  S21Matrix& operator=(
      S21Matrix&& other) noexcept;  // Присваивание через перемещение
  S21Matrix operator+=(const S21Matrix& other);  // Сложение с присваиванием
  S21Matrix operator+(const S21Matrix& other) const;  // Сложение
  S21Matrix operator-=(const S21Matrix& other);  // Вычитание с присваиванием
  S21Matrix operator-(const S21Matrix& other) const;  // Вычитание
  S21Matrix operator*(const S21Matrix& other) const;  // Умножение
  friend S21Matrix operator*(double multiplier, const S21Matrix& matrix);
  friend S21Matrix operator*(const S21Matrix& matrix, double multiplier);
  bool operator==(const S21Matrix& other) const noexcept;  // Оператор равенства
  S21Matrix operator*=(
      const S21Matrix& other);  // Умножение матриц с присваиванием
  S21Matrix operator*=(
      const double mul);  // Умножение матрицы на скаляр с присваиванием
  double& operator()(int i, int j);  // Доступ к элементам матрицы
  const double& operator()(
      int i, int j) const;  // Доступ к элементам матрицы (версия const)

  // Основные функции
  bool EqMatrix(const S21Matrix& other) const noexcept;  // Сравнение матриц
  void SumMatrix(const S21Matrix& other);  // Добавление другой матрицы
  void SubMatrix(const S21Matrix& other);  // Вычитание другой матрицы
  void MulNumber(const double num) noexcept;  // Умножение матрицы на число
  void MulMatrix(const S21Matrix& other);  // Умножение матриц
  S21Matrix Transpose() const noexcept;  // Транспонирование матрицы
  S21Matrix CalcComplements() const;  // Расчёт дополнений матрицы
  double Determinant() const;  // Расчёт детерминанта
  S21Matrix InverseMatrix();   // Расчёт обратной матрицы

  // Геттеры и сеттеры для доступа к приватным полям класса
  int GetRows() const;  // Получить количество строк
  int GetCols() const;  // Получить количество столбцов
  void SetRows(int rows);  // Установить количество строк
  void SetCols(int cols);  // Установить количество столбцов
  void SetRowsCols(int rowCount, int colCount);

 private:
  // Приватные поля
  int rows_, cols_;  // Количество строк и столбцов матрицы
  double** matrix_;  // Двумерный массив, представляющий матрицу

  // Приватные вспомогательные функции
  void InitializeMatrix();  // Инициализация матрицы
  void CopyFromOther(const S21Matrix& other);  // Копирование матрицы
  void FreeMatrixMemory();  // Очистка памяти матрицы
  void MatrixOperation(
      const S21Matrix& other,
      std::function<double(double, double)>
          operation);  // Реализация операций вычитания и сложения над матрицами
  void CopyMatrixValues(S21Matrix& newMatrix, int rows,
                        int cols);  // Копирование значений матрицы
  void ValidateDimensionsAreEqual(const S21Matrix& other)
      const;  // Проверка, что матрицы имеют одинаковые размеры
  void ValidateSquare() const;  // Проверка, что матрица квадратная
  void CreateCofactorMatrix(
      S21Matrix& complements) const;  // Создание матрицы коплексов
  void CreateMinor(S21Matrix& minor, int row,
                   int col) const;      // Создание минора
  double CalculateDeterminant() const;  // Подсчёт детерминанта
  void ValidateIndex(int row, int col) const;  // Проверка индекса
};

#endif  // S21_MATRIX_S21_MATRIX_OOP_H_