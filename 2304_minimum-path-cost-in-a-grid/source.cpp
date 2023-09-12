
using SizeType = unsigned char; // 2 <= m, n <= 50 ((less than unsigned char))
using SizeCostType = int; // max cost sum is 250'000 

class Solution {
    inline void adding_layer_transition_cost(
        std::vector<std::vector<SizeCostType>>& walkthrough_weights,
        const SizeType layer,
        const std::vector<std::vector<int>>& grid_indicies_layers, 
        const std::vector<std::vector<int>>& move_cost_layers
    ) const noexcept(true)
    {
        auto& weights = walkthrough_weights[layer];
        const auto width = weights.size();
        const auto& indicies = grid_indicies_layers[layer];
        const auto& next_indicies = grid_indicies_layers[layer + 1];

        std::remove_reference_t<decltype(weights)> costs(width, std::numeric_limits<SizeCostType>::max());
        for (const auto& index : indicies)
        {
            const auto& move_costs_to_element = move_cost_layers[index];
            for (SizeType i = 0u; i < width; ++i)
            {
                const auto walkthrough = index + move_costs_to_element[i] + next_indicies[i] + weights[i];
                auto& cost = costs[i];
                if (walkthrough < cost)
                    cost = walkthrough;
            }
        }

        walkthrough_weights[layer + 1] = std::move(costs);
    }
public:
    int minPathCost(std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& moveCost) {
        const auto depth = grid.size();
        const auto width = grid.front().size();
        
        std::vector<std::vector<SizeCostType>> cost_weigths(depth);
        cost_weigths.front() = std::vector<SizeCostType>(width, 0);

        for (SizeType i = 0; i < depth - 1; ++i)
        {
            adding_layer_transition_cost(cost_weigths, i, grid, moveCost);
        }

        for (const auto& it : cost_weigths)
        {
            std::copy(it.begin(), it.end(), std::ostream_iterator<SizeCostType>(std::cout, " "));
            std::cout << std::endl;
        }

        const auto layer = cost_weigths.back();
        return *std::min_element(layer.begin(), layer.end());
    }
};
