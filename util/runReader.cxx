
#include <cstdlib>
#include <string>

#include "TChain.h"
#include "Cintex/Cintex.h"

#include "ReadTuple/Reader.h"

using namespace std;

int main(int argc, char** argv)
{
    string input("/gdata/atlas/gerbaudo/wh/Susy2013_Nt_01_04_dev/SusyTest0/run/out/susysel/merged/diboson_Dec_02.root");
    string treeName("SusySel");
    TChain* chain = new TChain(treeName.c_str());
    chain->Add(input.c_str());
    Long64_t nEntries = chain->GetEntries();
    nEntries = 10;
    Long64_t nSkip = 0;
    Reader* reader = new Reader();
    const char* opt="";
    chain->Process(reader, opt, nEntries, nSkip);
    cout<<endl<<"Reader job done"<<endl;
    delete chain;
    delete reader;
    return 0;
}
