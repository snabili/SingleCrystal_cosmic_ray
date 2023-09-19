#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TBrowser.h"
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include "TH2.h"
#include <TPaveText.h>
#include "TRandom.h"
#include <TLegend.h>
#include "DD4hep/Printout.h"
#include "DD4hep/Objects.h"
#include "DD4hep/Factories.h"
#include "DDG4/Geant4Particle.h"
#include "DDG4/Geant4Data.h"
#include "../src/DualCrystalCalorimeterHit.h"

#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

void print_vector_dt(vector<float> const &ptrdt) //function to print a vector of double (floating point numbers)
{
 for(unsigned int i=0; i<ptrdt.size(); i++)
 {
  std::cout << ptrdt.at(i) << ' ';
 }
 std::cout << std::endl;
}

void Plot_med()
{
 Float_t Channel_Numbers, Median_values;
 std::vector<int> angle_values{-85,-80,-75,-70,-65,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85};
 std::vector<int> angle_values_mod{-85,-75,-65,-60,-55,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,65,75,80,85}; //Populate this in the first loop
 float adc_avg, time_avg;
 std::vector<std::vector<float>> adc_angle;

 for(int entry_index=0;entry_index<angle_values_mod.size();entry_index++) //Histogram initialization loop - might have to put angle wise graphs for wavelength distribution here too
 {  
  TFile *f = new TFile(Form("Med_files/0829/Output_Root_Files/Med_%i_0829.root",angle_values_mod.at(entry_index)));
  TTree *hgcroc = (TTree *)f->Get("Med_channel");
  
  hgcroc->SetBranchAddress("Channel_Numbers", &Channel_Numbers);
  hgcroc->SetBranchAddress("Median_values", &Median_values);
  int total_entries = hgcroc->GetEntries(); //total events
  std::vector<float> adc_chan;

  for(int i=0;i<total_entries;i++)
  {
  hgcroc->GetEntry(i); //channel number 2
  adc_chan.push_back(Median_values);
  }
  adc_angle.push_back(adc_chan);

  print_vector_dt(adc_chan);
 }

  TFile* file = new TFile("test.root","NEW");
  TTree hgcroc_new("hgcroc","hgcroc");
  auto adc = hgcroc_new.Branch("Values", &(adc_avg),angle_values_mod.size());
  auto time = hgcroc_new.Branch("time", &(time_avg),angle_values_mod.size());
  //Color_t leg_col[4] = {kRed,kBlue,kGreen,kOrange};

  for(int entry_index=0;entry_index<angle_values_mod.size();entry_index++) //Histogram initialization loop - might have to put angle wise graphs for wavelength distribution here too
  {  
   adc_avg = adc_angle.at(entry_index).at(3);
   time_avg = angle_values_mod.at(entry_index);
   std::cout << adc_avg << " " << time_avg << std::endl;
   hgcroc_new.Fill();
   (hgcroc_new).SetMarkerColor(kRed);
   (hgcroc_new).SetMarkerStyle(20);
   (hgcroc_new).SetMarkerSize(0.5);
  }
  hgcroc_new.Draw("Values:time");
 }
