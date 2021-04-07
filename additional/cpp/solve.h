// NOTE: only works for a-z cars
#pragma once

#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <regex>

using level_type = std::array<size_t, 26>;

struct Metadata
{
    std::vector<std::vector<char>> grid;
    std::set<char> cars;
    std::map<char, std::vector<std::pair<size_t, size_t>>> tiles;
    std::map<char, bool> orientation;
    level_type size;
    level_type fixed_position;

    size_t node_count = 0;

    Metadata(const std::vector<std::vector<char>> &grid) : grid(grid)
    {
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                if (grid[i][j] == '.')
                {
                    continue;
                }

                cars.insert(grid[i][j]);

                if (tiles.find(grid[i][j]) == tiles.end())
                {
                    tiles[grid[i][j]] = {};
                }

                tiles[grid[i][j]].push_back({i, j});
            }
        }

        for (auto car : cars)
        {
            int car_int = (int) car - 97;
            cars.insert(car);
            orientation[car] = (tiles[car][0].first != tiles[car][1].first);
            size[car_int] = tiles[car].size();
            fixed_position[car_int] = orientation[car] ? tiles[car][0].second : tiles[car][0].first;
        }
    }
};

void convert_to_grid(std::vector<std::vector<char>> &grid, level_type &u, Metadata &metadata)
{
    for (auto car : metadata.cars)
    {
        int car_int = (int) car - 97;
        bool orientation = metadata.orientation[car];
        size_t size = metadata.size[car_int];
        size_t fp = metadata.fixed_position[car_int];
        size_t vp = u[car_int];

        if (car == 'x' && vp + size > 6)
        {
            size -= 1;
        }

        for (size_t d = 0; d < size; d++)
        {
            auto index1 = orientation ? vp+d : fp;
            auto index2 = orientation ? fp : vp+d;
            grid[index1][index2] = car;
        }
    }
}

void get_neighbors(std::vector<level_type> &neighbors, level_type &u, Metadata &metadata)
{
    std::vector<std::vector<char>> grid(6, std::vector<char>(6, '.'));
    convert_to_grid(grid, u, metadata);

    for (auto car : metadata.cars)
    {
        int car_int = (int) car - 97;
        bool orientation = metadata.orientation[car];
        size_t size = metadata.size[car_int];
        size_t fp = metadata.fixed_position[car_int];
        size_t vp = u[car_int];

        for (int np = (int) vp - 1; np >= 0; np -= 1)
        {
            if ((orientation && grid[np][fp] != '.') ||
                (!orientation && grid[fp][np] != '.'))
            {
                break;
            }

            level_type neighbor = u;
            neighbor[car_int] = np;

            neighbors.push_back(neighbor);
        }

        for (int np = (int) vp + (int) size; np <= 6; np++)
        {
            if ((np < 6 && orientation && grid[np][fp] != '.') ||
                (np < 6 && !orientation && grid[fp][np] != '.') ||
                (np == 6 && car != 'x'))
            {
                break;
            }

            level_type neighbor = u;
            neighbor[car_int] = np - size + 1;

            neighbors.push_back(neighbor);
        }
    }

    metadata.node_count += neighbors.size();
}

std::vector<level_type> shortest_path(std::map<level_type, level_type> &prev,
                                                  level_type &src, level_type &target)
{
    std::vector<level_type> path;
    auto &u = target;

    while (prev.find(u) != prev.end())
    {
        path.insert(path.begin(), u);
        u = prev[u];
    }

    path.insert(path.begin(), src);
    return path;
}

std::vector<level_type> solve(level_type &src, Metadata &metadata)
{
    std::map<level_type, size_t> dist;
    std::map<level_type, level_type> prev;    
    dist[src] = 0;

    std::deque<std::pair<size_t, level_type>> q = {{0, src}};
    while (!q.empty())
    {
        //std::sort(q.begin(), q.end(), [](const auto &lhs, const auto &rhs) {
        //    return lhs.first < rhs.first;
        //});

        auto item = q[0];
        q.pop_front();

        size_t distu = item.first;
        level_type &u = item.second;

        int car_int = int('x') - 97;
        if (u[car_int] == 5)
        {
            return shortest_path(prev, src, u);
        }

        std::vector<level_type> neighbors;
        get_neighbors(neighbors, u, metadata);

        for (auto &v : neighbors)
        {
            size_t alt = distu + 1;
            if (dist.find(v) == dist.end() || alt < dist[v])
            {
                dist[v] = alt;
                prev[v] = u;
                q.push_back({alt, v});
            }
        }
    }

    return {};
}

std::vector<std::string> split(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}
