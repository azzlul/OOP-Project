#pragma once
#include <utility>
#include "iostream"
#include "string"

using std::string;
using std::cout;
class Film{
    string title;
    string genre;
    int year;
    string actor;
public:
    Film() = default;
    Film(string  title, string  genre, const int year, string  actor):title{std::move(title)},
                                                                      genre{std::move(genre)},
                                                                      year{year},
                                                                      actor{std::move(actor)}{}
    Film(const Film& other):title{other.title},
                            genre{other.genre},
                            year{other.year},
                            actor{other.actor}{
        //cout<<"huh\n";
    }
    ~Film() = default;
    Film& operator=(const Film& ot) = default;
    Film(Film&& ot) = default;
    Film& operator=(Film&& ot) = default;

    [[nodiscard]] string getTitle() const{
        return title;
    }
    [[nodiscard]] string getGenre() const{
        return genre;
    }
    [[nodiscard]] int getYear() const{
        return year;
    }
    [[nodiscard]] string getActor() const{
        return actor;
    }
};

void testeDomain();