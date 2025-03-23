#include <string>

namespace {
    const int weights[] = {
        1, // A
        3, // B
        3, // C
        2, // D
        1, // E
        4, // F
        2, // G
        4, // H
        1, // I
        8, // J
        5, // K
        1, // L
        3, // M
        1, // N
        1, // O
        3, // P
        10, // Q
        1, // R
        1, // S
        1, // T
        1, // U
        4, // V
        4, // W
        8, // X
        4, // Y
        10, // Z
    };
}

int countScrabbleScore(const std::string& word)
{    
    int score = 0;
    for (const char wordLetter: word) {
        score += weights[std::toupper(wordLetter) - 'A'];
    }
    return score;
}