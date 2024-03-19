#ifdef __CLING__
#pragma cling optimize(0)
#endif
void Ch_1_Angular_dependence_comparison()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Mar 18 22:24:00 2024) by ROOT version 6.26/08
   TCanvas *c = new TCanvas("c", "c",34,57,800,800);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p1
   TPad *p1 = new TPad("p1", "p1",0.1,0.2,0.9,1);
   p1->Draw();
   p1->cd();
   p1->Range(0,0,1,1);
   p1->SetFillColor(0);
   p1->SetBorderMode(0);
   p1->SetBorderSize(2);
   p1->SetFrameBorderMode(0);
   
   Double_t _fx1[19] = {
   -90,
   -80,
   -70,
   -60,
   -50,
   -40,
   -30,
   -20,
   -10,
   0,
   10,
   20,
   30,
   40,
   50,
   60,
   70,
   80,
   90};
   Double_t _fy1[19] = {
   25.92593,
   36.2963,
   42.22222,
   30.37037,
   21.48148,
   18.51852,
   20,
   20,
   20,
   15.55556,
   12.59259,
   14.07407,
   12.59259,
   12.59259,
   14.07407,
   20,
   28.88889,
   25.92593,
   25.92593};
   TGraph *graph = new TGraph(19,_fx1,_fy1);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(3);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,-108,108);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(70);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetRange(4,97);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Number of p.e. counts");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("ap");
   
   TH1F *Plot_comp__1 = new TH1F("Plot_comp__1","Plot_comp",37,-92.5,92.5);
   Plot_comp__1->SetBinContent(1,28);
   Plot_comp__1->SetBinContent(2,32);
   Plot_comp__1->SetBinContent(3,38);
   Plot_comp__1->SetBinContent(4,51);
   Plot_comp__1->SetBinContent(5,53);
   Plot_comp__1->SetBinContent(6,48);
   Plot_comp__1->SetBinContent(7,41);
   Plot_comp__1->SetBinContent(8,36);
   Plot_comp__1->SetBinContent(9,31);
   Plot_comp__1->SetBinContent(10,28);
   Plot_comp__1->SetBinContent(11,26);
   Plot_comp__1->SetBinContent(12,25);
   Plot_comp__1->SetBinContent(13,25);
   Plot_comp__1->SetBinContent(14,24);
   Plot_comp__1->SetBinContent(15,24);
   Plot_comp__1->SetBinContent(16,25);
   Plot_comp__1->SetBinContent(17,22);
   Plot_comp__1->SetBinContent(18,17);
   Plot_comp__1->SetBinContent(19,16);
   Plot_comp__1->SetBinContent(20,14);
   Plot_comp__1->SetBinContent(21,13);
   Plot_comp__1->SetBinContent(22,12);
   Plot_comp__1->SetBinContent(23,11);
   Plot_comp__1->SetBinContent(24,13);
   Plot_comp__1->SetBinContent(25,15);
   Plot_comp__1->SetBinContent(26,14);
   Plot_comp__1->SetBinContent(27,16);
   Plot_comp__1->SetBinContent(28,15);
   Plot_comp__1->SetBinContent(29,17);
   Plot_comp__1->SetBinContent(30,21);
   Plot_comp__1->SetBinContent(31,24);
   Plot_comp__1->SetBinContent(32,27);
   Plot_comp__1->SetBinContent(33,31);
   Plot_comp__1->SetBinContent(34,29);
   Plot_comp__1->SetBinContent(35,27);
   Plot_comp__1->SetBinContent(36,29);
   Plot_comp__1->SetBinContent(37,28);
   Plot_comp__1->SetBinError(1,28);
   Plot_comp__1->SetBinError(2,32);
   Plot_comp__1->SetBinError(3,38);
   Plot_comp__1->SetBinError(4,51);
   Plot_comp__1->SetBinError(5,53);
   Plot_comp__1->SetBinError(6,48);
   Plot_comp__1->SetBinError(7,41);
   Plot_comp__1->SetBinError(8,36);
   Plot_comp__1->SetBinError(9,31);
   Plot_comp__1->SetBinError(10,28);
   Plot_comp__1->SetBinError(11,26);
   Plot_comp__1->SetBinError(12,25);
   Plot_comp__1->SetBinError(13,25);
   Plot_comp__1->SetBinError(14,24);
   Plot_comp__1->SetBinError(15,24);
   Plot_comp__1->SetBinError(16,25);
   Plot_comp__1->SetBinError(17,22);
   Plot_comp__1->SetBinError(18,17);
   Plot_comp__1->SetBinError(19,16);
   Plot_comp__1->SetBinError(20,14);
   Plot_comp__1->SetBinError(21,13);
   Plot_comp__1->SetBinError(22,12);
   Plot_comp__1->SetBinError(23,11);
   Plot_comp__1->SetBinError(24,13);
   Plot_comp__1->SetBinError(25,15);
   Plot_comp__1->SetBinError(26,14);
   Plot_comp__1->SetBinError(27,16);
   Plot_comp__1->SetBinError(28,15);
   Plot_comp__1->SetBinError(29,17);
   Plot_comp__1->SetBinError(30,21);
   Plot_comp__1->SetBinError(31,24);
   Plot_comp__1->SetBinError(32,27);
   Plot_comp__1->SetBinError(33,31);
   Plot_comp__1->SetBinError(34,29);
   Plot_comp__1->SetBinError(35,27);
   Plot_comp__1->SetBinError(36,29);
   Plot_comp__1->SetBinError(37,28);
   Plot_comp__1->SetEntries(37);

   ci = TColor::GetColor("#000099");
   Plot_comp__1->SetLineColor(ci);
   Plot_comp__1->GetXaxis()->SetLabelFont(42);
   Plot_comp__1->GetXaxis()->SetTitleOffset(1);
   Plot_comp__1->GetXaxis()->SetTitleFont(42);
   Plot_comp__1->GetYaxis()->SetLabelFont(42);
   Plot_comp__1->GetYaxis()->SetTitleFont(42);
   Plot_comp__1->GetZaxis()->SetLabelFont(42);
   Plot_comp__1->GetZaxis()->SetTitleOffset(1);
   Plot_comp__1->GetZaxis()->SetTitleFont(42);
   Plot_comp__1->Draw("hist same");
   p1->Modified();
   c->cd();
  
