#pragma once
#include <vector>
#include <cmath>
#include <ranges>
#include <algorithm>

// PSC: rule of thumb: function < 5 lines should be inlined for perf

// PSC GENERAL REMARKS
// Good doc
// No additional tests
// Safety fail when "abusing" operator++ and vector::operator[] / operator*
// Evaluation would ideally be lazy
// Primes 1
// Correct: 9/9
// Quality: 1/3
// Doc: 3/3
// Primes 2
// Correct: 0/3
// Quality: 0/1
// Doc: 0/1
// Tot 13/20

/**
 * @class prime_number_range
 * @brief Represents a range of prime numbers.
 *
 * The prime_number_range class generates and provides an iterator over a range
 * of prime numbers based on the given count.
 */
class prime_number_range {
private:
    std::size_t count_;             /**< Number of prime numbers to generate */
    std::vector<int> prime_numbers; /**< Vector to store the generated prime numbers */

public:
    /**
     * @class iterator
     * @brief Iterator for iterating over the prime numbers in the range.
     *
     * The iterator class allows iteration over the prime numbers within the
     * prime_number_range.
     */
    class iterator {
    public:
        /**
         * @brief Constructs an iterator for the given prime_number_range and starting index. Time complexity : O(1)
         *
         * @param range The prime_number_range to iterate over.
         * @param curr  The starting index within the range.
         */
        explicit iterator(const prime_number_range& range, std::size_t curr = 0);

        const prime_number_range& range; /**< Reference to the prime_number_range being iterated over */
        std::size_t curr;                /**< Current index within the range */

        /**
         * @brief Dereferences the iterator, returning the current prime number. Time complexity : O(1)
         *
         * @return The current prime number.
         */
        int operator*() const;

        /**
         * @brief Pre-increment operator. Moves the iterator to the next prime number. Time complexity : O(1)
         *
         * @return A reference to the updated iterator.
         */
        iterator operator++();

        /**
         * @brief Inequality operator. Checks if two iterators are pointing to different positions. Time complexity : O(1)
         *
         * @param other The iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const iterator other) const; // PSC: better inlined friend construction

        /**
         * @brief Equality operator. Checks if two iterators are pointing to the same position. Time complexity : O(1)
         *
         * @param other The iterator to compare with.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator==(const iterator other) const;
    };

    /**
     * @brief Returns an iterator pointing to the beginning of the prime number range. Time complexity : O(1)
     *
     * @return An iterator pointing to the beginning of the range.
     */
    iterator begin();

    /**
     * @brief Returns an iterator pointing to the end of the prime number range. Time complexity : O(1)
     *
     * @return An iterator pointing to the end of the range.
     */
    iterator end();

    /**
     * @brief Constructs a prime_number_range with the specified count.
     * Time Complexity: O(X * log X) where X is the largest prime // PSC O(X * X^0.5)?
     *
     * The prime_number_range is initialized with the provided count, which
     * determines the number of prime numbers to generate within the range.
     *
     * @param count The number of prime numbers to generate.
     */
    prime_number_range(std::size_t count);
};