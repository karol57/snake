#pragma once

struct size2d
{
    int width;
    int height;

    size2d operator*(int scale) const noexcept { return { width * scale, height * scale }; }

    int area() const noexcept { return width * height; }
};