#pragma once

#include <string_view>
#include <sys/types.h>
#include <vector>

#include "engine/rgba.h"

struct DrawBoxOptions {
    std::uint64_t padding_top = 0, 
                  padding_bottom = 0, 
                  padding_left = 0, 
                  padding_right = 0;

    std::uint64_t margin_top = 0,
                  margin_bottom = 0,
                  margin_left = 0,
                  margin_right = 0;
                  
    std::string_view flex_type = "column";
    std::vector<double> flex_list;

    arctic::Rgba background_color = arctic::Rgba(0, 0, 0);
};