#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <cmath>

#include "Defines.h"
#include "Vector4.h"

namespace YAM {

    class Mat4 {
    private:
        static constexpr uint8_t GRID_SIZE_X = 4;
        static constexpr uint8_t GRID_SIZE_Y = 4;

        std::array<Vector4, 4> grid{};

    public:
        Mat4() : Mat4(0) {}

        explicit Mat4(flt x) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    if (i == j)
                        grid[i][j] = x;
                    else
                        grid[i][j] = 0;
                }
            }
        }

        Mat4(const Mat4& clone) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    grid[i][j] = clone.grid[i][j];
                }
            }
        }

        flt operator[](const std::pair<int, int>& coordinates) const {
            return grid[coordinates.first][coordinates.second];
        }
        
        flt& operator[](const std::pair<int, int>& coordinates) {
            return grid[coordinates.first][coordinates.second];
        }
        
        Vector4& operator[](const uint32_t index) {
            return grid[index];
        }
        
        const Vector4& operator[](const uint32_t index) const {
            return grid[index];
        }

        Mat4 operator-() const {
            Mat4 result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = -this->grid[i][j];
                }
            }
            return result;
        }

        Mat4 operator+(const Mat4& another) const {
            Mat4 result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = grid[i][j] + another.grid[i][j];
                }
            }

            return result;
        }

        Mat4 operator-(const Mat4& another) const {
            Mat4 result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = grid[i][j] - another.grid[i][j];
                }
            }

            return result;
        }

        Mat4& operator=(const Mat4& another) {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    grid[i][j] = another.grid[i][j];
                }
            }

            return *this;
        }

        bool operator==(const Mat4& another) const {
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    if(grid[i][j] != another.grid[i][j])
                        return false;
                }
            }

            return true;
        }

        void operator+=(const Mat4& another) {
            *this = *this + another;
        }

        void operator-=(const Mat4& another) {
            *this = *this - another;
        }

        Mat4 operator*(const flt scalar) const {
            Mat4 result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    result.grid[i][j] = scalar * grid[i][j];
                }
            }
            return result;
        }

        void operator*=(flt scalar) {
            *this = *this * scalar;
        }

        Mat4 operator*(const Mat4& another) const {
            Mat4 result(0);
            for (int i = 0; i < GRID_SIZE_X; ++i) {
                for (int j = 0; j < GRID_SIZE_Y; ++j) {
                    for (int k = 0; k < GRID_SIZE_X; ++k) {
                        result.grid[i][j] += grid[k][j] * another.grid[i][k];
                    }
                }
            }

            return result;
        }

        void operator*=(const Mat4& Another) {
            *this = *this * Another;
        }

        Mat4 Transpose() const {
            Mat4 result(0);

            for (int i = 0; i < GRID_SIZE_X; i++) {
                for (int j = 0; j < GRID_SIZE_Y; j++) {
                    result.grid[i][j] = grid[j][i];
                }
            }
            return result;
        }

        flt Det() const {
            flt result = 1;
            Mat4 helper(*this);
            for (int i = 0; i < 4; i++) {
                for (int k = i + 1; k < 4; k++) {
                    const flt coefficient = helper.grid[k][i] / helper.grid[i][i];
                    for (int j = i; j < 4; j++)
                        helper.grid[k][j] = helper.grid[k][j] - coefficient * helper.grid[i][j];
                }
            }
            for (int i = 0; i < 4; i++)
                result *= helper.grid[i][i];
            return result;
        }

        Mat4 Inverse() const {
            std::array<flt, 16> result{};
            std::array<flt, 16> flatGrid{};

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


            const float det = this->Det();

            if (det == 0)
                return Mat4(0);

            Mat4 finalResult(0);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; ++j) {
                    finalResult.grid[i][j] = result[i * 4 + j] / det;
                }
            }

            return finalResult;
        }

        Mat4 ClearTranslation() const {
            Mat4 result = *this;
            
            result.grid[3][0] = 0;
            result.grid[3][1] = 0;
            result.grid[3][2] = 0;

            return result;
        }

        friend std::ostream &operator<<(std::ostream &os, const Mat4 &mat4) {
            for (int i = 0; i < 4; ++i) {
                os << "[ ";
                for (int j = 0; j < 4; ++j) {
                    os << mat4.grid[j][i] << " ";
                }
                os << "]" << "\n";
            }
            return os;
        }

        static Mat4 Translation(flt x, flt y, flt z) {
            Mat4 result(1);

            result[{3, 0}] = x;
            result[{3, 1}] = y;
            result[{3, 2}] = z;
            return  result;
        }


        static Mat4 Scale(flt x, flt y, flt z)
        {
            Mat4 result(1);

            result[{0, 0}] = x;
            result[{1, 1}] = y;
            result[{2, 2}] = z;
            return  result;
        }

        static Mat4 RotationX(flt radians)
        {
            Mat4 result(1);

            result[{1, 1}] = std::cos(radians);
            result[{2, 1}] = -std::sin(radians);
            result[{1, 2}] = std::sin(radians);
            result[{2, 2}] = std::cos(radians);
            return  result;
        }

        static Mat4 RotationY(flt radians)
        {
            Mat4 result(1);

            result[{0, 0}] = std::cos(radians);
            result[{0, 2}] = std::sin(radians);
            result[{2, 0}] = -std::sin(radians);
            result[{2, 2}] = std::cos(radians);
            return  result;
        }

        static Mat4 RotationZ(flt radians)
        {
            Mat4 result(1);

            result[{0, 0}] = std::cos(radians);
            result[{0, 1}] = -std::sin(radians);
            result[{1, 0}] = std::sin(radians);
            result[{1, 1}] = std::cos(radians);
            return  result;
        }

        static Mat4 Perspective(flt fov, flt aspect, flt near, flt far) {
            Mat4 result {0};
            
            flt f = std::cos(fov) / std::sin(fov);
            result[{0, 0}] = f / aspect;
            result[{1, 1}] = f;
            result[{2, 2}] = (far + near) / (near - far);
            result[{3, 2}] = -1.;
            result[{3, 2}] = 2. * far * near / (near - far);

            return result;
        }

        static Mat4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
            Mat4 result {0};
            
            const Vector3 forward = (center - eye).Normal();
            const Vector3 left = Vector3::Cross(forward, up);
            const Vector3 trueUp = Vector3::Cross(left, forward);

            result[0] = Vector4{left[0], up[0], -forward[0], 0};
            result[1] = Vector4{left[1], up[1], -forward[1], 0};
            result[2] = Vector4{left[2], up[2], -forward[2], 0};
            result[3] = Vector4{-eye[0], -eye[1], -eye[2], 1};

            return result;
        }
        
        Vector4 operator*(const Vector4& vec4) const {
            Vector4 result;
            result.x = vec4.x * grid[0][0] + vec4.y * grid[1][0] + vec4.z * grid[2][0] + vec4.w * grid[3][0];
            result.y = vec4.x * grid[0][1] + vec4.y * grid[1][1] + vec4.z * grid[2][1] + vec4.w * grid[3][1];
            result.z = vec4.x * grid[0][2] + vec4.y * grid[1][2] + vec4.z * grid[2][2] + vec4.w * grid[3][2];
            result.w = vec4.x * grid[0][3] + vec4.y * grid[1][3] + vec4.z * grid[2][3] + vec4.w * grid[3][3];

            return result;
        }
    };
}
