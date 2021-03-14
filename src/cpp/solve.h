#pragma once

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <regex>

struct Metadata
{
    std::vector<std::vector<char>> grid;
    std::set<char> cars;
    std::map<char, std::vector<std::pair<size_t, size_t>>> tiles;
    std::map<char, bool> orientation;
    std::map<char, size_t> size;
    std::map<char, size_t> fixed_position;
    size_t node_count = 0;

    Metadata(const std::vector<std::vector<char>> grid) : grid(grid)
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
            cars.insert(car);
            orientation[car] = (tiles[car][0].first != tiles[car][1].first);
            size[car] = tiles[car].size();
            fixed_position[car] = orientation[car] ? tiles[car][0].second : tiles[car][0].first;
        }
    }
};

std::vector<std::vector<char>> convert_to_grid(std::map<char, size_t> &u, Metadata &metadata)
{
    std::vector<std::vector<char>> grid(6, std::vector<char>(6, '.'));

    for (auto car : metadata.cars)
    {
        bool orientation = metadata.orientation[car];
        size_t size = metadata.size[car];
        size_t fp = metadata.fixed_position[car];
        size_t vp = u[car];

        if (car == 'x' && vp + size > 6)
        {
            size -= 1;
        }

        for (size_t d = 0; d < size; d++)
        {
            if (orientation)
            {
                grid[vp + d][fp] = car;
            }
            else
            {
                grid[fp][vp + d] = car;
            }
        }
    }

    return grid;
}

std::vector<std::map<char, size_t>> get_neighbors(std::map<char, size_t> &u, Metadata &metadata)
{
    std::vector<std::map<char, size_t>> neighbors;
    std::vector<std::vector<char>> grid = convert_to_grid(u, metadata);

    for (auto car : metadata.cars)
    {
        bool orientation = metadata.orientation[car];
        size_t size = metadata.size[car];
        size_t fp = metadata.fixed_position[car];
        size_t vp = u[car];

        for (int np = (int) vp - 1; np >= 0; np -= 1)
        {
            if ((orientation && grid[np][fp] != '.') ||
                (!orientation && grid[fp][np] != '.'))
            {
                break;
            }

            std::map<char, size_t> neighbor = u;
            neighbor[car] = np;

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

            std::map<char, size_t> neighbor = u;
            neighbor[car] = np - size + 1;

            neighbors.push_back(neighbor);
        }
    }

    metadata.node_count += neighbors.size();
    return neighbors;
}

std::vector<std::map<char, size_t>> shortest_path(std::map<std::map<char, size_t>, std::map<char, size_t>> &prev,
                                                  std::map<char, size_t> &src, std::map<char, size_t> &target)
{
    std::vector<std::map<char, size_t>> path;
    auto &u = target;

    while (prev.find(u) != prev.end())
    {
        path.insert(path.begin(), u);
        u = prev[u];
    }

    path.insert(path.begin(), src);
    return path;
}

std::vector<std::map<char, size_t>> solve(std::map<char, size_t> &src, Metadata &metadata)
{
    std::map<std::map<char, size_t>, size_t> dist;
    std::map<std::map<char, size_t>, std::map<char, size_t>> prev;
    dist[src] = 0;
    std::vector<std::pair<size_t, std::map<char, size_t>>> q = {{0, src}};
    while (!q.empty())
    {
        std::sort(q.begin(), q.end(), [](const auto &lhs, const auto &rhs) {
            return lhs.first < rhs.first;
        });

        auto item = q[0];
        q.erase(q.begin());

        size_t distu = item.first;
        std::map<char, size_t> &u = item.second;

        if (u['x'] == 5)
        {
            return shortest_path(prev, src, u);
        }

        for (auto &v : get_neighbors(u, metadata))
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
