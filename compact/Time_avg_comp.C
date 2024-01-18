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
#include <TPad.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <TSystem.h>

void Time_avg_comp(int angle_1, int angle_2)
{
   int nchan = 10;
  TH1F *hcEcalntot_1[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *h_conv_1[nchan]; //Scintillation Generated and also for all the SiPMs

  TH1F *hcEcalntot_2[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *h_conv_2[nchan]; //Scintillation Generated and also for all the SiPMs

  //TH1F *h_spr = new TH1F("h_spr","h_spr",1000,0.,100); //Is this in MeV?, all events with cut applied

  for (int i=0;i<nchan;i++) //Although the range of the x axis on the histograms will be much smaller for the SiPM channels
  {   
   if(i>=2 && i<=9)
   {
    hcEcalntot_1[i] = new TH1F(Form("hcEcalntot_1_%d",i),"total number of S+C chan 1",1000,0.,100);
    h_conv_1[i] = new TH1F(Form("h_conv_1_%d",i),"Convolved signal",1000,0.,100);

    hcEcalntot_2[i] = new TH1F(Form("hcEcalntot_2_%d",i),"total number of S+C chan 1",1000,0.,100);
    h_conv_2[i] = new TH1F(Form("h_conv_2_%d",i),"Convolved signal",1000,0.,100);

    } //Initial binsize = 1 for all SiPMs

   else
   {
    hcEcalntot_1[i] = new TH1F(Form("hcEcalntot_1_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
    h_conv_1[i] = new TH1F(Form("h_conv_1_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
    
    hcEcalntot_2[i] = new TH1F(Form("hcEcalntot_2_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
    h_conv_2[i] = new TH1F(Form("h_conv_2_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
    }
   }
  std::vector<float> *Ch_new[8];
  std::vector<float> *Ch_conv[8];
  for(int i=0;i<8;i++)
  {
   Ch_new[i]=new vector<float>;
   Ch_conv[i]=new vector<float>;
  }

   TFile *f_1 = new TFile(Form("Time_avg_%i_0116_time.root",angle_1));
   TTree *Timing_avg_1 = (TTree *)f_1->Get("Timing_avg_cut");

   for(int i=0;i<8;i++)
   {
    Timing_avg_1->SetBranchAddress(Form("Ch_new_%i",i),&Ch_new[i]);
    Timing_avg_1->SetBranchAddress(Form("Ch_conv_%i",i),&Ch_conv[i]);
   }

   Timing_avg_1->GetEntry(0);//Only one entry for each branch
   for(int i=0;i<8;i++)
   {
    for(int j=0;j<Ch_new[i]->size();j++)
    {
    hcEcalntot_1[i+2]->SetBinContent(j+1,Ch_new[i]->at(j));
    h_conv_1[i+2]->SetBinContent(j+1,Ch_conv[i]->at(j));
    }
   }


   TFile *f_2 = new TFile(Form("Time_avg_%i_0116_time.root",angle_2));
   TTree *Timing_avg_2 = (TTree *)f_2->Get("Timing_avg_cut");

   for(int i=0;i<8;i++)
   {
    Timing_avg_2->SetBranchAddress(Form("Ch_new_%i",i),&Ch_new[i]);
    Timing_avg_2->SetBranchAddress(Form("Ch_conv_%i",i),&Ch_conv[i]);
   }

   Timing_avg_2->GetEntry(0);//Only one entry for each branch
   //True peak size
   ///*
   for(int i=0;i<8;i++)
   {
    for(int j=0;j<Ch_new[i]->size();j++)
    {
    hcEcalntot_2[i+2]->SetBinContent(j+1,Ch_new[i]->at(j));
    h_conv_2[i+2]->SetBinContent(j+1,Ch_conv[i]->at(j));
    }
   }
   //*/

   //Normalized size
   /*
   for(int i=0;i<8;i++)
   {
    for(int j=0;j<Ch_new[i]->size();j++)
    {
    hcEcalntot_2[i+2]->SetBinContent(j+1,Ch_new[i]->at(j)*hcEcalntot_1[i+2]->GetBinContent(hcEcalntot_1[i+2]->GetMaximumBin())/hcEcalntot_2[i+2]->GetBinContent(hcEcalntot_2[i+2]->GetMaximumBin()));
    h_conv_2[i+2]->SetBinContent(j+1,Ch_conv[i]->at(j)*h_conv_1[i+2]->GetBinContent(h_conv_1[i+2]->GetMinimumBin())/h_conv_2[i+2]->GetBinContent(h_conv_2[i+2]->GetMinimumBin()));
    }
   }
   */

 TCanvas *c1=new TCanvas("c_1","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
 int i_plot = 4;

 double max_val_1 = h_conv_1[i_plot]->GetBinContent(h_conv_1[i_plot]->GetMinimumBin());
 double max_val_2 = h_conv_2[i_plot]->GetBinContent(h_conv_2[i_plot]->GetMinimumBin());
std::cout <<"Mod of Maximum values " << max_val_1 << " " << max_val_2 << std::endl;
  ///*
  for(int j=0;j<Ch_new[i_plot]->size();j++)
  {
   h_conv_2[i_plot]->SetBinContent(j+1,Ch_conv[i_plot-2]->at(j)*max_val_1/max_val_2);
  }
  //*/
  /*
  hcEcalntot_1[i_plot]->Draw("");
  hcEcalntot_1[i_plot]->SetLineColor(kGreen);
  hcEcalntot_1[i_plot]->SetStats(0);

  hcEcalntot_2[i_plot]->Draw("same");
  hcEcalntot_2[i_plot]->SetLineColor(kRed);
  hcEcalntot_2[i_plot]->SetStats(0);
  */
  ///*
  h_conv_1[i_plot]->Draw("");
  h_conv_1[i_plot]->SetLineColor(kGreen);
  h_conv_1[i_plot]->SetStats(0);

  h_conv_2[i_plot]->Draw("same");
  h_conv_2[i_plot]->SetLineColor(kRed);
  h_conv_2[i_plot]->SetStats(0);
  //*/
}
