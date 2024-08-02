#pragma once
#include <iostream>
#include <string>
#include <INI.h>
#include <zip.h>


using zipcpp::zip;

namespace DJ
{
    class BPDataBase {//BlockPrototype - BP
    public:

        static BPDataBase& Settings() {
            static BPDataBase instance;
            return instance;
        }

    private:
        BPDataBase()
        {
            try {

            }
            catch (...) {
                std::cerr << "Error reading configuration file: " << std::endl;
            }
        }
        BPDataBase(const BPDataBase&) = delete;
        BPDataBase& operator=(const BPDataBase&) = delete;
    };
}