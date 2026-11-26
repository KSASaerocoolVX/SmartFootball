#include "logic/commands/SortCommand.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <type_traits>

SortCommand::SortCommand(SortField field, SortOrder order) : m_field(field), m_order(order) {
    if (m_order != SortOrder::Ascending && m_order != SortOrder::Descending) {
        throw std::invalid_argument("Invalid sort order");
    }
}

std::vector<Player> SortCommand::execute(const std::vector<Player>& players) const {
    std::vector<Player> result = players;
    const bool ascending = m_order == SortOrder::Ascending;
    const auto sortBy = [&result, ascending](auto field) {
        std::stable_sort(result.begin(), result.end(), [field, ascending](const Player& lhs,
                                                                         const Player& rhs) {
            const auto& left = lhs.*field;
            const auto& right = rhs.*field;
            using FieldType = std::decay_t<decltype(left)>;

            if constexpr (std::is_same_v<FieldType, QString>) {
                const int comparison = left.compare(right, Qt::CaseInsensitive);
                return ascending ? comparison < 0 : comparison > 0;
            } else {
                if constexpr (std::is_floating_point_v<FieldType>) {
                    // Поля модели открыты, поэтому NaN может попасть в список.
                    // Ставим его в конец при любом направлении, сохраняя строгий порядок.
                    if (std::isnan(left) || std::isnan(right)) {
                        return !std::isnan(left);
                    }
                }
                return ascending ? left < right : right < left;
            }
        });
    };

    switch (m_field) {
    case SortField::Name:
        sortBy(&Player::name);
        break;
    case SortField::Rating:
        sortBy(&Player::rating);
        break;
    case SortField::MarketValue:
        sortBy(&Player::marketValueM);
        break;
    case SortField::Goals:
        sortBy(&Player::goals);
        break;
    case SortField::Assists:
        sortBy(&Player::assists);
        break;
    default:
        throw std::invalid_argument("Invalid sort field");
    }
    return result;
}
