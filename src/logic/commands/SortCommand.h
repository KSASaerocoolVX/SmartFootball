#pragma once

#include "logic/ICommand.h"

enum class SortField { Name, Rating, MarketValue, Goals, Assists };
enum class SortOrder { Ascending, Descending };

class SortCommand : public ICommand {
public:
    SortCommand(SortField field, SortOrder order);

    std::vector<Player> execute(const std::vector<Player>& players) const override;

private:
    SortField m_field;
    SortOrder m_order;
};
