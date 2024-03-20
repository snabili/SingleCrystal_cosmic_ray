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
#include <TAttLine.h>
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
/*
void print_vector_vt(vector<vector<Double_t>> const &ptrvt) //function to print a vector of double (floating point numbers)
{
 std::ofstream file("Sorted_event_data_by_channel.txt");
 for(unsigned int i=0; i<ptrvt.size(); i++)
 {
  print_vector_dt(ptrvt.at(i), file);
 }
 file << endl;
 file.close();
}
*/
void Plot_comp(string title_path, string data_path)
{
  int channel_plot=0;
  Float_t Channel_Numbers, Median_values, Median_values_QE;

  //std::vector<int> angle_values{-90,-85,-80,-75,-70,-65,-60,-55,-50,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90};
  std::vector<int> angle_values{-90,-80,-70,-60,-50,-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90};
  float adc_avg, adc_QE_avg, time_avg;
  float mpv_values;
  std::vector<std::vector<float>> adc_angle, adc_QE_angle;
  int i_cut=0;
  int i_cut_div = 0;

  TGraph* Plot_comp_data = new TGraph();
  TGraph* plot_ratio = new TGraph();
  //TH1F* hist=new TH1F("Plot_comp","Plot_comp",37,-92.5,92.5); //without cut for median;
  TH1F* hist=new TH1F("Plot_comp","Plot_comp",19,-95,95); //without cut for median;

  TCanvas *c = new TCanvas("c", "c", 800,800);
  c->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gStyle->SetLineStyleString(2,"12 12");
  //gStyle->SetLineStyleString("kDashed","12 12");

  c->cd();

  TPad *toppad = new TPad("toppad", "toppad",0.01,0.355,0.99,0.99);
  toppad->Draw();
  toppad->cd();
  //toppad->Range(-75,-4.296785,425,14.07152);
  toppad->SetFillColor(0);
  toppad->SetBorderMode(0);
  toppad->SetBorderSize(2);
  toppad->SetLeftMargin(0.15);
  toppad->SetRightMargin(0.05);
  toppad->SetTopMargin(0.08);
  toppad->SetBottomMargin(0.0);
  toppad->SetFrameBorderMode(0);
  toppad->SetFrameBorderMode(0);

   //Hui-Chi's graphs
   for(int entry_index=0;entry_index<angle_values.size();entry_index++) //Histogram initialization loop - might have to put angle wise graphs for wavelength distribution here too
 {  
  //std::cout << angle_values.at(entry_index) << " Whether file exists or not " <<  << std::endl;
  if(gSystem->AccessPathName(Form(data_path.c_str(),-angle_values.at(entry_index)))) //File does not exist
  {
   //std::cout << angle_values.at(entry_index) << std::endl;
  }
  else
  {
   
  TFile *f_data = new TFile(Form(data_path.c_str(),-angle_values.at(entry_index))); 
  TTree *hgcroc_data = (TTree *)f_data->Get("MPV_channel");

  hgcroc_data->SetBranchAddress("MPVs", &mpv_values);

  int total_entries_data = hgcroc_data->GetEntries(); //total events

  hgcroc_data->GetEntry(channel_plot); //channel number 0
  Plot_comp_data->SetPoint(i_cut,angle_values.at(entry_index),mpv_values/67.5);
  i_cut++;
  }
 }

  TLegend *leg = new TLegend(0.48,0.619707,0.6074114,0.9012957,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);

  TLegendEntry *entry=leg->AddEntry("Plot_comp_data","Data","P");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(1.15);
  entry->SetTextFont(42);
  entry->SetTextSize(0.04);

  entry=leg->AddEntry("hist_comp","MC","L");
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetLineColor(kBlue);
  entry->SetTextFont(42);
  entry->SetTextSize(0.04);

  Plot_comp_data->Draw("AP");
  Plot_comp_data->SetMarkerStyle(20);
  Plot_comp_data->SetMarkerSize(0.6);
  TH1F* hist_comp = Plot_comp_data->GetHistogram();
  hist_comp->GetYaxis()->SetRangeUser(0,70);
  hist_comp->GetXaxis()->SetRangeUser(-100,100);
  //hist_comp->GetXaxis()->SetTitle("Angle in deg");
  hist_comp->GetYaxis()->SetTitle("Number of p.e. counts");

  hist_comp->GetXaxis()->SetLabelFont(42);
  hist_comp->GetXaxis()->SetLabelSize(0);
  hist_comp->GetXaxis()->SetTitleSize(0);
  hist_comp->GetXaxis()->SetTickLength(0.01884422);
  hist_comp->GetXaxis()->SetTitleOffset(1.1);
  hist_comp->GetXaxis()->SetTitleFont(42);
  hist_comp->GetYaxis()->SetLabelFont(42);
  hist_comp->GetYaxis()->SetLabelSize(0.03);
  hist_comp->GetYaxis()->SetTitleSize(0.03);
  hist_comp->GetYaxis()->SetTickLength(0.01884422);
  hist_comp->GetYaxis()->SetTitleOffset(1.1);
  hist_comp->GetYaxis()->SetTitleFont(42);

  hist_comp->Draw("same");
  hist_comp->Draw("AXIS same");

  leg->Draw("same");  
  std::string title_text = "Ch " + std::to_string(channel_plot);
  TLatex* tex = new TLatex(0.17,0.83,title_text.c_str());
  tex->SetNDC();
 tex->SetTextFont(52);
 tex->SetTextSize(0.05);
 tex->SetLineWidth(2);
 tex->Draw("same");

  int Ndata = Plot_comp_data->GetN();
  std::cout << "Total number of data points " << Ndata << std::endl;

  std::vector<float> ratio_val;
  for(int entry_index=0;entry_index<angle_values.size();entry_index++) //Histogram initialization loop - might have to put angle wise graphs for wavelength distribution here too
 {  
  //std::cout << angle_values.at(entry_index) << " Whether file exists or not " <<  << std::endl;
  if(gSystem->AccessPathName(Form(title_path.c_str(),angle_values.at(entry_index)))) //File does not exist
  {
   //std::cout << angle_values.at(entry_index) << std::endl;
  }
  else
  {
   
  TFile *f = new TFile(Form(title_path.c_str(),angle_values.at(entry_index))); 
  TTree *hgcroc = (TTree *)f->Get("Med_channel");

  hgcroc->SetBranchAddress("Channel_Numbers", &Channel_Numbers);
  hgcroc->SetBranchAddress("Median_values", &Median_values);
  hgcroc->SetBranchAddress("Median_values_QE", &Median_values_QE);

  int total_entries = hgcroc->GetEntries(); //total events
   std::vector<float> adc_chan, adc_QE_chan;
  //std::cout << "Total number of angles " << total_entries << std::endl;
  int i_start = 1;
  //std::cout << "Reached here " << i_start << std::endl;

  hgcroc->GetEntry(channel_plot+1); //channel number 2
  //Plot_comp_data->SetPoint(i_cut,angle_values.at(entry_index),Median_values_QE);
  hist->Fill(angle_values.at(entry_index),Median_values_QE); // ?

  for(int i=0; i < Ndata; ++i) 
  {
   double x,y;
   Plot_comp_data->GetPoint(i, x, y);//So here x is the angle
   if(x==angle_values.at(entry_index) && y!=0)
   {
    std::cout << "Angle " << x << " " << "Data value " << y  << " MC value " << Median_values_QE << std::endl;
    plot_ratio->SetPoint(i_cut_div,x,y/Median_values_QE);
    ratio_val.push_back(y/Median_values_QE);
    std::cout << "Ratio point set " << i_cut_div << " X coordinate " << x << " Y coordinate " << y/Median_values_QE << std::endl;
    break;
   }
  }

  i_cut_div ++;
  }
 }
 
 hist->Draw("hist same");
 

  c->cd();
   TPad *bottompad = new TPad("bottompad", "bottompad",0.01,0.01,0.99,0.345);
   bottompad->Draw();
   bottompad->cd();
   //bottompad->Range(-75,-0.923077,425,2.153846);
   bottompad->SetFillColor(0);
   bottompad->SetBorderMode(0);
   bottompad->SetBorderSize(2);
   bottompad->SetLeftMargin(0.15);
   bottompad->SetRightMargin(0.05);
   bottompad->SetTopMargin(0.05);
   bottompad->SetBottomMargin(0.3);
   bottompad->SetFrameBorderMode(0);
   bottompad->SetFrameBorderMode(0);

  plot_ratio->Draw("AP");
  plot_ratio->SetMarkerStyle(20);
  plot_ratio->SetMarkerSize(0.6);
  TH1F *hist_ratio = plot_ratio->GetHistogram();
  hist_ratio->GetXaxis()->SetRangeUser(-100,100);
  hist_ratio->GetYaxis()->SetTitle("#frac{Data}{MC}");
  hist_ratio->GetXaxis()->SetTitle("Angle in deg");

   hist_ratio->GetXaxis()->SetLabelFont(42);
   hist_ratio->GetXaxis()->SetLabelSize(0.05);
   hist_ratio->GetXaxis()->SetTitleSize(0.05);
   hist_ratio->GetXaxis()->SetTitleOffset(1.1);
   hist_ratio->GetXaxis()->SetTitleFont(42);
   hist_ratio->GetYaxis()->SetLabelFont(42);
   hist_ratio->GetYaxis()->SetLabelSize(0.05);
   hist_ratio->GetYaxis()->SetTitleSize(0.05);
   hist_ratio->GetYaxis()->SetTitleOffset(0.75);
   hist_ratio->GetYaxis()->SetTitleFont(42);

  //Problematic because there is a zero point at 0 deg which is in the ratio plot
  /*
  float min_ratio = hist_ratio->GetMinimum();
  float max_ratio = hist_ratio->GetMaximum();
  */
  float min_ratio = *min_element(ratio_val.begin(), ratio_val.end());
  float max_ratio = *max_element(ratio_val.begin(), ratio_val.end());
  std::cout << "Minimum ratio " << min_ratio << " Maximum ratio " << max_ratio << std::endl;
  float ratio_limit = std::max(1.0-min_ratio,max_ratio-1.0);
  std::cout << "Ratio limit " << ratio_limit << std::endl;

  TLine* ratio_1_axis = new TLine(-100.,1.0,100.,1.0);
  ratio_1_axis->SetLineStyle(kDashed);
  ratio_1_axis->Draw("same");

  hist_ratio->GetYaxis()->SetRangeUser(1.0-ratio_limit-0.05,1.0+ratio_limit+0.05);
  hist_ratio->Draw("same");

  string macro_path = "Plots/PbF2/0316/Ch_"+std::to_string(channel_plot) + "_Angular_dependence_comparison.C";
  string plot_path = "Plots/PbF2/0316/Ch_"+std::to_string(channel_plot) + "_Angular_dependence_comparison.pdf";
  c->Print(macro_path.c_str());
  c->Print(plot_path.c_str());
  c->Close();
  gApplication->Terminate();
 }
