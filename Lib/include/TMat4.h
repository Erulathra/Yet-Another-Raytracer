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

        std::array<std::array<T, 4>, 4> Grid;

    public:
        TMat4() : TMat4(0) {}

        TMat4(T x) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    if (i == j)
                        Grid[i][j] = x;
                    else
                        Grid[i][j] = 0;
                }
            }
        }

        TMat4(TMat4<T> &Clone) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    Grid[i][j] = Clone.Grid[i][j];
                }
            }
        }

        T &operator[](std::pair<int, int> Coordinates) {
            return Grid[Coordinates.first][Coordinates.second];
        }

        TMat4<T>& operator-() {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    this->Grid[i][j] = -this->Grid[i][j];
                }
            }
            return *this;
        }

        TMat4<T> operator+(TMat4<T> Another) {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    Result.Grid[i][j] = Grid[i][j] + Another.Grid[i][j];
                }
            }

            return Result;
        }

        TMat4<T> operator-(TMat4<T> Another) {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    Result.Grid[i][j] = Grid[i][j] - Another.Grid[i][j];
                }
            }

            return Result;
        }

        TMat4<T> &operator=(TMat4<T> Another) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    Grid[i][j] = Another.Grid[i][j];
                }
            }
        }

        bool operator==(TMat4<T> Another) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    if(Grid[i][j] != Another.Grid[i][j])
                        return false;
                }
            }
            return true;
        }

        void operator+=(TMat4<T> Another) {
            *this = *this + Another;
        }

        void operator-=(TMat4<T> Another) {
            *this = *this - Another;
        }

        TMat4<T> operator*(T Scalar) {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    Result.Grid[i][j] = Scalar * Grid[i][j];
                }
            }
            return Result;
        }

        void operator*=(T Scalar) {
            *this = *this * Scalar;
        }

        TMat4<T> operator*(TMat4<T> Another) {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    for (int k = 0; k < GRID_SIZE_X; ++k) {
                        Result.Grid[i][j] += Grid[k][j] * Another.Grid[i][k];
                    }
                }
            }

            return Result;
        }

        void operator*=(TMat4<T> Another) {
            *this = *this * Another;
        }

        TMat4<T> Transpose() {
            TMat4<T> Result(0);

            for (int i = 0; i < GRID_SIZE_X; i++) {
                for (int j = 0; j < GRID_SIZE_Y; j++) {
                    Result.Grid[i][j] = Grid[j][i];
                }
            }
            return Result;
        }

        double Det() {
            double Coefficient, Result = 1;
            TMat4<T> Helper(*this);
            for (int i = 0; i < 4; i++) {
                for (int k = i + 1; k < 4; k++) {
                    Coefficient = Helper.Grid[k][i] / Helper.Grid[i][i];
                    for (int j = i; j < 4; j++)
                        Helper.Grid[k][j] = Helper.Grid[k][j] - Coefficient * Helper.Grid[i][j];
                }
            }
            for (int i = 0; i < 4; i++)
                Result *= Helper.Grid[i][i];
            return Result;
        }

        TMat4<T> Inverse() {
            std::array<T, 16> Result;
            std::array<T, 16> FlatGrid;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; ++j) {
                    FlatGrid[i + j * 4] = Grid[j][i];
                }
            }

            Result[0] = FlatGrid[5] * FlatGrid[10] * FlatGrid[15] -
                        FlatGrid[5] * FlatGrid[11] * FlatGrid[14] -
                        FlatGrid[9] * FlatGrid[6] * FlatGrid[15] +
                        FlatGrid[9] * FlatGrid[7] * FlatGrid[14] +
                        FlatGrid[13] * FlatGrid[6] * FlatGrid[11] -
                        FlatGrid[13] * FlatGrid[7] * FlatGrid[10];

            Result[4] = -FlatGrid[4] * FlatGrid[10] * FlatGrid[15] +
                        FlatGrid[4] * FlatGrid[11] * FlatGrid[14] +
                        FlatGrid[8] * FlatGrid[6] * FlatGrid[15] -
                        FlatGrid[8] * FlatGrid[7] * FlatGrid[14] -
                        FlatGrid[12] * FlatGrid[6] * FlatGrid[11] +
                        FlatGrid[12] * FlatGrid[7] * FlatGrid[10];

            Result[8] = FlatGrid[4] * FlatGrid[9] * FlatGrid[15] -
                        FlatGrid[4] * FlatGrid[11] * FlatGrid[13] -
                        FlatGrid[8] * FlatGrid[5] * FlatGrid[15] +
                        FlatGrid[8] * FlatGrid[7] * FlatGrid[13] +
                        FlatGrid[12] * FlatGrid[5] * FlatGrid[11] -
                        FlatGrid[12] * FlatGrid[7] * FlatGrid[9];

            Result[12] = -FlatGrid[4] * FlatGrid[9] * FlatGrid[14] +
                         FlatGrid[4] * FlatGrid[10] * FlatGrid[13] +
                         FlatGrid[8] * FlatGrid[5] * FlatGrid[14] -
                         FlatGrid[8] * FlatGrid[6] * FlatGrid[13] -
                         FlatGrid[12] * FlatGrid[5] * FlatGrid[10] +
                         FlatGrid[12] * FlatGrid[6] * FlatGrid[9];

            Result[1] = -FlatGrid[1] * FlatGrid[10] * FlatGrid[15] +
                        FlatGrid[1] * FlatGrid[11] * FlatGrid[14] +
                        FlatGrid[9] * FlatGrid[2] * FlatGrid[15] -
                        FlatGrid[9] * FlatGrid[3] * FlatGrid[14] -
                        FlatGrid[13] * FlatGrid[2] * FlatGrid[11] +
                        FlatGrid[13] * FlatGrid[3] * FlatGrid[10];

            Result[5] = FlatGrid[0] * FlatGrid[10] * FlatGrid[15] -
                        FlatGrid[0] * FlatGrid[11] * FlatGrid[14] -
                        FlatGrid[8] * FlatGrid[2] * FlatGrid[15] +
                        FlatGrid[8] * FlatGrid[3] * FlatGrid[14] +
                        FlatGrid[12] * FlatGrid[2] * FlatGrid[11] -
                        FlatGrid[12] * FlatGrid[3] * FlatGrid[10];

            Result[9] = -FlatGrid[0] * FlatGrid[9] * FlatGrid[15] +
                        FlatGrid[0] * FlatGrid[11] * FlatGrid[13] +
                        FlatGrid[8] * FlatGrid[1] * FlatGrid[15] -
                        FlatGrid[8] * FlatGrid[3] * FlatGrid[13] -
                        FlatGrid[12] * FlatGrid[1] * FlatGrid[11] +
                        FlatGrid[12] * FlatGrid[3] * FlatGrid[9];

            Result[13] = FlatGrid[0] * FlatGrid[9] * FlatGrid[14] -
                         FlatGrid[0] * FlatGrid[10] * FlatGrid[13] -
                         FlatGrid[8] * FlatGrid[1] * FlatGrid[14] +
                         FlatGrid[8] * FlatGrid[2] * FlatGrid[13] +
                         FlatGrid[12] * FlatGrid[1] * FlatGrid[10] -
                         FlatGrid[12] * FlatGrid[2] * FlatGrid[9];

            Result[2] = FlatGrid[1] * FlatGrid[6] * FlatGrid[15] -
                        FlatGrid[1] * FlatGrid[7] * FlatGrid[14] -
                        FlatGrid[5] * FlatGrid[2] * FlatGrid[15] +
                        FlatGrid[5] * FlatGrid[3] * FlatGrid[14] +
                        FlatGrid[13] * FlatGrid[2] * FlatGrid[7] -
                        FlatGrid[13] * FlatGrid[3] * FlatGrid[6];

            Result[6] = -FlatGrid[0] * FlatGrid[6] * FlatGrid[15] +
                        FlatGrid[0] * FlatGrid[7] * FlatGrid[14] +
                        FlatGrid[4] * FlatGrid[2] * FlatGrid[15] -
                        FlatGrid[4] * FlatGrid[3] * FlatGrid[14] -
                        FlatGrid[12] * FlatGrid[2] * FlatGrid[7] +
                        FlatGrid[12] * FlatGrid[3] * FlatGrid[6];

            Result[10] = FlatGrid[0] * FlatGrid[5] * FlatGrid[15] -
                         FlatGrid[0] * FlatGrid[7] * FlatGrid[13] -
                         FlatGrid[4] * FlatGrid[1] * FlatGrid[15] +
                         FlatGrid[4] * FlatGrid[3] * FlatGrid[13] +
                         FlatGrid[12] * FlatGrid[1] * FlatGrid[7] -
                         FlatGrid[12] * FlatGrid[3] * FlatGrid[5];

            Result[14] = -FlatGrid[0] * FlatGrid[5] * FlatGrid[14] +
                         FlatGrid[0] * FlatGrid[6] * FlatGrid[13] +
                         FlatGrid[4] * FlatGrid[1] * FlatGrid[14] -
                         FlatGrid[4] * FlatGrid[2] * FlatGrid[13] -
                         FlatGrid[12] * FlatGrid[1] * FlatGrid[6] +
                         FlatGrid[12] * FlatGrid[2] * FlatGrid[5];

            Result[3] = -FlatGrid[1] * FlatGrid[6] * FlatGrid[11] +
                        FlatGrid[1] * FlatGrid[7] * FlatGrid[10] +
                        FlatGrid[5] * FlatGrid[2] * FlatGrid[11] -
                        FlatGrid[5] * FlatGrid[3] * FlatGrid[10] -
                        FlatGrid[9] * FlatGrid[2] * FlatGrid[7] +
                        FlatGrid[9] * FlatGrid[3] * FlatGrid[6];

            Result[7] = FlatGrid[0] * FlatGrid[6] * FlatGrid[11] -
                        FlatGrid[0] * FlatGrid[7] * FlatGrid[10] -
                        FlatGrid[4] * FlatGrid[2] * FlatGrid[11] +
                        FlatGrid[4] * FlatGrid[3] * FlatGrid[10] +
                        FlatGrid[8] * FlatGrid[2] * FlatGrid[7] -
                        FlatGrid[8] * FlatGrid[3] * FlatGrid[6];

            Result[11] = -FlatGrid[0] * FlatGrid[5] * FlatGrid[11] +
                         FlatGrid[0] * FlatGrid[7] * FlatGrid[9] +
                         FlatGrid[4] * FlatGrid[1] * FlatGrid[11] -
                         FlatGrid[4] * FlatGrid[3] * FlatGrid[9] -
                         FlatGrid[8] * FlatGrid[1] * FlatGrid[7] +
                         FlatGrid[8] * FlatGrid[3] * FlatGrid[5];

            Result[15] = FlatGrid[0] * FlatGrid[5] * FlatGrid[10] -
                         FlatGrid[0] * FlatGrid[6] * FlatGrid[9] -
                         FlatGrid[4] * FlatGrid[1] * FlatGrid[10] +
                         FlatGrid[4] * FlatGrid[2] * FlatGrid[9] +
                         FlatGrid[8] * FlatGrid[1] * FlatGrid[6] -
                         FlatGrid[8] * FlatGrid[2] * FlatGrid[5];


            float Det = this->Det();

            if (Det == 0)
                return TMat4<T>(0);

            TMat4<T> FinalResult(0);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; ++j) {
                    FinalResult.Grid[i][j] = Result[i * 4 + j] / Det;
                }
            }

            return FinalResult;
        }

        friend std::ostream &operator<<(std::ostream &os, const TMat4 &mat4) {
            for (int i = 0; i < 4; ++i) {
                os << "[ ";
                for (int j = 0; j < 4; ++j) {
                    os << mat4.Grid[j][i] << " ";
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