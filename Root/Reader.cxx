#include "ReadTuple/Reader.h"

#include <iostream>

using namespace std;
using namespace Susy;

//-----------------------------------------
Reader::Reader() :
    m_chainEntry(0),
    m_eventParameters(0),
    m_eventParameters_b(0)
{
    m_eventParameters = new susy::wh::EventParameters();
}
//-----------------------------------------
Reader::~Reader()
{
    if(m_eventParameters) { delete m_eventParameters; m_eventParameters = 0; }
}
//-----------------------------------------
void    Reader::Init(TTree *tree)
{
    cout<<"calling init"<<endl;
    if(tree)
        tree->SetBranchAddress("pars", &m_eventParameters, &m_eventParameters_b);
}
//-----------------------------------------
void    Reader::Begin(TTree *tree)
{
    cout<<"calling begin"<<endl;
}
//-----------------------------------------
Bool_t  Reader::Process(Long64_t entry)
{
    cout<<"Processing Entry number "<<entry<<endl;
    m_eventParameters_b->GetEntry(entry);
    const susy::wh::EventParameters &ep = *m_eventParameters;
    cout<<"EventParameters: weight "<<ep.weight<<" event "<<ep.eventNumber<<" run "<<ep.runNumber<<endl;
    ++m_chainEntry;
    return kTRUE;
}
//-----------------------------------------
void    Reader::Terminate()
{
    cout<<endl<<"Total Number of Events: "<<m_chainEntry<<endl;
}
//-----------------------------------------
