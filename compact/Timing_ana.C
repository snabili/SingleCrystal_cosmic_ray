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

const int nchan = 10;
//const int ichan[nchan] = {289,256,292,293,294,295,296,297,298,299};
//std::string namechan[nchan] = {"crystal","Air","left SiPM 1","left SiPM 2","left SiPM 3","left SiPM 4","right SiPM 1","right SiPM 2","right SiPM 3","right SiPM 4"};
const int ichan[nchan] = {289,256,294,292,295,293,296,298,297,299};
std::string namechan[nchan] = {"crystal","Air","Ch 0","Ch 1","Ch 2","Ch 3","Ch 4","Ch 5","Ch 6","Ch 7"};

std::ofstream C_gen, S_gen;
std:: ofstream C_S_SiPM;

double UV_sipm_QE_x[89] = {282.6086957, 288.0434783, 290.2173913, 291.3043478, 292.3913043, 293.4782609, 294.5652174, 295.6521739, 296.7391304, 297.826087, 298.9130435, 301.0869565, 303.2608696, 304.3478261, 307.6086957, 309.7826087, 314.1304348, 317.3913043, 321.7391304, 329.3478261, 335.8695652, 343.4782609, 350., 358.6956522, 367.3913043, 373.9130435, 378.2608696, 383.6956522, 388.0434783, 394.5652174, 402.173913, 408.6956522, 417.3913043, 428.2608696, 440.2173913, 452.173913, 465.2173913, 475., 482.6086957, 489.1304348, 494.5652174, 500., 505.4347826, 510.8695652, 517.3913043, 522.826087, 529.3478261, 534.7826087, 542.3913043, 548.9130435, 555.4347826, 561.9565217, 568.4782609, 577.173913, 583.6956522, 590.2173913, 596.7391304, 603.2608696, 610.8695652, 617.3913043, 623.9130435, 631.5217391, 638.0434783, 644.5652174, 652.173913, 659.7826087, 667.3913043, 676.0869565, 685.8695652, 694.5652174, 703.2608696, 713.0434783, 721.7391304, 731.5217391, 741.3043478, 753.2608696, 764.1304348, 775., 785.8695652, 797.826087, 808.6956522, 819.5652174, 831.5217391, 844.5652174, 855.4347826, 866.3043478, 877.173913, 889.1304348, 898.9130435};

double UV_sipm_QE_y[89] = {0.02983683, 0.041958042, 0.068997669, 0.106293706, 0.131468531, 0.158508159, 0.185547786, 0.211655012, 0.225641026, 0.240559441, 0.255477855, 0.271328671, 0.287179487, 0.299300699, 0.30955711, 0.321678322, 0.331934732, 0.342191142, 0.353379953, 0.363636364, 0.374825175, 0.385081585, 0.393473193, 0.399067599, 0.407459207, 0.418648019, 0.431701632, 0.443822844, 0.455011655, 0.466200466, 0.476456876, 0.485780886, 0.494172494, 0.502564103, 0.508158508, 0.509090909, 0.506293706, 0.498834499, 0.48951049, 0.479254079, 0.468997669, 0.458741259, 0.446620047, 0.437296037, 0.427039627, 0.416783217, 0.405594406, 0.395337995, 0.384149184, 0.373892774, 0.363636364, 0.352447552, 0.342191142, 0.331002331, 0.320745921, 0.31048951, 0.301165501, 0.290909091, 0.280652681, 0.271328671, 0.261072261, 0.251748252, 0.242424242, 0.233100233, 0.222843823, 0.214452214, 0.204195804, 0.193939394, 0.185547786, 0.176223776, 0.167832168, 0.158508159, 0.151048951, 0.142657343, 0.134265734, 0.125874126, 0.118414918, 0.11002331, 0.102564103, 0.095104895, 0.087645688, 0.082051282, 0.074592075, 0.068065268, 0.061538462, 0.055944056, 0.049417249, 0.044755245, 0.038694639};

double RGB_sipm_QE_x[89] = {282.6086957, 288.0434783, 290.2173913, 291.3043478, 292.3913043, 293.4782609, 294.5652174, 295.6521739, 296.7391304, 297.826087, 298.9130435, 301.0869565, 303.2608696, 304.3478261, 307.6086957, 309.7826087, 314.1304348, 317.3913043, 321.7391304, 329.3478261, 335.8695652, 343.4782609, 350., 358.6956522, 367.3913043, 373.9130435, 378.2608696, 383.6956522, 388.0434783, 394.5652174, 402.173913, 408.6956522, 417.3913043, 428.2608696, 440.2173913, 452.173913, 465.2173913, 475., 482.6086957, 489.1304348, 494.5652174, 500., 505.4347826, 510.8695652, 517.3913043, 522.826087, 529.3478261, 534.7826087, 542.3913043, 548.9130435, 555.4347826, 561.9565217, 568.4782609, 577.173913, 583.6956522, 590.2173913, 596.7391304, 603.2608696, 610.8695652, 617.3913043, 623.9130435, 631.5217391, 638.0434783, 644.5652174, 652.173913, 659.7826087, 667.3913043, 676.0869565, 685.8695652, 694.5652174, 703.2608696, 713.0434783, 721.7391304, 731.5217391, 741.3043478, 753.2608696, 764.1304348, 775., 785.8695652, 797.826087, 808.6956522, 819.5652174, 831.5217391, 844.5652174, 855.4347826, 866.3043478, 877.173913, 889.1304348, 898.9130435};

double RGB_sipm_QE_y[89] = {0.02983683, 0.041958042, 0.068997669, 0.106293706, 0.131468531, 0.158508159, 0.185547786, 0.211655012, 0.225641026, 0.240559441, 0.255477855, 0.271328671, 0.287179487, 0.299300699, 0.30955711, 0.321678322, 0.331934732, 0.342191142, 0.353379953, 0.363636364, 0.374825175, 0.385081585, 0.393473193, 0.399067599, 0.407459207, 0.418648019, 0.431701632, 0.443822844, 0.455011655, 0.466200466, 0.476456876, 0.485780886, 0.494172494, 0.502564103, 0.508158508, 0.509090909, 0.506293706, 0.498834499, 0.48951049, 0.479254079, 0.468997669, 0.458741259, 0.446620047, 0.437296037, 0.427039627, 0.416783217, 0.405594406, 0.395337995, 0.384149184, 0.373892774, 0.363636364, 0.352447552, 0.342191142, 0.331002331, 0.320745921, 0.31048951, 0.301165501, 0.290909091, 0.280652681, 0.271328671, 0.261072261, 0.251748252, 0.242424242, 0.233100233, 0.222843823, 0.214452214, 0.204195804, 0.193939394, 0.185547786, 0.176223776, 0.167832168, 0.158508159, 0.151048951, 0.142657343, 0.134265734, 0.125874126, 0.118414918, 0.11002331, 0.102564103, 0.095104895, 0.087645688, 0.082051282, 0.074592075, 0.068065268, 0.061538462, 0.055944056, 0.049417249, 0.044755245, 0.038694639};

