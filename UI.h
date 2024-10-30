#pragma once
#include "Service.h"
#include "Domain.h"
class UI {
    Service& srv;
    /**
     * Reads the title, genre, release year and main actor of a film, and adds it in the application
     * Throws exception if a film with the same title is already memorized or the data isn't valid
     */
    void addUI();
    /**
     * Reads the title, genre, release year and main actor of a film, and adds it in the application
     * Throws exception if no film with the given title exists, or the data isn't valid
     */
    void updateUI();
    /**
     * Reads the title of a film and deletes it from the application
     * Throws exception if no film with the given title exists, or the title isn't valid
     */
    void deleteUI();
    /**
     * Reads the title of a film and prints it
     * Throws exception if no film with the given title exists, or the title isn't valid
     */
    void findUI();
    /**
     * Reads an option and parameter and prints the filtered films
     * Throws exception if the parameter is invalid or can't be parsed as int in the case of option 2
     */
    void filterUI();
    /**
     * Reads an option and prints the sorted films
     */
    void sortUI();
    /**
     * Empties the contents from the cart
     */
    void emptyCartUI();
    /**
     * Adds a film to the cart with the title given by the user
     * throws exception if the film with the given title doesn't exist, or the title isn't valid
     */
    void addCartUI();
    /**
     * Generates a cart with the number of movies given by the user
     * If the number given is bigger than the total number of movies, all movies are added
     * Throws exception if the number in negative or 0
     */
    void generateCartUI();
    /**
     * Prints all carts
     */
    void printAllCart();
    /**
     *  Prints all the films from a vector of films
     * @param films = Film vector
     */
    static void printFilms(const vector<Film>& films);
    /**
     * Prints how many films are there of each genre
     */
    void getRapportUI();
    /**
     * Exports the cart in a CVS file with the name given by the user
     */
    void exportCVSUI();
    /**
     * Undoes the last action, if there is one available
     */
    void undoUI();
public:
    explicit UI(Service& srv):srv{srv}{}
    ~UI() = default;
    UI& operator=(const UI& ot) = delete;
    UI(const UI&& rep) = delete;
    UI& operator=(const UI&& ot) = delete;
    UI(UI& ot) = delete;
    /**
     * Aplicatie pornire UI
     */
    void runUI();
};
