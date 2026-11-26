#pragma once

#include <QString>

/**
 * @brief Football club entity in the tracked league.
 */
struct Team {
    unsigned int id = 0;
    unsigned int badgeCode = 0;
    QString name;
    QString shortName;
    unsigned int leaguePosition = 0;

    static bool isValidId(long long rawId);

    bool isValid() const;
    bool setIdChecked(long long rawId);
    void normalize();
    QString displayName() const;
};