//Filter on left side
double UV_filter_x[122] = {309.0140845, 322.5352113, 338.3098592, 352.9577465, 365.3521127, 380., 392.3943662, 402.5352113, 412.6760563, 426.1971831, 438.5915493, 449.8591549, 463.3802817, 478.028169, 489.2957746, 502.8169014, 511.8309859, 524.2253521, 536.6197183, 549.0140845, 562.5352113, 572.6760563, 579.4366197, 582.8169014, 585.0704225, 586.1971831, 587.3239437, 588.4507042, 589.5774648, 590.7042254, 591.8309859, 592.9577465, 594.084507, 595.2112676, 596.3380282, 597.4647887, 598.5915493, 599.7183099, 600.8450704, 601.971831, 603.0985915, 604.2253521, 605.3521127, 606.4788732, 607.6056338, 608.7323944, 609.8591549, 610.9859155, 612.1126761, 613.2394366, 614.3661972, 615.4929577, 616.6197183, 617.7464789, 620., 622.2535211, 624.5070423, 627.8873239, 632.3943662, 639.1549296, 647.0422535, 656.056338, 665.0704225, 674.084507, 681.971831, 692.1126761, 698.8732394, 709.0140845, 715.7746479, 723.6619718, 730.4225352, 738.3098592, 745.0704225, 751.8309859, 757.4647887, 764.2253521, 772.1126761, 781.1267606, 789.0140845, 798.028169, 807.0422535, 814.9295775, 822.8169014, 831.8309859, 838.5915493, 849.8591549, 858.8732394, 867.8873239, 879.1549296, 887.0422535, 897.1830986, 906.1971831, 916.3380282, 926.4788732, 934.3661972, 943.3802817, 952.3943662, 961.4084507, 971.5492958, 981.6901408, 989.5774648, 998.5915493, 1007.605634, 1017.746479, 1026.760563, 1038.028169, 1047.042254, 1057.183099, 1067.323944, 1078.591549, 1087.605634, 1096.619718, 1106.760563, 1116.901408, 1128.169014, 1140.56338, 1150.704225, 1161.971831, 1172.112676, 1181.126761, 1190.140845, 1196.901408}; //R60 filter
double UV_filter_y[122] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.009057971, 0.018115942, 0.028985507, 0.041666667, 0.059782609, 0.076086957, 0.112318841, 0.141304348, 0.15942029, 0.177536232, 0.219202899, 0.260869565, 0.300724638, 0.365942029, 0.405797101, 0.445652174, 0.505434783, 0.543478261, 0.60326087, 0.625, 0.661231884, 0.69384058, 0.733695652, 0.773550725, 0.788043478, 0.80615942, 0.820652174, 0.835144928, 0.849637681, 0.865942029, 0.880434783, 0.894927536, 0.911231884, 0.925724638, 0.942028986, 0.951086957, 0.963768116, 0.971014493, 0.976449275, 0.980072464, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.985507246, 0.985507246, 0.985507246, 0.985507246, 0.985507246, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.989130435, 0.989130435, 0.989130435, 0.989130435, 0.987318841, 0.989130435, 0.989130435}; //R60 filter
double GG_filter_x[92] = {300.0, 310.0, 320.0, 330.0, 340.0, 350.0, 360.0, 370.0, 380.0, 390.0, 400.0, 410.0, 420.0, 430.0, 440.0, 450.0, 460.0, 470.0, 480.0, 490.0, 500.0, 510.0, 520.0, 530.0, 540.0, 550.0, 560.0, 570.0, 580.0, 590.0, 600.0, 610.0, 620.0, 630.0, 640.0, 650.0, 660.0, 670.0, 680.0, 690.0, 700.0, 710.0, 720.0, 730.0, 740.0, 750.0, 760.0, 770.0, 780.0, 790.0, 800.0, 810.0, 820.0, 830.0, 840.0, 850.0, 860.0, 870.0, 880.0, 890.0, 900.0, 910.0, 920.0, 930.0, 940.0, 950.0, 960.0, 970.0, 980.0, 990.0, 1000.0, 1010.0, 1020.0, 1030.0, 1040.0, 1050.0, 1060.0, 1070.0, 1080.0, 1090.0, 1100.0, 1110.0, 1120.0, 1130.0, 1140.0, 1150.0, 1160.0, 1170.0, 1180.0, 1190.0, 1200.0, 1250.0};
double GG_filter_y[92] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

