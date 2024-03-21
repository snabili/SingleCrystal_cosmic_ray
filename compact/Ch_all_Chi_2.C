#ifdef __CLING__
#pragma cling optimize(0)
#endif

#include  <TMultiGraph.h>
void Ch_all_Chi_2()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Mar 21 02:50:58 2024) by ROOT version 6.26/08
   TCanvas *c = new TCanvas("c", "c",86,109,800,800);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   Double_t _fx0[20] = {
   0,
   0.05,
   0.15,
   0.2,
   0.25,
   0.3,
   0.35,
   0.4,
   0.45,
   0.5,
   0.55,
   0.6,
   0.65,
   0.7,
   0.75,
   0.8,
   0.85,
   0.9,
   0.95,
   1};
   Double_t _fy0[20] = {
   53.12999,
   21.14538,
   6.791273,
   9.813226,
   13.23253,
   14.43477,
   16.65307,
   18.07457,
   16.21348,
   23.88323,
   20.14392,
   20.03488,
   19.97364,
   24.52427,
   21.65843,
   24.54312,
   25.21377,
   19.65048,
   22.75341,
   20.28999};

   Double_t _fy1[20] = {
   80.10615,
   27.53608,
   15.43198,
   14.12126,
   20.02573,
   20.7073,
   21.35807,
   24.76079,
   23.45375,
   25.66661,
   23.8045,
   24.19882,
   28.41837,
   27.02384,
   26.9494,
   37.16472,
   26.43683,
   21.84699,
   24.24025,
   26.20856};

   Double_t _fy3[20] = {
   49.58436,
   16.26253,
   24.00311,
   29.73752,
   37.35979,
   37.42147,
   43.261,
   37.75429,
   47.14862,
   55.74905,
   53.57887,
   54.56878,
   48.95864,
   53.08109,
   45.44247,
   58.46774,
   49.17303,
   52.37782,
   50.4869,
   53.29196};


   Double_t _fy4[20] = {
   73.4549,
   13.68763,
   11.15635,
   11.95898,
   19.82875,
   18.88544,
   28.28811,
   20.12057,
   26.93829,
   30.36974,
   24.94745,
   33.43053,
   25.7763,
   24.67315,
   28.29342,
   23.41377,
   30.95136,
   31.0083,
   30.93736,
   33.18039};

   Double_t _fy5[20] = {
   94.05904,
   36.06178,
   18.82961,
   10.09622,
   13.42698,
   10.60387,
   14.58763,
   15.0464,
   16.76374,
   17.03181,
   18.42068,
   21.67797,
   21.95623,
   13.84571,
   20.5659,
   15.27344,
   18.38159,
   22.35691,
   16.85805,
   16.72697};

   Double_t _fy6[20] = {
   51.29669,
   13.395,
   10.58893,
   14.52167,
   17.24271,
   20.21042,
   23.41208,
   30.31663,
   26.98388,
   27.22351,
   32.24693,
   29.67601,
   30.21299,
   34.59173,
   33.14511,
   37.54698,
   32.80578,
   38.27729,
   31.24516,
   23.99054};

   Double_t _fy7[20] = {
   81.46053,
   27.39065,
   14.15425,
   15.42151,
   18.55995,
   21.26474,
   14.65315,
   21.06005,
   22.35719,
   18.03493,
   23.1659,
   26.13192,
   17.19144,
   24.12667,
   20.09341,
   15.01041,
   21.20627,
   18.41912,
   17.73368,
   17.9506};

   TGraph *graph0 = new TGraph(20,_fx0,_fy0);
   graph0->SetName("");
   graph0->SetTitle("");
   graph0->SetFillStyle(1000);
   graph0->SetMarkerColor(kBlue);
   graph0->SetMarkerStyle(20);

   TGraph *graph1 = new TGraph(20,_fx0,_fy1);
   graph1->SetName("");
   graph1->SetTitle("");
   graph1->SetFillStyle(1000);
   graph1->SetMarkerColor(kRed);
   graph1->SetMarkerStyle(20);
  
   TGraph *graph3 = new TGraph(20,_fx0,_fy3);
   graph3->SetName("");
   graph3->SetTitle("");
   graph3->SetFillStyle(1000);
   graph3->SetMarkerColor(kGreen);
   graph3->SetMarkerStyle(20);


   TGraph *graph4 = new TGraph(20,_fx0,_fy4);
   graph4->SetName("");
   graph4->SetTitle("");
   graph4->SetFillStyle(1000);
   graph4->SetMarkerColor(kOrange);
   graph4->SetMarkerStyle(20);

   TGraph *graph5 = new TGraph(20,_fx0,_fy5);
   graph5->SetName("");
   graph5->SetTitle("");
   graph5->SetFillStyle(1000);
   graph5->SetMarkerColor(kBlack);
   graph5->SetMarkerStyle(20);

   TGraph *graph6 = new TGraph(20,_fx0,_fy6);
   graph6->SetName("");
   graph6->SetTitle("");
   graph6->SetFillStyle(1000);
   graph6->SetMarkerColor(kPink);
   graph6->SetMarkerStyle(20);

   TGraph *graph7 = new TGraph(20,_fx0,_fy7);
   graph7->SetName("");
   graph7->SetTitle("");
   graph7->SetFillStyle(1000);
   graph7->SetMarkerColor(kCyan);
   graph7->SetMarkerStyle(20);

   TMultiGraph *graph_all = new TMultiGraph();
   graph_all->Add(graph0);
   graph_all->Add(graph1);
   graph_all->Add(graph3);
   graph_all->Add(graph4);
   graph_all->Add(graph5);
   graph_all->Add(graph6);
   graph_all->Add(graph7);

   graph_all->Draw("AP");

  TH1F* hist_chi = graph_all->GetHistogram();
  hist_chi->GetXaxis()->SetTitle("Percentage of specular lobe reflection");
  hist_chi->GetYaxis()->SetTitle("#chi_2 value");
  hist_chi->Draw("same");

    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->SetFillColor(0);
    leg->AddEntry(graph0, "Ch 0", "lp");
    leg->AddEntry(graph1, "Ch 1", "lp");
    leg->AddEntry(graph3, "Ch 3", "lp");
    leg->AddEntry(graph4, "Ch 4", "lp");
    leg->AddEntry(graph5, "Ch 5", "lp");
    leg->AddEntry(graph6, "Ch 6", "lp");
    leg->AddEntry(graph7, "Ch 7", "lp");

    leg->Draw("same");   
}
