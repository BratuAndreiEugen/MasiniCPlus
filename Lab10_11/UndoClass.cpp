#include "UndoClass.h"

void UndoStore::doUndo()
{
	repo.remove(toDelete);
}

void UndoRemove::doUndo()
{
	repo.store(toAdd);
}

void UndoModify::doUndo()
{
	Masina m = repo.find(toRestore.getNumar());
	repo.modify(m, toRestore);
}