void Timing_ana(int angle/*int num_evtsmax, const char* inputfilename*/) {


  typedef std::vector<dd4hep::sim::Geant4Particle*> GenParts;
  typedef std::vector<CalVision::DualCrystalCalorimeterHit*> CalHits;
  typedef dd4hep::sim::Geant4HitData::MonteCarloContrib Contribution;
  typedef std::vector<dd4hep::sim::Geant4HitData::MonteCarloContrib> Contributions;


  // read in libraries that define the classes
  Long_t result;
  char text[1024];
  const char* dd4hep = gSystem->Getenv("DD4hepINSTALL");
  snprintf(text,sizeof(text)," -I%s/include -D__DD4HEP_DDEVE_EXCLUSIVE__ -Wno-shadow -g -O0",dd4hep);
  gSystem->AddIncludePath(text);
  TString fname = "libDDG4IO";
  const char* io_lib = gSystem->FindDynamicLibrary(fname,kTRUE);
  result = gSystem->Load("libDDG4IO");
  result = gSystem->Load("libDDEvePlugins");
  result = gSystem->Load("libDDEvePlugins");
  result = gSystem->Load("libSingleDualCrystal");
  result = gSystem->Load("libDDG4Plugins");


  // define histograms
  
  //gen particles
  TH1F *hgenPsize = new TH1F("hgenPsize","number of generator particles",600,0.,40000);
  TH1F *hgenPdgID = new TH1F("hgenpdgID","pdgID of generator particles",600,-200,200);
  
  // calorimeter infor
  TH1F *hchan = new TH1F("hchan","channel ID number",1028,0.,1028);
  TH1F *hcEcalE = new TH1F("hcEcalE","sum crystal ecal energy",100,0.,100.);
  
  TH1F *hcEcalE1 = new TH1F("hcEcalE1","energy chan 1",100,0.,10000);
  TH1F *hcEcalE2 = new TH1F("hcEcalE2","energy chan 2",100,0.,10000);
  TH1F *hcEcalE3 = new TH1F("hcEcalE3","energy chan 3",100,0.,10000);
 
  // open data and output file for histograms

  //  const char* inputfilename="/data/users/eno/dd4hep/DD4hep/DDDetectors/compact/testSid.root";
  const char* outputfilename="hist.root";
  float esumchan_avg[nchan], ncerchan_avg[nchan], nscintchan_avg[nchan];


  // get Tree
  //  TFile *f = new TFile(inputfilename);
  //f->Print();
  GenParts* pgenparts = new GenParts();
  CalHits* pcalhits = new CalHits();
  int num_evt,nbyte;
  //float cer_anglei[nchan+8], scint_angle[nchan+8], esum_angle[nchan+8]; //Fill the average values for each angle here before closing the first loop
  std::vector<float> cer_angle[nchan+8],scint_angle[nchan+8],tot_angle[nchan+8];
  std::vector<float> cer_angle_err[nchan+8],scint_angle_err[nchan+8];
  float cerchan_angle[nchan+8], scintchan_angle[nchan+8];
  
  TH1F *hcEcalE0;
  TH1F *hcEcalncer[nchan]; //Cerenkov Generated and also for all the SiPMs
  TH1F *hcEcalnscint[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *hcEcalntot[nchan]; //Scintillation Generated and also for all the SiPMs

  
  TH1F* gcertime[nchan];
  TH1F* gscinttime[nchan];
  
  TH1F* gcertimecut[nchan];
  TH1F* gscinttimecut[nchan];
    
  TH2F* gcerwave_time[nchan];
  TH2F* gscintwave_time[nchan];

  TH2F* gcerwave_timecut[nchan];
  TH2F* gscintwave_timecut[nchan];
  
  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",10000,0.,100000); //Is this in MeV?
  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",100,0.,200); //Extra Zoomed in, is this in MeV?
  hcEcalE0 = new TH1F(Form("hcEcalE0_%d",angle),"energy chan 0",2000,0.,2000); //Is this in MeV?, all events with cut applied
  
  for (int i=0;i<nchan;i++) //Although the range of the x axis on the histograms will be much smaller for the SiPM channels
  {
   gcertime[i] = new TH1F(Form("gcertime_%d",i),"gcertime",1000,0,100);
   gscinttime[i] = new TH1F(Form("gscinttime_%d",i),"gscinttime",1000,0,100);
   gcertimecut[i] = new TH1F(Form("gcertimecut_%d",i),"gcertimecut",1000,0,100);
   gscinttimecut[i] = new TH1F(Form("gscinttimecut_%d",i),"gscinttimecut",1000,0,100);

   gcerwave_time[i] = new TH2F(Form("gcerwavetime_%d",i),"gcerwavetime",1000,0,100, 1000, 300, 1240);
   gscintwave_time[i] = new TH2F(Form("gscintwavetime_%d",i),"gscintwavetime",1000,0,100, 1000, 300, 1240);
   gcerwave_timecut[i] = new TH2F(Form("gcerwavetimecut_%d",i),"gcerwavetimecut",1000,0,100, 1000, 300, 1240);
   gscintwave_timecut[i] = new TH2F(Form("gscintwavetimecut_%d",i),"gscintwavetimecut",1000,0,100, 1000, 300, 1240);   
   
   if(i==0)
   {
   //hcEcalncer[i] = new TH1F(Form("hcEcalncer_%d",i),"total number of cerenkov chan 1",100,0.,200000);
   //hcEcalnscint[i] = new TH1F(Form("hcEcalnscint_%d",i),"total number of scintillation chan 1",100,0.,2000000);
   hcEcalncer[i] = new TH1F(Form("hcEcalncer_%d",i),"total number of cerenkov chan 1",2000000,0.,2000000);
   hcEcalnscint[i] = new TH1F(Form("hcEcalnscint_%d",i),"total number of scintillation chan 1",5000000,0.,5000000);
   hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",7000000,0.,7000000);
   }
   else
   {
   hcEcalncer[i] = new TH1F(Form("hcEcalncer_%d",i),"total number of cerenkov chan 1",200000,0.,200000);
   hcEcalnscint[i] = new TH1F(Form("hcEcalnscint_%d",i),"total number of scintillation chan 1",500000,0.,500000);
   hcEcalntot[i] = new TH1F(Form("hcEcalntot_%d",i),"total number of S+C chan 1",700000,0.,700000);
   }   
  }

  C_S_SiPM.open("C_S_total_SiPMs_0811_100_PbWO4.csv");

  //TFile* f = TFile::Open(Form("Root_files/Protons/PbWO4/out_0705_%i.root",angle));
  TFile* f = TFile::Open(Form("Root_files/Protons/PbWO4/0811_100_ev/out_0811_%i.root",angle));
  //TFile* f = TFile::Open(Form("Root_files/Protons/PbWO4/out_0627_1000_%i.root",angle)); //1000 events for PbWO4
  //TFile* f = TFile::Open(Form("Root_files/Protons/PbWO4/out_0611_%i.root",angle)); //Actually the ones for PbF2 crystal
  //TFile* f = TFile::Open(Form("Root_files/Protons/PbF2/out_0626_1000_%i.root",angle)); //Actually the ones for PbF2 crystal
  //TFile* f = TFile::Open(Form("Root_files/PbWO4/out_%i_0330.root",angle)); //Old files possibly having muon data
  TTree* t = (TTree*)f->Get("EVENT;1");
  t->Print();

  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",10000,0.,100000); //Is this in MeV?
  
  
  // loop over events
  TBranch* b_mc = t->GetBranch("MCParticles");
  TBranch* b_ecal = t->GetBranch("DRCNoSegment");
  int ihaha = b_mc->GetEntries();
  //num_evt= std::min(ihaha,num_evtsmax);
  num_evt= 100;
  //num_evt= 5;
  std::cout<<" doing "<<b_mc->GetName()<<std::endl;
  std::cout<<"num_evt gen loop is "<<num_evt<<std::endl;
  

std::cout<<std::endl;
  
  
  //if(num_evt>0) {
  
    // find branches
    GenParts* gens = new GenParts();
    b_mc->SetAddress(&gens);
    CalHits* ecalhits = new CalHits();
    b_ecal->SetAddress(&ecalhits);

      float esum_avg=0.;
      float ncercutchan_avg[nchan]; //Cerenkov Photons above cutoff
      float nscintcutchan_avg[nchan]; //Scintillation photons below cutoff

      for(int i=0;i<nchan;i++)
      {
      esumchan_avg[i]=0.;
      ncerchan_avg[i]=0.;
      nscintchan_avg[i]=0.;
      ncercutchan_avg[i]=0.;
      nscintcutchan_avg[i]=0.;
      }
      
      float ncertot_avg=0;
      float nscinttot_avg=0;
      
      std::vector<float> number_of_bins_avg[nchan]; //Only required for filter here
      
      //Declaration for time arrays
      std::vector<float> ncertimechan_avg[nchan];
      std::vector<float> nscinttimechan_avg[nchan];   
      std::vector<float> number_of_bins_time_avg[nchan];
      
      std::vector<float> ncertimecutchan_avg[nchan];
      std::vector<float> nscinttimecutchan_avg[nchan];   
      
      
      //Declaration for wavelength time 2D arrays
      std::vector<std::vector<float>> ncerwave_timechan_avg[nchan];
      std::vector<std::vector<float>> nscintwave_timechan_avg[nchan];   
      std::vector<std::vector<float>> number_of_bins_wave_time_avg[nchan];  
      
      std::vector<std::vector<float>> ncerwave_timecutchan_avg[nchan];
      std::vector<std::vector<float>> nscintwave_timecutchan_avg[nchan];   
      
      
      std::vector<int> ncerwave_dummy_avg[nchan];
      std::vector<int> nscintwave_dummy_avg[nchan];    


    int SCEPRINT2=10;
    int ievt_min = 0;
    int icount = 0;
    C_gen.open("Generated_Cerenkov_photons.txt"); //Opening this before the event loop
    S_gen.open("Generated_Scintillation_photons.txt"); //Opening this before the event loop
    
    for(int ievt=0;ievt<num_evt; ++ievt) 
    {
      //std::cout<<"event number is "<<ievt<<std::endl;
      //gen particles
      nbyte = b_mc->GetEntry(ievt);
      
      if( nbyte>0) {
	//if(ievt<SCEPRINT2) std::cout<<gens->size()<<" Gen particles "<<std::endl;
      }
      float mainee=-1;
      hgenPsize->Fill(gens->size());
      for(size_t i=0;i<gens->size(); ++i) {
        dd4hep::sim::Geant4Particle* agen =gens->at(i);
        hgenPdgID->Fill(agen->pdgID);

	float px=agen->psx;
	float py=agen->psy;
	float pz=agen->psz;
	float mass=agen->mass;
	float ee=sqrt(mass*mass+px*px+py*py+pz*pz);

	//if(i==0&&ievt<SCEPRINT2) std::cout<<" first particle pid energy are "<<agen->pdgID<<" "<<ee<<std::endl;

	if(ee>mainee) {
	  mainee=ee;
	  //if(ievt<SCEPRINT2) std::cout<<"highest e  gen now has pid "<<agen->pdgID<<" energy "<<ee<<std::endl;
	}
	float vsy=agen->vsy;
	/*if(vsy>20)*/ /*std::cout<<" pid "<<agen->pdgID<<" "
			      <<"vs ("<<agen->vsx<<","<<agen->vsy<<","<<agen->vsz<<") "
			      <<"ve ("<<agen->vex<<","<<agen->vey<<","<<agen->vez<<") "
			      <<"ps ("<<agen->psx<<","<<agen->psy<<","<<agen->psz<<") "
			      <<"pe ("<<agen->pex<<","<<agen->pey<<","<<agen->pez<<") "
			      <<std::endl;*/



      }



    // ECAL hits  
    // there are hits in the crystal and also the photodetectors "kill media"
    // in the crystal, photons created in the crystal are counted and their wavelengths stored
    // in the photodetector, photons that enter are counted, wavelength stored, and then they are killed


      int nbyte = b_ecal->GetEntry(ievt);
      if( nbyte>0) {
      //std::cout<<" Ecal Hits "<<nbyte<<" bytes "<<ecalhits->size() <<std::endl;
      }
      float esum=0.;
      float esumchan[nchan];
      int ncerchan[nchan], nscintchan[nchan];
      float ncercutchan[nchan], nscintcutchan[nchan];
     for(int k=0;k<nchan;k++)
     { 

     ncercutchan[k] = 0.;
     nscintcutchan[k] = 0.;
     ncerchan[k] = 0;
     nscintchan[k] = 0;
     esumchan[k] = 0;
     }

      int ncertot=0;
      int nscinttot=0;
      int SCEPRINT=10;

      std::vector<float> number_of_bins[nchan];
          
      std::vector<float> ncertimechan[nchan];
      std::vector<float> nscinttimechan[nchan];   
      std::vector<float> ncertimecutchan[nchan];
      std::vector<float> nscinttimecutchan[nchan];   
      std::vector<float> number_of_bins_time[nchan];
      
      //Again 2 D vectors for wavelength and time for each event
      std::vector<std::vector<float>> ncerwave_timechan[nchan]; //Really this should be int, changed to float due to push back problems
      std::vector<std::vector<float>> nscintwave_timechan[nchan]; //Really this should be int, changed to float due to push back 
      std::vector<std::vector<float>> ncerwave_timecutchan[nchan];
      std::vector<std::vector<float>> nscintwave_timecutchan[nchan];      
      std::vector<std::vector<float>> number_of_bins_wave_time[nchan];
      
      std::vector<float> ncerwave_dummy[nchan];
      std::vector<float> nscintwave_dummy[nchan];


      for(size_t i=0;i<ecalhits->size(); ++i) 
      {
	CalVision::DualCrystalCalorimeterHit* aecalhit =ecalhits->at(i);
	//	std::cout<<"       "<<i<<" energy "<<aecalhit->energyDeposit<<std::endl;
	esum+=aecalhit->energyDeposit;
	ncertot+=aecalhit->ncerenkov;
	nscinttot+=aecalhit->nscintillator;
 	//if(i<SCEPRINT&&ievt<SCEPRINT2) std::cout<<" hit channel is "<<aecalhit->cellID<<" in hex is "<< std::hex<< aecalhit->cellID<<std::dec<<" "<<aecalhit->energyDeposit<<" "<<aecalhit->ncerenkov<<" "<<aecalhit->nscintillator<<std::endl;




	// see ../src/DRCrystal_geo.cpp to see the assignments
	int ihitchan=aecalhit->cellID;
	int idet = (ihitchan & 0xC0)>>6;  // this assignment is made in SCEPCALConstants.xml
	int ilayer = (ihitchan & 0x38)>>3; // this is 1 for crystal and detectors, 0 for air around it
	int islice = (ihitchan & 0x07);  //   this is 1 or 4 for photodetectors, 2 for crystal
	// channels are 64 air
	//             73 77 detectors
	//            75 crystal
  //Others for the silicone gap 
	//if(i<SCEPRINT&&ievt<SCEPRINT2) std::cout<<" idet,ilayer,islice is ("<<idet<<","<<ilayer<<","<<islice<<")"<<std::endl;

  // print out wavelength spectra and also timing histograms
	int ijchan=aecalhit->nbin;
 	float binsize = (aecalhit->wavelenmax-aecalhit->wavelenmin)/ijchan; //Copied from SDAction
  //std::cout << "Bin size " << binsize << std::endl;
  int ijchan_t=aecalhit->nbin_t;
  float binsize_t = (aecalhit->timemax-aecalhit->timemin)/ijchan_t; //Copied from SDAction
  
  //int bincut=(wavelencut-aecalhit->wavelenmin)/binsize;
  //std::cout<<bincut<<std::endl;
	//for (int j=0;j<ijchan;j++) {
	//  std::cout<<"  ncerwave["<<j<<"]="<<(aecalhit->ncerwave)[j]<<std::endl;
	//  std::cout<<"  nscintwave["<<j<<"]="<<(aecalhit->nscintwave)[j]<<std::endl;
	//}
  hchan->Fill(aecalhit->cellID);


      // there is a better way to do this
	int jchan=aecalhit->cellID;
	int kchan=-1;
	for( int i=0;i<nchan;i++ ) 
  {
	  if(ichan[i]==jchan) kchan=i; //comparing with the entries of ichan which is populated with the cellIDs 
	}
	if(kchan==-1)
  {
	  //std::cout<<"unknown hit channel is "<< aecalhit->cellID<<std::endl;
	} 
  else
  {
	  esumchan[kchan]+=aecalhit->energyDeposit;
	  ncerchan[kchan]+=aecalhit->ncerenkov;
	  nscintchan[kchan]+=aecalhit->nscintillator;

    for (int j=0; j<ijchan;j++) //Wavelength bin loop
    {
     float bin_wavelength = 0.0;
     bin_wavelength= j*binsize + aecalhit->wavelenmin;
     number_of_bins[kchan].push_back(bin_wavelength); //lower wavelength of the j th bin
    }    

    for (int j_t=0; j_t<ijchan_t;j_t++) //time bin loop
    {
     ncertimechan[kchan].push_back((aecalhit->ncertime)[j_t]);
     nscinttimechan[kchan].push_back((aecalhit->nscinttime)[j_t]);
     ncertimecutchan[kchan].push_back(0.0);
     nscinttimecutchan[kchan].push_back(0.0);

     number_of_bins_time[kchan].push_back(j_t*binsize_t + aecalhit->timemin); //lower time stamp of the j th bin
    }
    
    for(int k=0; k<ijchan; k++)
     {
      ncerwave_dummy[kchan].push_back(0.0);
      nscintwave_dummy[kchan].push_back(0.0);
     }

    for(int k_t=0; k_t<ijchan_t; k_t++)
    {
     for(int k=0; k<ijchan; k++) //For each row the value of the dummy row vector changes
     {
      ncerwave_dummy[kchan].at(k) = (aecalhit->ncerwave_time)[k_t][k];
      nscintwave_dummy[kchan].at(k) = (aecalhit->nscintwave_time)[k_t][k];
      //std::cout << ncerwave_dummy[kchan].at(k) << " ";
      //std::cout << (aecalhit->ncerwave_time)[k_t][k] << " ";
     }
     ncerwave_timechan[kchan].push_back(ncerwave_dummy[kchan]);
     nscintwave_timechan[kchan].push_back(nscintwave_dummy[kchan]);

     for(int k=0; k<ijchan; k++) //For each row the value of the dummy row vector changes
     {
      ncerwave_dummy[kchan].at(k) = 0.0;
      nscintwave_dummy[kchan].at(k) = 0.0;
      //std::cout << ncerwave_dummy[kchan].at(k) << " ";
      //std::cout << (aecalhit->ncerwave_time)[k_t][k] << " ";
     }

     ncerwave_timecutchan[kchan].push_back(ncerwave_dummy[kchan]);
     nscintwave_timecutchan[kchan].push_back(nscintwave_dummy[kchan]);

    }

	}
 
         // get MC truth information about individual contributions to this hit
        Contributions zxzz=aecalhit->truth;
        float hacheck=0.;
        for(size_t j=0;j<zxzz.size(); j++) {
          //      std::cout<<"testing truth truth number "<<i<<" with pdgID "<<(zxzz.at(i)).pdgID<<std::endl;
          // other member functions are trackID, deposit, time, length, x,y,z
          hacheck+=(zxzz.at(j)).deposit;
        }
        if(i<SCEPRINT2) {
	  //std::cout<<"    difference between truth sum and total deposit is "<<hacheck-aecalhit->energyDeposit<<" where "<<aecalhit->energyDeposit<<" is the hit size."<<std::endl;
          //if(aecalhit->energyDeposit>0) std::cout<<"      percent diff is "<<(hacheck-aecalhit->energyDeposit)/aecalhit->energyDeposit<<std::endl;
        }


      }  // end loop over hits
      std::cout << "Reached here end of hit loop MMP" << std::endl;
      esum_avg+=esum;
      ncertot_avg+=ncertot;
      nscinttot_avg+=nscinttot;
     
      std::vector<float> filter[nchan];
      std::vector<float> QE[nchan];
    for(int j=0;j<ncerwave_dummy[0].size();j++) //Right now all sizes are the same = binsize, taken the channel 0
    {
     //int ent_UG11 = 91, ent_GG420 = 121; //Filter on right side
     int ent_UG11 = 121, ent_GG420 = 91; //Filter on left side
     if (number_of_bins[0].at(j) >= UV_filter_x[0] && number_of_bins[0].at(j) < UV_filter_x[ent_UG11]) //within range specified for filter (which is basically the entire range over which the bins are specified)
     {
      for(int i=0;i<ent_UG11;i++)
      {
       if (number_of_bins[0].at(j) >= UV_filter_x[i] && number_of_bins[0].at(j) < UV_filter_x[i + 1]) //Checking what 'bin' the wavelength lies in
       {
       filter[2].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins[0].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);
       filter[3].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins[0].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);
       filter[4].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins[0].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);
       filter[5].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins[0].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);       
       }
      }
     }      
     else 
     {
      filter[2].push_back(0.0); //outside range
      filter[3].push_back(0.0); //outside range
      filter[4].push_back(0.0); //outside range
      filter[5].push_back(0.0); //outside range
     }
     
     if (number_of_bins[0].at(j) >= GG_filter_x[0] && number_of_bins[0].at(j) < GG_filter_x[ent_GG420]) //within range specified for filter (which is basically the entire range over which the bins are specified)
     {
      for(int i=0;i<ent_GG420;i++)
      {
       if (number_of_bins[0].at(j) >= GG_filter_x[i] && number_of_bins[0].at(j) < GG_filter_x[i + 1]) //Checking what 'bin' the wavelength lies in
       {
       filter[6].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins[0].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       filter[7].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins[0].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       filter[8].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins[0].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       filter[9].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins[0].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       }
      }
     }      
     else 
     {
      filter[6].push_back(0.0); //outside range
      filter[7].push_back(0.0); //outside range
      filter[8].push_back(0.0); //outside range
      filter[9].push_back(0.0); //outside range
     }
     
     filter[0].push_back(1.0);
     filter[1].push_back(1.0);
    }
   //if(ievt==894){std::cout << "Problematic event " << ievt << " "<< ncerwavechan[0].size() << std::endl;}    
      for(int j=0;j<ncerwave_dummy[0].size();j++) //Right now all sizes are the same = binsize, taken the channel 0
      {
      int ent_UV = 88, ent_RGB = 88;
      if(number_of_bins[0].at(j) >= UV_sipm_QE_x[0] && number_of_bins[0].at(j) < UV_sipm_QE_x[ent_UV]) //i.e. if it lies within the range of sensitivity of the UV SiPM
      //1 less than actual size i.e. 23 because of usual indexing quirks (starts from 0)
      {
       for(int i=0;i<ent_UV;i++)
       {
        if (number_of_bins[0].at(j) >= UV_sipm_QE_x[i] && number_of_bins[0].at(j) < UV_sipm_QE_x[i + 1]) //Checking what 'bin' the wavelength lies in 
        {
        QE[2].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins[0].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        QE[3].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins[0].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        QE[4].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins[0].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        QE[5].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins[0].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        }
       }
      } 
       else 
       {
        QE[2].push_back(0.0);
        QE[3].push_back(0.0);
        QE[4].push_back(0.0);
        QE[5].push_back(0.0);
       }
       
       
       
      if(number_of_bins[0].at(j) >= RGB_sipm_QE_x[0] && number_of_bins[0].at(j) < RGB_sipm_QE_x[ent_RGB]) //i.e. if it lies within the range of sensitivity of the RGB SiPM
      //1 less than actual size i.e. 29 because of usual indexing quirks (starts from 0)
      {
       for(int i=0;i<ent_RGB;i++)
       {
        if (number_of_bins[0].at(j) >= RGB_sipm_QE_x[i] && number_of_bins[0].at(j) < RGB_sipm_QE_x[i + 1]) //Checking what 'bin' the wavelength lies in
        {
        QE[6].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins[0].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        QE[7].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins[0].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        QE[8].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins[0].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        QE[9].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins[0].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        }
       }
      } 
       else 
       {
        QE[6].push_back(0.0);
        QE[7].push_back(0.0);
        QE[8].push_back(0.0);
        QE[9].push_back(0.0);
       }
       
       QE[0].push_back(1.0);
       QE[1].push_back(1.0);
      }
      //std::cout << "Added filter and QE " << std::endl;
      if(ncerchan[0]>0/*<20000*/ && ncerwave_dummy[0].size() > 0)
      {
       icount++;      
       C_gen << ncerchan[0] << endl;
       S_gen << nscintchan[0] << endl;
      for(int k=0;k<nchan;k++)
      {
       esumchan_avg[k]+=esumchan[k];
       ncerchan_avg[k]+=ncerchan[k];
       nscintchan_avg[k]+=nscintchan[k];
       //std::cout << ncerwavechan[k].size() << std::endl;
        
       for(int j_t=0;j_t<ncertimechan[k].size();j_t++) //Right now all sizes are the same = binsize
       {
         if(icount == 1) //Only the first instance of a non zero array
         {
         ncertimechan_avg[k].push_back(ncertimechan[k].at(j_t));
         nscinttimechan_avg[k].push_back(nscinttimechan[k].at(j_t));

         number_of_bins_time_avg[k].push_back(number_of_bins_time[k].at(j_t));

          ievt_min = ievt;
         }
         else if (ievt>ievt_min &&ievt<num_evt) //i.e. the avg vector already has this size because this condition is necessarily occurring after the 'if' one above
        {
         ncertimechan_avg[k].at(j_t) += ncertimechan[k].at(j_t);
         nscinttimechan_avg[k].at(j_t) += nscinttimechan[k].at(j_t);        
         //Don't change the number_of_bins_avg here
        }

        }
       //std::cout << "Added time filter cuts " <<std::endl;
        
       for(int k_t=0; k_t<ncerwave_timechan[k].size(); k_t++)
       {
        if(icount == 1)
        {
         ncerwave_timechan_avg[k].push_back(ncerwave_timechan[k].at(k_t));
         nscintwave_timechan_avg[k].push_back(nscintwave_timechan[k].at(k_t));
        }
        
        else if (ievt>ievt_min &&ievt<num_evt) //i.e. the avg vector already has this size because this condition is necessarily occurring after the 'if' one above
       {
        for(int k_w=0; k_w<ncerwave_timechan[k].at(k_t).size(); k_w++) //For each row the value of the dummy row vector changes
        {
         ncerwave_timechan_avg[k].at(k_t).at(k_w) += ncerwave_timechan[k].at(k_t).at(k_w);
         nscintwave_timechan_avg[k].at(k_t).at(k_w) += nscintwave_timechan[k].at(k_t).at(k_w);
        }
       }
        for(int k_w=0; k_w<ncerwave_timechan[k].at(k_t).size(); k_w++) 
        {
        ncerwave_timecutchan[k].at(k_t).at(k_w) += ncerwave_timechan[k].at(k_t).at(k_w)*filter[k].at(k_w)*QE[k].at(k_w);
        nscintwave_timecutchan[k].at(k_t).at(k_w) += nscintwave_timechan[k].at(k_t).at(k_w)*filter[k].at(k_w)*QE[k].at(k_w);
        }

       if(icount == 1)
       {
         ncerwave_timecutchan_avg[k].push_back(ncerwave_timecutchan[k].at(k_t)); //This is also a 'wavelength' vector
         nscintwave_timecutchan_avg[k].push_back(nscintwave_timecutchan[k].at(k_t)); //This is also a 'wavelength' vector
       }
       else if (ievt>ievt_min &&ievt<num_evt) //i.e. the avg vector already has this size because this condition is necessarily occurring after the 'if' one above
       {
        for(int k_w=0; k_w<ncerwave_timechan[k].at(k_t).size(); k_w++) //For each row the value of the dummy row vector changes
        {
         ncerwave_timecutchan_avg[k].at(k_t).at(k_w) += ncerwave_timecutchan[k].at(k_t).at(k_w);
         nscintwave_timecutchan_avg[k].at(k_t).at(k_w) += nscintwave_timecutchan[k].at(k_t).at(k_w);
        }
       }
      }
       //std::cout << "Added wave and time filter cuts " <<std::endl;
     //std::cout << ncertimecutchan[k].size() << std::endl;
     for(int k_t=0; k_t<ncerwave_timechan[k].size(); k_t++)
     {
      for(int k_w=0; k_w<ncerwave_timechan[k].at(k_t).size(); k_w++)
      {
       ncertimecutchan[k].at(k_t)+= ncerwave_timecutchan[k].at(k_t).at(k_w);
       nscinttimecutchan[k].at(k_t)+= nscintwave_timecutchan[k].at(k_t).at(k_w);
      }
        ncercutchan[k]+=ncertimecutchan[k].at(k_t);
        nscintcutchan[k]+= nscinttimecutchan[k].at(k_t);
       
        //std::cout << ncerwave_timecutchan[k].at(k_t).size() << std::endl;
       if(icount == 1)
       {
         ncertimecutchan_avg[k].push_back(ncertimecutchan[k].at(k_t));
         nscinttimecutchan_avg[k].push_back(nscinttimecutchan[k].at(k_t));
       }
       else if (ievt>ievt_min &&ievt<num_evt) //i.e. the avg vector already has this size because this condition is necessarily occurring after the 'if' one above
       {
         ncertimecutchan_avg[k].at(k_t) += ncertimecutchan[k].at(k_t);
         nscinttimecutchan_avg[k].at(k_t) += nscinttimecutchan[k].at(k_t);
       }
       //std::cout << "First event " << ievt_min << std::endl;
      }
      //std::cout << "Event number " << ievt << " Individual counts in channel " << k << " " << ncercutchan[k] << " " << nscintcutchan[k] << std::endl;
       ncercutchan_avg[k]+=ncercutchan[k];
       nscintcutchan_avg[k]+=nscintcutchan[k];

      //std::cout << "Added wave and time filter cuts " <<std::endl;
     }
      }
      else if(ncerwave_dummy[0].size() == 0)
      {
       C_gen << ncerchan[0] << endl;
       S_gen << nscintchan[0] << endl;       
      }
      
      //std::cout << sizeof(UV_sipm_QE_x) << ' ' << sizeof(RGB_sipm_QE_x) << std::endl;
       
      if(ncerchan[0]>0/*<20000*/ && ncerwave_dummy[0].size() > 0)
      {
       hcEcalE0->Fill(esumchan[0]);
       for(int i=0;i<nchan;i++)
       {
        hcEcalncer[i]->Fill(ncercutchan[i]);
        hcEcalnscint[i]->Fill(nscintcutchan[i]); //This is for total with cuts instead of just scintillation, at least for this script
        hcEcalntot[i]->Fill(ncercutchan[i]+nscintcutchan[i]); //Total for comparison with Hui-Chi's plots
       }
      }
    }  //end loop over events
    
    C_gen.close();
    S_gen.close();    
    std::cout << "Number of non zero events: " << icount << std::endl;
    std::cout << "Angle value: " << angle << std::endl;
    
    for( int i=0;i<nchan;i++)
    {
     esumchan_avg[i] = esumchan_avg[i]/icount;
     nscintchan_avg[i] = nscintchan_avg[i]/icount;
     ncerchan_avg[i] = ncerchan_avg[i]/icount;

     nscintcutchan_avg[i] = nscintcutchan_avg[i]/icount;
     ncercutchan_avg[i] = ncercutchan_avg[i]/icount;

     
     for(int j_t=0;j_t<ncertimechan_avg[i].size();j_t++)
     {
      ncertimechan_avg[i].at(j_t) = ncertimechan_avg[i].at(j_t)/icount;
      nscinttimechan_avg[i].at(j_t) = nscinttimechan_avg[i].at(j_t)/icount;
      ncertimecutchan_avg[i].at(j_t) = ncertimecutchan_avg[i].at(j_t)/icount;
      nscinttimecutchan_avg[i].at(j_t) = nscinttimecutchan_avg[i].at(j_t)/icount;

     }
     
     for(int k_t=0; k_t<ncerwave_timechan_avg[i].size(); k_t++)
     {
      for(int k_w=0; k_w<ncerwave_timechan_avg[i].at(k_t).size(); k_w++)
      {
       ncerwave_timechan_avg[i].at(k_t).at(k_w) = ncerwave_timechan_avg[i].at(k_t).at(k_w)/icount;
       nscintwave_timechan_avg[i].at(k_t).at(k_w) = nscintwave_timechan_avg[i].at(k_t).at(k_w)/icount;
       
       ncerwave_timecutchan_avg[i].at(k_t).at(k_w) = ncerwave_timecutchan_avg[i].at(k_t).at(k_w)/icount;
       nscintwave_timecutchan_avg[i].at(k_t).at(k_w) = nscintwave_timecutchan_avg[i].at(k_t).at(k_w)/icount;
      }
     }

     std::cout<<"esum_avg ["<<namechan[i]<<"]="<<esumchan_avg[i]<<std::endl;
     std::cout<<"nscintillator_avg ["<<namechan[i]<<"]="<<nscintchan_avg[i]<<std::endl;
     std::cout<<"ncerenkov_avg ["<<namechan[i]<<"]="<<ncerchan_avg[i]<<std::endl;
     
     std::cout<<"nscintillator_avg with filter and QE ["<<namechan[i]<<"]="<<nscintcutchan_avg[i]<<std::endl;
     std::cout<<"ncerenkov_avg with filter and QE ["<<namechan[i]<<"]="<<ncercutchan_avg[i]<<std::endl;     
     std::cout<<"ntotal_avg with filter and QE ["<<namechan[i]<<"]="<<ncercutchan_avg[i]+nscintcutchan_avg[i]<<std::endl;     

    }
    
    
    std::vector<float>wavelencut;
    for(int i=0;i<number_of_bins_avg[0].size();i++)
    {
     wavelencut.push_back(number_of_bins_avg[0].at(i)); //cuts in general are spanning over all the bins
    }

    std::cout << wavelencut.size() << std::endl;
    C_S_SiPM << angle << ",";
     
    for( int i=0;i<nchan;i++)
    {
    
    if(i!=1)
    {
     C_S_SiPM << ncercutchan_avg[i] << "," << nscintcutchan_avg[i] << ",";
     }

     if(i>1 && i<nchan) //New branches that are in the same order as the indices of the corresponding SiPMs
     {
      std::cout << "Branch number " << i+8 <<std::endl; 
     }
    }
      C_S_SiPM << endl; 
      f->Close();
      
        
    //for(int j=0;j<2;j++) //For toggling through the different graphs
    for(int j=0;j<nchan;j++)
    { 
    /*if(j==0)
    {*/
     //gcerscint = new TGraph(ncertimechan_avg[side_toggle+SiPM_number].size(), &number_of_bins_time_avg[side_toggle+SiPM_number][0],&ncertimechan_avg[side_toggle+SiPM_number][0]);
     for(int k_t=0; k_t<ncertimechan_avg[j].size(); k_t++)
     {
      gcertime[j]->SetBinContent(k_t+1,ncertimechan_avg[j].at(k_t));
      gcertimecut[j]->SetBinContent(k_t+1,ncertimecutchan_avg[j].at(k_t));      
     }
     
     for(int k_t=0; k_t<nscinttimechan_avg[j].size(); k_t++)
     {
      gscinttime[j]->SetBinContent(k_t+1,nscinttimechan_avg[j].at(k_t)); 
      gscinttimecut[j]->SetBinContent(k_t+1,nscinttimecutchan_avg[j].at(k_t));            
     }     
     
     for(int k_t=0; k_t<nscintwave_timechan_avg[j].size(); k_t++)
     {
      for(int k_w=0; k_w<nscintwave_timechan_avg[j].at(0).size(); k_w++)
      {
      gscintwave_time[j]->SetBinContent(k_t+1, k_w+1, nscintwave_timechan_avg[j].at(k_t).at(k_w));
      gscintwave_timecut[j]->SetBinContent(k_t+1, k_w+1, nscintwave_timecutchan_avg[j].at(k_t).at(k_w));      
      }
     }
     
     for(int k_t=0; k_t<ncerwave_timechan_avg[j].size(); k_t++)
     {
      for(int k_w=0; k_w<ncerwave_timechan_avg[j].at(0).size(); k_w++)
      {
      gcerwave_time[j]->SetBinContent(k_t+1, k_w+1, ncerwave_timechan_avg[j].at(k_t).at(k_w));
      gcerwave_timecut[j]->SetBinContent(k_t+1, k_w+1, ncerwave_timecutchan_avg[j].at(k_t).at(k_w));
      }
     }
   }
     

