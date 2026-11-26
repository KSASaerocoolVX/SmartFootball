#pragma once

#include "logic/ICommand.h"

class FindCommand : public ICommand {
public:
    explicit FindCommand(const QString& query);

    std::vector<Player> execute(const std::vector<Player>& players) const override;

private:
    QString m_query;
};
