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
//const int ichan[nchan] = {289,256,294,292,295,293,296,298,297,299};
const int ichan[nchan] = {257,256,262,260,263,261,264,266,265,267}; //Simplified geometry
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

void Ana_track_90(int angle/*, const char* inputfilename*/) {


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
  std::vector<float> cer_angle[nchan+8],scint_angle[nchan+8],tot_angle[nchan+8];
  std::vector<float> cer_angle_err[nchan+8],scint_angle_err[nchan+8];
  float cerchan_angle[nchan+8], scintchan_angle[nchan+8];
  
  TH1F *hcEcalE0;
  TH1F *hcEcalncer[nchan]; //Cerenkov Generated and also for all the SiPMs
  TH1F *hcEcalnscint[nchan]; //Scintillation Generated and also for all the SiPMs
  TH1F *hcEcalntot[nchan]; //Scintillation Generated and also for all the SiPMs
  
  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",10000,0.,100000); //Is this in MeV?
  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",100,0.,200); //Extra Zoomed in, is this in MeV?
  hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",2000,0.,2000); //Is this in MeV?, all events with cut applied
  for (int i=0;i<nchan;i++) //Although the range of the x axis on the histograms will be much smaller for the SiPM channels
  {   
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

  TH1F* hcer_y_cut[4];
  hcer_y_cut[0] = new TH1F("hcer_y_cut[0]","total number of cerenkov satisfying 1st cut",300000,0.,300000);
  hcer_y_cut[1] = new TH1F("hcer_y_cut[1]","total number of cerenkov satisfying 2nd cut",300000,0.,300000);
  hcer_y_cut[2] = new TH1F("hcer_y_cut[2]","total number of cerenkov satisfying 3rd cut",300000,0.,300000);
  hcer_y_cut[3] = new TH1F("hcer_y_cut[3]","total number of cerenkov satisfying 4th cut",300000,0.,300000);
  TH1F *hcer_y_neg = new TH1F("hcer_y_neg","total number of cerenkov bottom y face",80000,0.,80000);//Relatively less for smaller angles
  TH1F *hcer_x_pos_neg = new TH1F("hcer_x_pos_neg","total number of cerenkov perpendicular face",700000,0.,700000);
  TH1F *hcer_dir = new TH1F("hcer_dir","total number of cerenkov direct to grease",200000,0.,200000);
  TH1F *hcer_nt = new TH1F("hcer_nt","total number of cerenkov not transmitted",700000,0.,700000);

  C_S_SiPM.open("C_S_total_SiPMs_0924_100_PbF2.csv");

  //TFile* f = TFile::Open(Form("Root_files/Protons/PbF2/0924/out_0924_%i.root",angle));
  //TFile* f = TFile::Open(Form("Root_files/out_1031_%i_mu-.root",angle));
  TFile* f = TFile::Open(Form("out_0208_%i_b10.root",angle));
  TTree* t = (TTree*)f->Get("EVENT;1");
  t->Print();

  //hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",10000,0.,100000); //Is this in MeV?
  
  
  // loop over events
  TBranch* b_mc = t->GetBranch("MCParticles");
  TBranch* b_ecal = t->GetBranch("DRCNoSegment");
  int ihaha = b_mc->GetEntries();
  //num_evt= std::min(ihaha,num_evtsmax);
  //num_evt= 100;
  num_evt= 5;
  std::cout<<" doing "<<b_mc->GetName()<<std::endl;
  std::cout<<"num_evt gen loop is "<<num_evt<<std::endl;
  

std::cout<<std::endl;
  TH1F* angle_side[4][num_evt];

  int ncer_gen[num_evt];
  /*
  for(int j=0;j<4;j++)
  {
   for(int i=0;i<num_evt;i++)
   {
    std::string angle_title = "angle_side_" + std::to_string(j) + "_" + std::to_string(i);
    angle_side[j][i] = new TH1F(angle_title.c_str(),angle_title.c_str(),360,-180.,180.);  
   }
  }
  */

   for(int i=0;i<num_evt;i++)
   {
    angle_side[0][i] = new TH1F("Cut 1 LHS","Angular distribution for photons hitting the downstream surface of the crystal (z = -30 mm) wrt the negative z normal",360,-180.,180.);  
    angle_side[1][i] = new TH1F("Cut 1 RHS","Angular distribution for photons hitting the upstream surface of the crystal (z = 30 mm) wrt the positive z normal",360,-180.,180.);  
    angle_side[2][i] = new TH1F("Cut 2 LHS","Angular distribution for photons passing into the cookie, at the downstream crystal-cookie interface (z = -30 mm) wrt the negative z normal",360,-180.,180.);  
    angle_side[3][i] = new TH1F("Cut 2 RHS","Angular distribution for photons passing into the cookie, at the upstream crystal-cookie interface (z = 30 mm) wrt the positive z normal",360,-180.,180.);  

   }

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
      std::vector<float> ncerwavechan_avg[nchan];
      std::vector<float> nscintwavechan_avg[nchan];
      std::vector<float> ncerwavecutchan_avg[nchan]; //Cerenkov Photons above cutoff
      std::vector<float> nscintwavecutchan_avg[nchan]; //Scintillation photons below cutoff
      std::vector<float> number_of_bins_avg[nchan];
      float a = 2.0;
      int kink_cut;
      

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
     std::cout << "Event number " << ievt << std::endl;
      std::cout << "Size of ecalhits " << ecalhits->size() << std::endl;
      for(size_t i=0;i<ecalhits->size(); ++i) 
      {
	CalVision::DualCrystalCalorimeterHit* aecalhit =ecalhits->at(i);
	//	std::cout<<"       "<<i<<" energy "<<aecalhit->energyDeposit<<std::endl;
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
	//int ijchan=aecalhit->nbin;
 	//float binsize = (aecalhit->wavelenmax-aecalhit->wavelenmin)/ijchan; //Copied from SDAction
  //std::cout << "Bin size " << binsize << std::endl;
  hchan->Fill(aecalhit->cellID);


      // there is a better way to do this
	int jchan=aecalhit->cellID;
	int kchan=-1;
	for( int i=0;i<nchan;i++ ) {
	  if(ichan[i]==jchan) kchan=i; //comparing with the entries of ichan which is populated with the cellIDs 
	}
	if(kchan==-1)
  {
	  //std::cout<<"unknown hit channel is "<< aecalhit->cellID<<std::endl;
	} 
  else
  {
    //std::cout << "Size of Cerenkov photon tracks is " << aecalhit->ncer_step.size() << std::endl;
    if(kchan==0) //Only for crystal for now
    {
     hcEcalncer[kchan]->Fill(aecalhit->ncer_step.size());
     ncer_gen[ievt] = aecalhit->ncer_step.size();

     //size 4 for the 4 different cuts (downstream and upstream)
     bool prod_cut[4][aecalhit->ncer_step.size()];
     float angle_z[4][aecalhit->ncer_step.size()];

     //std::cout << "Event number " << ievt << std::endl;
     std::cout << "Size of gen Cerenkov photon tracks in crystal is " << aecalhit->ncer_step.size() << std::endl;
     double pi = 4*atan(1.0);
     double y_norm[3] = {0.,cos(angle*pi/180.0),sin(angle*pi/180.0)}; //Angle argument given in radians
     //std::cout << "x component of beam direction " << y_norm[0] << " y component of beam direction " << y_norm[1] << " z component of beam direction " << y_norm[2] << std::endl;
     int y_cut_pos = 0; //Reaching the top y surface at the first reflection (main one in display for 10 and 20 deg at least)
     int y_cut_neg = 0; //Reaching the bottom y surface (outside cone)
     int x_cut_pos_neg = 0; //Reaching the side faces (perpendicular to the display plane i.e. x direction)
     int i_nt = 0; //Not transmitted due to being less than transmission wavelength cutoff, or aborted after the first step
     int i_dir = 0; //First step reaching the silicone grease directly
     int num_cut[4];
     for(int i=0;i<4;i++){num_cut[i] = 0;}


    //For example, photons reaching the positive side and photons reaching the negative side are not mutually exclusive


    //Cut 1 LHS - Downstream crystal (z = -30 mm)    
     for(int j=0; j<aecalhit->ncer_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
     {
      prod_cut[0][j]=0; //Default
      angle_z[0][j]=0; //Default
      for(int i=0;i<aecalhit->ncer_step.at(j).size();i++)
      {
       //if(aecalhit->ncer_step.at(j).at(i).Sce_mat == "PbF2" && aecalhit->ncer_step.at(j).at(i).z_fin < 30.000001 && aecalhit->ncer_step.at(j).at(i).z_fin > 29.999999)
       if(aecalhit->ncer_step.at(j).at(i).Sce_mat == "PbF2" && aecalhit->ncer_step.at(j).at(i).z_fin > -30.000001 && aecalhit->ncer_step.at(j).at(i).z_fin < -29.999999)
      {
       prod_cut[0][j] = 1;
       //jth photon, ith step
       double cos_comp1 = (aecalhit->ncer_step.at(j).at(i).z_fin-aecalhit->ncer_step.at(j).at(i).z_in)/sqrt(pow((aecalhit->ncer_step.at(j).at(i).x_fin-aecalhit->ncer_step.at(j).at(i).x_in),2)+pow((aecalhit->ncer_step.at(j).at(i).y_fin-aecalhit->ncer_step.at(j).at(i).y_in),2)+pow((aecalhit->ncer_step.at(j).at(i).z_fin-aecalhit->ncer_step.at(j).at(i).z_in),2));
       angle_z[0][j] = acos(-cos_comp1)*180.0/pi;
       break;
      }
     }
    }
    
    //Cut 1 RHS - Upstream crystal (z = 30 mm)    
     for(int j=0; j<aecalhit->ncer_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
     {
      prod_cut[1][j]=0; //Default
      angle_z[1][j]=0; //Default
      for(int i=0;i<aecalhit->ncer_step.at(j).size();i++)
      {
       if(aecalhit->ncer_step.at(j).at(i).Sce_mat == "PbF2" && aecalhit->ncer_step.at(j).at(i).z_fin < 30.000001 && aecalhit->ncer_step.at(j).at(i).z_fin > 29.999999)
      {
       prod_cut[1][j] = 1;
       //jth photon, ith step
       double cos_comp2 = (aecalhit->ncer_step.at(j).at(i).z_fin-aecalhit->ncer_step.at(j).at(i).z_in)/sqrt(pow((aecalhit->ncer_step.at(j).at(i).x_fin-aecalhit->ncer_step.at(j).at(i).x_in),2)+pow((aecalhit->ncer_step.at(j).at(i).y_fin-aecalhit->ncer_step.at(j).at(i).y_in),2)+pow((aecalhit->ncer_step.at(j).at(i).z_fin-aecalhit->ncer_step.at(j).at(i).z_in),2));
       angle_z[1][j] = acos(cos_comp2)*180.0/pi;
       break;
      }
     }
    }

    //Cut 2 LHS - Downstream cookie (z = -31 mm) 
     for(int j=0; j<aecalhit->ncer_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
     {
      prod_cut[2][j]=0; //Default
      angle_z[2][j]=0; //Default

      for(int i=1;i<aecalhit->ncer_step.at(j).size();i++)
      //This excludes the step where photons are generated in the silicone gap, so that the 'previous step' is actually valid
      {
       //if(aecalhit->ncer_step.at(j).at(i).Sce_mat == "Silicone_gap" && aecalhit->ncer_step.at(j).at(i).z_fin < 31.000001 && aecalhit->ncer_step.at(j).at(i).z_fin > 30.999999)
       if(aecalhit->ncer_step.at(j).at(i).Sce_mat == "Silicone_gap" && aecalhit->ncer_step.at(j).at(i).z_fin > -31.000001 && aecalhit->ncer_step.at(j).at(i).z_fin < -30.999999)
      {
       prod_cut[2][j] = 1;
       //num_cut++;
       //Previous step inside crystal (just before TIR)
       double cos_comp3 = (aecalhit->ncer_step.at(j).at(i-1).z_fin-aecalhit->ncer_step.at(j).at(i-1).z_in)/sqrt(pow((aecalhit->ncer_step.at(j).at(i-1).x_fin-aecalhit->ncer_step.at(j).at(i-1).x_in),2)+pow((aecalhit->ncer_step.at(j).at(i-1).y_fin-aecalhit->ncer_step.at(j).at(i-1).y_in),2)+pow((aecalhit->ncer_step.at(j).at(i-1).z_fin-aecalhit->ncer_step.at(j).at(i-1).z_in),2));
       angle_z[2][j] = acos(-cos_comp3)*180.0/pi;
       break;
      }
     }
    }
        

    //Cut 2 RHS - Upstream cookie (z = 31 mm) 
     for(int j=0; j<aecalhit->ncer_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
     {
      prod_cut[3][j]=0; //Default
      angle_z[3][j]=0; //Default

      for(int i=1;i<aecalhit->ncer_step.at(j).size();i++)
      //This excludes the step where photons are generated in the silicone gap, so that the 'previous step' is actually valid
      {
       if(aecalhit->ncer_step.at(j).at(i).Sce_mat == "Silicone_gap" && aecalhit->ncer_step.at(j).at(i).z_fin < 31.000001 && aecalhit->ncer_step.at(j).at(i).z_fin > 30.999999)
      {
       prod_cut[3][j] = 1;
       //Previous step inside crystal (just before TIR)
       double cos_comp4 = (aecalhit->ncer_step.at(j).at(i-1).z_fin-aecalhit->ncer_step.at(j).at(i-1).z_in)/sqrt(pow((aecalhit->ncer_step.at(j).at(i-1).x_fin-aecalhit->ncer_step.at(j).at(i-1).x_in),2)+pow((aecalhit->ncer_step.at(j).at(i-1).y_fin-aecalhit->ncer_step.at(j).at(i-1).y_in),2)+pow((aecalhit->ncer_step.at(j).at(i-1).z_fin-aecalhit->ncer_step.at(j).at(i-1).z_in),2));
       angle_z[3][j] = acos(cos_comp4)*180.0/pi;
       break;
      }
     }
    }
    
     for(int i=0;i<aecalhit->ncer_step.size();i++)
     {
      if(aecalhit->ncer_step.at(i).size() == 1) //Only the gen step, not transmitted
      {
        i_nt++;
      }
      if(aecalhit->ncer_step.at(i).at(0).x_in == aecalhit->ncer_step.at(i).at(0).x_fin && aecalhit->ncer_step.at(i).at(0).y_in == aecalhit->ncer_step.at(i).at(0).y_fin && aecalhit->ncer_step.at(i).at(0).z_in == aecalhit->ncer_step.at(i).at(0).z_fin){}
      else //if transmitted
      {
       for(int j=0;j<4;j++)
       {
        if(prod_cut[j][i]==1)
        {
        num_cut[j]++;
        angle_side[j][ievt]->Fill(angle_z[j][i]);
        }
       }
      }
     }
     
      std::cout << "Number of photons reaching the crystal on the downstream side " << num_cut[0] << std::endl;
      std::cout << "Number of photons reaching the grease on the downstream side " << num_cut[2] << std::endl;
    
      std::cout << "Number of photons reaching the crystal on the upstream side " << num_cut[1] << std::endl;
      std::cout << "Number of photons reaching the grease on the upstream side " << num_cut[3] << std::endl;
      
      
      for(int i=0;i<4;i++)
      {
       hcer_y_cut[i]->Fill(num_cut[i]);
      }

        //angle_side->Draw();    
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

    }  //end loop over events
        
       //hcEcalncer[0]->Draw();   
       ///*
       for(int i=0;i<num_evt;i++)
       {
        int numbins = angle_side[0][i]->GetXaxis()->GetNbins(); //same bins for all 4 graphs
        for(int j=0;j<numbins;j++)
        {
        for(int k=0;k<4;k++)
        {
         angle_side[k][i]->SetBinContent(j+1,(angle_side[k][i]->GetBinContent(j+1))/ncer_gen[i]);
        }
        }
       }
       //*/

       ///*
       for(int i=1;i<num_evt;i++)
       {
        for(int k=0;k<4;k++)
        {
         angle_side[k][0]->Add(angle_side[k][i]);
        }
       }
       //*/
       //angle_side[2][0]->Draw();

      TCanvas *c1 = new TCanvas("c1","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
      c1->Divide(2,2); //16 in 1 canvas


        for(int k=0;k<4;k++)
        {
         c1->cd(k+1);
         angle_side[k][0]->Draw();

        }

       /*for(int i=1;i<num_evt;i++)
       {
        angle_side[i]->Draw("same");
       }*/
    /*   
    stringstream j_s_1;
    string entry_filter_string;
    j_s_1 << angle;
    j_s_1 >> entry_filter_string;
    string y_pos_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov reflecting first at top y face for " + entry_filter_string + " deg.pdf";
    string y_2_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov satisfying 2nd cut for " + entry_filter_string + " deg.pdf";
    string y_3_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov satisfying 3rd cut for " + entry_filter_string + " deg.pdf";

    string y_neg_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov reflecting first at bottom y face for " + entry_filter_string + " deg.pdf";
    string x_pos_neg_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov reflecting first at x faces for " + entry_filter_string + " deg.pdf";
    string num_dir_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov going directly to grease " + entry_filter_string + " deg.pdf";
    string num_nt_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Number of cerenkov not transmitted " + entry_filter_string + " deg.pdf";

    string y_angle_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Angular distribution for cerenkov reflecting first at top y face for " + entry_filter_string + " deg.pdf";
    string y_angle_2_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Angular distribution for cerenkov satisfying 2nd cut for " + entry_filter_string + " deg.pdf";
    string y_angle_3_pdf ="Plots/PbF2/0926/Angle_"+ entry_filter_string + "_deg/" + " Angular distribution for cerenkov satisfying 3rd cut for " + entry_filter_string + " deg.pdf";

    int binmax_1 = hcer_y_pos->GetMaximumBin();
    double x_1 = hcer_y_pos->GetXaxis()->GetBinCenter(binmax_1);
    std::cout << "MPV of Number of cerenkov reflecting first at top y face " << x_1 << std::endl;

    int binmax_2 = hcer_y_cut_2->GetMaximumBin();
    double x_2 = hcer_y_cut_2->GetXaxis()->GetBinCenter(binmax_2);
    std::cout << "MPV of Number of cerenkov satisfying 2nd cut " << x_2 << std::endl;

    int binmax_3 = hcer_y_cut_3->GetMaximumBin();
    double x_3 = hcer_y_cut_3->GetXaxis()->GetBinCenter(binmax_3);
    std::cout << "MPV of Number of cerenkov satisfying 3rd cut " << x_3 << std::endl;

    int binmax_4 = hcer_y_neg->GetMaximumBin();
    double x_4 = hcer_y_neg->GetXaxis()->GetBinCenter(binmax_4);
    std::cout << "MPV of Number of cerenkov reflecting first at bottom y face " << x_4 << std::endl;

    int binmax_5 = hcer_x_pos_neg->GetMaximumBin();
    double x_5 = hcer_x_pos_neg->GetXaxis()->GetBinCenter(binmax_5);
    std::cout << "MPV of Number of cerenkov reflecting first at x faces " << x_5 << std::endl;

    int binmax_6 = hcer_dir->GetMaximumBin();
    double x_6 = hcer_dir->GetXaxis()->GetBinCenter(binmax_6);
    std::cout << "MPV of Number of cerenkov going directly to grease " << x_6 << std::endl;

    int binmax_7 = hcer_nt->GetMaximumBin();
    double x_7 = hcer_nt->GetXaxis()->GetBinCenter(binmax_7);
    std::cout << "MPV of Number of cerenkov not transmitted " << x_7 << std::endl;

    TCanvas *c1 = new TCanvas("c1","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_y_pos->Draw();
    c1->SetLogx();
    c1 -> Print(y_pos_pdf.c_str()); //Copy canvas to pdf
    c1->Close();

    TCanvas *c2 = new TCanvas("c2","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_y_cut_2->Draw();
    c2->SetLogx();
    c2 -> Print(y_2_pdf.c_str()); //Copy canvas to pdf
    c2->Close();

    TCanvas *c3 = new TCanvas("c3","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_y_cut_3->Draw();
    c3->SetLogx();
    c3 -> Print(y_3_pdf.c_str()); //Copy canvas to pdf
    c3->Close();

    TCanvas *c4 = new TCanvas("c4","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_y_neg->Draw();
    c4->SetLogx();
    c4 -> Print(y_neg_pdf.c_str()); //Copy canvas to pdf
    c4->Close();

    TCanvas *c5 = new TCanvas("c5","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_x_pos_neg->Draw();
    c5->SetLogx();
    c5 -> Print(x_pos_neg_pdf.c_str()); //Copy canvas to pdf
    c5->Close();

    TCanvas *c6 = new TCanvas("c6","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_dir->Draw();
    c6->SetLogx();
    c6 -> Print(num_dir_pdf.c_str()); //Copy canvas to pdf
    c6->Close();

    TCanvas *c7 = new TCanvas("c7","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    hcer_nt->Draw();
    c7->SetLogx();
    c7 -> Print(num_nt_pdf.c_str()); //Copy canvas to pdf
    c7->Close();

    TCanvas *c8 = new TCanvas("c8","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    angle_side[0]->Draw();
    c8 -> Print(y_angle_pdf.c_str()); //Copy canvas to pdf
    c8->Close();

    TCanvas *c9 = new TCanvas("c9","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    angle_side_2[0]->Draw();
    c9 -> Print(y_angle_2_pdf.c_str()); //Copy canvas to pdf
    c9->Close();

    TCanvas *c10 = new TCanvas("c10","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    angle_side_3[0]->Draw();
    c10 -> Print(y_angle_3_pdf.c_str()); //Copy canvas to pdf
    c10->Close();
    */
}


