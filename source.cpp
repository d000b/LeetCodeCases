
using SizeType = unsigned char;

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        const auto height = grid.size(), width = grid.front().size();

        std::vector<std::vector<size_t>> weights(height, std::vector<size_t>(width, 0));

        weights.front().front() = grid.front().front(); 
        
        const SizeType minimal = std::min(height, width);
        const SizeType maximal = std::max(height, width);

        auto& Row = weights.front();
        const auto& Paths = grid.front();
        
        for (SizeType i = 1u; i < minimal; ++i)
        {
            Row[i] = Paths[i] + Row[i - 1];
            weights[i].front() = grid[i].front() + weights[i - 1].front();
        }

        if (maximal == height)
            for (SizeType i = minimal; i < maximal; ++i)
                weights[i].front() = grid[i].front() + weights[i - 1].front();
        else
            for (SizeType i = minimal; i < maximal; ++i)
                Row[i] = Paths[i] + Row[i - 1];

        for (SizeType y = 1u; y < height; ++y)
        {
            auto& Row = weights[y];
            auto& TopRow = weights[y - 1];
            const auto& Paths = grid[y];
            for (SizeType x = 1u; x < width; ++x)
            {
                Row[x] = Paths[x] + std::min(Row[x - 1], TopRow[x]);
            }
        }

        return weights[height - 1][width - 1];
    }
};