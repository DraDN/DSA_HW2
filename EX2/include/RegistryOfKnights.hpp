#pragma once

#include "BST.hpp"
#include "Knight.hpp"

#include <ostream>


namespace RK {

    /// @brief Registry of knights
    ///
    /// A wrapper class for a binary search tree of knights
    class RegistryOfKnights {
        public:
            /// @brief Inserts a knight into the registry
            /// @param name string literal of the knights name - unique
            /// @param braveryScore integer representing the knights order in the registry tree - unique
            /// @param battlesWon integer representing the number of battles the knight has won
            /// @param house string literal of the knights house
            /// @return `0` if the knight was inserted,
            ///
            /// `1` if the braveryScore isn't unique
            /// 
            /// `2` if the name isn't unique
            int insert(const char* name, int braveryScore, unsigned int battlesWon, const char* house);

            /// @brief Inserts a knight into the registry
            /// @param knight the night to be inserted into the registry
            void insert(const Knight& knight) { registry.insert(knight); }


            /// @brief Removes a knight from the registry
            /// @param name the name of the knight to be removed
            /// @return `tools::Optional<Knight>` containing the knight that was removed
            ///
            /// `tools::nullopt` if the knight was not found
            tools::Optional<Knight> remove(const char* name);
            

            /// @brief Prints the knights in the registry via in-order traversal
            /// @param os the output stream to print to
            void tournamentRankingScroll(std::ostream& os) const;

            /// @brief Prints the knights in the registry via pre-order traversal
            /// @param os the output stream to print to
            void royalProclamationOrder(std::ostream& os) const;

            /// @brief Prints the knights in the registry via post-order traversal
            /// @param os the output stream to print to
            void tributeCollectionOrder(std::ostream& os) const;

            void printFullTree(std::ostream& os) const;


            /// @brief Returns all knights of a specific house
            /// @param house the house to search for
            /// @param knights `tools::Queue<Knight>` to store the search results
            void getKnightsOfHouse(const char* house, tools::Queue<Knight>& knights) const;

            /// @brief Returns all knights with a bravery score between minBravery and maxBravery
            /// @param minBravery lower bound of the search
            /// @param maxBravery upper bound of the search
            /// @param knights `tools::Queue<Knight>` to store the search results
            void getKnightsByBravery(int minBravery, int maxBravery, tools::Queue<Knight>& knights) const { registry.findInRange(minBravery, maxBravery, knights); }


            /// @brief Returns the knight with the lowest bravery score
            /// @return `tools::Optional<Knight>` containing the newest recruit
            ///
            /// `tools::nullopt` if the registry is empty
            tools::Optional<Knight> getNewestRecruit() const { return registry.getMin(); }

            /// @brief Returns the knight with the highest bravery score
            /// @return `tools::Optional<Knight>` containing the champion of the realm
            ///
            /// `tools::nullopt` if the registry is empty
            tools::Optional<Knight> getChampionOfTheRealm() const { return registry.getMax(); }


            /// @brief Returns the height of the tree
            /// @return The height
            unsigned int getHeight() const { return registry.getHeight(); }
            // unsigned int getNumberOfLeafs() const { return registry.getNumberOfLeafs(); }

            /// @brief Returns all leafs of the tree
            /// @param result `tools::Queue<Knight>` to store the search results
            void getLeafs(tools::Queue<Knight>& result) const { registry.getLeafs(result); }

            /// @brief Checks if the tree is balanced
            /// @return `true` if the tree is balanced, `false` otherwise
            bool isBalanced() const { return registry.isBalanced(); }


            /// @brief Returns the k-th valored knight
            /// @param k the order of lower bravery score of the knight to search for
            /// @return `tools::Optional<Knight>` containing the knight if found
            ///
            /// `tools::nullopt` if the tree doesn't contain at least k elements
            tools::Optional<Knight> getKthValoredKnight(unsigned int k) const { return registry.getKthLargest(k); }

            /// @brief Returns the lowest common ancestor of two knights
            /// @param name1 the name of the first knight
            /// @param name2 the name of the second knight
            /// @return `tools::Optional<Knight>` containing the LCA if found
            ///
            /// `tools::nullopt` if (1) one or both of the knights are not in the tree or (2) the tree is empty / not enough elements or (3) the knights don't share a common ancestor
            tools::Optional<Knight> getLowestCommonAncestor(const char* name1, const char* name2) const;

        private:
            tools::BST<Knight> registry;
    };

}
