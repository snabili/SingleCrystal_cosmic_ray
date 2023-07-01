
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
const int ichan[nchan] = {289,256,292,293,294,295,296,297,298,299};
std::string namechan[nchan] = {"crystal","Air","left SiPM 1","left SiPM 2","left SiPM 3","left SiPM 4","right SiPM 1","right SiPM 2","right SiPM 3","right SiPM 4"};
std::ofstream C_gen, S_gen;

double UV_sipm_QE_x[89] = {282.6086957, 288.0434783, 290.2173913, 291.3043478, 292.3913043, 293.4782609, 294.5652174, 295.6521739, 296.7391304, 297.826087, 298.9130435, 301.0869565, 303.2608696, 304.3478261, 307.6086957, 309.7826087, 314.1304348, 317.3913043, 321.7391304, 329.3478261, 335.8695652, 343.4782609, 350., 358.6956522, 367.3913043, 373.9130435, 378.2608696, 383.6956522, 388.0434783, 394.5652174, 402.173913, 408.6956522, 417.3913043, 428.2608696, 440.2173913, 452.173913, 465.2173913, 475., 482.6086957, 489.1304348, 494.5652174, 500., 505.4347826, 510.8695652, 517.3913043, 522.826087, 529.3478261, 534.7826087, 542.3913043, 548.9130435, 555.4347826, 561.9565217, 568.4782609, 577.173913, 583.6956522, 590.2173913, 596.7391304, 603.2608696, 610.8695652, 617.3913043, 623.9130435, 631.5217391, 638.0434783, 644.5652174, 652.173913, 659.7826087, 667.3913043, 676.0869565, 685.8695652, 694.5652174, 703.2608696, 713.0434783, 721.7391304, 731.5217391, 741.3043478, 753.2608696, 764.1304348, 775., 785.8695652, 797.826087, 808.6956522, 819.5652174, 831.5217391, 844.5652174, 855.4347826, 866.3043478, 877.173913, 889.1304348, 898.9130435};

double UV_sipm_QE_y[89] = {0.02983683, 0.041958042, 0.068997669, 0.106293706, 0.131468531, 0.158508159, 0.185547786, 0.211655012, 0.225641026, 0.240559441, 0.255477855, 0.271328671, 0.287179487, 0.299300699, 0.30955711, 0.321678322, 0.331934732, 0.342191142, 0.353379953, 0.363636364, 0.374825175, 0.385081585, 0.393473193, 0.399067599, 0.407459207, 0.418648019, 0.431701632, 0.443822844, 0.455011655, 0.466200466, 0.476456876, 0.485780886, 0.494172494, 0.502564103, 0.508158508, 0.509090909, 0.506293706, 0.498834499, 0.48951049, 0.479254079, 0.468997669, 0.458741259, 0.446620047, 0.437296037, 0.427039627, 0.416783217, 0.405594406, 0.395337995, 0.384149184, 0.373892774, 0.363636364, 0.352447552, 0.342191142, 0.331002331, 0.320745921, 0.31048951, 0.301165501, 0.290909091, 0.280652681, 0.271328671, 0.261072261, 0.251748252, 0.242424242, 0.233100233, 0.222843823, 0.214452214, 0.204195804, 0.193939394, 0.185547786, 0.176223776, 0.167832168, 0.158508159, 0.151048951, 0.142657343, 0.134265734, 0.125874126, 0.118414918, 0.11002331, 0.102564103, 0.095104895, 0.087645688, 0.082051282, 0.074592075, 0.068065268, 0.061538462, 0.055944056, 0.049417249, 0.044755245, 0.038694639};

double RGB_sipm_QE_x[89] = {282.6086957, 288.0434783, 290.2173913, 291.3043478, 292.3913043, 293.4782609, 294.5652174, 295.6521739, 296.7391304, 297.826087, 298.9130435, 301.0869565, 303.2608696, 304.3478261, 307.6086957, 309.7826087, 314.1304348, 317.3913043, 321.7391304, 329.3478261, 335.8695652, 343.4782609, 350., 358.6956522, 367.3913043, 373.9130435, 378.2608696, 383.6956522, 388.0434783, 394.5652174, 402.173913, 408.6956522, 417.3913043, 428.2608696, 440.2173913, 452.173913, 465.2173913, 475., 482.6086957, 489.1304348, 494.5652174, 500., 505.4347826, 510.8695652, 517.3913043, 522.826087, 529.3478261, 534.7826087, 542.3913043, 548.9130435, 555.4347826, 561.9565217, 568.4782609, 577.173913, 583.6956522, 590.2173913, 596.7391304, 603.2608696, 610.8695652, 617.3913043, 623.9130435, 631.5217391, 638.0434783, 644.5652174, 652.173913, 659.7826087, 667.3913043, 676.0869565, 685.8695652, 694.5652174, 703.2608696, 713.0434783, 721.7391304, 731.5217391, 741.3043478, 753.2608696, 764.1304348, 775., 785.8695652, 797.826087, 808.6956522, 819.5652174, 831.5217391, 844.5652174, 855.4347826, 866.3043478, 877.173913, 889.1304348, 898.9130435};

double RGB_sipm_QE_y[89] = {0.02983683, 0.041958042, 0.068997669, 0.106293706, 0.131468531, 0.158508159, 0.185547786, 0.211655012, 0.225641026, 0.240559441, 0.255477855, 0.271328671, 0.287179487, 0.299300699, 0.30955711, 0.321678322, 0.331934732, 0.342191142, 0.353379953, 0.363636364, 0.374825175, 0.385081585, 0.393473193, 0.399067599, 0.407459207, 0.418648019, 0.431701632, 0.443822844, 0.455011655, 0.466200466, 0.476456876, 0.485780886, 0.494172494, 0.502564103, 0.508158508, 0.509090909, 0.506293706, 0.498834499, 0.48951049, 0.479254079, 0.468997669, 0.458741259, 0.446620047, 0.437296037, 0.427039627, 0.416783217, 0.405594406, 0.395337995, 0.384149184, 0.373892774, 0.363636364, 0.352447552, 0.342191142, 0.331002331, 0.320745921, 0.31048951, 0.301165501, 0.290909091, 0.280652681, 0.271328671, 0.261072261, 0.251748252, 0.242424242, 0.233100233, 0.222843823, 0.214452214, 0.204195804, 0.193939394, 0.185547786, 0.176223776, 0.167832168, 0.158508159, 0.151048951, 0.142657343, 0.134265734, 0.125874126, 0.118414918, 0.11002331, 0.102564103, 0.095104895, 0.087645688, 0.082051282, 0.074592075, 0.068065268, 0.061538462, 0.055944056, 0.049417249, 0.044755245, 0.038694639};

