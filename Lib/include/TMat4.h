#ifndef REALISTICENGINE_TMAT4_H
#define REALISTICENGINE_TMAT4_H

#include <array>
#include <cstdint>

namespace SG
{
    template<typename T> class TMat4
    {
    private:
        static const uint8_t GRID_SIZE_X = 4;
        static const uint8_t GRID_SIZE_Y = 4;

        std::array<std::array<T, 4>, 4> Grid;

    public:
        TMat4() : TMat4(0)
        {}

        TMat4(T x)
        {
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    if (i == j)
                        Grid[i][j] = 1;
                    else
                        Grid[i][j] = 0;
                }
            }
        }

        TMat4(TMat4<T>& Clone)
        {
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    Grid[i][j] = Clone.Grid[i][j];
                }
            }
        }

        T operator[](std::pair<int, int> Coordinates)
        {
            return Grid[Coordinates.first][Coordinates.second];
        }

        TMat4<T> operator-()
        {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    Result[i][j] = -Grid[i][j];
                }
            }
            return Result;
        }

        TMat4<T> operator+(TMat4<T> Another)
        {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    Result.Grid[i][j] = Grid[i][j] + Another.Grid[i][j];
                }
            }

            return Result;
        }

        TMat4<T> operator-(TMat4<T> Another)
        {
            return *this + (-Another);
        }

        TMat4<T>& operator=(TMat4<T> Another)
        {
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    Grid[i][j] = Another.Grid[i][j];
                }
            }
        }

        void operator+=(TMat4<T> Another)
        {
            *this = *this + Another;
        }

        void operator-=(TMat4<T> Another)
        {
            *this = *this - Another;
        }

        TMat4<T> operator*(T Scalar)
        {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    Result.Grid[i][j] = Scalar * Grid[i][j];
                }
            }
            return Result;
        }

        void operator*=(T Scalar)
        {
            *this = *this * Scalar;
        }

        TMat4<T> operator*(TMat4<T> Another)
        {
            TMat4<T> Result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    for (int k = 0; k < GRID_SIZE_X; ++k)
                    {
                        Result.Grid[i][j] += Grid[i][k] * Another.Grid[k][j];
                    }
                }
            }

            return Result;
        }

        void operator*=(TMat4<T> Another)
        {
            *this = *this * Another;
        }

        TMat4<T> Transpose()
        {
            TMat4<T> Result(0);

            for (int i = 0; i < GRID_SIZE_X; ++i)
            {
                for (int j = 0; j < GRID_SIZE_Y; ++j)
                {
                    Result[i][j] = Grid[j][i];
                }
            }
            return Result;
        }

        double Det()
        {
            double Coefficient, Result = 1;
            TMat4<T> Helper(*this);
            for (int i = 0; i < 4; i++)
            {
                for (int k = i + 1; k < 4; k++)
                {
                    Coefficient = Helper[k][i] / Helper[i][i];
                    for (int j = i; j < 4; j++)
                        Helper[k][j] = Helper[k][j] - Coefficient * Helper[i][j];
                }
            }
            for (int i = 0; i < 4; i++)
                Result *= Helper[i][i];
            return Result;
        }

    };
}

#endif //REALISTICENGINE_TMAT4_H
