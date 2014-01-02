#include <iostream> 
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <TString.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TMinuit.h>

#include "AnaInput.h"
#include "CosmicsStudy.h"

using namespace std; 

int main( int argc, const char* argv[] ) { 

  string datacardfile = ( argc > 1 ) ? argv[1] : "DataCard.txt";
  AnaInput  *Input = new AnaInput( datacardfile );

  // method to read root files
  string dataFileNames ;
  Input->GetParameters( "TheData", &dataFileNames );

  int module = -1 ;
  Input->GetParameters( "Module", & module ) ;

  CosmicsStudy * cos = new CosmicsStudy( datacardfile ) ;
  if ( module == 1 ) {
     cos->SimpleRun() ;
  }
  if ( module == 2 ) {
     cos->Open() ;
     cos->DrawHistograms() ;
  }

  cout<<" Finished !!!"<<endl ;

  return 0;

}