//Once we get a proper filter with non trivial wavelength dependence it will probably have to be put here
double UV_filter_x[92] = {300.0, 310.0, 320.0, 330.0, 340.0, 350.0, 360.0, 370.0, 380.0, 390.0, 400.0, 410.0, 420.0, 430.0, 440.0, 450.0, 460.0, 470.0, 480.0, 490.0, 500.0, 510.0, 520.0, 530.0, 540.0, 550.0, 560.0, 570.0, 580.0, 590.0, 600.0, 610.0, 620.0, 630.0, 640.0, 650.0, 660.0, 670.0, 680.0, 690.0, 700.0, 710.0, 720.0, 730.0, 740.0, 750.0, 760.0, 770.0, 780.0, 790.0, 800.0, 810.0, 820.0, 830.0, 840.0, 850.0, 860.0, 870.0, 880.0, 890.0, 900.0, 910.0, 920.0, 930.0, 940.0, 950.0, 960.0, 970.0, 980.0, 990.0, 1000.0, 1010.0, 1020.0, 1030.0, 1040.0, 1050.0, 1060.0, 1070.0, 1080.0, 1090.0, 1100.0, 1110.0, 1120.0, 1130.0, 1140.0, 1150.0, 1160.0, 1170.0, 1180.0, 1190.0, 1200.0, 1250.0};

/*double UV_filter_y[92] = {0.88, 0.91, 0.9200, 0.9260, 0.9210, 0.9060, 0.8660, 0.7560, 0.4820, 0.1200, 0.003999, 0.00001047, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0003631, 0.008128, 0.05000, 0.1380, 0.2220, 0.2780, 0.2830, 0.2400, 0.1850, 0.1360, 0.09700, 0.06700, 0.04700, 0.03300, 0.02400, 0.01800, 0.01382, 0.01088, 0.009121, 0.007965, 0.007014, 0.006255, 0.005892, 0.005834, 0.005948, 0.006114, 0.006368, 0.007000, 0.008090, 0.009390, 0.01100, 0.01300, 0.01520, 0.01825, 0.02132, 0.02498, 0.02809, 0.03263, 0.03673, 0.04100, 0.04375, 0.04599, 0.04800, 0.04828, 0.04897, 0.04608, 0.04300, 0.03948, 0.03666, 0.03325, 0.02970, 0.02691, 0.02354, 0.02064, 0.01775, 0.008800};*/

double UV_filter_y[92] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

/*double GG_filter_x[92] = {300.0, 310.0, 320.0, 330.0, 340.0, 350.0, 360.0, 370.0, 380.0, 390.0, 400.0, 410.0, 420.0, 430.0, 440.0, 450.0, 460.0, 470.0, 480.0, 490.0, 500.0, 510.0, 520.0, 530.0, 540.0, 550.0, 560.0, 570.0, 580.0, 590.0, 600.0, 610.0, 620.0, 630.0, 640.0, 650.0, 660.0, 670.0, 680.0, 690.0, 700.0, 710.0, 720.0, 730.0, 740.0, 750.0, 760.0, 770.0, 780.0, 790.0, 800.0, 810.0, 820.0, 830.0, 840.0, 850.0, 860.0, 870.0, 880.0, 890.0, 900.0, 910.0, 920.0, 930.0, 940.0, 950.0, 960.0, 970.0, 980.0, 990.0, 1000.0, 1010.0, 1020.0, 1030.0, 1040.0, 1050.0, 1060.0, 1070.0, 1080.0, 1090.0, 1100.0, 1110.0, 1120.0, 1130.0, 1140.0, 1150.0, 1160.0, 1170.0, 1180.0, 1190.0, 1200.0, 1250.0};*/

/*double GG_filter_y[92] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00007048, 0.06112, 0.4792, 0.7703, 0.8551, 0.8849, 0.9032, 0.9176, 0.9300, 0.9409, 0.9500, 0.9578, 0.9645, 0.9703, 0.9747, 0.9781, 0.9809, 0.9829, 0.9843, 0.9852, 0.9857, 0.9858, 0.9856, 0.9852, 0.9847, 0.9841, 0.9834, 0.9825, 0.9814, 0.9803, 0.9792, 0.9780, 0.9767, 0.9754, 0.9740, 0.9724, 0.9706, 0.9691, 0.9676, 0.9662, 0.9649, 0.9635, 0.9622, 0.9609, 0.9596, 0.9585, 0.9574, 0.9563, 0.9552, 0.9541, 0.9531, 0.9523, 0.9517, 0.9512, 0.9507, 0.9503, 0.9499, 0.9495, 0.9491, 0.9488, 0.9484, 0.9481, 0.9478, 0.9475, 0.9472, 0.9470, 0.9468, 0.9467, 0.9466, 0.9465, 0.9465, 0.9465, 0.9465, 0.9465, 0.9466, 0.9467, 0.9468, 0.9469, 0.9470, 0.9472, 0.9474, 0.9484};*/ // This one is for GG420

/*double GG_filter_y[92] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01043, 0.2606, 0.7129, 0.9022, 0.9523, 0.9691, 0.9773, 0.9819, 0.9850, 0.9866, 0.9877, 0.9882, 0.9881, 0.9876, 0.9872, 0.9864, 0.9857, 0.9850, 0.9842, 0.9833, 0.9822, 0.9811, 0.9799, 0.9783, 0.9769, 0.9754, 0.9739, 0.9722, 0.9704, 0.9686, 0.9667, 0.9649, 0.9632, 0.9616, 0.9600, 0.9583, 0.9568, 0.9554, 0.9541, 0.9529, 0.9516, 0.9504, 0.9492, 0.9482, 0.9474, 0.9468, 0.9461, 0.9454, 0.9449, 0.9443, 0.9438, 0.9434, 0.9429, 0.9424, 0.9420, 0.9416, 0.9412, 0.9409, 0.9407, 0.9406, 0.9405, 0.9404, 0.9404, 0.9404, 0.9404, 0.9404, 0.9404, 0.9405, 0.9406, 0.9407, 0.9408, 0.9409, 0.9411, 0.9413, 0.9415, 0.9430};*/ //This one is for GG475 which is the one being used

