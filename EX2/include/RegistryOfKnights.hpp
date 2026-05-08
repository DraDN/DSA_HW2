#pragma once

#include "BST.hpp"
#include "Knight.hpp"

#include <ostream>


namespace RK {

    class RegistryOfKnights {
        public:
            void insert(const char* name, int braveryScore, int battlesWon, const char* house) { registry.insert(Knight(name, braveryScore, battlesWon, house)); }
            void insert(const Knight& knight) { registry.insert(knight); }

            void remove(const char* name);
            
            void tournamentRankingScroll(std::ostream& os) const;
            void royalProclamationOrder(std::ostream& os) const;
            void tributeCollectionOrder(std::ostream& os) const;

            void getKnightsOfHouse(const char* house, tools::Queue<Knight>& knights) const;
            void getKnightsByBravery(int minBravery, int maxBravery, tools::Queue<Knight>& knights) const;

            Knight getNewestRecruit() const;
            Knight getChampionOfTheRealm() const;

            unsigned int getHeight() const { return registry.getHeight(); }
            unsigned int getNumberOfLeafs() const { return registry.getNumberOfLeafs(); }
            bool isBalanced() const { return registry.isBalanced(); }

            tools::Optional<Knight> getKthValoredKnight(unsigned int k) const { return registry.getKthLargest(k); }
            tools::Optional<Knight> getLowestCommonAncestor(const char* name1, const char* name2) const;

        private:
            tools::BST<Knight> registry;
    };

}
