#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Typedefs.h"

namespace DJ
{
	class Block
	{
	public:
		blockid_t Id;

		/// MiningMultipliers
        std::unordered_map<std::string, number_t> ToolMultiplier;

		std::vector<std::string> tags;


        /// Does the block passing lights into itself
        bool lightPassing = false;

        /// Does the block passing top-down sky lights into itself
        bool skyLightPassing = false;

		/// Is the block a physical obstacle
        bool obstacle = false;
    
        /// Can the block be selected
        bool selectable = false;
    
        /// Can the block be replaced with other. 
        /// Examples of replaceable blocks: air, flower, water
        bool replaceable = false;
    
        /// Can player destroy the block
        bool breakable = false;
    
        /// Can the block be oriented different ways
        bool rotatable = false;
    
        /// Can the block exist without physical support be a solid block below
        bool grounded = false;
	};
}