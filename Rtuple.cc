#include "Rtuple.h"

void setRtupleAddresses(TTree* tr, Rtuple& vr ) {

   tr->SetBranchAddress("runId",      &vr.runId);
   tr->SetBranchAddress("eventId",    &vr.eventId);
   tr->SetBranchAddress("triggered",  &vr.triggered);
   tr->SetBranchAddress("L1a",        &vr.L1a);
   tr->SetBranchAddress("nSC",        &vr.nSC);
   tr->SetBranchAddress("nDT",        &vr.nDT);
   tr->SetBranchAddress("nCSC",       &vr.nCSC);
   tr->SetBranchAddress("nMuons",     &vr.nMuons);

   tr->SetBranchAddress("met",        &vr.met );
   tr->SetBranchAddress("metPx",      &vr.metPx );
   tr->SetBranchAddress("metPy",      &vr.metPy );

   tr->SetBranchAddress("dtdEta",     vr.dtdEta );
   tr->SetBranchAddress("dtdPhi",     vr.dtdPhi );
   tr->SetBranchAddress("cscdPhi",    vr.cscdPhi );
   tr->SetBranchAddress("cscRho",     vr.cscRho );
   tr->SetBranchAddress("xtalE",      vr.xtalE );
   tr->SetBranchAddress("xtalSigma",  vr.xtalSigma );
   tr->SetBranchAddress("xtalSwissX", vr.xtalSwissX );
   tr->SetBranchAddress("xtalChi2",   vr.xtalChi2 );
   tr->SetBranchAddress("xtal_x",     vr.xtal_x );
   tr->SetBranchAddress("xtal_y",     vr.xtal_y );
   tr->SetBranchAddress("xtal_z",     vr.xtal_z );
   tr->SetBranchAddress("xtal_t",     vr.xtal_t );
   tr->SetBranchAddress("bc_sMaj",    vr.bc_sMaj );
   tr->SetBranchAddress("bc_sMin",    vr.bc_sMin );
   tr->SetBranchAddress("bc_E",       vr.bc_E );
   tr->SetBranchAddress("bc_nXtals",  vr.bc_nXtals );
   tr->SetBranchAddress("bc_nBC",     vr.bc_nBC );

   tr->SetBranchAddress("cscX",       vr.cscX );
   tr->SetBranchAddress("cscY",       vr.cscY );
   tr->SetBranchAddress("cscZ",       vr.cscZ );
   tr->SetBranchAddress("cscdX",      vr.cscdX );
   tr->SetBranchAddress("cscdY",      vr.cscdY );
   tr->SetBranchAddress("cscdZ",      vr.cscdZ );
   tr->SetBranchAddress("csc_dPhi",   vr.csc_dPhi );

   tr->SetBranchAddress("dtX",        vr.dtX );
   tr->SetBranchAddress("dtY",        vr.dtY );
   tr->SetBranchAddress("dtZ",        vr.dtZ );
   tr->SetBranchAddress("dtdX",       vr.dtdX );
   tr->SetBranchAddress("dtdY",       vr.dtdY );
   tr->SetBranchAddress("dtdZ",       vr.dtdZ );
   tr->SetBranchAddress("dt_dR",      vr.dt_dR );

}

/*
void setRtupleBranches(TTree* chain, Rtuple& treeVars) {

  chain -> Branch("nJets",       &treeVars.nJets,                "nJets/I");
  chain -> Branch("nPhotons",    &treeVars.nPhotons,             "nPhotons/I");

  chain -> Branch("met",         &treeVars.met,                  "met/F");
  chain -> Branch("g1Pt",        &treeVars.g1Pt,                 "g1Pt/F");
  chain -> Branch("g2Pt",        &treeVars.g2Pt,                 "g2Pt/F");
}


void initRtuple(TTree* chain, Rtuple& treeVars) {
  
  treeVars.nJets      = 0 ; 
  treeVars.nPhotons   = 0 ; 

  treeVars.met     = 0 ;
  treeVars.g1Pt    = 0 ;
  treeVars.g2Pt    = 0 ;

}
*/

