#pragma once
#include "User.h"
#include "Barn.h"
#include "Farm.h"

class Player : public User
{
private:
    static unsigned nextId;
    unsigned id;
    double balance;
    int score;
    Barn barn;
    Farm farm;

public:
    Player(const std::string& username, const std::string& password);

    // ── Getters ──────────────────────────────────────────────────────────
    unsigned getId() const;
    double getBalance() const;
    int getScore() const;
    Barn& getBarn();
    Farm& getFarm();

    // ── Setters ──────────────────────────────────────────────────────────
    bool setBalance(double newBalance);
    bool setScore(int newScore);
    void addBalance(double amount);
    void addScore(int amount);

    // ── User overrides ───────────────────────────────────────────────────
    std::string profileInfo()const override;

    // ── Save / load ──────────────────────────────────────────────────────
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};