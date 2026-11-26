#include "model/Player.h"

#include <algorithm>
#include <cmath>
#include <limits>

bool Player::isValidId(long long rawId) {
    return rawId > 0 && rawId < static_cast<long long>(std::numeric_limits<unsigned int>::max());
}

bool Player::isValidPosition(const QString& pos) {
    const QString upper = pos.trimmed().toUpper();
    return upper == "GK" || upper == "DEF" || upper == "MID" || upper == "FWD";
}

bool Player::isValidRating(double value) {
    return std::isfinite(value) && value >= 0.0 && value <= 10.0;
}

bool Player::isValidMarketValue(double valueM) {
    return std::isfinite(valueM) && valueM >= 0.0;
}

bool Player::isValid() const {
    const bool gkGoalsOk = (position.trimmed().toUpper() != "GK") || (goals == 0);
    return isValidId(id) &&
           photoCode < std::numeric_limits<unsigned int>::max() &&
           isValidId(teamId) &&
           !name.trimmed().isEmpty() &&
           isValidPosition(position) &&
           isValidRating(rating) &&
           isValidMarketValue(marketValueM) &&
           goals < std::numeric_limits<unsigned short>::max() &&
           assists < std::numeric_limits<unsigned short>::max() &&
           gkGoalsOk;
}

bool Player::setIdChecked(long long rawId) {
    if (!isValidId(rawId)) {
        return false;
    }
    id = static_cast<unsigned int>(rawId);
    return true;
}

bool Player::setRatingChecked(double newRating) {
    if (!isValidRating(newRating)) {
        return false;
    }
    rating = newRating;
    return true;
}

bool Player::setMarketValueChecked(double valueM) {
    if (!isValidMarketValue(valueM)) {
        return false;
    }
    marketValueM = valueM;
    return true;
}

bool Player::setGoalsChecked(long long rawGoals) {
    if (rawGoals < 0 || rawGoals >= static_cast<long long>(std::numeric_limits<unsigned short>::max())) {
        return false;
    }
    if (position.trimmed().toUpper() == "GK") {
        goals = 0;
        return true;
    }
    goals = static_cast<unsigned short>(rawGoals);
    return true;
}

bool Player::setAssistsChecked(long long rawAssists) {
    if (rawAssists < 0 || rawAssists >= static_cast<long long>(std::numeric_limits<unsigned short>::max())) {
        return false;
    }
    assists = static_cast<unsigned short>(rawAssists);
    return true;
}

void Player::resetGoalkeeperGoals() {
    if (position.trimmed().toUpper() == "GK") {
        goals = 0;
    }
}

QString Player::formattedMarketValue() const {
    return QString("€%1M").arg(marketValueM, 0, 'f', 1);
}

unsigned int Player::goalContributions() const {
    return static_cast<unsigned int>(goals) + static_cast<unsigned int>(assists);
}

int Player::overallIndexStub() const {
    // Заглушка: позже учесть xG, xA и минуты
    const double clamped = std::clamp(rating, 0.0, 10.0);
    return static_cast<int>(std::round((clamped / 10.0) * 100.0));
}
