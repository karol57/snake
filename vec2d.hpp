#pragma once

struct vec2d
{
    vec2d() noexcept = default;
    constexpr vec2d(int x, int y) noexcept : x{x}, y{y} {}
    constexpr vec2d(const vec2d&) noexcept = default;
    constexpr vec2d(vec2d&&) noexcept = default;
    ~vec2d() = default;

    constexpr vec2d& operator=(const vec2d&) noexcept = default;
    constexpr vec2d& operator=(vec2d&&) noexcept = default;

    constexpr bool operator==(const vec2d& rhs) const noexcept { return x == rhs.x && y == rhs.y; }
    constexpr bool operator!=(const vec2d& rhs) const noexcept { return x != rhs.x || y != rhs.y; }
    constexpr bool operator<(const vec2d& rhs) const noexcept
    {
        if (y < rhs.y)
            return true;
        if (y > rhs.y)
            return false;
        return x < rhs.x;
    }

    constexpr vec2d operator-(const vec2d& rhs) const noexcept { return { x - rhs.x, y - rhs.y }; }

    constexpr vec2d operator*(int scale) const noexcept { return { x * scale, y * scale }; }

    int x;
    int y;
};