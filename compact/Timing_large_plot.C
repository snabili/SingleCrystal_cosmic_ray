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

void print_vector_dt(vector<float> const &ptrdt) //function to print a vector of double (floating point numbers)
{
 for(unsigned int i=0; i<ptrdt.size(); i++)
 {
  std::cout << ptrdt.at(i) << ' ';
 }
 std::cout << std::endl;
}

void print_vector_it(vector<Int_t> const &ptrit) //function to print a vector of double (floating point numbers)
{
 for(unsigned int i=0; i<ptrit.size(); i++)
 {
  cout << ptrit.at(i) << ' ';
 }
 cout << endl;
}

struct evt_num
{
 int evt;
 float gen_tot; //In this case it is obtained by adding up over all the time bins
 std::vector<float> gen; //Only gen and the 8 channels with SiPM cut 
 std::vector<float> Ch[8];//The 8 channels with SiPM cut 
};

/*
void init_struct(evt_num &evt_ind, int event_nos, std::vector<float> Gen_crys, std::vector<float> Ch[8])
{
  evt_ind.evt = event_nos;
  evt_ind.gen.clear(); //at the beginning of each initialization
  for(int j=0;j<Gen_crys.size();j++)
  {
  evt_ind.gen.push_back(Gen_crys.at(j));
  }
  std::cout << "Gen Size of vector for each event " << evt_ind.gen.size() << std::endl;

  for(int i=0;i<8;i++)
  {
   evt_ind.Ch[i].clear(); //at the beginning of each initialization
  for(int j=0;j<Ch[i]->size();j++)
  {
   evt_ind.Ch[i].push_back(Ch[i]->at(j));
  }
  std::cout << "Size of each vector for each event " << i << " " << evt_ind.Ch[i].size() << std::endl;
}
}
*/


