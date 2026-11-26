#pragma once

#include <QString>

/**
 * @brief Football player entity with rating, market value, and core season stats.
 */
struct Player {
    unsigned int id = 0;
    unsigned int photoCode = 0;
    QString name;
    unsigned int teamId = 0;
    QString position;  // GK, DEF, MID, FWD
    double rating = 0.0;
    double marketValueM = 0.0;  // Цена >= 0
    unsigned short goals = 0;
    unsigned short assists = 0;
    bool isFavorite = false;

    static bool isValidId(long long rawId);
    static bool isValidPosition(const QString& pos);
    static bool isValidRating(double value);
    static bool isValidMarketValue(double valueM);

    bool isValid() const;
    bool setIdChecked(long long rawId);
    bool setRatingChecked(double newRating);
    bool setMarketValueChecked(double valueM);
    bool setGoalsChecked(long long rawGoals);
    bool setAssistsChecked(long long rawAssists);
    void resetGoalkeeperGoals();

    QString formattedMarketValue() const;
    unsigned int goalContributions() const;
    int overallIndexStub() const;
};
