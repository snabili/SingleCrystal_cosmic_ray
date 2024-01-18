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
 std::vector<float> Ch_other[8];//The non photon time signal for all the SiPM channels
};

double time_ns[191] = {0, 1.6973, 1.9095, 2.3338, 2.5459, 2.7581, 2.9703, 2.9703, 2.9703, 2.9703, 3.1824, 3.3946, 3.3946, 3.3946, 3.3946, 3.6068, 3.6068, 3.8189, 3.8189, 3.8189, 4.0311, 4.2433, 4.6676, 4.6676, 4.8797, 5.0919, 5.5162, 5.7284, 6.1527, 6.7892, 7.2136, 7.6379, 7.85, 8.0622, 8.2744, 8.4865, 8.6987, 8.9109, 9.123, 9.3352, 9.7595, 10.1838, 10.396, 10.6082, 10.8203, 11.2447, 11.669, 12.0933, 12.3055, 12.942, 13.3663, 13.5785, 13.7906, 14.215, 14.4271, 14.6393, 14.8515, 15.0636, 15.2758, 15.7001, 16.1244, 16.5488, 16.7609, 16.9731, 17.1853, 17.3974, 17.6096, 17.8218, 18.4582, 18.2461, 18.4582, 18.8826, 19.3069, 19.9434, 20.3677, 21.0042, 21.6407, 22.2772, 22.7015, 22.9137, 23.5502, 23.7624, 24.1867, 24.611, 25.0353, 25.4597, 25.6718, 26.0962, 26.5205, 27.157, 27.5813, 28.43, 28.6421, 29.0665, 29.4908, 29.9151, 30.5516, 30.9759, 31.1881, 32.0367, 32.2489, 32.6732, 33.3097, 33.5219, 33.9462, 34.3706, 35.007, 35.6435, 36.0679, 37.1287, 37.9773, 39.0382, 39.8868, 40.7355, 41.5841, 42.2206, 42.8571, 44.1301, 44.9788, 45.1909, 45.4031, 46.0396, 46.4639, 46.8882, 47.3126, 48.1612, 49.0099, 50.0707, 51.5558, 52.1923, 53.041, 53.2532, 53.4653, 54.7383, 54.9505, 55.1626, 55.7991, 56.6478, 57.2843, 57.4964, 58.1329, 58.3451, 58.7694, 58.9816, 60.0424, 60.6789, 61.5276, 62.8005, 63.8614, 64.0735, 64.71, 65.5587, 66.1952, 67.4681, 68.1046, 68.3168, 68.9533, 69.1655, 69.802, 70.0141, 70.4384, 71.2871, 71.9236, 72.5601, 73.6209, 74.4696, 74.6817, 75.1061, 76.379, 76.8034, 77.4399, 78.925, 79.3493, 80.6223, 81.0467, 82.3196, 83.1683, 83.8048, 84.8656, 85.0778, 85.7143, 86.5629, 87.4116, 87.6237, 88.4724, 89.7454, 91.2305, 92.9278, 95.4738, 96.959, 98.2319};
double signal_mV[191] = {0.101075, 0.095341, 0.072401, 0.049462, -0.02509, -0.07384, -0.12545, -0.17133, -0.24014, -0.29749, -0.31756, -0.39211, -0.4552, -0.52975, -0.6043, -0.62724, -0.69319, -0.719, -0.77061, -0.81935, -0.89391, -0.96559, -1.03441, -1.05735, -1.07455, -1.08889, -1.10036, -1.08889, -1.06882, -1.04875, -1.00287, -0.97706, -0.92832, -0.88244, -0.85376, -0.83369, -0.81362, -0.78781, -0.76487, -0.74194, -0.69319, -0.62151, -0.59857, -0.57563, -0.55556, -0.53548, -0.51541, -0.48961, -0.46953, -0.44659, -0.42652, -0.40072, -0.35484, -0.3147, -0.28602, -0.26595, -0.23154, -0.21147, -0.23728, -0.26308, -0.28889, -0.25735, -0.1828, -0.22867, -0.04803, -0.02509, 0.049462, 0.083871, 0.072401, 0.043728, -0.01362, -0.0681, -0.11398, -0.13118, -0.10824, -0.09677, -0.07384, -0.0509, -0.02796, -0.00215, -0.01362, -0.03369, -0.0509, -0.0681, -0.07957, -0.06237, -0.03082, -0.00215, 0.020789, 0.037993, 0.020789, 0.009319, 0.029391, 0.055197, 0.072401, 0.092473, 0.112545, 0.138351, 0.146953, 0.129749, 0.112545, 0.095341, 0.060932, 0.078136, 0.101075, 0.115412, 0.101075, 0.081004, 0.066667, 0.092473, 0.112545, 0.098208, 0.081004, 0.092473, 0.115412, 0.098208, 0.115412, 0.10681, 0.121147, 0.144086, 0.158423, 0.175627, 0.146953, 0.132616, 0.109677, 0.132616, 0.152688, 0.132616, 0.089606, 0.066667, 0.081004, 0.095341, 0.115412, 0.135484, 0.10681, 0.083871, 0.058065, 0.072401, 0.095341, 0.11828, 0.146953, 0.158423, 0.138351, 0.115412, 0.092473, 0.109677, 0.124014, 0.141219, 0.121147, 0.081004, 0.058065, 0.072401, 0.092473, 0.112545, 0.098208, 0.072401, 0.055197, 0.035125, 0.060932, 0.10681, 0.124014, 0.144086, 0.112545, 0.092473, 0.109677, 0.126882, 0.135484, 0.146953, 0.132616, 0.115412, 0.098208, 0.109677, 0.11828, 0.098208, 0.075269, 0.072401, 0.086738, 0.10681, 0.126882, 0.115412, 0.101075, 0.101075, 0.121147, 0.146953, 0.146953, 0.11828, 0.095341, 0.081004, 0.086738, 0.095341, 0.109677};

