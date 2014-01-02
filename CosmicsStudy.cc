#include "CosmicsStudy.h"
#include <TTree.h>
#include <algorithm>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TF2.h>

CosmicsStudy::CosmicsStudy( string datacardfile ) {

  Input  = new AnaInput( datacardfile );

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("HFileName",     &hfileName ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("Cuts",          &cuts ) ;
  //h_draw = new hDraw( datacardfile ) ;
}

CosmicsStudy::~CosmicsStudy(){

  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete Input ;
  //delete h_draw ;
  cout<<" done ! "<<endl ;

}

void CosmicsStudy::Create() {

  gSystem->mkdir( hfolder.c_str() );

  TString Path_fName = hfolder + hfileName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  //theFile->cd() ;

  // Raw information
  h_eta_phi      = new TH2D( "h_eta_phi",  " eta vs phi of xtals", 102, -2.6, 2.6, 63, -3.15, 3.15 ) ;
  h_eta_phi1     = new TH2D( "h_eta_phi1", " eta vs phi of xtals", 102, -2.6, 2.6, 63, -3.15, 3.15 ) ;
  h_eta_Time     = new TH2D( "h_eta_Time", " eta vs Ecal time", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_phi_Time     = new TH2D( "h_phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  h_sMaj_sMin    = new TH2D( "h_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  h_dt_dPhi_dEta = new TH2D( "h_dt_dPhi_dEta", " DT dEta, dPhi  ", 64, 0, 3.2 , 50, 0, 1. ) ;
  h_seedE_Time   = new TH2D( "h_seedE_Time",  " XtalE vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  
  h_cscdPhi      = new TH1D( "h_cscdPhi", " CSC d#Phi ", 65, 0, 3.25 ) ;
  h_nBC          = new TH1D( "h_nBC",   "N Basic Cluster ", 30, 0, 30 ) ;
  h_nXtal        = new TH1D( "h_nXtal", "N crystals ", 50, 0, 50 ) ;
  h_swissX       = new TH1D( "h_swissX", "Swiss-X ", 110, 0, 1.1 ) ;
  h_met          = new TH1D( "h_met",    " MET ", 50, 0, 250 ) ;
  h_seedTime     = new TH1D( "h_seedTime", " Seed Time ", 400, -100, 100 ) ;
  h_seedTime1    = new TH1D( "h_seedTime1", " Seed Time ", 200, -25, 25 ) ;

}

void CosmicsStudy::Open() {

     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<endl ;

     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     cout<<" file opened ! "<<endl ;

     h_eta_phi   = (TH2D*) theFile->Get("h_eta_phi");
     h_eta_phi1  = (TH2D*) theFile->Get("h_eta_phi1");
     h_eta_Time  = (TH2D*) theFile->Get("h_eta_Time");
     h_phi_Time  = (TH2D*) theFile->Get("h_phi_Time");
     h_sMaj_sMin = (TH2D*) theFile->Get("h_sMaj_sMin");
     h_dt_dPhi_dEta = (TH2D*) theFile->Get("h_dt_dPhi_dEta");
     h_seedE_Time  = (TH2D*) theFile->Get("h_seedE_Time") ;

     h_cscdPhi = (TH1D*) theFile->Get("h_cscdPhi");
     h_nXtal   = (TH1D*) theFile->Get("h_nXtal");
     h_nBC     = (TH1D*) theFile->Get("h_nBC");
     h_swissX  = (TH1D*) theFile->Get("h_swissX");
     h_met     = (TH1D*) theFile->Get("h_met");
     h_seedTime  = (TH1D*) theFile->Get("h_seedTime");
     h_seedTime1 = (TH1D*) theFile->Get("h_seedTime1");
     cout<<" link all histograms  "<<endl ;
}

void CosmicsStudy::Write() {

  cout<<" start writting  ! "<< endl ;
  h_cscdPhi->Write() ;
  h_nBC->Write() ;
  h_nXtal->Write() ;
  h_swissX->Write() ;
  h_met->Write() ;
  h_seedTime->Write() ;
  h_seedTime1->Write() ;

  h_eta_phi->Write() ;
  h_eta_phi1->Write() ;
  h_eta_Time->Write() ;
  h_phi_Time->Write() ;
  h_dt_dPhi_dEta->Write() ;
  h_seedE_Time->Write() ;
  h_sMaj_sMin->Write() ;
  cout<<" Output historams written ! "<< endl ;

}

void CosmicsStudy::SimpleRun( string dataName, double weight ) { 

   // Open file and link the tree
   string dataFileNames ;
   if ( dataName.size() > 0 ) {
      dataFileNames = dataName ;
   } else {
      Input->GetParameters( "TheData", &dataFileNames );
   }
   tr   = Input->GetTree( dataFileNames, "CosmicAnalysis" );
   cout<<" Get the tree ! "<<endl ;


   totalN = tr->GetEntries();
   //setRtupleAddresses( tr, rt );
   
   tr->SetBranchAddress("runId",      &runId);
   tr->SetBranchAddress("eventId",    &eventId);
   tr->SetBranchAddress("triggered",  &triggered);
   tr->SetBranchAddress("L1a",        &L1a);
   tr->SetBranchAddress("nSC",        &nSC);
   tr->SetBranchAddress("nDT",        &nDT);
   tr->SetBranchAddress("nCSC",       &nCSC);
   tr->SetBranchAddress("nMuons",       &nMuons);

   tr->SetBranchAddress("met",        &met );
   tr->SetBranchAddress("metPx",      &metPx );
   tr->SetBranchAddress("metPy",      &metPy );

   tr->SetBranchAddress("dtdEta",     dtdEta );
   tr->SetBranchAddress("dtdPhi",     dtdPhi );
   tr->SetBranchAddress("cscdPhi",    cscdPhi );
   tr->SetBranchAddress("cscRho",     cscRho );
   tr->SetBranchAddress("xtalE",      xtalE );
   tr->SetBranchAddress("xtalSigma",  xtalSigma );
   tr->SetBranchAddress("xtalSwissX", xtalSwissX );
   tr->SetBranchAddress("xtalChi2",   xtalChi2 );
   tr->SetBranchAddress("xtalEta",    xtalEta );
   tr->SetBranchAddress("xtalPhi",    xtalPhi );
   tr->SetBranchAddress("xtal_x",     xtal_x );
   tr->SetBranchAddress("xtal_y",     xtal_y );
   tr->SetBranchAddress("xtal_z",     xtal_z );
   tr->SetBranchAddress("xtal_t",     xtal_t );
   tr->SetBranchAddress("bc_sMaj",    bc_sMaj );
   tr->SetBranchAddress("bc_sMin",    bc_sMin );
   tr->SetBranchAddress("bc_E",       bc_E );
   tr->SetBranchAddress("bc_nXtals",  bc_nXtals );
   tr->SetBranchAddress("bc_nBC",     bc_nBC );

   tr->SetBranchAddress("cscX",       cscX );
   tr->SetBranchAddress("cscY",       cscY );
   tr->SetBranchAddress("cscZ",       cscZ );
   tr->SetBranchAddress("cscdX",      cscdX );
   tr->SetBranchAddress("cscdY",      cscdY );
   tr->SetBranchAddress("cscdZ",      cscdZ );
   tr->SetBranchAddress("csc_dPhi",   csc_dPhi );

   tr->SetBranchAddress("dtX",        dtX );
   tr->SetBranchAddress("dtY",        dtY );
   tr->SetBranchAddress("dtZ",        dtZ );
   tr->SetBranchAddress("dtdX",       dtdX );
   tr->SetBranchAddress("dtdY",       dtdY );
   tr->SetBranchAddress("dtdZ",       dtdZ );
   tr->SetBranchAddress("dt_dR",      dt_dR );
   cout<<" Link Tree variables ! "<<endl ;


   // Create hitograms
   Create() ;

   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   cout<<" from  "<< dataFileNames  <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   for ( int i= beginEvent ; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;

       //printf(" nSC: %d, nDT: %d , nCSC: %d\n ", rt.nSC, rt.nDT, rt.nCSC ) ;
       //printf(" met x:%f , y:%f, pt:%f \n", rt.metPx, rt.metPy, rt.met ) ;
       //TLorentzVector met( rt.metPx, rt.metPy, 0., rt.met )  ;
       if ( nDT < 1 ) continue ;

       bool passFinal = false ;
       for ( int k=0 ; k < nSC ; k++ ) {

           //printf("    --> E:%.2f, t:%.2f \n", xtalE[k], xtal_t[k]  ) ;
           float xtal_r   = sqrt( (xtal_x[k]*xtal_x[k]) + (xtal_y[k]*xtal_y[k]) + (xtal_z[k]*xtal_z[k]) );
           float xtal_rho = sqrt( (xtal_x[k]*xtal_x[k]) + (xtal_y[k]*xtal_y[k]) );
           //if ( xtal_rho < 129. ||  fabs(xtal_z[k]) > 390. ) {
           //   printf(" [%d] ( %.1f, %.1f, %.1f , %.2f , %.2f ) \n", 
           //              k, xtal_x[k], xtal_y[k], xtal_z[k], xtalEta[k], xtalPhi[k] ) ;
           //}
           if ( xtal_rho < 129. && fabs(xtal_z[k]) < 340. ) continue ;
           if ( xtal_rho > 135. ) continue ;
           if ( fabs(xtal_z[k]) > 390. ) continue ;
            
	   TLorentzVector gP4 = TLorentzVector( xtal_x[k], xtal_y[k], xtal_z[k], xtal_r ) ;
           h_eta_phi->Fill( gP4.Eta(), gP4.Phi() ) ;

           // bad crystals : (1.186, 1.108) , (0.191, 1.004) , (0.225, 0.987) , (-1.306, -2.996) , (-1.443, 3.115) 
           //                (0.695, -0.655) , (-1.408 , -0.953)  
           bool badXtal =  false ;
           if ( gP4.Eta() > 1.18 && gP4.Eta() < 1.19 && gP4.Phi() >  1.10 && gP4.Phi() <  1.11  ) badXtal = true ;
           if ( gP4.Eta() > 0.69 && gP4.Eta() < 0.70 && gP4.Phi() > -0.66 && gP4.Phi() < -0.65  ) badXtal = true ; 
           if ( gP4.Eta() > 0.22 && gP4.Eta() < 0.23 && gP4.Phi() >  0.98 && gP4.Phi() <  0.99  ) badXtal = true ;
           if ( gP4.Eta() > 0.19 && gP4.Eta() < 0.20 && gP4.Phi() >  1.00 && gP4.Phi() <  1.01  ) badXtal = true ;
           if ( gP4.Eta() > -1.31 && gP4.Eta() < -1.30 && gP4.Phi() > -3.00 && gP4.Phi() < -2.99 ) badXtal = true ;
           if ( gP4.Eta() > -1.41 && gP4.Eta() < -1.40 && gP4.Phi() > -0.96 && gP4.Phi() < -0.95 ) badXtal = true ; 
           if ( gP4.Eta() > -1.45 && gP4.Eta() < -1.44 && gP4.Phi() >  3.11 && gP4.Phi() <  3.12 ) badXtal = true ;
           if ( badXtal ) continue ;
           h_eta_phi1->Fill( gP4.Eta(), gP4.Phi() ) ;

           h_seedTime->Fill( xtal_t[k] ) ;
           if ( xtalE[k] < cuts[0] ) continue ;
           h_seedE_Time->Fill( xtalE[k], xtal_t[k] ) ;

           h_cscdPhi->Fill( cscdPhi[k] ) ;
           if ( cscdPhi[k] < cuts[1] ) continue ;
            
           h_swissX->Fill( xtalSwissX[k] ) ;
           if ( xtalSwissX[k] < cuts[2] || xtalSwissX[k] > cuts[3] ) continue ;

           h_dt_dPhi_dEta->Fill( dtdPhi[k], dtdEta[k] ) ;
           if ( dtdEta[k] > cuts[4] || dtdPhi[k] > cuts[5] ) continue ;

           h_sMaj_sMin->Fill( bc_sMaj[k], bc_sMin[k] ) ;
           h_eta_Time->Fill( gP4.Eta(), xtal_t[k] ) ;
           h_phi_Time->Fill( gP4.Phi(), xtal_t[k] ) ;

           h_nBC->Fill( bc_nBC[k] ) ;
           h_nXtal->Fill( bc_nXtals[k] ) ;
           h_seedTime1->Fill( xtal_t[k] ) ;
           passFinal = true ;

       }
       if ( passFinal ) h_met->Fill( met ) ;
     
   }

   // Write histograms
   //theFile->cd() ;
   Write() ;

   // Draw histograms
   DrawHistograms() ;
}

void CosmicsStudy::DrawHistograms() {

   //bool createDrawer = false ;
   //if ( h_draw == NULL ) {
   hfolder += "Cosmics/" ;
   cout <<" create drawing class " << endl ;
   cout <<" hfolder = "<< hfolder << endl ;
   gSystem->mkdir( hfolder.c_str() );
   hDraw* h_draw = new hDraw( hfolder, plotType ) ;

   //h_draw->SetPath( hfolder ) ;

   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);

   gStyle->SetOptStat("");
   //gStyle->SetOptStat(kFALSE);
   gPad->SetGridx() ;
   h_draw->Draw2D( h_eta_phi,     "h_eta_phi",    "#eta", "#phi",  "logZ", 8 ) ;
   h_draw->Draw2D( h_eta_phi1,    "h_eta_phi1",    "#eta", "#phi",  "logZ", 8 ) ;
   h_draw->Draw2D( h_eta_Time,    "h_eta_Time",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_phi_Time,    "h_phi_Time",    "#phi", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_seedE_Time,  "h_seedE_Time", " Seed Xtal E", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_sMaj_sMin,   "h_sMaj_sMin",    "sMaj", "sMin",  "logZ", 8 ) ;
   h_draw->Draw2D( h_dt_dPhi_dEta, "h_dt_dPhi_dEta",    "#delta#phi", "#delta#eta",  "logZ", 8 ) ;

   h_draw->Draw(   h_seedTime,    "h_seedTime", " SeedTime ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_seedTime1,   "h_seedTime1", " SeedTime ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_met,         "h_met",      " MET ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_nBC,         "h_nBC",      "N of basic clusters ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_nXtal,       "h_nXtal",    "N of crystals ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_swissX,      "h_swissX",    " Swiss-X value ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   h_cscdPhi,     "h_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;

   // ========================
   //if ( createDrawer ) delete h_draw ;
   delete h_draw ;
}

