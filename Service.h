#pragma once

#include "observer.h"
#include "Domain.h"
#include "Repository.h"
#include "Validator.h"
#include "VectorTemplate.h"
#include "string"
#include "vector"
#include "functional"
#include "map"
#include "Undo.h"
#include "memory"
using std::map;
using std::string;
using std::vector;
using std::function;
using std::unique_ptr;
class Service: public Observable{
    RepositoryInterface& rep;
    vector<Film> cart;
    vector<unique_ptr<ActiuneUndo>> undoActions;
private:
    /**
     * Function that returns a filtered list of all films, based on the given function
     * @param fct = function that takes a Film, and returns a bool
     * @return Film vector
     */
    vector<Film> filterFct(const function<bool(const Film&)>& fct);
    vector<Film> sortFct(const function<bool(const Film&, const Film&)>& fct);
public:
    explicit Service(RepositoryInterface& rep):rep{rep}{}
    Service(Service& ot) = delete;
    ~Service() = default;
    Service& operator=(const Service& ot) = delete;
    Service(const Service&& rep) = delete;
    Service& operator=(const Service&& ot) = delete;
    /**
     * Returns a vector with all films in the object
     * @return = vector of films
     */
    const vector<Film>& getAll();
    /**
     * Adds a film in the object with the specified parameters
     * Throws exception if a film with the same title already exists or the film is not valid
     * @param title = string
     * @param genre = string
     * @param year = int
     * @param author = string
     */
    void addSrv(const string& title, const string& genre, int year, const string& author);
    /**
     * Updates a film with the same title with the given genre, year and actor
     * Throws exception if no film with the given title exists or if the film is not valid
     * @param title = string
     * @param genre = string
     * @param year = year
     * @param author = string
     */
    void updateSrv(const string& title, const string& genre, int year, const string& actor);
    /**
     * Deletes a film with the given title
     * Throws exception if the film with the given title doesn't exist or the given title is not valid
     * @param title = string
     */
    void deleteSrv(const string& title);
    /**
     * Returns the film with the given title
     * Throws exception if the film with the given title doesn't exist or the given title is not valid
     * @param title = string
     */
    const Film& findSrv(const string& title);
    /**
     * Returns a vector of films filtered by one of 2 options:
     * 1 - filter by title
     * 2 - filter by release year
     * Throws exception if the parameter is invalid, or can't pe parsed into int if option 2 is chosen
     * @param option = 1 or 2
     * @param parameter = string
     * @return = Film vector
     */
    vector<Film> filter(int option, const string& parameter);
    /**
     * Returns a vector of films sorted by one of 3 options:
     * 1 - sort by title
     * 2 - sort by main actor
     * 3 - sort by release year + genre
     * @param option = 1, 2, 3
     * @return = Film vector
     */
    vector<Film> sort(int option);
    /**
     * Empties the contents of the shopping cart
     */
    void emptyCart();
    /**
     * Adds the film with the given title to the cart
     * throws exception if title is invalid
     * @param title = string
     */
    void addCart(const string& title);
    /**
     * Adds a given number of randomly selected films in the cart
     * throws exception if nr is invalid
     * if there are less than nr films in memory, all available films are added
     * @param nr = int > 0
     */
    void generateCart(unsigned long long nr);
    /**
     * Returns the number of films in the cart
     */
    size_t showCartSize();
    /**
     * Returns the cart vector
     * @return Film vector
     */
    vector<Film>& getAllCart();
    /**
     * Returns a rapport of how many movies are there for each genre, in the form of a map
     * @return  map with string key and int value
     */
    map<string, int> getRapport();
    /**
     * Exports the contents of the cart to a CVS file
     * @param fileName string
     */
    void exportCVS(const string& fileName);
    /**
     * Undoes the last action that modified the film list
     * @return true if the undo action was successful, false if no undo action is available
     */
    bool undo();
};

void testeSrv();