void Timing_large_plot(int angle, float cut)
{
 std:: ofstream C_SiPM;
C_SiPM.open("Channel_1207_100.csv");

  std::vector<evt_num> evt_80;
  evt_num cur_evt;
  TH1F *hcEcalE0;
  TH1F *hcEcalE_sil_l;
  TH1F *hcEcalE_sil_r;
  TH1F *hcEcalE_flt;
  int nchan = 10;
  TH1F *hcEcalncer[nchan]; //Cerenkov Generated and also for all the SiPMs
  TH1F *hcEcalnscint[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *hcEcalntot[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *hcEcalncer_crys[nchan]; //Cerenkov from crystal (in SiPM)
  TH1F *hcEcalncer_sil[nchan]; //Cerenkov from cookie (in SiPM)
  TH1F *hcEcalncer_flt[nchan]; //Cerenkov from filter (in SiPM)
  
  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",10000,0.,100000); //Is this in MeV?
  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",100,0.,200); //Extra Zoomed in, is this in MeV?
  hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",2500,0.,2500); //Is this in MeV?, all events with cut applied
  hcEcalE_sil_l = new TH1F("hcEcalE_sil_l","energy chan 10",2500,0.,2500); //Is this in MeV?, all events with cut applied
  hcEcalE_sil_r = new TH1F("hcEcalE_sil_r","energy chan 11",2500,0.,2500); //Is this in MeV?, all events with cut applied
  hcEcalE_flt = new TH1F("hcEcalE_flt","energy chan 12",2500,0.,2500); //Is this in MeV?, all events with cut applied
  
  for (int i=0;i<nchan;i++) //Although the range of the x axis on the histograms will be much smaller for the SiPM channels
  {   
   //hcEcalncer[i] = new TH1F(Form("hcEcalncer_%d",i),"total number of cerenkov chan 1",100,0.,200000);
   //hcEcalnscint[i] = new TH1F(Form("hcEcalnscint_%d",i),"total number of scintillation chan 1",100,0.,2000000);
   hcEcalncer[i] = new TH1F(Form("hcEcalncer_%d",i),"total number of cerenkov chan 1",7000000,0.,7000000);
   hcEcalnscint[i] = new TH1F(Form("hcEcalnscint_%d",i),"total number of scintillation chan 1",7000000,0.,7000000);
   //hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
   //hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",50000,0.,7000000);

   /*if(i>=2 && i<=5){hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",25000,0.,50000);}
   else if(i>=6 && i<=9){hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",500,0.,50000);}*/

   if(i>=2 && i<=9){hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",1000,0.,100);} //Initial binsize = 1 for all SiPMs

   else{hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",7000000,0.,7000000);}
   hcEcalncer_crys[i] = new TH1F(Form("hcEcalncer_crys_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
   hcEcalncer_sil[i] = new TH1F(Form("hcEcalncer_sil_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
   hcEcalncer_flt[i] = new TH1F(Form("hcEcalncer_flt_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
  }


 std::vector<float> gen_avg;
 std::vector<float> Ch_avg[8];

 

 TFile *f = new TFile(Form("Event_files/1207/Output_Root_Files/Event_%i_1207_time_test_new.root",angle));
 TTree *Timing_channel = (TTree *)f->Get("Timing_channel");

  int event_nos;
  float gen_tot;
  std::vector<float> *Gen_crys = new vector<float>;
  std::vector<float> *Ch[8];
  for(int i=0;i<8;i++)
  {
   Ch[i]=new vector<float>;
  }

  Timing_channel->SetBranchAddress("Event_Numbers", &event_nos);
  Timing_channel->SetBranchAddress("Gen_crys", &Gen_crys);

  for(int i=0;i<8;i++)
  {
   Timing_channel->SetBranchAddress(Form("Ch_%i",i),&Ch[i]);
  }

  for(int i=0;i<Timing_channel->GetEntries();i++) //Number of entries is equal to number of events here
  //for(int i=0;i<400;i++)
  {
    gen_tot=0;
    Timing_channel->GetEntry(i);
    std::cout << "Entry index " << i << " Size of timing bin vector " << Gen_crys->size() << std::endl;
    int size = Gen_crys->size();
    std::cout << "Values of timing signal " << " ";

    for(int j=0;j<std::min(size,1000);j++)
    {
    std::cout << Gen_crys->at(j) << " ";
    }

    std::cout << std::endl;

    //Contents of init function
    
    cur_evt.evt = event_nos;
    
    cur_evt.gen.clear(); //at the beginning of each initialization
    for(int j=0;j<Gen_crys->size();j++)
    {
     if(i==0){gen_avg.push_back(0.0);}
    cur_evt.gen.push_back(Gen_crys->at(j));
    gen_tot+=Gen_crys->at(j);
    }
    std::cout << "Gen Size of vector for each event " << i << " " << cur_evt.gen.size() << std::endl;
    ///*
    for(int k=0;k<8;k++)
    {
     cur_evt.Ch[k].clear(); //at the beginning of each initialization
     for(int j=0;j<Ch[k]->size();j++)
     {
       if(i==0){Ch_avg[k].push_back(0.0);}
     cur_evt.Ch[k].push_back(Ch[k]->at(j));
     }
     std::cout << "Size of each vector for each event number " << i << " " << k << " " << cur_evt.Ch[k].size() << std::endl;
    }

    cur_evt.gen_tot = gen_tot;
    //init_struct(cur_evt,event_nos,Gen_crys,Ch);
    hcEcalntot[0]->Fill(cur_evt.gen_tot);
    evt_80.push_back(cur_evt);
    
   //std::cout << event_nos << " Number of gen photons " << Gen_crys << std::endl;
  }

  
  float ncerchan_histcut[nchan], ncerchan_hist_medcut[nchan], nscintchan_histcut[nchan], nscintchan_hist_medcut[nchan], ntotchan_histcut[nchan], ntotchan_hist_medcut[nchan];
  TCanvas *c1=new TCanvas("c_1","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
  hcEcalntot[0]->Draw("");
  //Double_t xcer0, qcer0=0.80 ; // for showering part i.e. last 20%
  Double_t xcer0, qcer0=1.0-cut ; // for showering part i.e. last 20%
  Double_t xcer1, qcer1=1.00 ; // for max counts

  hcEcalntot[0]->GetQuantiles(1,&xcer0,&qcer0);
  hcEcalntot[0]->GetQuantiles(1,&xcer1,&qcer1);

  Color_t leg[4] = {kBlue,kRed,kOrange,kGreen};
  float xmin[4],xmax[4];
  

  TH1F* h_tot_0 = (TH1F*) gROOT->FindObject(Form("hcEcalntot_%d",0));
  float x1 = (h_tot_0->FindLastBinAbove(0,1));
  std::cout << "New lower limit " << xcer0 << " Max counts " << x1 <<std::endl;
  int icut =0;
  int bin_optimum = 140; //For all channels between min and max
  int start_ch = 2;
  for(int i=0;i<Timing_channel->GetEntries();i++)
  {
   if(evt_80.at(i).gen_tot>=xcer0)
   {
    icut++;
    //hcEcalntot[j]->Fill(evt_80.at(i).Ch[j-2]);
    for(int j=0;j<gen_avg.size();j++)
    {
     gen_avg.at(j)+=evt_80.at(i).gen.at(j);
    }

    for(int k=0;k<8;k++)
    {
    for(int j=0;j<Ch_avg[k].size();j++)
    {
     Ch_avg[k].at(j)+=evt_80.at(i).Ch[k].at(j);
    }
    }
   }
  }

   std::cout << "Number of events passing the cut " << icut << std::endl;
    for(int j=0;j<gen_avg.size();j++)
    {
     gen_avg.at(j) = gen_avg.at(j)/icut;
    }

    for(int k=0;k<8;k++)
    {
    for(int j=0;j<Ch_avg[k].size();j++)
    {
     Ch_avg[k].at(j) = Ch_avg[k].at(j)/icut;
    }
    }

    //Filling the histogram with the average time signal (for events passing the cut)
    for(int k=0;k<8;k++)
    {
    for(int j=0;j<Ch_avg[k].size();j++)
    {
     hcEcalntot[k+2]->SetBinContent(j+1,Ch_avg[k].at(j));
    }
    }

  
  hcEcalntot[3]->Draw("");
  hcEcalntot[3]->SetStats(0);
  
 /* TH1F* h_tot = (TH1F*) gROOT->FindObject(Form("hcEcalntot_%d",j));
  xmin[j-start_ch] = (h_tot->FindFirstBinAbove(0,1));
  xmax[j-start_ch] = (h_tot->FindLastBinAbove(0,1));

  std::cout << "Min counts " << xmin[j-start_ch] << " Max counts " << xmax[j-start_ch] << std::endl;
  std::cout << "Number of bins to be combined into one " << (xmax[j-start_ch]-xmin[j-start_ch])/bin_optimum <<std::endl;
  hcEcalntot[j]->Rebin((xmax[j-start_ch]-xmin[j-start_ch])/bin_optimum);  */


  //Drawing part for 4 channels of each side together
  /*
  float *x_min = std::min_element(std::begin(xmin), std::end(xmin));
  float *x_max = std::max_element(std::begin(xmax), std::end(xmax));

  std::cout << "Net min counts " << *x_min << " Net max counts " << *x_max << std::endl;
  for(int j=start_ch;j<start_ch+4;j++)
  {
  hcEcalntot[j]->GetXaxis()->SetRangeUser(*x_min-20,*x_max+20);
  hcEcalntot[j]->SetLineColor(leg[j-start_ch]);
  
  if(j==start_ch){hcEcalntot[j]->Draw("");}
  else{hcEcalntot[j]->Draw("same");}
  
  }
  */

  //hcEcalntot[0]->Draw("");   
   
}
