#include <vector>
#include <queue>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <memory>

// forward declarations
struct Node;

struct Puzzle
{
    std::unordered_set<char> car_names;

    std::unordered_map<char, bool> car_orientation;
    
    std::unordered_map<char, int> car_size;

    std::unordered_map<char, int> fixed_position;

    std::unique_ptr<Node> initial_node;

    int search_count = 1;

    Puzzle() : initial_node(nullptr)
    {
    }
    
    virtual ~Puzzle()
    {
    }
};

struct State
{
    Puzzle &puzzle;
    
    std::unordered_map<char, int> var_pos;

    State(Puzzle &puzzle, std::unordered_map<char, int> var_pos) :
        puzzle(puzzle), var_pos(var_pos)
    {
    }

    virtual ~State()
    {
    }

    bool is_goal() const
    {
        auto it = var_pos.find('x');
        return it->second == 5;
    }

    std::array<std::array<char, 6>, 6> get_grid()
    {
        std::array<std::array<char, 6>, 6> grid;
        
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                grid[i][j] = '.';
            }
        }

        for (auto car_name : puzzle.car_names) {
            auto orientation = puzzle.car_orientation[car_name];
            auto size = puzzle.car_size[car_name];
            auto fp = puzzle.fixed_position[car_name];
            if (car_name == 'x' && (var_pos[car_name] + size) > 6) {
                size -= 1;   
            }
            if (orientation) { // vertical
                for (int d = 0; d < size; d++) {
                    grid[var_pos[car_name] + d][fp] = car_name;
                }
            }
            else { // horizontal
                for (int d = 0; d < size; d++) {
                    grid[fp][var_pos[car_name] + d] = car_name;
                }
            }
        }

        return grid;
    }

    std::vector<State> expand()
    {
        const std::array<std::array<char, 6>, 6> grid = get_grid();
        std::vector<State> new_states;

        for (auto car_name : puzzle.car_names) {
            auto p = var_pos[car_name];
            auto fp = puzzle.fixed_position[car_name];
            auto orientation = puzzle.car_orientation[car_name];

            for (int np = p - 1; np >= 0; np -= 1) {
                if (orientation && grid[np][fp] != '.') { // vert
                    break;
                }
                if (!orientation && grid[fp][np] != '.') { // hor 
                    break;
                }
                auto new_var_pos = var_pos;
                new_var_pos[car_name] = np;
                new_states.push_back(State(puzzle, new_var_pos));
            }

            int car_size = puzzle.car_size[car_name];
            for (int np = 0; np <= 6; np++) {
                if (np < 6 && (orientation && grid[np][fp] != '.')) {
                    break;
                }
                if (np < 6 && (!orientation && grid[fp][np] != '.')) {
                    break;
                }
                if (np == 6 && car_name != 'x') {
                    break;
                }
                auto new_var_pos = var_pos;
                new_var_pos[car_name] = np - car_size + 1;
                new_states.push_back(State(puzzle, new_var_pos));
            }
        }

        // for stats purpose
        puzzle.search_count += new_states.size();

        return new_states;
    }
};

struct Node
{
    State state;

    int depth;

    Node *parent;

    Node(State state, int depth, Node *parent) :
        state(state), depth(depth), parent(parent)
    {
    }

    virtual ~Node()
    {
    }

    std::vector<std::unique_ptr<Node>> expand()
    {
        auto new_states = state.expand();
        std::vector<std::unique_ptr<Node>> new_nodes;
        for (auto &state : new_states) {
            auto node = std::make_unique<Node>(state, depth + 1, this);
            new_nodes.push_back(std::move(node));
        }

        return new_nodes;
    }
};

struct AStar
{
    Puzzle &puzzle;

    AStar(Puzzle &puzzle) :
        puzzle(puzzle)
    {
    }

    virtual ~AStar()
    {
    }

    std::deque<State> build_path(Node &current)
    {
        std::deque<State> path;
        Node *node = &current;
        while (node) {
            path.push_front(node->state);
            node = node->parent;
        }

        return path;
    }

    int find_node(const std::vector<std::unique_ptr<Node>> &nodelist, const Node &node) {
        auto &node_state = node.state;
        for (int i = 0; i < nodelist.size(); i++) {
            auto &nl_node = nodelist[i];
            auto &nl_node_state = nl_node->state;
            if (nl_node_state.var_pos == node_state.var_pos) {
                return i;
            }
        }

        return -1;
    }

    std::deque<State> solve()
    {
        auto &initial_node = puzzle.initial_node;
        auto root = std::make_unique<Node>(initial_node->state, initial_node->depth, initial_node->parent);
        std::vector<std::unique_ptr<Node>> open = {std::move(root)};
        std::vector<std::unique_ptr<Node>> closed;

        while (!open.empty()) {
            std::sort(open.begin(), open.end(), [](auto &a, auto &b) {
                return a.depth < b.depth;
            });
            auto current = std::move(open[0]);
            open.erase(open.begin());
            if (current->state.is_goal()) {
                auto path = build_path(*current);
                return path;
            }

            closed.push_back(std::move(current));
            for (auto &successor : closed[closed.size() - 1]->expand()) {
                if (find_node(open, *successor) != -1) {
                    update_open(open, successor);
                }
                else if (find_node(closed, *successor) != -1) {
                    open.push_back(std::move(successor));
                }
            }
        }
    }

    void update_open(std::vector<std::unique_ptr<Node>> &open, std::unique_ptr<Node> &successor) {
        int existing_index = find_node(open, *successor);
        auto &existing = open[existing_index];
        if (existing->depth > successor->depth) {
            auto successor_new = std::move(successor);
            open.erase(open.begin() + existing_index);
            open.push_back(successor_new);
        }
    }
};

void read_board(std::string file, Puzzle &puzzle) {
    std::ifstream infile(file);
    std::string line;
    std::array<std::array<char, 6>, 6> grid;
    int i = 0;
    while (std::getline(infile, line)) {
        int j = 0;
        for (auto c : line) {
            grid[i][j] = c;
            j += 1;
        }
        i += 1;
    }
    infile.close();

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (grid[i][j] != '.') {
                puzzle.car_names.insert(grid[i][j]);
            }
        }
    }

    std::unordered_map<char, int> var_pos;

    for (auto car_name : puzzle.car_names) {

        std::vector<std::pair<int, int>> squares;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (grid[i][j] == car_name) {
                    squares.push_back({ i, j });
                }
            }
        }

        bool orientation = true;
        for (auto &square : squares) {
            if (square.second != squares[0].second) {
                orientation = false;
                break;
            }
        }

        int size = squares.size();
        int fp = (orientation) ? squares[0].second : squares[0].first;
        int vp = (orientation) ? squares[0].first : squares[0].second;

        puzzle.car_orientation[car_name] = orientation;
        puzzle.car_size[car_name] = size;
        puzzle.fixed_position[car_name] = fp;
        var_pos[car_name] = vp;
    }

    auto state = State(puzzle, var_pos);
    auto initial_node = std::make_unique<Node>(state, 0, nullptr);
    puzzle.initial_node = std::move(initial_node);
    puzzle.search_count = 1;
}

int main() {

    Puzzle puzzle;
    read_board("D:/rushhour_solver/jams/jam_1.txt", puzzle);

    return 0;
}