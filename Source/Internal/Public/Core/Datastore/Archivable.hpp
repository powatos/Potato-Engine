#pragma once

#include <unordered_map>
#include <functional>

// called in each cpp of archivable classes to register into static archive
#define ARCHIVE_STATIC(type) \
static struct __##type##_Register { \
    __##type##_Register() { \
        __Archive::_GetArchive()[#type] = []() -> Archivable* { return new type(); }; \
    } \
} __##type##_register;

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
