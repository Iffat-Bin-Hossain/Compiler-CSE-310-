#include "2005087_ScopeTable.cpp"
class SymbolTable
{
private:
    unsigned long long bucketSize;
    ScopeTable *currentScope;

public:
    SymbolTable(unsigned long long bucketSize)
    {
        this->bucketSize = bucketSize;
        currentScope = new ScopeTable(bucketSize);
        currentScope->setId("1");
        cout<< "\tScopeTable# " << currentScope->getId() << " created" << endl;
    }
    ScopeTable *getCurrentScope() { return currentScope; }
    void EnterScope()
    {
        ScopeTable *newScope = new ScopeTable(bucketSize);
        newScope->setParentScope(currentScope);
        currentScope->setScopeNo(currentScope->getScopeNo()+1);
        newScope->setId(currentScope->getId()+"."+to_string(currentScope->getScopeNo()));
        currentScope = newScope;
        cout << "\tScopeTable# " << currentScope->getId() << " created" << endl;
    }
    void ExitScope()
    {
        cout<<"\tScopeTable# "<<currentScope->getId()<<" deleted"<<endl;
        ScopeTable *temp = currentScope->getParentScope();
        delete currentScope;
        currentScope = temp;
    }
    bool Insert(SymbolInfo *sInfo)
    {
        return currentScope->Insert(sInfo);
    }
    bool Remove(SymbolInfo *sInfo)
    {
        return currentScope->Delete(sInfo);
    }
    SymbolInfo *Lookup(SymbolInfo *sInfo)
    {
        ScopeTable *current = currentScope;
        while (current!= NULL)
        {
            SymbolInfo *searched = current->Lookup(sInfo);
            if (searched != NULL)
            {
                cout << "\t'" << sInfo->getName() << "' found at position <" << current->hashFunction(sInfo) + 1 << ", " << current->Position(sInfo) + 1 << "> of ScopeTable# " << current->getId() << endl;
                return searched;
            }
            current = current->getParentScope();
        }
        return NULL;
    }
    void PrintCurrentScope()
    {
        currentScope->Print();
    }
    void PrintAllScope()
    {
        ScopeTable *current = currentScope;
        while (current != NULL)
        {
            current->Print();
            current = current->getParentScope();
        }
    }
    ~SymbolTable(){
        while (currentScope != NULL)
            {
                ScopeTable *parent = currentScope->getParentScope();
                ExitScope();
                currentScope = parent;
            }
    }

};
