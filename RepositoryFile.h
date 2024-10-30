#pragma once
#include <utility>

#include "Repository.h"
#include "Domain.h"
#include "string"
using std::string;
class RepositoryFile: public Repository{
    string file_path;
    /**
 * Saves the contents of the repository to a CVS file
 */
    void saveToCSV();
    /**
     * Loads the contents of a CSV to a repository
     */
    void loadFromCSV();
public:
    explicit RepositoryFile(string file_path): file_path{std::move(file_path)}{};
    RepositoryFile(const RepositoryFile& rep) = delete;
    ~RepositoryFile() override = default;
    RepositoryFile& operator=(const RepositoryFile& ot) = delete;
    RepositoryFile(const RepositoryFile&& rep) = delete;
    RepositoryFile& operator=(const RepositoryFile&& ot) = delete;
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
    [[nodiscard]]const Film & find(const string& title) override;
    /**
     * Returns a vector with all the films in the repository
     * @return = films = Film vector
     */
    [[nodiscard]] const vector<Film> & getAll() override;

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

void testeRepoFile();