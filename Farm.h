#pragma once
#include "Animal.h"
#include "Plant.h"
#include "Barn.h"
#include <vector>
#include <iostream>

class Farm
{
private:
    std::vector<Plant>  cropland;   // active plants
    std::vector<Animal> farmland;   // active animals
    size_t croplandCapacity;
    size_t farmlandCapacity;

public:
    Farm();

    // ── Planting / adding ──────────────────────────────────────────────────
    // Returns false if capacity is full or the required seed is not in barn.
    bool sowPlant(ProductType seedType, Barn& barn);

    // Returns false if capacity is full or the animal is not in barn.
    bool addAnimal(ProductType animalType, Barn& barn);

    // ── Harvest ────────────────────────────────────────────────────────────
    // Advances all cycles by 1, then collects every ready plant/animal into
    // barn and removes it from the farm. Returns number of items harvested.
    int harvest(Barn& barn);
	void advanceCycles();

    // ── Expansion ──────────────────────────────────────────────────────────
    void expandCropland();
    void expandFarmland();

    // ── Getters ────────────────────────────────────────────────────────────
    size_t getCroplandCapacity()  const;
    size_t getFarmlandCapacity()  const;
    size_t getCroplandUsed()      const;
    size_t getFarmlandUsed()      const;
    size_t getCroplandFree()      const;
    size_t getFarmlandFree()      const;

    // ── Display ────────────────────────────────────────────────────────────
    void display() const;

    // ── Save / load ────────────────────────────────────────────────────────
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};