// ------------>Primitives in pad: p2
   TPad *p2 = new TPad("p2", "p2",0.1,0,0.9,0.25);
   p2->Draw();
   p2->cd();
   p2->Range(0,0,1,1);
   p2->SetFillColor(0);
   p2->SetBorderMode(0);
   p2->SetBorderSize(2);
   p2->SetFrameBorderMode(0);
   
   Double_t _fx2[37] = {
   -90,
   0,
   -80,
   0,
   -70,
   0,
   -60,
   0,
   -50,
   0,
   -40,
   0,
   -30,
   0,
   -20,
   0,
   -10,
   0,
   0,
   0,
   10,
   0,
   20,
   0,
   30,
   0,
   40,
   0,
   50,
   0,
   60,
   0,
   70,
   0,
   80,
   0,
   90};
   Double_t _fy2[37] = {
   0.9259259,
   0,
   0.9551657,
   0,
   0.7966457,
   0,
   0.7407407,
   0,
   0.692951,
   0,
   0.7122507,
   0,
   0.8,
   0,
   0.8333333,
   0,
   0.9090909,
   0,
   0.9722222,
   0,
   0.968661,
   0,
   1.279461,
   0,
   0.8395062,
   0,
   0.787037,
   0,
   0.8278867,
   0,
   0.8333333,
   0,
   0.9318996,
   0,
   0.9602195,
   0,
   0.9259259};
   graph = new TGraph(37,_fx2,_fy2);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(3);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","",100,-108,108);
   Graph_Graph2->SetMinimum(0);
   Graph_Graph2->SetMaximum(2);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetTitle("Angle in deg");
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph2->GetXaxis()->SetTitleOffset(1);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetTitle("#frac{Data - MC}{MC}");
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetTitleOffset(1);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   graph->Draw("ap");
   p2->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
