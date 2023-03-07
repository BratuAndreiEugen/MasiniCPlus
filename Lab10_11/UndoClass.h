#pragma once
#include "Repository.h"

// Clasa cu rol de interfata ( pure virtual )
class UndoClass
{
public:
	virtual void doUndo() = 0;
	virtual ~UndoClass() {};
	virtual const Masina getCar() {
		Masina m{ 101, "a", "fd", "fd" };
		return m;
	};
};

// Clasa pentru undo adaugare
class UndoStore : public UndoClass
{
	RepositoryMasini& repo;
	Masina toDelete;
public:
	UndoStore(RepositoryMasini& r, const Masina& m) : repo{ r }, toDelete{ m } {}
	void doUndo() override;
	const Masina getCar() override
	{
		return toDelete;
	}

	
};

// Clasa pentru undo stergere
class UndoRemove : public UndoClass
{
public:
	UndoRemove(RepositoryMasini& r, const Masina& m) : repo{ r }, toAdd{ m } {}
	void doUndo() override;
	const Masina getCar() override
	{
		return toAdd;
	}
private:
	RepositoryMasini& repo;
	Masina toAdd;
};

// Clasa pentru undo modificare
class UndoModify : public UndoClass
{
public:
	UndoModify(RepositoryMasini& r, const Masina& m) : repo{ r }, toRestore{ m } {}
	void doUndo() override;
	const Masina getCar() override
	{
		return toRestore;
	}
private:
	RepositoryMasini& repo;
	Masina toRestore;
};