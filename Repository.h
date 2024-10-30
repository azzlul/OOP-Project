#pragma once
#include <utility>
#include "VectorTemplate.h"
#include "RepositoryInterface.h"
#include "Domain.h"
#include "vector"
#include "string"
#include "ostream"

using std::vector;
using std::string;
using std::ostream;

class Repository: public RepositoryInterface{
protected:
    vector<Film> films;
    [[nodiscard]] bool exist(const Film& fl) override;
public:
    Repository() = default;
    Repository(const Repository& rep) = delete;
    ~Repository() override = default;
    Repository& operator=(const Repository& ot) = delete;
    Repository(const Repository&& rep) = delete;
    Repository& operator=(const Repository&& ot) = delete;
    /**
     * Add a film to the repository
     * Throws an exception if a film with the same title is already in the repository
     * @param fl = Film
     */
    void add(const Film& fl) override;
    /**
     * Searches for the film with the given title
     * Throws exception if the film is not in repository
     * @param title = string
     * @return fl = Film with the given title
     */
    [[nodiscard]]const  Film& find(const string& title) override;
    /**
     * Returns a vector with all the films in the repository
     * @return = films = Film vector
     */
    [[nodiscard]] const vector<Film>& getAll() override;

    /**
     * Updates a film from the repository
     * Throws an exception if no film with the same title exists
     * @param fl = Film
     * @return previous film
     */
    Film update(const Film& fl) override;
    /**
     * Deletes the film with the given title
     * Throws an exception if no film with the given title exists
     * @param title = string
     * @return deleted film
     */
    Film del(const string& title) override;
};

class RepositoryException: public std::exception{
    string msg;
public:
    explicit RepositoryException(string m): msg{std::move(m)} {}
    string getMessage(){
        return msg;
    }
    friend ostream& operator<<(ostream& out, const RepositoryException& ex);
};

ostream& operator<<(ostream& out, const RepositoryException& ex);

void testeRepo();