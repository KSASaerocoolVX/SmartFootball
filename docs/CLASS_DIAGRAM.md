# Схема классов — SmartFootball

```mermaid
classDiagram
    class Team {
        +int id
        +QString name
        +QString shortName
        +int leaguePosition
    }

    class Player {
        +int id
        +QString name
        +int teamId
        +QString position
        +double rating
        +double marketValueM
        +int goals
        +int assists
        +bool isFavorite
    }

    class LeagueRepository {
        -Team[] m_teams
        -Player[] m_players
        +filteredPlayers() Player[]
        +findPlayerById(id) Player
    }

    class DatabaseManager {
        +loadFromFile(path, repo) bool
        +saveToFile(path, repo) bool
    }

    class MainWindow {
        -LeagueRepository m_repo
        -PlayerCardWidget m_card
        +refreshTable() void
    }

    class PlayerCardWidget {
        -Player m_player
        +setPlayer(player) void
        +paintEvent(event) void
    }

    LeagueRepository --> Team
    LeagueRepository --> Player
    MainWindow --> LeagueRepository
    MainWindow --> PlayerCardWidget
    MainWindow --> DatabaseManager
    PlayerCardWidget --> Player
```

`+` — `public` (открытые поля/методы), `-` — `private` (закрытые поля/методы).

---

> **Примечание:** архитектура приложения пока находится в разработке и будет дополняться по мере реализации модулей (фильтры, поиск и запросы, загрузка данных и сравнение игроков), но эти базовые классы являются обязательным минимумом для работы приложения.
