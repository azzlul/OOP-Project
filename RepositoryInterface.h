#pragma once
#include <utility>
#include "VectorTemplate.h"
#include "Domain.h"
#include "vector"
#include "string"
#include "ostream"

using std::vector;
using std::string;
using std::ostream;

class RepositoryInterface {
    vector<Film> films;
    [[nodiscard]] virtual bool exist(const Film& fl)  = 0;
public:
    RepositoryInterface() = default;
    RepositoryInterface(const RepositoryInterface& rep) = delete;
    virtual ~RepositoryInterface() = default;
    RepositoryInterface& operator=(const RepositoryInterface& ot) = delete;
    RepositoryInterface(const RepositoryInterface&& rep) = delete;
    RepositoryInterface& operator=(const RepositoryInterface&& ot) = delete;
    /**
     * Add a film to the repository
     * Throws an exception if a film with the same title is already in the repository
     * @param fl = Film
     */
    virtual void add(const Film& fl) = 0;
    /**
     * Searches for the film with the given title
     * Throws exception if the film is not in repository
     * @param title = string
     * @return fl = Film with the given title
     */
    [[nodiscard]]virtual const  Film& find(const string& title) = 0;
    /**
     * Returns a vector with all the films in the repository
     * @return = films = Film vector
     */
    [[nodiscard]]virtual const vector<Film>& getAll() = 0;

    /**
     * Updates a film from the repository
     * Throws an exception if no film with the same title exists
     * @param fl = Film
     * @return previous film
     */
    virtual Film update(const Film& fl) = 0;
    /**
     * Deletes the film with the given title
     * Throws an exception if no film with the given title exists
     * @param title = string
     * @return deleted film
     */
    virtual Film del(const string& title) = 0;
};