C_S_SiPM.close();
//  }  // end if no events - Not needed since num_evt is already specified

    //Graphs for time distribution of C,S generated, detected and with effects of SiPM QE and filtering action
    
      std::ofstream C_total_hist;  

    int side_toggle; //Insert 2 for left side and 6 for right side   
    string side_string;
    float max_cer_gen = gcertime[0]->GetMaximum();
    float max_scint_gen =  gscinttime[0]->GetMaximum();
    stringstream j_s_1;
    string entry_filter_string;
    j_s_1 << angle;
    j_s_1 >> entry_filter_string;

    C_total_hist.open("Time_-30deg.csv");

    //Gen graphs to be added outside the loop

    string Entry_index_time_gen ="Plots/PbWO4/0811_100_ev/Angle_"+ entry_filter_string + "_deg/" + " Time distribution of generated photons for " + entry_filter_string + " deg.pdf";
    string time_gen = " Time distribution of generated photons for " + entry_filter_string + " deg";
    string Entry_index_wave_time_gen ="Plots/PbWO4/0811_100_ev/Angle_"+ entry_filter_string + "_deg/" + " Wavelength and Time distribution of generated photons for " + entry_filter_string + " deg.pdf";
    string wave_time_gen = " Wavelength and Time distribution of generated photons for " + entry_filter_string + " deg";


    //Time 1D for generated photons
    TCanvas *c_time_gen = new TCanvas("c_time_gen","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    if(max_cer_gen>max_scint_gen)
    {
     std::cout << "Plot Cerenkov first" << std::endl;
     gcertime[0]->Draw();
     gscinttime[0]->Draw("same"); 
     gcertime[0]->GetXaxis()->SetTitle("Time (in ns)");
     gcertime[0]->GetYaxis()->SetTitle("Number of counts");
     gcertime[0]->SetTitle(time_gen.c_str());     
    }  
    else if(max_cer_gen<max_scint_gen)
    {
     std::cout << "Plot scintillation first" << std::endl;
     gscinttime[0]->Draw();
     gcertime[0]->Draw("same");
     gscinttime[0]->GetXaxis()->SetTitle("Time (in ns)");
     gscinttime[0]->GetYaxis()->SetTitle("Number of counts");
     gscinttime[0]->SetTitle(time_gen.c_str());     
    } 
    
    gcertime[0] -> SetLineColor(kGreen);
    gscinttime[0] -> SetLineColor(kRed);
        
    c_time_gen -> Print(Entry_index_time_gen.c_str()); //Copy canvas to pdf
    c_time_gen->Close();    
    //End of Time 1D for generated photons
    
     //2D wavelength and time plots for generated photons
    TCanvas *c_wave_time_gen = new TCanvas("c_wave_time_gen","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    
    gscintwave_time[0]->Draw("SURF");
    gcerwave_time[0]->Draw("SURF same");
    gcerwave_time[0]-> SetLineColor(kGreen);
    gscintwave_time[0]-> SetLineColor(kRed);

    gscintwave_time[0]->GetXaxis()->SetTitle("Time (in ns)");
    gscintwave_time[0]->GetYaxis()->SetTitle("Wavelength (in nm)");
    gscintwave_time[0]->GetZaxis()->SetTitle("Number of counts");    
    gscintwave_time[0]->SetTitle(wave_time_gen.c_str());
    c_wave_time_gen -> Print(Entry_index_wave_time_gen.c_str()); //Copy canvas to pdf
    c_wave_time_gen->Close();    
    //End of 2D wavelength and time plots for generated photons
   
    
    for (int k=0;k<2;k++) //Left or right side
    {
     if(k==0)
     {
     side_toggle=2;
     side_string = "Left";
     }
     else if (k==1)
     {
     side_toggle=6;
     side_string = "Right";
     }

     for(int SiPM_number=0;SiPM_number<4;SiPM_number++)
     {
     stringstream j_s;
     string title_string;
     j_s << SiPM_number;
     j_s >> title_string;
     
     string Net_title_string, aux_title_string;
    float max_cer_cut = gcertimecut[side_toggle+SiPM_number]->GetMaximum();
    float max_scint_cut =  gscinttimecut[side_toggle+SiPM_number]->GetMaximum();
    float max_cer = gcertime[side_toggle+SiPM_number]->GetMaximum();
    float max_scint =  gscinttime[side_toggle+SiPM_number]->GetMaximum();
    std::cout << "Cerenkov max cut "<< max_cer_cut << " Scintillation max cut " << max_scint_cut << std::endl;
    std::cout << "Cerenkov max "<< max_cer << " Scintillation max " << max_scint << std::endl;    
    string Entry_index_filter_time_cut ="Plots/PbWO4/0811_100_ev/Angle_"+ entry_filter_string + "_deg/" + side_string + " SiPM " + title_string + " Time distribution with SiPM and filter for " + entry_filter_string + " deg.pdf";
    string filter_time = side_string + " SiPM " + title_string + " Time distribution with SiPM and filter for " + entry_filter_string + " deg";

    string Entry_index_time ="Plots/PbWO4/0811_100_ev/Angle_"+ entry_filter_string + "_deg/" + side_string + " SiPM " + title_string + " Time distribution for " + entry_filter_string + " deg.pdf";
    string time = side_string + " SiPM " + title_string + " Time distribution for " + entry_filter_string + " deg";

    string Entry_index_wave_time_cut ="Plots/PbWO4/0811_100_ev/Angle_"+ entry_filter_string + "_deg/" + side_string + " SiPM " + title_string + " Wavelength and Time distribution with SiPM and filter for " + entry_filter_string + " deg.pdf";
    string wave_time_cut = side_string + " SiPM " + title_string + " Wavelength and Time distribution with SiPM and filter for " + entry_filter_string + " deg";

    string Entry_index_wave_time ="Plots/PbWO4/0811_100_ev/Angle_"+ entry_filter_string + "_deg/" + side_string + " SiPM " + title_string + " Wavelength and Time distribution for " + entry_filter_string + " deg.pdf";
    string wave_time = side_string + " SiPM " + title_string + " Wavelength and Time distribution for " + entry_filter_string + " deg";
    
    //Time plots with SiPMs and filter
    TCanvas *c_timecut = new TCanvas("c_time","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    
    if(max_cer_cut>max_scint_cut)
    {
     std::cout << "Plot Cerenkov cut first" << std::endl;
     gcertimecut[side_toggle+SiPM_number]->SetStats(0);
     gcertimecut[side_toggle+SiPM_number]->Draw();

     gscinttimecut[side_toggle+SiPM_number]->SetStats(0);
     gscinttimecut[side_toggle+SiPM_number]->Draw("same"); 

     gcertimecut[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
     gcertimecut[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Number of counts");
     gcertimecut[side_toggle+SiPM_number]->SetTitle(filter_time.c_str());
    }  
    else if(max_cer_cut<max_scint_cut)
    {
     std::cout << "Plot scintillation cut first" << std::endl;
     gscinttimecut[side_toggle+SiPM_number]->SetStats(0);
     gscinttimecut[side_toggle+SiPM_number]->Draw();

     gcertimecut[side_toggle+SiPM_number]->SetStats(0);
     gcertimecut[side_toggle+SiPM_number]->Draw("same");

     gscinttimecut[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
     gscinttimecut[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Number of counts");
     gscinttimecut[side_toggle+SiPM_number]->SetTitle(filter_time.c_str());
    } 
    
    gcertimecut[side_toggle+SiPM_number] -> SetLineColor(kGreen);
    gscinttimecut[side_toggle+SiPM_number] -> SetLineColor(kRed);
    gcertimecut[side_toggle+SiPM_number]->Add(gscinttimecut[side_toggle+SiPM_number]);
    gcertimecut[side_toggle+SiPM_number]->Draw();
    gcertimecut[side_toggle+SiPM_number]->SetStats(0);
    gcertimecut[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
    gcertimecut[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Total Number of counts");
    for(int k_t=0; k_t<1000; k_t++)
    {
      C_total_hist << gcertimecut[side_toggle+SiPM_number] ->GetBinContent(k_t+1) << ",";
    }
    C_total_hist << endl;
    c_timecut -> Print(Entry_index_filter_time_cut.c_str()); //Copy canvas to pdf
    c_timecut->Close();
    //End of 1D Time plots with SiPMs and filter
    
    
    
    //Time 1D plots without SiPM or filter (reaching the SiPMs)
    TCanvas *c_time = new TCanvas("c_time","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    /*
    if(max_cer>max_scint)
    {
     std::cout << "Plot Cerenkov first" << std::endl;
     gcertime[side_toggle+SiPM_number]->SetStats(0);
     gcertime[side_toggle+SiPM_number]->Draw();
     
     gscinttime[side_toggle+SiPM_number]->SetStats(0);
     gscinttime[side_toggle+SiPM_number]->Draw("same"); 
     gcertime[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
     gcertime[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Number of counts");
     gcertime[side_toggle+SiPM_number]->SetTitle(time.c_str());     
    }  
    else if(max_cer<max_scint)
    {
     std::cout << "Plot scintillation first" << std::endl;
     gscinttime[side_toggle+SiPM_number]->SetStats(0);
     gscinttime[side_toggle+SiPM_number]->Draw();

     gcertime[side_toggle+SiPM_number]->SetStats(0);
     gcertime[side_toggle+SiPM_number]->Draw("same");
     gscinttime[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
     gscinttime[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Number of counts");
     gscinttime[side_toggle+SiPM_number]->SetTitle(time.c_str());     
    } 
    */
    gcertime[side_toggle+SiPM_number] -> SetLineColor(kGreen);
    gscinttime[side_toggle+SiPM_number] -> SetLineColor(kRed);
        
    gcertime[side_toggle+SiPM_number] -> Add(gscinttime[side_toggle+SiPM_number]);
    gcertime[side_toggle+SiPM_number] -> Draw();
    gcertime[side_toggle+SiPM_number]->SetStats(0);
    gcertime[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
    gcertime[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Total Number of counts");

    c_time -> Print(Entry_index_time.c_str()); //Copy canvas to pdf
    c_time->Close();    
    //End of Time 1D plots without SiPM or filter (reaching the SiPMs)
    
    
    //2D wavelength and time plots with SiPM and filter
  
    TCanvas *c_wave_time_cut = new TCanvas("c_wave_time_cut","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    gscintwave_timecut[side_toggle+SiPM_number]->SetStats(0);
    gscintwave_timecut[side_toggle+SiPM_number]->Draw("colz");

    gcerwave_timecut[side_toggle+SiPM_number]->SetStats(0);
    gcerwave_timecut[side_toggle+SiPM_number]->Draw("colz same");
    gcerwave_timecut[side_toggle+SiPM_number]-> SetLineColor(kGreen);
    gscintwave_timecut[side_toggle+SiPM_number]-> SetLineColor(kRed);

    gscintwave_timecut[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
    gscintwave_timecut[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Wavelength (in nm)");
    gscintwave_timecut[side_toggle+SiPM_number]->GetZaxis()->SetTitle("Number of counts");    
    gscintwave_timecut[side_toggle+SiPM_number]->SetTitle(wave_time_cut.c_str());
    c_wave_time_cut -> Print(Entry_index_wave_time_cut.c_str()); //Copy canvas to pdf
    c_wave_time_cut->Close(); 
    
    //End of 2D wavelength and time plots with SiPM and filter
    
    //2D wavelength and time plots without SiPM and filter
  
    TCanvas *c_wave_time = new TCanvas("c_wave_time","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    gscintwave_time[side_toggle+SiPM_number]->SetStats(0);
    gscintwave_time[side_toggle+SiPM_number]->Draw("colz");

    gcerwave_time[side_toggle+SiPM_number]->SetStats(0);
    gcerwave_time[side_toggle+SiPM_number]->Draw("colz same");
    gcerwave_time[side_toggle+SiPM_number]-> SetLineColor(kGreen);
    gscintwave_time[side_toggle+SiPM_number]-> SetLineColor(kRed);

    gscintwave_time[side_toggle+SiPM_number]->GetXaxis()->SetTitle("Time (in ns)");
    gscintwave_time[side_toggle+SiPM_number]->GetYaxis()->SetTitle("Wavelength (in nm)");
    gscintwave_time[side_toggle+SiPM_number]->GetZaxis()->SetTitle("Number of counts");    
    gscintwave_time[side_toggle+SiPM_number]->SetTitle(wave_time.c_str());
    c_wave_time -> Print(Entry_index_wave_time.c_str()); //Copy canvas to pdf
    c_wave_time->Close();   
   
    //End of 2D wavelength and time plots without SiPM and filter
    
    //c_time -> BuildLegend();

    
    }
    }
    C_total_hist.close();

  
     //End of graphs for time distribution
}


