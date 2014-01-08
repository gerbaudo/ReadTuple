// emacs -*- C++ -*-
#ifndef Reader_h
#define Reader_h

// Common Packages

// Root Packages
#include "TROOT.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TSelector.h"

#include "SusyTest0/TupleMakerObjects.h"

class Reader : public TSelector
{
public:
    Reader();
    virtual ~Reader();
    virtual void    Init(TTree *tree);
    virtual void    Begin(TTree *tree);
    virtual Bool_t  Notify() { return kTRUE; }
    virtual Bool_t  Process(Long64_t entry);
    virtual void    Terminate();
    virtual Int_t   Version() const { return 2; }
    ClassDef(Reader, 2);

protected:
    Int_t m_chainEntry;
    susy::wh::EventParameters* m_eventParameters;
    susy::wh::FourMom *m_l0, *m_l1, *m_met;
    TBranch* m_eventParameters_b;
    TBranch *m_l0_b, *m_l1_b, *m_met_b;

private:
    void readBranches(Long64_t entry);
};

#endif // Reader_h
