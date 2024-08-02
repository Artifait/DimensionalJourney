#pragma once
#include <iostream>
#include <string>
#include <DJINI.h>

#include "../DataStruct/v2i.h"

namespace DJ
{
    class EngineSettings {
    public:

        static EngineSettings& Settings() {
            static EngineSettings instance;
            return instance;
        }
        
        std::string TexturePackPath() const { return _texturePackPath; }
        std::string ModPackPath() const { return _modPackPath; }
        int ChunkWidth() const { return _chunkWidth; }
        int ChunkHeight() const { return _chunkHeight; }
        DJ::v2i ChunkSize() const { return v2i(_chunkWidth, _chunkHeight); }

    private:
        const std::string _pathConfigurationFile = "M:\\Games\\FinalProject\\MineCraft\\DJ\\DimensionalJourney\\x64\\Debug\\DJEngineSettings.ini";

        int _chunkWidth;
        int _chunkHeight;
        std::string _modPackPath;
        std::string _texturePackPath;

        EngineSettings()
        {
            try {
                DJIni ini(_pathConfigurationFile);

                _chunkWidth = ini.GetAs<int>("ChunkSize", "width", 16);
                _chunkHeight = ini.GetAs<int>("ChunkSize", "height", 16);

                _modPackPath = ini.GetAs<std::string>("Paths", "ModPackPath", "ModPack");
                _texturePackPath = ini.GetAs<std::string>("Paths", "TexturePackPath", "TexturePack");
                //throw std::runtime_error("Мне не нравиться ставь defoalt value");
            }
            catch(...) {
                std::cerr << "[DJ] Error reading configuration file. Loaded defoalt values." << std::endl;

                //#default value
                _chunkWidth = 16;
                _chunkHeight = 16;

                _modPackPath = "ModPack";
                _texturePackPath = "TexturePack";
            }
        }
        EngineSettings(const EngineSettings&) = delete;
        EngineSettings& operator=(const EngineSettings&) = delete;
    };
}