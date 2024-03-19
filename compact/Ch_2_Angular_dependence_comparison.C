#ifdef __CLING__
#pragma cling optimize(0)
#endif
void Ch_2_Angular_dependence_comparison()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Mar 18 22:26:32 2024) by ROOT version 6.26/08
   TCanvas *c = new TCanvas("c", "c",60,83,800,800);
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
   14.07407,
   17.03704,
   18.51852,
   18.51852,
   18.51852,
   12.59259,
   11.11111,
   9.62963,
   8.148148,
   9.62963,
   9.62963,
   9.62963,
   8.148148,
   9.62963,
   9.62963,
   11.11111,
   15.55556,
   14.07407,
   14.07407};
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
   Plot_comp__1->SetBinContent(1,27);
   Plot_comp__1->SetBinContent(2,37);
   Plot_comp__1->SetBinContent(3,46);
   Plot_comp__1->SetBinContent(4,49);
   Plot_comp__1->SetBinContent(5,51);
   Plot_comp__1->SetBinContent(6,44);
   Plot_comp__1->SetBinContent(7,41);
   Plot_comp__1->SetBinContent(8,36);
   Plot_comp__1->SetBinContent(9,33);
   Plot_comp__1->SetBinContent(10,28);
   Plot_comp__1->SetBinContent(11,25);
   Plot_comp__1->SetBinContent(12,23);
   Plot_comp__1->SetBinContent(13,19);
   Plot_comp__1->SetBinContent(14,16);
   Plot_comp__1->SetBinContent(15,12);
   Plot_comp__1->SetBinContent(16,10);
   Plot_comp__1->SetBinContent(17,12);
   Plot_comp__1->SetBinContent(18,14);
   Plot_comp__1->SetBinContent(19,14);
   Plot_comp__1->SetBinContent(20,14);
   Plot_comp__1->SetBinContent(21,15);
   Plot_comp__1->SetBinContent(22,15);
   Plot_comp__1->SetBinContent(23,13);
   Plot_comp__1->SetBinContent(24,12);
   Plot_comp__1->SetBinContent(25,12);
   Plot_comp__1->SetBinContent(26,13);
   Plot_comp__1->SetBinContent(27,16);
   Plot_comp__1->SetBinContent(28,19);
   Plot_comp__1->SetBinContent(29,18);
   Plot_comp__1->SetBinContent(30,20);
   Plot_comp__1->SetBinContent(31,22);
   Plot_comp__1->SetBinContent(32,26);
   Plot_comp__1->SetBinContent(33,30);
   Plot_comp__1->SetBinContent(34,29);
   Plot_comp__1->SetBinContent(35,28);
   Plot_comp__1->SetBinContent(36,29);
   Plot_comp__1->SetBinContent(37,27);
   Plot_comp__1->SetBinError(1,27);
   Plot_comp__1->SetBinError(2,37);
   Plot_comp__1->SetBinError(3,46);
   Plot_comp__1->SetBinError(4,49);
   Plot_comp__1->SetBinError(5,51);
   Plot_comp__1->SetBinError(6,44);
   Plot_comp__1->SetBinError(7,41);
   Plot_comp__1->SetBinError(8,36);
   Plot_comp__1->SetBinError(9,33);
   Plot_comp__1->SetBinError(10,28);
   Plot_comp__1->SetBinError(11,25);
   Plot_comp__1->SetBinError(12,23);
   Plot_comp__1->SetBinError(13,19);
   Plot_comp__1->SetBinError(14,16);
   Plot_comp__1->SetBinError(15,12);
   Plot_comp__1->SetBinError(16,10);
   Plot_comp__1->SetBinError(17,12);
   Plot_comp__1->SetBinError(18,14);
   Plot_comp__1->SetBinError(19,14);
   Plot_comp__1->SetBinError(20,14);
   Plot_comp__1->SetBinError(21,15);
   Plot_comp__1->SetBinError(22,15);
   Plot_comp__1->SetBinError(23,13);
   Plot_comp__1->SetBinError(24,12);
   Plot_comp__1->SetBinError(25,12);
   Plot_comp__1->SetBinError(26,13);
   Plot_comp__1->SetBinError(27,16);
   Plot_comp__1->SetBinError(28,19);
   Plot_comp__1->SetBinError(29,18);
   Plot_comp__1->SetBinError(30,20);
   Plot_comp__1->SetBinError(31,22);
   Plot_comp__1->SetBinError(32,26);
   Plot_comp__1->SetBinError(33,30);
   Plot_comp__1->SetBinError(34,29);
   Plot_comp__1->SetBinError(35,28);
   Plot_comp__1->SetBinError(36,29);
   Plot_comp__1->SetBinError(37,27);
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
   0.521262,
   0,
   0.3703704,
   0,
   0.3631082,
   0,
   0.4516712,
   0,
   0.5611672,
   0,
   0.5037037,
   0,
   0.5847953,
   0,
   0.8024691,
   0,
   0.6790123,
   0,
   0.6878307,
   0,
   0.6419753,
   0,
   0.7407407,
   0,
   0.6790123,
   0,
   0.6018519,
   0,
   0.5349794,
   0,
   0.5050505,
   0,
   0.5185185,
   0,
   0.5026455,
   0,
   0.521262};
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
