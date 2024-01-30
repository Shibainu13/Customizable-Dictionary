#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ResourceID.hpp>

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <map>
#include <memory>

template <typename Resource, typename Identifier>
class ResourceManager
{
public:
    void load(Identifier id, const std::string &filename);
    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include <ResourceManager.inl>

#endif