#pragma once

#include <ostream>
#include <istream>

#include "RegistryOfKnights.hpp"

namespace RK {

    class RegistryOfKnightsUI {
        public:
            RegistryOfKnightsUI(RegistryOfKnights& registry, std::ostream& out, std::istream& in) : registry(registry), out(out), in(in) {}

            void handleInsert();
            void handleRemove();

            void printTournamentRanking() { out << "In-order (Tournament Ranking):\n"; registry.tournamentRankingScroll(out); out << "\n"; }
            void printRoyalProclamationOrder() { out << "Pre-order (Royal Proclamation):\n"; registry.royalProclamationOrder(out); out << "\n"; }
            void printTributeCollectionOrder() { out << "Post-order (Tribute Collection):\n"; registry.tributeCollectionOrder(out); out << "\n"; }

            void handleSearchByHouse();
            void handleSearchByRange();

            void printNewRecruit();
            void printChampionOfTheRealm();

            void printKthValoredKnight();
            void printLowestCommonAncestor();

            void printRegistryInfo();

        private:
            RegistryOfKnights& registry;
            std::ostream& out;
            std::istream& in;

    };

}