double GG_filter_x[122] = {309.0140845, 322.5352113, 338.3098592, 352.9577465, 365.3521127, 380., 392.3943662, 402.5352113, 412.6760563, 426.1971831, 438.5915493, 449.8591549, 463.3802817, 478.028169, 489.2957746, 502.8169014, 511.8309859, 524.2253521, 536.6197183, 549.0140845, 562.5352113, 572.6760563, 579.4366197, 582.8169014, 585.0704225, 586.1971831, 587.3239437, 588.4507042, 589.5774648, 590.7042254, 591.8309859, 592.9577465, 594.084507, 595.2112676, 596.3380282, 597.4647887, 598.5915493, 599.7183099, 600.8450704, 601.971831, 603.0985915, 604.2253521, 605.3521127, 606.4788732, 607.6056338, 608.7323944, 609.8591549, 610.9859155, 612.1126761, 613.2394366, 614.3661972, 615.4929577, 616.6197183, 617.7464789, 620., 622.2535211, 624.5070423, 627.8873239, 632.3943662, 639.1549296, 647.0422535, 656.056338, 665.0704225, 674.084507, 681.971831, 692.1126761, 698.8732394, 709.0140845, 715.7746479, 723.6619718, 730.4225352, 738.3098592, 745.0704225, 751.8309859, 757.4647887, 764.2253521, 772.1126761, 781.1267606, 789.0140845, 798.028169, 807.0422535, 814.9295775, 822.8169014, 831.8309859, 838.5915493, 849.8591549, 858.8732394, 867.8873239, 879.1549296, 887.0422535, 897.1830986, 906.1971831, 916.3380282, 926.4788732, 934.3661972, 943.3802817, 952.3943662, 961.4084507, 971.5492958, 981.6901408, 989.5774648, 998.5915493, 1007.605634, 1017.746479, 1026.760563, 1038.028169, 1047.042254, 1057.183099, 1067.323944, 1078.591549, 1087.605634, 1096.619718, 1106.760563, 1116.901408, 1128.169014, 1140.56338, 1150.704225, 1161.971831, 1172.112676, 1181.126761, 1190.140845, 1196.901408}; //R60 filter

double GG_filter_y[122] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.009057971, 0.018115942, 0.028985507, 0.041666667, 0.059782609, 0.076086957, 0.112318841, 0.141304348, 0.15942029, 0.177536232, 0.219202899, 0.260869565, 0.300724638, 0.365942029, 0.405797101, 0.445652174, 0.505434783, 0.543478261, 0.60326087, 0.625, 0.661231884, 0.69384058, 0.733695652, 0.773550725, 0.788043478, 0.80615942, 0.820652174, 0.835144928, 0.849637681, 0.865942029, 0.880434783, 0.894927536, 0.911231884, 0.925724638, 0.942028986, 0.951086957, 0.963768116, 0.971014493, 0.976449275, 0.980072464, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.983695652, 0.985507246, 0.985507246, 0.985507246, 0.985507246, 0.985507246, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.987318841, 0.989130435, 0.989130435, 0.989130435, 0.989130435, 0.987318841, 0.989130435, 0.989130435}; //R60 filter

