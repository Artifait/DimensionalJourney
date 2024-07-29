#pragma once
#include <iostream>
#include <string>

#include <INI.h>

namespace DJ
{
    class EngineSettings {
    public:

        static EngineSettings& Settings() {
            static EngineSettings instance;
            return instance;
        }

        int ChunkWidth() const { return _chunkWidth; }
        int ChunkHeight() const { return _chunkHeight; }

    private:
        const std::string _pathConfigurationFile = "DJEngineSettings.ini";

        int _chunkWidth;
        int _chunkHeight;

        EngineSettings()
        {

            try {
                INI ini(_pathConfigurationFile, true);

                _chunkWidth = ini.getAs<int>("ChunkSize", "width");
                _chunkHeight = ini.getAs<int>("ChunkSize", "height");
            }
            catch(...) {
                std::cerr << "Error reading configuration file: " << std::endl;

                //#default value
                _chunkWidth = 16;
                _chunkHeight = 16;
            }
        }
        EngineSettings(const EngineSettings&) = delete;
        EngineSettings& operator=(const EngineSettings&) = delete;
    };
}