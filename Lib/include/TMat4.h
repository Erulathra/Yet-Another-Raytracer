#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <cmath>

namespace SG {
    template<typename T>
    class TMat4 {
    private:
        static const uint8_t GRID_SIZE_X = 4;
        static const uint8_t GRID_SIZE_Y = 4;

        std::array<std::array<T, 4>, 4> grid;

    public:
        TMat4() : TMat4(0) {}

        explicit TMat4(T x) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    if (i == j)
                        grid[i][j] = x;
                    else
                        grid[i][j] = 0;
                }
            }
        }

        TMat4(TMat4<T> &clone) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    grid[i][j] = clone.grid[i][j];
                }
            }
        }

        T &operator[](std::pair<int, int> coordinates) {
            return grid[coordinates.first][coordinates.second];
        }

        TMat4<T> operator-() {
            TMat4<T> result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = -this->grid[i][j];
                }
            }
            return result;
        }

        TMat4<T> operator+(TMat4<T> another) {
            TMat4<T> result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = grid[i][j] + another.grid[i][j];
                }
            }

            return result;
        }

        TMat4<T> operator-(TMat4<T> another) {
            TMat4<T> result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = grid[i][j] - another.grid[i][j];
                }
            }

            return result;
        }

        TMat4<T> &operator=(TMat4<T> another) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    grid[i][j] = another.grid[i][j];
                }
            }
        }

        bool operator==(TMat4<T> another) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    if(grid[i][j] != another.grid[i][j])
                        return false;
                }
            }
            return true;
        }

        void operator+=(TMat4<T> another) {
            *this = *this + another;
        }

        void operator-=(TMat4<T> another) {
            *this = *this - another;
        }

        TMat4<T> operator*(T scalar) {
            TMat4<T> result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = scalar * grid[i][j];
                }
            }
            return result;
        }

        void operator*=(T scalar) {
            *this = *this * scalar;
        }

        TMat4<T> operator*(TMat4<T> another) {
            TMat4<T> result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    for (int k = 0; k < GRID_SIZE_X; ++k) {
                        result.grid[i][j] += grid[k][j] * another.grid[i][k];
                    }
                }
            }

            return result;
        }

        void operator*=(TMat4<T> Another) {
            *this = *this * Another;
        }

        TMat4<T> Transpose() {
            TMat4<T> result(0);

            for (int i = 0; i < GRID_SIZE_X; i++) {
                for (int j = 0; j < GRID_SIZE_Y; j++) {
                    result.grid[i][j] = grid[j][i];
                }
            }
            return result;
        }

        double Det() {
            double Coefficient, result = 1;
            TMat4<T> helper(*this);
            for (int i = 0; i < 4; i++) {
                for (int k = i + 1; k < 4; k++) {
                    Coefficient = helper.grid[k][i] / helper.grid[i][i];
                    for (int j = i; j < 4; j++)
                        helper.grid[k][j] = helper.grid[k][j] - Coefficient * helper.grid[i][j];
                }
            }
            for (int i = 0; i < 4; i++)
                result *= helper.grid[i][i];
            return result;
        }

        TMat4<T> Inverse() {
            std::array<T, 16> result;
            std::array<T, 16> flatGrid;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; ++j) {
                    flatGrid[i + j * 4] = grid[j][i];
                }
            }

            result[0] = flatGrid[5] * flatGrid[10] * flatGrid[15] -
                        flatGrid[5] * flatGrid[11] * flatGrid[14] -
                        flatGrid[9] * flatGrid[6] * flatGrid[15] +
                        flatGrid[9] * flatGrid[7] * flatGrid[14] +
                        flatGrid[13] * flatGrid[6] * flatGrid[11] -
                        flatGrid[13] * flatGrid[7] * flatGrid[10];

            result[4] = -flatGrid[4] * flatGrid[10] * flatGrid[15] +
                        flatGrid[4] * flatGrid[11] * flatGrid[14] +
                        flatGrid[8] * flatGrid[6] * flatGrid[15] -
                        flatGrid[8] * flatGrid[7] * flatGrid[14] -
                        flatGrid[12] * flatGrid[6] * flatGrid[11] +
                        flatGrid[12] * flatGrid[7] * flatGrid[10];

            result[8] = flatGrid[4] * flatGrid[9] * flatGrid[15] -
                        flatGrid[4] * flatGrid[11] * flatGrid[13] -
                        flatGrid[8] * flatGrid[5] * flatGrid[15] +
                        flatGrid[8] * flatGrid[7] * flatGrid[13] +
                        flatGrid[12] * flatGrid[5] * flatGrid[11] -
                        flatGrid[12] * flatGrid[7] * flatGrid[9];

            result[12] = -flatGrid[4] * flatGrid[9] * flatGrid[14] +
                         flatGrid[4] * flatGrid[10] * flatGrid[13] +
                         flatGrid[8] * flatGrid[5] * flatGrid[14] -
                         flatGrid[8] * flatGrid[6] * flatGrid[13] -
                         flatGrid[12] * flatGrid[5] * flatGrid[10] +
                         flatGrid[12] * flatGrid[6] * flatGrid[9];

            result[1] = -flatGrid[1] * flatGrid[10] * flatGrid[15] +
                        flatGrid[1] * flatGrid[11] * flatGrid[14] +
                        flatGrid[9] * flatGrid[2] * flatGrid[15] -
                        flatGrid[9] * flatGrid[3] * flatGrid[14] -
                        flatGrid[13] * flatGrid[2] * flatGrid[11] +
                        flatGrid[13] * flatGrid[3] * flatGrid[10];

            result[5] = flatGrid[0] * flatGrid[10] * flatGrid[15] -
                        flatGrid[0] * flatGrid[11] * flatGrid[14] -
                        flatGrid[8] * flatGrid[2] * flatGrid[15] +
                        flatGrid[8] * flatGrid[3] * flatGrid[14] +
                        flatGrid[12] * flatGrid[2] * flatGrid[11] -
                        flatGrid[12] * flatGrid[3] * flatGrid[10];

            result[9] = -flatGrid[0] * flatGrid[9] * flatGrid[15] +
                        flatGrid[0] * flatGrid[11] * flatGrid[13] +
                        flatGrid[8] * flatGrid[1] * flatGrid[15] -
                        flatGrid[8] * flatGrid[3] * flatGrid[13] -
                        flatGrid[12] * flatGrid[1] * flatGrid[11] +
                        flatGrid[12] * flatGrid[3] * flatGrid[9];

            result[13] = flatGrid[0] * flatGrid[9] * flatGrid[14] -
                         flatGrid[0] * flatGrid[10] * flatGrid[13] -
                         flatGrid[8] * flatGrid[1] * flatGrid[14] +
                         flatGrid[8] * flatGrid[2] * flatGrid[13] +
                         flatGrid[12] * flatGrid[1] * flatGrid[10] -
                         flatGrid[12] * flatGrid[2] * flatGrid[9];

            result[2] = flatGrid[1] * flatGrid[6] * flatGrid[15] -
                        flatGrid[1] * flatGrid[7] * flatGrid[14] -
                        flatGrid[5] * flatGrid[2] * flatGrid[15] +
                        flatGrid[5] * flatGrid[3] * flatGrid[14] +
                        flatGrid[13] * flatGrid[2] * flatGrid[7] -
                        flatGrid[13] * flatGrid[3] * flatGrid[6];

            result[6] = -flatGrid[0] * flatGrid[6] * flatGrid[15] +
                        flatGrid[0] * flatGrid[7] * flatGrid[14] +
                        flatGrid[4] * flatGrid[2] * flatGrid[15] -
                        flatGrid[4] * flatGrid[3] * flatGrid[14] -
                        flatGrid[12] * flatGrid[2] * flatGrid[7] +
                        flatGrid[12] * flatGrid[3] * flatGrid[6];

            result[10] = flatGrid[0] * flatGrid[5] * flatGrid[15] -
                         flatGrid[0] * flatGrid[7] * flatGrid[13] -
                         flatGrid[4] * flatGrid[1] * flatGrid[15] +
                         flatGrid[4] * flatGrid[3] * flatGrid[13] +
                         flatGrid[12] * flatGrid[1] * flatGrid[7] -
                         flatGrid[12] * flatGrid[3] * flatGrid[5];

            result[14] = -flatGrid[0] * flatGrid[5] * flatGrid[14] +
                         flatGrid[0] * flatGrid[6] * flatGrid[13] +
                         flatGrid[4] * flatGrid[1] * flatGrid[14] -
                         flatGrid[4] * flatGrid[2] * flatGrid[13] -
                         flatGrid[12] * flatGrid[1] * flatGrid[6] +
                         flatGrid[12] * flatGrid[2] * flatGrid[5];

            result[3] = -flatGrid[1] * flatGrid[6] * flatGrid[11] +
                        flatGrid[1] * flatGrid[7] * flatGrid[10] +
                        flatGrid[5] * flatGrid[2] * flatGrid[11] -
                        flatGrid[5] * flatGrid[3] * flatGrid[10] -
                        flatGrid[9] * flatGrid[2] * flatGrid[7] +
                        flatGrid[9] * flatGrid[3] * flatGrid[6];

            result[7] = flatGrid[0] * flatGrid[6] * flatGrid[11] -
                        flatGrid[0] * flatGrid[7] * flatGrid[10] -
                        flatGrid[4] * flatGrid[2] * flatGrid[11] +
                        flatGrid[4] * flatGrid[3] * flatGrid[10] +
                        flatGrid[8] * flatGrid[2] * flatGrid[7] -
                        flatGrid[8] * flatGrid[3] * flatGrid[6];

            result[11] = -flatGrid[0] * flatGrid[5] * flatGrid[11] +
                         flatGrid[0] * flatGrid[7] * flatGrid[9] +
                         flatGrid[4] * flatGrid[1] * flatGrid[11] -
                         flatGrid[4] * flatGrid[3] * flatGrid[9] -
                         flatGrid[8] * flatGrid[1] * flatGrid[7] +
                         flatGrid[8] * flatGrid[3] * flatGrid[5];

            result[15] = flatGrid[0] * flatGrid[5] * flatGrid[10] -
                         flatGrid[0] * flatGrid[6] * flatGrid[9] -
                         flatGrid[4] * flatGrid[1] * flatGrid[10] +
                         flatGrid[4] * flatGrid[2] * flatGrid[9] +
                         flatGrid[8] * flatGrid[1] * flatGrid[6] -
                         flatGrid[8] * flatGrid[2] * flatGrid[5];


            float det = this->Det();

            if (det == 0)
                return TMat4<T>(0);

            TMat4<T> finalResult(0);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; ++j) {
                    finalResult.grid[i][j] = result[i * 4 + j] / det;
                }
            }

            return finalResult;
        }

        friend std::ostream &operator<<(std::ostream &os, const TMat4 &mat4) {
            for (int i = 0; i < 4; ++i) {
                os << "[ ";
                for (int j = 0; j < 4; ++j) {
                    os << mat4.grid[j][i] << " ";
                }
                os << "]" << "\n";
            }
            return os;
        }

        static TMat4<T> Translation(T x, T y, T z) {
            TMat4<T> Result(1);

            Result[{3, 0}] = x;
            Result[{3, 1}] = y;
            Result[{3, 2}] = z;
            return  Result;
        }

        static TMat4<T> Scale(T x, T y, T z)
        {
            TMat4<T> Result(1);

            Result[{0, 0}] = x;
            Result[{1, 1}] = y;
            Result[{2, 2}] = z;
            return  Result;
        }

        static TMat4<T> RotationX(T radians)
        {
            TMat4<T> Result(1);

            Result[{1, 1}] = std::cos(radians);
            Result[{2, 1}] = -std::sin(radians);
            Result[{1, 2}] = std::sin(radians);
            Result[{2, 2}] = std::cos(radians);
            return  Result;
        }

        static TMat4<T> RotationY(T radians)
        {
            TMat4<T> Result(1);

            Result[{0, 0}] = std::cos(radians);
            Result[{0, 2}] = std::sin(radians);
            Result[{2, 0}] = -std::sin(radians);
            Result[{2, 2}] = std::cos(radians);
            return  Result;
        }

        static TMat4<T> RotationZ(T radians)
        {
            TMat4<T> Result(1);

            Result[{0, 0}] = std::cos(radians);
            Result[{0, 1}] = -std::sin(radians);
            Result[{1, 0}] = std::sin(radians);
            Result[{1, 1}] = std::cos(radians);
            return  Result;
        }

    };
}