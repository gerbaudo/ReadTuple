#include "ReadTuple/Reader.h"

#include <iostream>
#include <sstream> // std::ostringstream

using namespace std;

//-----------------------------------------
Reader::Reader() :
    m_chainEntry(0),
    m_eventParameters(0),
    m_l0(0),
    m_l1(0),
    m_met(0),
    m_eventParameters_b(0),
    m_l0_b(0),
    m_l1_b(0),
    m_met_b(0)
{
    m_eventParameters = new susy::wh::EventParameters();
    m_l0 = new susy::wh::FourMom();
    m_l1 = new susy::wh::FourMom();
    m_met = new susy::wh::FourMom();
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
    if(tree){
        tree->SetBranchAddress("pars", &m_eventParameters, &m_eventParameters_b);
        tree->SetBranchAddress("l0", &m_l0, &m_l0_b);
        tree->SetBranchAddress("l1", &m_l1, &m_l1_b);
        tree->SetBranchAddress("met", &m_met, &m_met_b);
    }
}
//-----------------------------------------
void    Reader::Begin(TTree *tree)
{
    cout<<"calling begin"<<endl;
}
//-----------------------------------------
string fourMom2str(const susy::wh::FourMom* fm)
{
    std::ostringstream oss;
    string lt(fm->isMu ? "mu" :
              fm->isEl ? "el" :
              fm->isJet ? "jet" : "??");
    if(fm) oss<<lt<<" px "<<fm->px<<" py "<<fm->py<<" pz "<<fm->pz<<" E "<<fm->E;
    return oss.str();
}
//-----------------------------------------
Bool_t  Reader::Process(Long64_t entry)
{
    cout<<"Processing Entry number "<<entry<<endl;
    readBranches(entry);
    const susy::wh::EventParameters &ep = *m_eventParameters;
    cout<<"EventParameters: weight "<<ep.weight<<" event "<<ep.eventNumber<<" run "<<ep.runNumber<<endl;
    cout<<"l0  : "<<fourMom2str(m_l0 )<<endl;
    cout<<"l1  : "<<fourMom2str(m_l1 )<<endl;
    cout<<"met : "<<fourMom2str(m_met)<<endl;
    ++m_chainEntry;
    return kTRUE;
}
//-----------------------------------------
void    Reader::Terminate()
{
    cout<<endl<<"Total Number of Events: "<<m_chainEntry<<endl;
}
//-----------------------------------------
void Reader::readBranches(Long64_t entry)
{
    m_eventParameters_b->GetEntry(entry);
    m_l0_b->GetEntry(entry);
    m_l1_b->GetEntry(entry);
    m_met_b->GetEntry(entry);
}
