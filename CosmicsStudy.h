#ifndef CosmicsStudy_H
#define CosmicsStudy_H

#include <TObject.h>
#include <TSystem.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TString.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "hDraw.h"
#include "Rtuple.h"

class CosmicsStudy : public TObject {

public:

   CosmicsStudy( string datacardfile = "DataCard.txt");     
   ~CosmicsStudy();     
   
   //void init( string dataName = "") ;
   void Create() ;
   void Open() ;
   void Write() ;

   void SimpleRun( string dataName = "", double weight = 1. ) ;

   void DrawHistograms( ) ;


private:

   AnaInput*   Input ;
   //hDraw*      h_draw ;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int ProcessEvents ;
   int SkipEvents ;
   int isData ;
   vector<double> cuts ;

   TFile *theFile ;

   int totalN ;
   TTree* tr ;
   Rtuple rt ;

   // Histograms set
   TH1D* h_cscdPhi ;
   TH1D* h_nBC ;
   TH1D* h_nXtal ;
   TH1D* h_swissX ;
   TH1D* h_met;
   TH1D* h_seedTime;
   TH1D* h_seedTime1;

   TH2D* h_eta_phi ;
   TH2D* h_eta_phi1 ;
   TH2D* h_eta_Time ;
   TH2D* h_phi_Time ;
   TH2D* h_dt_dPhi_dEta ;
   TH2D* h_seedE_Time ;
   TH2D* h_sMaj_sMin ;

  unsigned int runId, eventId;
  int triggered, L1a, nSC, nDT, nCSC, nMuons ;

  float met, metPx, metPy ;

  float dtdEta[MAXPHO], dtdPhi[MAXPHO], cscdPhi[MAXPHO], cscRho[MAXPHO] ;

  float xtalEta[MAXPHO], xtalPhi[MAXPHO] ;
  float xtalE[MAXPHO], xtalSigma[MAXPHO], xtalSwissX[MAXPHO], xtalChi2[MAXPHO] ;
  float xtal_x[MAXPHO], xtal_y[MAXPHO], xtal_z[MAXPHO], xtal_t[MAXPHO] ;
  float bc_sMaj[MAXPHO], bc_sMin[MAXPHO], bc_E[MAXPHO] ;
  int bc_nXtals[MAXPHO], bc_nBC[MAXPHO] ;

  float cscX[MAXDT], cscY[MAXDT], cscZ[MAXDT] ;
  float cscdX[MAXDT], cscdY[MAXDT], cscdZ[MAXDT], csc_dPhi[MAXDT] ;

  float dtX[MAXDT], dtY[MAXDT], dtZ[MAXDT] ;
  float dtdX[MAXDT], dtdY[MAXDT], dtdZ[MAXDT], dt_dR[MAXDT] ;


   //ClassDef(CosmicsStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(CosmicsStudy);
#endif

