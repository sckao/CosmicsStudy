#ifndef Rtuple_h
#define Rtuple_h

#include "TChain.h" 

#define MAXDT 15
#define MAXPHO 15

struct Rtuple {

  unsigned int runId;
  unsigned int eventId;
  int triggered ;
  int L1a;  
  int nSC ;
  int nDT ;
  int nCSC ;
  int nMuons ;
  
  float met ;
  float metPx ;
  float metPy ;

  float dtdEta[MAXPHO] ;
  float dtdPhi[MAXPHO] ;
  float cscdPhi[MAXPHO] ;
  float cscRho[MAXPHO] ;

  float xtalEta[MAXPHO] ;
  float xtalPhi[MAXPHO] ;
  float xtalE[MAXPHO] ;
  float xtalSigma[MAXPHO] ;
  float xtalSwissX[MAXPHO] ;
  float xtalChi2[MAXPHO] ;
  float xtal_x[MAXPHO] ;
  float xtal_y[MAXPHO] ;
  float xtal_z[MAXPHO] ;
  float xtal_t[MAXPHO] ;
  float bc_sMaj[MAXPHO] ;
  float bc_sMin[MAXPHO] ;
  float bc_E[MAXPHO] ;
  int bc_nXtals[MAXPHO] ;
  int bc_nBC[MAXPHO] ;

  float cscX[MAXDT] ;
  float cscY[MAXDT] ;
  float cscZ[MAXDT] ;
  float cscdX[MAXDT] ;
  float cscdY[MAXDT] ;
  float cscdZ[MAXDT] ;
  float csc_dPhi[MAXDT] ;

  float dtX[MAXDT] ;
  float dtY[MAXDT] ;
  float dtZ[MAXDT] ;
  float dtdX[MAXDT] ;
  float dtdY[MAXDT] ;
  float dtdZ[MAXDT] ;
  float dt_dR[MAXDT] ;

} ;

// ------------------------------------------------------------------------
//! branch addresses settings
void setRtupleAddresses(TTree* chain, Rtuple& Vars );

//! create branches for a tree
//void setRtupleBranches(TTree* chain, Rtuple& treeVars);

//! initialize branches
//void initRtuple(TTree* chain, Rtuple& treeVars);



#endif