void Ana_loop(/*int num_evtsmax, const char* inputfilename*/) {


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
  //TH1F *hcEcalncer = new TH1F("hcEcalncer","total number of cerenkov",100,0.,10000);
  //TH1F *hcEcalncer0 = new TH1F("hcEcalncer0","total number of cerenkov chan 1",100,0.,200000);
  //TH1F *hcEcalnscint0 = new TH1F("hcEcalnscint0","total number of scintillation chan 1",100,0.,2000000);
  
  //TH1F *hcEcalncer1 = new TH1F("hcEcalncer1","total number of cerenkov chan 2",100,0.,10000);
  //TH1F *hcEcalncer2 = new TH1F("hcEcalncer2","total number of cerenkov chan 3",100,0.,10000);
  //TH1F *hcEcalncer3 = new TH1F("hcEcalncer3","total number of cerenkov chan 4",100,0.,10000);
  //TH1F *hccerwave = new TH1F("hccerwave","wavelength distribution of cerenkov chan 1",100,0.,10000);
  //TH1F *hcscintwave = new TH1F("hcscintwave","wavelength distribution of scintillation chan 1",100,0.,10000);
  
  //TH1F *hcEcalE0 = new TH1F("hcEcalE0","energy chan 0",100,0.,10000); 
  //Instead of this define a 1D array of histograms, one for each angle
  
  TH1F *hcEcalE1 = new TH1F("hcEcalE1","energy chan 1",100,0.,10000);
  TH1F *hcEcalE2 = new TH1F("hcEcalE2","energy chan 2",100,0.,10000);
  TH1F *hcEcalE3 = new TH1F("hcEcalE3","energy chan 3",100,0.,10000);

  // open data and output file for histograms

  //  const char* inputfilename="/data/users/eno/dd4hep/DD4hep/DDDetectors/compact/testSid.root";
  const char* outputfilename="hist.root";
  float esumchan_avg[nchan], ncerchan_avg[nchan], nscintchan_avg[nchan];
  int angle_pt, entry_index;  

  // get Tree
  //  TFile *f = new TFile(inputfilename);
  //f->Print();
  GenParts* pgenparts = new GenParts();
  CalHits* pcalhits = new CalHits();
  int num_evt,nbyte;
  //int initial_angle_pt = -60, final_angle_pt = 55; //Limits of angle for loop
  //int initial_angle_pt = -85, final_angle_pt = -60; //Limits of angle for loop
  //int angle_spacing = 5;
  //int n_entries = ((final_angle_pt - initial_angle_pt)/angle_spacing) + 1;
  
  //int n_entries = 28; //Depends on the number of the root files that are available and have not been made zombies
  //std::vector<int> angle_values{-85,-80,-75,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,65,70,75,80,85}; //PbF2
  std::vector<float> angle_values{-85.0,-80.0,-60.0,-55.0,-50.0,-45.0,-40.0,-35.0,-30.0,-25.0,-20.0,-15.0,-10.0,-5.0,0.0,5.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,50.0,55.0,65.0,75.0,80.0}; //PbWO4
  //std::vector<float> angle_values{-85,-80,-75,-70,-65,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,10,15,20,25,30,35,40,45,50,55,60,75,80,85}; //PbF2
  //std::vector<float> angle_values{-85,-80}; //PbF2
  //float cer_angle[angle_values.size()][nchan+8], scint_angle[angle_values.size()][nchan+8], esum_angle[angle_values.size()][nchan+8]; //Fill the average values for each angle here before closing the first loop
  std::vector<float> cer_angle[nchan+8],scint_angle[nchan+8];
  std::vector<float> cer_angle_err[nchan+8],scint_angle_err[nchan+8];
  float cerchan_angle[nchan+8], scintchan_angle[nchan+8];
  
  TH1F *hcEcalE0[angle_values.size()];
  TH1F *hcEcalncer[nchan][angle_values.size()]; //Cerenkov Generated and also for all the SiPMs
  TH1F *hcEcalnscint[nchan][angle_values.size()]; //Scintillation Generated and also for all the SiPMs
  
  
 for(entry_index=0;entry_index<angle_values.size();entry_index++) //Histogram initialization loop - might have to put angle wise graphs for wavelength distribution here too
 {  
  //hcEcalE0[entry_index] = new TH1F("hcEcalE0[entry_index]","energy chan 0",10000,0.,100000); //Is this in MeV?
  //hcEcalE0[entry_index] = new TH1F("hcEcalE0[entry_index]","energy chan 0",100,0.,200); //Extra Zoomed in, is this in MeV?
  hcEcalE0[entry_index] = new TH1F("hcEcalE0[entry_index]","energy chan 0",2000,0.,2000); //Is this in MeV?, all events with cut applied
  
  for (int i=0;i<nchan;i++) //Although the range of the x axis on the histograms will be much smaller for the SiPM channels
  {
   if(i==0)
   {
   //hcEcalncer[i][entry_index] = new TH1F("hcEcalncer[i][entry_index]","total number of cerenkov chan 1",100,0.,200000);
   //hcEcalnscint[i][entry_index] = new TH1F("hcEcalnscint[i][entry_index]","total number of scintillation chan 1",100,0.,2000000);
   hcEcalncer[i][entry_index] = new TH1F("hcEcalncer[i][entry_index]","total number of cerenkov chan 1",500,0.,20000);
   hcEcalnscint[i][entry_index] = new TH1F("hcEcalnscint[i][entry_index]","total number of scintillation chan 1",500,0.,200000);
   }
   else
   {
   hcEcalncer[i][entry_index] = new TH1F("hcEcalncer[i][entry_index]","total number of cerenkov chan 1",500,0.,2000);
   hcEcalnscint[i][entry_index] = new TH1F("hcEcalnscint[i][entry_index]","total number of scintillation chan 1",500,0.,20000);
   }   
  }
 } 
 
 //for(angle_pt = initial_angle_pt; angle_pt <= final_angle_pt; angle_pt+=angle_spacing)
 //for(angle_pt = -15; angle_pt <= 65; angle_pt+=10)
 for(entry_index=0;entry_index<angle_values.size();entry_index++)
 {
  //int entry_index = (angle_pt - initial_angle_pt)/angle_spacing; //For cer_angle and scint_angle for filling the tree
  angle_pt = angle_values.at(entry_index);
  
  TFile* f = TFile::Open(Form("Root_files/Protons/PbWO4/out_0614_%i.root",angle_pt));
  //TFile* f = TFile::Open(Form("Root_files/Protons/PbWO4/out_0611_%i.root",angle_pt)); //Actually the ones for PbF2 crystal
  //TFile* f = TFile::Open(Form("Root_files/Protons/PbF2/out_0626_1000_%i.root",angle_pt)); //Actually the ones for PbF2 crystal
  //TFile* f = TFile::Open(Form("Root_files/PbWO4/out_%i_0330.root",angle_pt)); //Old files possibly having muon data
  TTree* t = (TTree*)f->Get("EVENT;1");
  t->Print();

  //hcEcalE0[entry_index] = new TH1F("hcEcalE0[entry_index]","energy chan 0",10000,0.,100000); //Is this in MeV?
  
  
  // loop over events
  TBranch* b_mc = t->GetBranch("MCParticles");
  TBranch* b_ecal = t->GetBranch("DRCNoSegment");
  int ihaha = b_mc->GetEntries();
  //num_evt= std::min(ihaha,num_evtsmax);
  num_evt= 100;
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
      for(int i=0;i<nchan;i++)
      {
      esumchan_avg[i]=0.;
      ncerchan_avg[i]=0.;
      nscintchan_avg[i]=0.;
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
      /*std::vector<float> ncertimechan_avg[nchan];
      std::vector<float> nscinttimechan_avg[nchan];   
      std::vector<float> number_of_bins_time_avg[nchan];*/

      std::vector<float> filter[nchan];
      std::vector<float> QE[nchan];
      //Defined for all channels including the crystal and the air, of course it is for convenience but does not make much physical sense, so all the elements of those two channels will be set to 1 for multiplying i.e. no action

    int SCEPRINT2=10;
    int ievt_min = 0;
    int icount = 0;
    C_gen.open("Generated_Cerenkov_photons.txt"); //Opening this before the event loop
    S_gen.open("Generated_Scintillation_photons.txt"); //Opening this before the event loop
    
    for(int ievt=0;ievt<num_evt; ++ievt) {
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
      float esumchan[nchan]={0.,0.,0.,0.};
      int ncerchan[nchan]={0,0,0,0};
      int nscintchan[nchan]={0,0,0,0};
      
      //int ncercutchan[nchan]={0,0,0,0}; //Cerenkov Photons above cutoff
      //int nscintcutchan[nchan]={0,0,0,0}; //Scintillation photons below cutoff

      int ncertot=0;
      int nscinttot=0;
      int SCEPRINT=10;
      std::vector<int> ncerwavechan[nchan];
      std::vector<int> nscintwavechan[nchan];
      std::vector<int> ncerwavecutchan[nchan]; //Cerenkov Photons above cutoff
      std::vector<int> nscintwavecutchan[nchan]; //Scintillation photons below cutoff      
      std::vector<float> number_of_bins[nchan];
      
      /*std::vector<int> ncertimechan[nchan];
      std::vector<int> nscinttimechan[nchan];   
      std::vector<float> number_of_bins_time[nchan];*/

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
  /*int ijchan_t=aecalhit->nbin_t;
  float binsize_t = (aecalhit->timemax-aecalhit->timemin)/ijchan_t; //Copied from SDAction*/
  float kink_wavelength = 575;
  kink_cut=(kink_wavelength-aecalhit->wavelenmin)/binsize;
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
	for( int i=0;i<nchan;i++ ) {
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
     ncerwavechan[kchan].push_back((aecalhit->ncerwave)[j]);
     nscintwavechan[kchan].push_back((aecalhit->nscintwave)[j]);
     bin_wavelength= j*binsize + aecalhit->wavelenmin;
     number_of_bins[kchan].push_back(bin_wavelength); //lower wavelength of the j th bin
    }    
    
    /*for (int j_t=0; j_t<ijchan_t;j_t++) //time bin loop
    {
     ncertimechan[kchan].push_back((aecalhit->ncertime)[j_t]);
     nscinttimechan[kchan].push_back((aecalhit->nscinttime)[j_t]);
     number_of_bins_time[kchan].push_back(j_t*binsize_t + aecalhit->timemin); //lower time stamp of the j th bin
    }*/
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

      esum_avg+=esum;
      ncertot_avg+=ncertot;
      nscinttot_avg+=nscinttot;
      if(ncerchan[0]/*>0*/<20000 && ncerwavechan[0].size() > 0)
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
       //std::cout << ncertimechan[k].size() << std::endl;       
       /*for(int j=0;j<ncerwavechan[k].size();j++) //Right now all sizes are the same = binsize
       {
        if(ievt==0)
        {
         ncerwavechan_avg[k].push_back(ncerwavechan[k].at(j));
         nscintwavechan_avg[k].push_back(nscintwavechan[k].at(j));

         number_of_bins_avg[k].push_back(number_of_bins[k].at(j));
        }
        else if (ievt>0 &&ievt<num_evt) //i.e. the avg vector already has this size because this condition is necessarily occurring after the 'if' one above
        {
         ncerwavechan_avg[k].at(j) += ncerwavechan[k].at(j);
         nscintwavechan_avg[k].at(j) += nscintwavechan[k].at(j);        
         //Don't change the number_of_bins_avg here
        }
       }*/
       for(int j=0;j<ncerwavechan[k].size();j++) //Right now all sizes are the same = binsize
       {
         if(icount == 1) //Only the first instance of a non zero array
         {
         ncerwavechan_avg[k].push_back(ncerwavechan[k].at(j));
         nscintwavechan_avg[k].push_back(nscintwavechan[k].at(j));

         number_of_bins_avg[k].push_back(number_of_bins[k].at(j));

          ievt_min = ievt;
         }
         else if (ievt>ievt_min &&ievt<num_evt) //i.e. the avg vector already has this size because this condition is necessarily occurring after the 'if' one above
        {
         ncerwavechan_avg[k].at(j) += ncerwavechan[k].at(j);
         nscintwavechan_avg[k].at(j) += nscintwavechan[k].at(j);        
         //Don't change the number_of_bins_avg here
        }

        }
       //std::cout << "First event " << ievt_min << std::endl;
      }
     }
      else if(ncerwavechan[0].size() == 0)
      {
       C_gen << ncerchan[0] << endl;
       S_gen << nscintchan[0] << endl;       
      }
      
      //std::cout << sizeof(UV_sipm_QE_x) << ' ' << sizeof(RGB_sipm_QE_x) << std::endl;
      
      /*for(int k=0;k<nchan;k++)
       {
        for(int j=0;j<ncerwavechan[k].size();j++) //Right now all sizes are the same = binsize
        {
                 
        }
       }*/
      
       
      /*hcEcalE->Fill(esum/1000.);
      hcEcalncer->Fill(ncertot);
      hcEcalncer0->Fill(ncerchan[0]);
      hcEcalnscint0->Fill(nscintchan[0]);
      hcEcalncer1->Fill(ncerchan[1]);
      hcEcalncer2->Fill(ncerchan[2]);
      hcEcalncer3->Fill(ncerchan[3]);
      
      //hcEcalE0->Fill(esumchan[0]);
      hcEcalE1->Fill(esumchan[1]);
      hcEcalE2->Fill(esumchan[2]);
      hcEcalE3->Fill(esumchan[3]);*/
      
      if(ncerchan[0]/*>0*/<20000 && ncerwavechan[0].size() > 0)
      {
       hcEcalE0[entry_index]->Fill(esumchan[0]);
       for(int i=0;i<nchan;i++)
       {
        hcEcalncer[i][entry_index]->Fill(ncerchan[i]);
        hcEcalnscint[i][entry_index]->Fill(nscintchan[i]);
       }
      }
      
      //Fill without cut
      /*for(int i=0;i<nchan;i++)
      {
       hcEcalncer[i][entry_index]->Fill(ncerchan[i]);
       hcEcalnscint[i][entry_index]->Fill(nscintchan[i]);
      }*/
    }  //end loop over events
    
    C_gen.close();
    S_gen.close();    
    std::cout << "Number of non zero events: " << icount << std::endl;
    std::cout << "Angle value: " << angle_pt << " Entry index " << entry_index << std::endl;
    for( int i=0;i<nchan;i++)
    {
     /*esumchan_avg[i] = esumchan_avg[i]/num_evt;
     nscintchan_avg[i] = nscintchan_avg[i]/num_evt;
     ncerchan_avg[i] = ncerchan_avg[i]/num_evt;*/
     esumchan_avg[i] = esumchan_avg[i]/icount;
     nscintchan_avg[i] = nscintchan_avg[i]/icount;
     ncerchan_avg[i] = ncerchan_avg[i]/icount;
     for(int j=0;j<ncerwavechan_avg[i].size();j++)
     {
      /*ncerwavechan_avg[i].at(j) = ncerwavechan_avg[i].at(j)/num_evt;
      nscintwavechan_avg[i].at(j) = nscintwavechan_avg[i].at(j)/num_evt;*/
      ncerwavechan_avg[i].at(j) = ncerwavechan_avg[i].at(j)/icount;
      nscintwavechan_avg[i].at(j) = nscintwavechan_avg[i].at(j)/icount;
     }
     
     /*for(int j_t=0;j_t<ncertimechan_avg[i].size();j_t++)
     {
      ncertimechan_avg[i].at(j_t) = ncertimechan_avg[i].at(j_t)/num_evt;
      nscinttimechan_avg[i].at(j_t) = nscinttimechan_avg[i].at(j_t)/num_evt;
     }*/
     
     std::cout<<"esum_avg ["<<namechan[i]<<"]="<<esumchan_avg[i]<<std::endl;
     std::cout<<"nscintillator_avg ["<<namechan[i]<<"]="<<nscintchan_avg[i]<<std::endl;
     std::cout<<"ncerenkov_avg ["<<namechan[i]<<"]="<<ncerchan_avg[i]<<std::endl;
     //cer_angle[entry_index][i]=ncerchan_avg[i];
     //scint_angle[entry_index][i]=nscintchan_avg[i];
     //esum_angle[entry_index][i]=esumchan_avg[i];
     cer_angle[i].push_back(ncerchan_avg[i]);
     scint_angle[i].push_back(nscintchan_avg[i]);

    }
    
        
    for(int j=0;j<ncerwavechan_avg[0].size();j++) //Right now all sizes are the same = binsize, taken the channel 0
    {
     int ent_UG11 = 91, ent_GG420 = 121;
     if (number_of_bins_avg[2].at(j) >= UV_filter_x[0] && number_of_bins_avg[2].at(j) < UV_filter_x[ent_UG11]) //within range specified for filter (which is basically the entire range over which the bins are specified)
     {
      for(int i=0;i<ent_UG11;i++)
      {
       if (number_of_bins_avg[2].at(j) >= UV_filter_x[i] && number_of_bins_avg[2].at(j) < UV_filter_x[i + 1]) //Checking what 'bin' the wavelength lies in
       {
       filter[2].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins_avg[2].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);
       filter[3].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins_avg[3].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);
       filter[4].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins_avg[4].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);
       filter[5].push_back((UV_filter_y[i + 1] - UV_filter_y[i]) * (number_of_bins_avg[5].at(j) - UV_filter_x[i]) / (UV_filter_x[i + 1] - UV_filter_x[i]) + UV_filter_y[i]);       
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
     
     if (number_of_bins_avg[1].at(j) >= GG_filter_x[0] && number_of_bins_avg[1].at(j) < GG_filter_x[ent_GG420]) //within range specified for filter (which is basically the entire range over which the bins are specified)
     {
      for(int i=0;i<ent_GG420;i++)
      {
       if (number_of_bins_avg[6].at(j) >= GG_filter_x[i] && number_of_bins_avg[6].at(j) < GG_filter_x[i + 1]) //Checking what 'bin' the wavelength lies in
       {
       filter[6].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins_avg[6].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       filter[7].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins_avg[7].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       filter[8].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins_avg[8].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
       filter[9].push_back((GG_filter_y[i + 1] - GG_filter_y[i]) * (number_of_bins_avg[9].at(j) - GG_filter_x[i]) / (GG_filter_x[i + 1] - GG_filter_x[i]) + GG_filter_y[i]);
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
    
     
      for(int j=0;j<ncerwavechan_avg[0].size();j++) //Right now all sizes are the same = binsize, taken the channel 0
      {
      int ent_UV = 88, ent_RGB = 88;
      if(number_of_bins_avg[2].at(j) >= UV_sipm_QE_x[0] && number_of_bins_avg[2].at(j) < UV_sipm_QE_x[ent_UV]) //i.e. if it lies within the range of sensitivity of the UV SiPM
      //1 less than actual size i.e. 23 because of usual indexing quirks (starts from 0)
      {
       for(int i=0;i<ent_UV;i++)
       {
        if (number_of_bins_avg[2].at(j) >= UV_sipm_QE_x[i] && number_of_bins_avg[2].at(j) < UV_sipm_QE_x[i + 1]) //Checking what 'bin' the wavelength lies in 
        {
        QE[2].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins_avg[2].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        QE[3].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins_avg[3].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        QE[4].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins_avg[4].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
        QE[5].push_back(((UV_sipm_QE_y[i + 1] - UV_sipm_QE_y[i]) * (number_of_bins_avg[5].at(j) - UV_sipm_QE_x[i]) / (UV_sipm_QE_x[i + 1] - UV_sipm_QE_x[i]) + UV_sipm_QE_y[i]));
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
       
       
       
      if(number_of_bins_avg[6].at(j) >= RGB_sipm_QE_x[0] && number_of_bins_avg[6].at(j) < RGB_sipm_QE_x[ent_RGB]) //i.e. if it lies within the range of sensitivity of the RGB SiPM
      //1 less than actual size i.e. 29 because of usual indexing quirks (starts from 0)
      {
       for(int i=0;i<ent_RGB;i++)
       {
        if (number_of_bins_avg[6].at(j) >= RGB_sipm_QE_x[i] && number_of_bins_avg[6].at(j) < RGB_sipm_QE_x[i + 1]) //Checking what 'bin' the wavelength lies in
        {
        QE[6].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins_avg[6].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        QE[7].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins_avg[7].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        QE[8].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins_avg[8].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
        QE[9].push_back(((RGB_sipm_QE_y[i + 1] - RGB_sipm_QE_y[i]) * (number_of_bins_avg[9].at(j) - RGB_sipm_QE_x[i]) / (RGB_sipm_QE_x[i + 1] - RGB_sipm_QE_x[i]) + RGB_sipm_QE_y[i]));
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
    
    std::vector<float>wavelencut;
    for(int i=0;i<number_of_bins_avg[0].size();i++)
    {
     wavelencut.push_back(number_of_bins_avg[0].at(i)); //cuts in general are spanning over all the bins
    }

    std::cout << wavelencut.size() << std::endl;
    float ncercutchan_avg[nchan]; //Cerenkov Photons above cutoff
    float nscintcutchan_avg[nchan]; //Scintillation photons below cutoff
    std::vector<float> ncer_cut_chan_k[nchan], nscint_cut_chan_k[nchan], optimize_C_S[nchan]; //the ones that are being graphed wrt wavelength cut
     for( int i=0;i<nchan;i++)
    {
     for(int l=0;l<number_of_bins_avg[0].size();l++)
    {
     ncerwavecutchan_avg[i].push_back(0);
     nscintwavecutchan_avg[i].push_back(0);
     //filter[i].push_back(0.0);
    }    
    }

    for( int i=0;i<nchan;i++)
    {
     for(int l=0;l<number_of_bins_avg[0].size();l++)
    {
     ncerwavecutchan_avg[i].at(l)=0.;
     nscintwavecutchan_avg[i].at(l)=0.;
    }    
     ncercutchan_avg[i] = 0.;
     nscintcutchan_avg[i] = 0.;

     for(int j=0;j<ncerwavechan_avg[i].size();j++)
     {
      /*ncerwavecutchan_avg[i].at(j) = ncerwavecutchan_avg[i].at(j)/num_evt;
      nscintwavecutchan_avg[i].at(j) = nscintwavecutchan_avg[i].at(j)/num_evt;*/
      
      ncerwavecutchan_avg[i].at(j)+=ncerwavechan_avg[i].at(j)*filter[i].at(j);
      nscintwavecutchan_avg[i].at(j)+=nscintwavechan_avg[i].at(j)*filter[i].at(j);
      
      ncerwavecutchan_avg[i].at(j) = ncerwavecutchan_avg[i].at(j)*QE[i].at(j);
      nscintwavecutchan_avg[i].at(j) = nscintwavecutchan_avg[i].at(j)*QE[i].at(j);
      
      /*ncerwavecutchan_avg[i].at(j)+=ncerwavechan_avg[i].at(j)*QE[i].at(j);
      nscintwavecutchan_avg[i].at(j)+=nscintwavechan_avg[i].at(j)*QE[i].at(j);*/
      
      ncercutchan_avg[i]+= ncerwavecutchan_avg[i].at(j);
      nscintcutchan_avg[i]+= nscintwavecutchan_avg[i].at(j);
     }
     std::cout<<"nscintillator_avg with filter and QE ["<<namechan[i]<<"]="<<nscintcutchan_avg[i]<<std::endl;
     std::cout<<"ncerenkov_avg with filter and QE ["<<namechan[i]<<"]="<<ncercutchan_avg[i]<<std::endl;     
     if(i>1 && i<nchan) //New branches that are in the same order as the indices of the corresponding SiPMs
     {
      std::cout << "Branch number " << i+8 <<std::endl; 
     //cer_angle[entry_index][i+8]=ncercutchan_avg[i];
     //scint_angle[entry_index][i+8]=nscintcutchan_avg[i];
     cer_angle[i+8].push_back(ncercutchan_avg[i]);
     scint_angle[i+8].push_back(nscintcutchan_avg[i]);
     //std::cout<< cer_angle[entry_index][i+8] << " " << scint_angle[entry_index][i+8] << std::endl;
     }
    }

      f->Close();
      
    float norm_cer = *max_element(ncerwavechan_avg[0].begin(), ncerwavechan_avg[0].end());
    float norm_scint = *max_element(nscintwavechan_avg[0].begin(), nscintwavechan_avg[0].end());   
    float norm_cer_det, norm_scint_det;

    std::cout<< "max cer is " << " " << norm_cer << endl;
    std::cout<< "max scint is " << " " << norm_scint << endl;
    
     for(int j=0;j<ncerwavechan_avg[0].size();j++) //Only for gen normalization
     {
      ncerwavechan_avg[0].at(j) = ncerwavechan_avg[0].at(j)/norm_cer;
      nscintwavechan_avg[0].at(j) = nscintwavechan_avg[0].at(j)/norm_scint;
     }    
        
    for(int i=2;i<nchan;i++) //Only for det normalization
    {
     norm_cer_det = *max_element(ncerwavechan_avg[i].begin(), ncerwavechan_avg[i].end());
     norm_scint_det = *max_element(nscintwavechan_avg[i].begin(), nscintwavechan_avg[i].end());
     for(int j=0;j<ncerwavechan_avg[i/*0*/].size();j++)
     {
      /*norm_cer_det = *max_element(ncerwavechan_avg[i].begin(), ncerwavechan_avg[i].end());
      norm_scint_det = *max_element(nscintwavechan_avg[i].begin(), nscintwavechan_avg[i].end());*/
      
      ncerwavechan_avg[i].at(j) = ncerwavechan_avg[i].at(j)/2/norm_cer_det;
      ncerwavecutchan_avg[i].at(j) = ncerwavecutchan_avg[i].at(j)/2/norm_cer_det;
      nscintwavechan_avg[i].at(j) = nscintwavechan_avg[i].at(j)/2/norm_scint_det;
      nscintwavecutchan_avg[i].at(j) = nscintwavecutchan_avg[i].at(j)/2/norm_scint_det;
     }
    }
                 
    //Graphs for wavelength distribution of C,S generated, detected and with effects of SiPM QE and filtering action
    /*
    Color_t leg_col_wave[4] = {kOrange,kBlue,kGreen,kMagenta};
    //Gen graphs to be added irrespective of any other choice

    int side_toggle; //Insert 2 for left side and 6 for right side   
    string side_string;
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
           
    for(int SiPM_number=0;SiPM_number<4;SiPM_number++) //This could be 0,1,2 or 3  
    {
     TMultiGraph* cerscint = new TMultiGraph();
     cerscint->SetName("cer_scint");
     
     TGraph* gcerwave_gen = new TGraph(ncerwavechan_avg[0].size(),&number_of_bins_avg[0][0],&ncerwavechan_avg[0][0]);
     gcerwave_gen->SetTitle("Cerenkov photons generated");    
     cerscint -> Add(gcerwave_gen);
     gcerwave_gen -> SetLineColor(kRed);
     TGraph* gscintwave_gen = new TGraph(nscintwavechan_avg[0].size(),&number_of_bins_avg[0][0],&nscintwavechan_avg[0][0]);
     gscintwave_gen->SetTitle("Scintillation photons generated");
     cerscint -> Add(gscintwave_gen);
     gscintwave_gen -> SetLineColor(kBlack);
     
     TGraph* QE_SiPM = new TGraph(QE[side_toggle].size(),&number_of_bins_avg[side_toggle][0],&QE[side_toggle][0]);
     QE_SiPM->SetTitle("SiPM QE");
     cerscint->Add(QE_SiPM);
     QE_SiPM->SetLineStyle(kDashed);
     QE_SiPM->SetLineColor(kCyan);
     QE_SiPM->SetLineWidth(3);

     TGraph* filter_SiPM = new TGraph(filter[side_toggle].size(),&number_of_bins_avg[side_toggle][0],&filter[side_toggle][0]);
     if(side_string == "Left")
     {
     filter_SiPM->SetTitle("No filter for Left SiPMs");
     }
     else if (side_string == "Right")
     {
     filter_SiPM->SetTitle("filter for Right SiPMs (R60)");    
     }
     filter_SiPM->SetLineColor(kGreen);
     filter_SiPM->SetLineStyle(kDashed);
     filter_SiPM->SetLineWidth(3);
     cerscint->Add(filter_SiPM);

    TGraph* gcerscint;
    stringstream j_s;
    string title_string;
    j_s << SiPM_number;
    j_s >> title_string;
    
    string Net_title_string, aux_title_string;    

    for(int j=0;j<4;j++) //For toggling through the different graphs
    { 
    if(j==0)
    {
     gcerscint = new TGraph(ncerwavechan_avg[side_toggle+SiPM_number].size(), &number_of_bins_avg[side_toggle+SiPM_number][0],&ncerwavechan_avg[side_toggle+SiPM_number][0]);
     aux_title_string = "Cerenkov photons reaching the ";
    }
    else if (j==1)
    {
     gcerscint = new TGraph(nscintwavechan_avg[side_toggle+SiPM_number].size(),&number_of_bins_avg[side_toggle+SiPM_number][0],&nscintwavechan_avg[side_toggle+SiPM_number][0]);
     aux_title_string = "Scintillation photons reaching the ";
    }
    else if (j==2)     
    {
     gcerscint = new TGraph(ncerwavecutchan_avg[side_toggle+SiPM_number].size(), &number_of_bins_avg[side_toggle+SiPM_number][0],&ncerwavecutchan_avg[side_toggle+SiPM_number][0]);
     aux_title_string = "Cerenkov photoelectrons with filter at ";
    }
    else if (j==3)     
    {     
     gcerscint = new TGraph(nscintwavecutchan_avg[side_toggle+SiPM_number].size(),&number_of_bins_avg[side_toggle+SiPM_number][0],&nscintwavecutchan_avg[side_toggle+SiPM_number][0]);
     aux_title_string = "Scintillation photoelectrons with filter at ";
    }
    
    Net_title_string = aux_title_string + side_string + " SiPM " + title_string;
    gcerscint->SetTitle(Net_title_string.c_str());
    cerscint -> Add(gcerscint);
    gcerscint -> SetLineColor(leg_col_wave[j]);
    gcerscint -> SetLineWidth(2);
   }
     
    TCanvas *c_wavelength = new TCanvas("c_wavelength","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
    cerscint -> Draw("AC"); //Draw with axes, curve
    //c1->SetLogy();
    TH1F* hist = cerscint->GetHistogram(); //Done purely for tweaking title, axes, etc.
    Double_t ymin = hist->GetMinimum();
    Double_t ymax = hist->GetMaximum();
    //The optimization cut y axis is the main one (and the Cerenkov/Scintillation distribution is the scaled one) so the ymin and ymax is for the optimization cut values

    hist->GetXaxis()->SetTitle("Wavelength (in nm)");
    hist->GetYaxis()->SetTitle("Number of counts");
    hist->SetTitle("C and S produced in crystal and detected for right killMedia)");
    c_wavelength -> BuildLegend();

    stringstream j_s_1;
    string entry_filter_string;
    j_s_1 << angle_pt;
    j_s_1 >> entry_filter_string;
    //string Entry_index_filter_pdf = "Plots/PbWO4/Energy distribution for " + entry_filter_string + " deg.pdf";
    string Entry_index_filter_pdf ="Plots/PbWO4/Angle_"+ entry_filter_string + "_deg/" + side_string + " SiPM " + title_string + " wavelength distribution for " + entry_filter_string + " deg.pdf";
    //string Entry_index_filter_pdf = "Plots/PbWO4/Scintillation/SiPMs/Scintillation distribution at right SiPM 2 for " + entry_filter_string + " deg.pdf";
  
    c_wavelength -> Print(Entry_index_filter_pdf.c_str()); //Copy canvas to pdf
    c_wavelength->Close();
    }
   }
   */
   //End of graphs for wavelength distribution
   
 }//end first loop over angle points

//  }  // end if no events - Not needed since num_evt is already specified

  
  for(entry_index=0;entry_index<angle_values.size();entry_index++) //Transfer this to the second angle loop later
  {
   angle_pt = angle_values.at(entry_index);
   std::cout << "Angle value: " <<  angle_pt << std::endl;
  TCanvas *c1 = new TCanvas("c1","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
  //hcEcalE0[entry_index]->Draw();
  //hcEcalncer[0][entry_index]->Draw();
  //hcEcalnscint[0][entry_index]->Draw();  
  
  for(int i=0;i<nchan;i++)
  {
   hcEcalncer[i][entry_index]->Draw();   
   cer_angle_err[i].push_back((hcEcalncer[i][entry_index]->GetStdDev())/sqrt(num_evt-1));
   hcEcalnscint[i][entry_index]->Draw();   
   scint_angle_err[i].push_back((hcEcalnscint[i][entry_index]->GetStdDev())/sqrt(num_evt-1));   
   if(i>=2 && i<nchan)
   {
    cer_angle_err[i+8].push_back(cer_angle_err[i].at(entry_index));
    scint_angle_err[i+8].push_back(scint_angle_err[i].at(entry_index));    
   }
  }
  
  c1->Close();
  }
  

  int graph_toggle;
  for(int C_S_toggle=0;C_S_toggle<2;C_S_toggle++) //0 for Cerenkov, 1 for Scintillation
  {
   for(int graph_loop=0;graph_loop<4;graph_loop++)
   {
   TCanvas *cangle = new TCanvas("c1","Graph Draw Options", 200,10,600,400);
   //Put 2, 6, 10 or 14 here
   if(graph_loop==0){graph_toggle=2;}
   else if(graph_loop==1){graph_toggle=6;}
   else if(graph_loop==2){graph_toggle=10;}
   else if(graph_loop==3){graph_toggle=14;}   

   TMultiGraph* Angular_dependence  = new TMultiGraph();
  
  /*
  TGraph* g = new TGraph(angle_values.size(),&angle_values[0],&cer_angle[0][0]);
  Angular_dependence->Add(g);  
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.5);
  g->SetMarkerColor(kRed);
  */
  
  Color_t leg_col[4] = {kRed,kBlue,kGreen,kOrange};
  //TGraph* g;
  TGraphErrors* g;
  string aux_string, Title, Title_pdf;
  for(int j=0;j<4;j++)
  {
    stringstream j_s;
    string j_string;
    j_s << j;
    j_s >> j_string;
    string Channel_j = "Channel " + j_string;
   if(C_S_toggle==0)
   {
   //g = new TGraph(angle_values.size(),&angle_values[0],&cer_angle[graph_toggle+j][0]);
   g = new TGraphErrors(angle_values.size(),&angle_values[0],&cer_angle[graph_toggle+j][0],0,&cer_angle_err[graph_toggle+j][0]);
   aux_string = "Cerenkov";
   }
   else if (C_S_toggle==1)
   {
   //g = new TGraph(angle_values.size(),&angle_values[0],&scint_angle[graph_toggle+j][0]);
   g = new TGraphErrors(angle_values.size(),&angle_values[0],&scint_angle[graph_toggle+j][0],0,&scint_angle_err[graph_toggle+j][0]);
   aux_string = "Scintillation";
   }
   
   g->SetTitle(Channel_j.c_str());
   Angular_dependence->Add(g);
   g->SetMarkerStyle(20);
   g->SetMarkerSize(0.5);
   g->SetMarkerColor(leg_col[j]);   
  }
  
  
  Angular_dependence->Draw("AP");
  TH1F* hist_angle = Angular_dependence->GetHistogram();
  hist_angle->GetXaxis()->SetTitle("Angle (in deg)");
  hist_angle->GetYaxis()->SetTitle("Number of counts");
  //hist_angle->SetTitle("Cerenkov Photons generated in the crystal");
  
  //Set title based graph_toggle value
  if(graph_toggle==2){Title = aux_string + " Photons reaching the left SiPMs";}
  else if (graph_toggle==6){Title = aux_string + " Photons reaching the right SiPMs";}
  else if (graph_toggle==10){Title = aux_string + " Photoelectrons obtained from the left SiPMs";}
  else if (graph_toggle==14){Title = aux_string + " Photoelectrons obtained from the right SiPMs";}
  
  Title_pdf = Title +".pdf";
  hist_angle->SetTitle(Title.c_str());
  cangle -> BuildLegend();
  cangle -> Print(Title_pdf.c_str()); //Copy canvas to pdf
  cangle->Close();
  }
  }

}


