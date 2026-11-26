#include "model/Team.h"

#include <limits>

bool Team::isValidId(long long rawId) {
    return rawId > 0 && rawId < static_cast<long long>(std::numeric_limits<unsigned int>::max());
}

bool Team::isValid() const {
    return isValidId(id) &&
           badgeCode < std::numeric_limits<unsigned int>::max() &&
           leaguePosition < std::numeric_limits<unsigned int>::max() &&
           !name.trimmed().isEmpty() &&
           !shortName.trimmed().isEmpty();
}

bool Team::setIdChecked(long long rawId) {
    if (!isValidId(rawId)) {
        return false;
    }
    id = static_cast<unsigned int>(rawId);
    return true;
}

void Team::normalize() {
    name = name.trimmed();
    shortName = shortName.trimmed().toUpper();
}

QString Team::displayName() const {
    if (shortName.trimmed().isEmpty()) {
        return name.trimmed();
    }
    return QString("%1 (%2)").arg(name.trimmed(), shortName.trimmed());
}
