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

using __ArchiveType = std::unordered_map< std::string, std::function<Archivable*()> >;

namespace __Archive {
    inline __ArchiveType& _GetArchive(){
        static __ArchiveType archive;
        return archive;
    }
}
