#pragma once

#include "BST.hpp"
#include "Knight.hpp"

#include <ostream>


namespace RK {

    class RegistryOfKnights {
        public:
            void insert(const char* name, int braveryScore, unsigned int battlesWon, const char* house) { registry.insert(Knight(name, braveryScore, battlesWon, house)); }
            void insert(const Knight& knight) { registry.insert(knight); }

            tools::Optional<Knight> remove(const char* name);
            
            void tournamentRankingScroll(std::ostream& os) const;
            void royalProclamationOrder(std::ostream& os) const;
            void tributeCollectionOrder(std::ostream& os) const;

            void getKnightsOfHouse(const char* house, tools::Queue<Knight>& knights) const;
            void getKnightsByBravery(int minBravery, int maxBravery, tools::Queue<Knight>& knights) const { registry.findInRange(minBravery, maxBravery, knights); }

            tools::Optional<Knight> getNewestRecruit() const { return registry.getMin(); }
            tools::Optional<Knight> getChampionOfTheRealm() const { return registry.getMax(); }

            unsigned int getHeight() const { return registry.getHeight(); }
            // unsigned int getNumberOfLeafs() const { return registry.getNumberOfLeafs(); }
            void getLeafs(tools::Queue<Knight>& result) const { registry.getLeafs(result); }
            bool isBalanced() const { return registry.isBalanced(); }

            tools::Optional<Knight> getKthValoredKnight(unsigned int k) const { return registry.getKthLargest(k); }
            tools::Optional<Knight> getLowestCommonAncestor(const char* name1, const char* name2) const;

        private:
            tools::BST<Knight> registry;
    };

}
