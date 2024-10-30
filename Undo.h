#pragma once
#include <utility>

#include "Domain.h"
#include "Repository.h"
class ActiuneUndo{
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo(){};
};
class UndoAdauga : public ActiuneUndo{
    Film film_adaugat;
    RepositoryInterface& repo;
public:
    UndoAdauga(RepositoryInterface& repo, Film fl) : film_adaugat{std::move(fl)}, repo{repo}{}
    void doUndo() override{
        repo.del(film_adaugat.getTitle());
    }
};
class UndoSterge : public ActiuneUndo{
    Film film_sters;
    RepositoryInterface& repo;
public:
    UndoSterge(RepositoryInterface& repo, Film fl) : film_sters{std::move(fl)}, repo{repo}{}
    void doUndo() override{
        repo.add(film_sters);
    }
};
class UndoModifica : public ActiuneUndo{
    Film film_modificat;
    RepositoryInterface& repo;
public:
    UndoModifica(RepositoryInterface& repo, Film fl) : film_modificat{std::move(fl)}, repo{repo}{}
    void doUndo() override{
        repo.update(film_modificat);
    }
};

