
using SizeType = unsigned char; // because Constraints: length like no more 200
using PathSizeType = unsigned int; // because Constraints: 200 x 200 x 2 (P.S. I wish use unsinged short by this less than 80'000 (> 65535))

class Solution {
    inline PathSizeType border_incident(
        const std::vector<std::vector<int>>& grid
    ) const noexcept(true)
    {
        if (grid.size() == 1)
        {
            const auto& Row = grid.front();
            return std::reduce(Row.begin(), Row.end());
        }
        else
        {
            return std::accumulate(grid.begin(), grid.end(), 0, [](int lhs, const std::vector<int>& rhs)
            {
                return lhs + rhs.front();
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
        weights.front().front() = grid.front().front();
        
        const SizeType minimal = std::min(height, width);
        const SizeType maximal = std::max(height, width);

        auto& Row = weights.front();
        PathSizeType ColumnPrev, RowPrev;
        RowPrev = ColumnPrev = Row.front();

        const auto& Paths = grid.front();
        for (SizeType i = 1u; i < minimal; ++i)
        {
            RowPrev = Row[i] = Paths[i] + RowPrev;
            ColumnPrev = weights[i].front() = grid[i].front() + ColumnPrev;
        }

        if (maximal == height)
        {
            for (SizeType i = minimal; i < maximal; ++i)
                ColumnPrev = weights[i].front() = grid[i].front() + ColumnPrev;
        }
        else
        {
            for (SizeType i = minimal; i < maximal; ++i)
                RowPrev = Row[i] = Paths[i] + RowPrev;
        }
    }

    inline void fill_path_matrix(
        std::vector<std::vector<PathSizeType>>& weights,
        const SizeType height,
        const SizeType width,
        std::vector<std::vector<int>>& grid
    ) const noexcept(true)
    {
        for (SizeType y = 1u; y < height; ++y)
        {
            auto& Row = weights[y];
            auto& TopRow = weights[y - 1];
            const auto& Paths = grid[y];
            auto RowPrev = Row.front();

            for (SizeType x = 1u; x < width; ++x)
            {
                RowPrev = Row[x] = Paths[x] + std::min(RowPrev, TopRow[x]);
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

        return weights.back().back();
    }
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        const auto height = grid.size(), width = grid.front().size();            
        
        if (height == 1 || width == 1)
            return border_incident(grid);

        return solve_matrix_paths_and_return_minimizes_paths(height, width, grid);
    }
};