void Timing_conv_2(int angle, float cut)
{
 std:: ofstream C_SiPM;
C_SiPM.open("Channel_0116_100.csv");

  std::vector<evt_num> evt_80_1;
  evt_num cur_evt;
  int nchan = 10;
  /*
  TH1F *hcEcalntot[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *h_conv[nchan]; //Scintillation Generated and also for all the SiPMs
    
  TH1F *h_spr = new TH1F("h_spr","h_spr",1000,0.,100); //Is this in MeV?, all events with cut applied

  for (int i=0;i<nchan;i++) //Although the range of the x axis on the histograms will be much smaller for the SiPM channels
  {   
   if(i>=2 && i<=9)
   {
    hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",1000,0.,100);
    h_conv[i] = new TH1F(Form("h_conv_%d",i),"Convolved signal",1000,0.,100);
    } //Initial binsize = 1 for all SiPMs

   else{hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
   h_conv[i] = new TH1F(Form("h_conv_%d",i),"total number of S+C chan 1",7000000,0.,7000000);}
  }
*/

 std::vector<float> gen_avg;
 std::vector<float> Ch_avg[8];

 

 TFile *f = new TFile(Form("Event_files/0116/Output_Root_Files/Event_%i_0116_time.root",angle));
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
     cur_evt.Ch_other[k].clear(); //at the beginning of each initialization
     for(int j=0;j<Ch[k]->size();j++)
     {
       if(i==0)
       {
        Ch_avg[k].push_back(0.0);
       }
     cur_evt.Ch[k].push_back(Ch[k]->at(j));
     }
     std::cout << "Size of each vector for each event number " << i << " " << k << " " << cur_evt.Ch[k].size() << std::endl;
    }

    cur_evt.gen_tot = gen_tot;
    //init_struct(cur_evt,event_nos,Gen_crys,Ch);
    hcEcalntot[0]->Fill(cur_evt.gen_tot);
    evt_80_1.push_back(cur_evt);
    
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
   if(evt_80_1.at(i).gen_tot>=xcer0)
   {
    icut++;
    //hcEcalntot[j]->Fill(evt_80_1.at(i).Ch[j-2]);
    for(int j=0;j<gen_avg.size();j++)
    {
     gen_avg.at(j)+=evt_80_1.at(i).gen.at(j);
    }

    for(int k=0;k<8;k++)
    {
    for(int j=0;j<Ch_avg[k].size();j++)
    {
     Ch_avg[k].at(j)+=evt_80_1.at(i).Ch[k].at(j);
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
  
  std::vector<float> number_of_bins, single_photon_response;
  for(int j=0;j<1000;j++)
  {
   number_of_bins.push_back(j*0.1);
  }

  //Single photon response to be convolved with the optical signal
    for(int j=0;j<1000-2;j++) //Right now all sizes are the same = binsize, taken the channel 0
    {

     int ent_spr = 190; 
     if (number_of_bins.at(j) >= time_ns[0] && number_of_bins.at(j) < time_ns[ent_spr]) //within range specified for function (which is basically the entire range over which the bins are specified)
     {
      for(int i=0;i<ent_spr;i++)
      {
       if (number_of_bins.at(j) >= time_ns[i] && number_of_bins.at(j) < time_ns[i + 1]) //Checking what 'bin' the wavelength lies in
       {
       single_photon_response.push_back((signal_mV[i + 1] - signal_mV[i]) * (number_of_bins.at(j) - time_ns[i]) / (time_ns[i + 1] - time_ns[i]) + signal_mV[i]);
       }
      }
     }      
     else{single_photon_response.push_back(0.0);}
    }

    std::cout << single_photon_response.size() << std::endl;

  float conv_j;
  std::vector<float> convolved_signal[8];
  for(int i=0;i<8;i++)
  {
  for(int j=0;j<single_photon_response.size();j++)
  {
   conv_j = 0;
   for(int k=0;k<=j;k++)
   {
    conv_j+=Ch_avg[i].at(k)*single_photon_response.at(j-k);
   }
   convolved_signal[i].push_back(conv_j);
  }
  }

   TFile *file_avg = TFile::Open(Form("Time_avg_%i_0116_time.root",angle),"recreate");
   TTree *Timing_avg_cut = new TTree("Timing_avg_cut","Eventwise values in crystal and SiPM channels with SiPM QE"); 

   //Add 16 branches - 8 for original optical signal and 8 for convolved
  std::vector<float> *Ch_new[8];
  std::vector<float> *Ch_conv[8];
  for(int i=0;i<8;i++)
  {
   Ch_new[i]=new vector<float>;
   Ch_conv[i]=new vector<float>;
  }

  for(int i=0;i<8;i++)
  {
   Timing_avg_cut->Branch(Form("Ch_new_%i",i),&Ch_new[i]);
   Timing_avg_cut->Branch(Form("Ch_conv_%i",i),&Ch_conv[i]);
  }

  for(int j=0;j<single_photon_response.size();j++)//Only filling these once, so no need to clear
  {
   for(int i=0;i<8;i++)
   {
   Ch_new[i]->push_back(Ch_avg[i].at(j));
   Ch_conv[i]->push_back(convolved_signal[i].at(j));
   }
  }

  Timing_avg_cut->Fill();
  file_avg->cd();
  Timing_avg_cut->Print();
  Timing_avg_cut->Write();

}
