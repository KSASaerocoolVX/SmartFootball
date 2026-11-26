#include "ui/DemoData.h"

namespace {

struct TeamRow {
    unsigned int id;
    const char* name;
    const char* shortName;
};

struct PlayerRow {
    unsigned int teamId;
    const char* name;
    const char* position;
    double rating;
    double marketValueM;
    unsigned short goals;
    unsigned short assists;
};

const TeamRow kTeams[] = {
    {1, "Liverpool", "LIV"},
    {2, "Arsenal", "ARS"},
    {3, "Manchester City", "MCI"},
    {4, "Chelsea", "CHE"},
    {5, "Newcastle United", "NEW"},
    {6, "Aston Villa", "AVL"},
    {7, "Tottenham Hotspur", "TOT"},
    {8, "Manchester United", "MUN"},
};

const PlayerRow kPlayers[] = {
    {1, "Alisson Becker", "GK", 6.9, 25.0, 0, 0},
    {1, "Virgil van Dijk", "DEF", 7.1, 23.0, 3, 1},
    {1, "Alexis Mac Allister", "MID", 7.0, 85.0, 5, 5},
    {1, "Mohamed Salah", "FWD", 7.9, 55.0, 29, 18},

    {2, "David Raya", "GK", 6.8, 40.0, 0, 0},
    {2, "William Saliba", "DEF", 7.0, 80.0, 2, 0},
    {2, "Martin Odegaard", "MID", 7.2, 85.0, 3, 8},
    {2, "Bukayo Saka", "FWD", 7.4, 150.0, 6, 10},

    {3, "Ederson", "GK", 6.7, 25.0, 0, 1},
    {3, "Ruben Dias", "DEF", 6.9, 70.0, 0, 1},
    {3, "Phil Foden", "MID", 6.9, 100.0, 7, 2},
    {3, "Erling Haaland", "FWD", 7.3, 180.0, 22, 3},

    {4, "Robert Sanchez", "GK", 6.5, 20.0, 0, 0},
    {4, "Levi Colwill", "DEF", 6.8, 50.0, 1, 1},
    {4, "Cole Palmer", "MID", 7.5, 130.0, 15, 8},
    {4, "Nicolas Jackson", "FWD", 6.9, 50.0, 10, 5},

    {5, "Nick Pope", "GK", 6.6, 12.0, 0, 0},
    {5, "Sven Botman", "DEF", 6.7, 40.0, 0, 0},
    {5, "Bruno Guimaraes", "MID", 7.2, 85.0, 5, 6},
    {5, "Alexander Isak", "FWD", 7.5, 120.0, 23, 6},

    {6, "Emiliano Martinez", "GK", 6.8, 20.0, 0, 0},
    {6, "Ezri Konsa", "DEF", 6.8, 40.0, 1, 1},
    {6, "Youri Tielemans", "MID", 7.1, 30.0, 3, 9},
    {6, "Ollie Watkins", "FWD", 7.0, 50.0, 16, 8},

    {7, "Guglielmo Vicario", "GK", 6.6, 25.0, 0, 0},
    {7, "Cristian Romero", "DEF", 6.9, 50.0, 1, 0},
    {7, "James Maddison", "MID", 7.0, 50.0, 9, 7},
    {7, "Dominic Solanke", "FWD", 6.8, 45.0, 9, 4},

    {8, "Andre Onana", "GK", 6.5, 25.0, 0, 0},
    {8, "Lisandro Martinez", "DEF", 6.8, 40.0, 1, 1},
    {8, "Bruno Fernandes", "MID", 7.4, 45.0, 8, 10},
    {8, "Rasmus Hojlund", "FWD", 6.4, 40.0, 4, 0},
};

}  // namespace

namespace DemoData {

std::vector<Team> teams() {
    std::vector<Team> result;
    unsigned int position = 1;
    for (const TeamRow& row : kTeams) {
        Team team;
        team.id = row.id;
        team.badgeCode = row.id;
        team.name = row.name;
        team.shortName = row.shortName;
        team.leaguePosition = position++;
        result.push_back(team);
    }
    return result;
}

std::vector<Player> players() {
    std::vector<Player> result;
    unsigned int nextId = 1;
    for (const PlayerRow& row : kPlayers) {
        Player player;
        player.id = nextId;
        player.photoCode = nextId;
        player.name = row.name;
        player.teamId = row.teamId;
        player.position = row.position;
        player.rating = row.rating;
        player.marketValueM = row.marketValueM;
        player.goals = row.goals;
        player.assists = row.assists;
        player.resetGoalkeeperGoals();
        result.push_back(player);
        ++nextId;
    }
    return result;
}

}  // namespace DemoData
