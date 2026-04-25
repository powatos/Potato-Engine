#pragma once

#include <unordered_map>
#include <functional>

class Archivable
{
public:
    Archivable() = default;
    virtual ~Archivable() = default;
};

namespace __Archive {
    inline std::unordered_map< std::string, std::function<Archivable*()> >& _GetArchive(){
        static std::unordered_map< std::string, std::function<Archivable*()> > archive;
        return archive;
    }
}
