
using SizeType = unsigned char;
using PathSizeType = int;

class Solution {
    inline PathSizeType border_incident(
        const std::vector<std::vector<int>>& grid
    ) const noexcept(true)
    {
        if (grid.size() == 1)
        {
            const auto& Row = grid.front();
            return std::accumulate(Row.rbegin(), Row.rend(), 1, [](int lhs, int rhs)
                {
                    return std::max(1, lhs - rhs);
                });
        }
        else
        {
            return std::accumulate(grid.rbegin(), grid.rend(), 1, [](int lhs, const std::vector<int>& rhs)
                {
                    return std::max(1, lhs - rhs.front());
                });
        }
    }

    inline void fill_path_sides(
        std::vector<std::vector<PathSizeType>>& weights,
        const SizeType height,
        const SizeType width,
        std::vector<std::vector<int>>& grid
    ) const noexcept(true)
    {
        PathSizeType ColumnPrev, RowPrev;
        auto& Row = weights.back();
        const auto& Paths = grid.back();
        RowPrev = ColumnPrev = Row.back() = 1 - Paths.back();

        for (SizeType i = height - 2; i != std::numeric_limits<SizeType>::max(); --i)
        {
            ColumnPrev = weights[i].back() = std::max(1, ColumnPrev - grid[i].back());
        }

        for (SizeType i = width - 2; i != std::numeric_limits<SizeType>::max(); --i)
        {
            RowPrev = Row[i] = std::max(1, RowPrev - Paths[i]);
        }
    }

    inline void fill_path_matrix(
        std::vector<std::vector<PathSizeType>>& weights,
        const SizeType height,
        const SizeType width,
        std::vector<std::vector<int>>& grid
    ) const noexcept(true)
    {
        for (SizeType y = height - 2; y != std::numeric_limits<SizeType>::max(); --y)
        {
            auto& Row = weights[y];
            auto& TopRow = weights[y + 1];
            const auto& Paths = grid[y];
            auto RowPrev = Row.back();

            for (SizeType x = width - 2; x != std::numeric_limits<SizeType>::max(); --x)
            {
                RowPrev = Row[x] = std::max(1, std::min(RowPrev, TopRow[x]) - Paths[x]);
            }
        }
    }

    inline PathSizeType solve_matrix_paths_and_return_minimizes_paths(
        const SizeType height,
        const SizeType width,
        std::vector<std::vector<int>>& grid
    ) const noexcept(true)
    {
        std::vector<std::vector<PathSizeType>> weights(height, std::vector<PathSizeType>(width, 0));

        fill_path_sides(weights, height, width, grid);
        fill_path_matrix(weights, height, width, grid);

        return weights.front().front();
    }
public:
    int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
        const auto height = dungeon.size(), width = dungeon.front().size();

        if (height == 1 || width == 1)
            return border_incident(dungeon);

        return solve_matrix_paths_and_return_minimizes_paths(height, width, dungeon);
    }
};
