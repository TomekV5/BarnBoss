#include "Farm.h"
#include <algorithm>
#include <iostream>

// ── Constants (from spec) ──────────────────────────────────────────────────
static const size_t INITIAL_CROPLAND_CAPACITY = 3;
static const size_t INITIAL_FARMLAND_CAPACITY = 3;

// ── Constructor ────────────────────────────────────────────────────────────
Farm::Farm(): croplandCapacity(INITIAL_CROPLAND_CAPACITY), farmlandCapacity(INITIAL_FARMLAND_CAPACITY)
{
}

// ── Planting ───────────────────────────────────────────────────────────────
bool Farm::sowPlant(ProductType seedType, Barn& barn)
{
    if (cropland.size() >= croplandCapacity)
    {
        std::cout << "Cannot plant: Cropland is full." << std::endl;
        return false;
    }
    if (!barn.hasProduct(seedType, 1))
    {
        std::cout << "Cannot plant: No " << toString(seedType) << " in barn." << std::endl;
        return false;
    }
    advanceCycles();

    barn.removeProduct(seedType, 1);
    cropland.emplace_back(seedType);
    return true;
}

// ── Adding animals ─────────────────────────────────────────────────────────
bool Farm::addAnimal(ProductType animalType, Barn& barn)
{
    if (farmland.size() >= farmlandCapacity)
    {
        std::cout << "Cannot add animal: Farmland is full." << std::endl;
        return false;
    }
    if (!barn.hasProduct(animalType, 1))
    {
        std::cout << "Cannot add animal: No " << toString(animalType) << " in barn." << std::endl;
        return false;
    }
    advanceCycles();
    barn.removeProduct(animalType, 1);
    farmland.emplace_back(animalType);
    return true;
}

// ── Harvest ────────────────────────────────────────────────────────────────
int Farm::harvest(Barn& barn)
{
    int harvested = 0;

    // Collect ready plants and remove them
    auto plantIt = cropland.begin();
    while (plantIt != cropland.end())
    {
        if (plantIt->isReady())
        {
            barn.addProduct(plantIt->getOutputProduct(), 1);
            plantIt = cropland.erase(plantIt);
            ++harvested;
        }
        else
        {
            ++plantIt;
        }
    }

    // Collect ready animals and remove them
    auto animalIt = farmland.begin();
    while (animalIt != farmland.end())
    {
        if (animalIt->isReady())
        {
            barn.addProduct(animalIt->getOutputProduct(), animalIt->getGivenQuantity());
            animalIt = farmland.erase(animalIt);
            ++harvested;
        }
        else
        {
            ++animalIt;
        }
    }

    return harvested;
}

void Farm::advanceCycles()
{
    for (auto& plant : cropland)  plant.advanceCycle();
    for (auto& animal : farmland)  animal.advanceCycle();
}


void Farm::expandCropland()
{
    advanceCycles();
    ++croplandCapacity;
}

void Farm::expandFarmland()
{
	advanceCycles();
    ++farmlandCapacity;
}

size_t Farm::getCroplandCapacity() const { return croplandCapacity; }
size_t Farm::getFarmlandCapacity() const { return farmlandCapacity; }
size_t Farm::getCroplandUsed()     const { return cropland.size(); }
size_t Farm::getFarmlandUsed()     const { return farmland.size(); }
size_t Farm::getCroplandFree()     const { return croplandCapacity - cropland.size(); }
size_t Farm::getFarmlandFree()     const { return farmlandCapacity - farmland.size(); }

void Farm::display() const
{
    std::cout << "=== FARM ===" << std::endl;
    std::cout << "Cropland : " << getCroplandUsed() << " / " << croplandCapacity
        << "  (free: " << getCroplandFree() << ")" << std::endl;
    std::cout << "Farmland : " << getFarmlandUsed() << " / " << farmlandCapacity
        << "  (free: " << getFarmlandFree() << ")" << std::endl;

    if (!cropland.empty())
    {
        std::cout << "  Plants:" << std::endl;
        for (const auto& p : cropland)
            std::cout << "    " << toString(p.getName())
            << "  cycles: " << p.getCurrentCycles()
            << " / " << p.getRequiredCycles() << std::endl;
    }
    if (!farmland.empty())
    {
        std::cout << "  Animals:" << std::endl;
        for (const auto& a : farmland)
            std::cout << "    " << toString(a.getName())
            << "  cycles: " << a.getCurrentCycles()
            << " / " << a.getRequiredCycles() << std::endl;
    }
}

void Farm::saveToFile(std::ostream& out) const
{
    out << croplandCapacity << " " << farmlandCapacity << "\n";

    out << cropland.size() << "\n";
    for (const auto& p : cropland)
        out << static_cast<int>(p.getName()) << " " << p.getCurrentCycles() << "\n";

    out << farmland.size() << "\n";
    for (const auto& a : farmland)
        out << static_cast<int>(a.getName()) << " " << a.getCurrentCycles() << "\n";
}

void Farm::loadFromFile(std::istream& in)
{
    cropland.clear();
    farmland.clear();

    in >> croplandCapacity >> farmlandCapacity;

    size_t plantCount;
    in >> plantCount;
    for (size_t i = 0; i < plantCount; i++)
    {
        int typeInt;
        unsigned cycles;
        in >> typeInt >> cycles;

        Plant p(fromInt(typeInt));
        for (unsigned c = 0; c < cycles; c++)
            p.advanceCycle();
        cropland.push_back(p);
    }

    size_t animalCount;
    in >> animalCount;
    for (size_t i = 0; i < animalCount; i++)
    {
        int typeInt;
        unsigned cycles;
        in >> typeInt >> cycles;

        Animal a(fromInt(typeInt));
        for (unsigned c = 0; c < cycles; c++)
            a.advanceCycle();
        farmland.push_back(a);
    }
}