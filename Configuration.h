#pragma once
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <vector>
#include <utility>

struct Configurationn {
    int id;
    std::vector<std::pair<int, int>> relative_positions; // ������������� ������� � ������������
    int cooldown;
};

std::vector<Configurationn> createConfigurations();

#endif // CONFIGURATION_H
