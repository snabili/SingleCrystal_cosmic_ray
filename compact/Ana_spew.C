#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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


using namespace std;

void print_vector_s(vector<string> const &ptr) //function to print a vector of strings
{
 for(unsigned int i=0; i<ptr.size(); i++)
 {
  cout << ptr.at(i) << endl;
 }
 cout << endl;
}

void print_vector_d(vector<float> const &ptrd) //function to print a vector of double (floating point numbers)
{
 for(unsigned int i=0; i<ptrd.size(); i++)
 {
  cout << ptrd.at(i) << ' ';
 }
 cout << endl;
}

struct step_details
{
 float SceCount, step_num, x_in, y_in, z_in, x_fin, y_fin, z_fin, wvln;
 string Sce_mat;
};

void print_vector_struct(vector<step_details> const &ptrst) //function to print a vector of double (floating point numbers)
{
 for(unsigned int i=0; i<ptrst.size(); i++)
 {
  std::cout << ptrst.at(i).SceCount << " " << ptrst.at(i).step_num << " " << ptrst.at(i).x_in << " " << ptrst.at(i).y_in << " " << ptrst.at(i).z_in << " " << ptrst.at(i).x_fin << " " << ptrst.at(i).y_fin << " " << ptrst.at(i).z_fin << " " << ptrst.at(i).wvln << " " << ptrst.at(i).Sce_mat << std::endl;
 }
 std::cout << std::endl;
}

void print_struct(step_details const &st)
{
  std::cout << st.SceCount << " " << st.step_num << " " << st.x_in << " " << st.y_in << " " << st.z_in << " " << st.x_fin << " " << st.y_fin << " " << st.z_fin << " " << st.wvln << " " << st.Sce_mat << std::endl; 
}


void Ana_spew()
{
 ifstream file;
 file.open("out_0908_-10.txt");
 //out_0818_-10_1.txt
 //out_0903_-20
 //out_0905_-10
 char output[500];
 vector<string> output_list;

 if (file.is_open())
 {
  while(!file.eof())
  {
   file >> output; 
   output_list.push_back(output);
  }
 }
 
 file.close();
//print_vector_s(output_list);

int i=0; //counting variable for how many photons are produced in killMedia
int No_TR=0;
int y_1_pos=0;
int x_1_pos=0;
int y_1_35=0;
double pi = 4*atan(1.0);
std::vector<step_details> prod_step;
std::vector<bool> prod_cut;
std::vector<step_details> SCE_step;

for(unsigned int j=0; j<output_list.size(); j++)
{
 if(output_list.at(j)=="SCECOUNT")
 {
  step_details cur_step;
  cur_step.SceCount = atof(output_list.at(j+2).c_str());
  cur_step.step_num = atof(output_list.at(j+36).c_str());
  cur_step.Sce_mat = output_list.at(j+15);
  int x_init = 43;
  int x_fin = 56;

  cur_step.x_in = atof(output_list.at(j+x_init).c_str());
  cur_step.y_in = atof(output_list.at(j+x_init+3).c_str());
  cur_step.z_in = atof(output_list.at(j+x_init+6).c_str());

  cur_step.x_fin = atof(output_list.at(j+x_fin).c_str());
  cur_step.y_fin = atof(output_list.at(j+x_fin+3).c_str());
  cur_step.z_fin = atof(output_list.at(j+x_fin+6).c_str());

  cur_step.wvln = atof(output_list.at(j+82).c_str());
  SCE_step.push_back(cur_step);
 }
}


std::cout << SCE_step.size() << std::endl;
//print_vector_struct(SCE_step);

for(int j=0; j<SCE_step.size();j++)
{
 if(SCE_step.at(j).step_num == 1 && SCE_step.at(j).Sce_mat == "PbF2")
 {
  prod_step.push_back(SCE_step.at(j));
  i+=1;
  if(SCE_step.at(j).x_in == SCE_step.at(j).x_fin && SCE_step.at(j).y_in == SCE_step.at(j).y_fin && SCE_step.at(j).z_in == SCE_step.at(j).z_fin){No_TR+=1;}
  else if(SCE_step.at(j).y_fin == 12.5) //"Normal" first reflection inside the cone
  {
   y_1_pos+=1;
   float cos_comp = (SCE_step.at(j).y_fin-SCE_step.at(j).y_in)/sqrt(pow((SCE_step.at(j).x_fin-SCE_step.at(j).x_in),2)+pow((SCE_step.at(j).y_fin-SCE_step.at(j).y_in),2)+pow((SCE_step.at(j).z_fin-SCE_step.at(j).z_in),2));
   float angle_y_1= acos(cos_comp)*180.0/pi;
   std::cout << SCE_step.at(j).SceCount << " Angle of first y incidence " << angle_y_1 << std::endl;
   std::cout << SCE_step.at(j).z_fin-SCE_step.at(j).z_in << std::endl;
   if(angle_y_1 > 37.0)
   {
    y_1_35+=1;
    std::cout << SCE_step.at(j).SceCount << " Outside TIR " << angle_y_1 << std::endl;
   }
   std::cout << std::endl;
  }
 }
}

std::cout << "Populated the photon count array " << std::endl;
TMultiGraph* filter_step = new TMultiGraph();
filter_step->SetName("filter_step");
TGraph* step_indv;
TH1F* angle_side = new TH1F("angle_side","angle_side",360,-180.,180.);
float angle_y, angle_beam;
//float y_20 = 0.9397, z_20 = -0.342; //20 deg
float y_20 = 0.9848, z_20 = -0.17365; //10 deg
std::cout << prod_step.size() << std::endl;
for(int j=0; j<prod_step.size();j++)
{
 angle_y= acos((prod_step.at(j).y_fin-prod_step.at(j).y_in)/sqrt(pow((prod_step.at(j).x_fin-prod_step.at(j).x_in),2)+pow((prod_step.at(j).y_fin-prod_step.at(j).y_in),2)+pow((prod_step.at(j).z_fin-prod_step.at(j).z_in),2)))*180.0/pi; 
 angle_beam = acos(((prod_step.at(j).y_fin-prod_step.at(j).y_in)*y_20 + (prod_step.at(j).z_fin-prod_step.at(j).z_in)*z_20)/sqrt(pow((prod_step.at(j).x_fin-prod_step.at(j).x_in),2)+pow((prod_step.at(j).y_fin-prod_step.at(j).y_in),2)+pow((prod_step.at(j).z_fin-prod_step.at(j).z_in),2)))*180.0/pi;
 //print_struct(prod_step.at(j));
 //std::cout << angle_y << std::endl;
 //if(prod_step.at(j).y_fin == 12.5)
 if(!(prod_step.at(j).x_in == prod_step.at(j).x_fin && prod_step.at(j).y_in == prod_step.at(j).y_fin && prod_step.at(j).z_in == prod_step.at(j).z_fin)) //All photons that are transmitted
 { 
  //print_struct(prod_step.at(j));
  std::cout << angle_y << std::endl;
  /*
  if(prod_step.at(j).z_fin-prod_step.at(j).z_in > 0){angle_side->Fill(-angle_y);}
  else if(prod_step.at(j).z_fin-prod_step.at(j).z_in <= 0){angle_side->Fill(angle_y);}
  */
  //angle_side->Fill(angle_beam); //Angle distribution in cone wrt beam direction

 }
}

std::cout << "Reached here MMP" << std::endl;
float j_end;
int num_cut=0;
/*
for(int j=0; j<prod_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
{
  prod_cut.push_back(0); //Default
  if(j==prod_step.size()-1){j_end = SCE_step.size()+1;}
  else{j_end = prod_step.at(j+1).SceCount;}

  for(int i=prod_step.at(j).SceCount+1;i<j_end;i++) //Obviously exclude the first step
  {
   if(SCE_step.at(i-1).Sce_mat == "PbF2" && SCE_step.at(i-1).z_fin == -30 && SCE_step.at(i-1).y_fin <=-1.25 && SCE_step.at(i-1).y_fin >= -7.25)
   {
    prod_cut.at(j) = 1;
    num_cut++;
    break; //exit the loop for that particular track altogether
   }
  }
}
*/

//Reached the PbF2 end and also reached the silicone grease
///*
for(int j=0; j<prod_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
{
  prod_cut.push_back(0); //Default
  if(j==prod_step.size()-1){j_end = SCE_step.size()+1;}
  else{j_end = prod_step.at(j+1).SceCount;}

  for(int i=prod_step.at(j).SceCount+1;i<j_end;i++)
  {
    if(SCE_step.at(i-1).Sce_mat == "Silicone_gap" && SCE_step.at(i-1).z_fin == -31 && SCE_step.at(i-1).y_fin <=-1.25 && SCE_step.at(i-1).y_fin >= -7.25)
    {
    prod_cut.at(j) = 1;
    num_cut++;
    break;
    }
  }
}
//*/

//Reached the PbF2 end, reached the silicone grease and also reached the SiPMs or the outside air
/*
for(int j=0; j<prod_step.size();j++) //Making a new vector of photons at the production step, which satisfy the cuts
{
  prod_cut.push_back(0); //Default
  if(j==prod_step.size()-1){j_end = SCE_step.size()+1;}
  else{j_end = prod_step.at(j+1).SceCount;}
  int Crys_z;
  for(int i=prod_step.at(j).SceCount+1;i<j_end;i++) //Obviously exclude the first step
  {
   if(SCE_step.at(i-1).Sce_mat == "PbF2" && SCE_step.at(i-1).z_fin == -30)
   {
    Crys_z = i; //first instance of hitting the leftmost face of the crystal (z=-30)
    std::cout << "Crystal_z in first loop " << Crys_z << std::endl;
    break; //exit the loop for that particular track altogether
   }
  }

  for(int i=SCE_step.at(Crys_z-1).SceCount+1;i<j_end;i++)
  {
    //std::cout << "Crystal_z " << SCE_step.at(Crys_z-1).SceCount+1 << std::endl;
    if(SCE_step.at(i-1).Sce_mat == "Silicone_gap" && SCE_step.at(i-1).z_fin == -31)
    {
     grease_z = i;
     break;
    }
  }

  for(int i=SCE_step.at(grease_z-1).SceCount+1;i<j_end;i++)
  {
    if((SCE_step.at(i-1).Sce_mat == "Silicone_gap" || )&& SCE_step.at(i-1).z_fin == -31 && SCE_step.at(i-1).y_fin <=-1.25 && SCE_step.at(i-1).y_fin >= -7.25)
    {
    prod_cut.at(j) = 1;
    num_cut++;
    break;
    }   
  }
}
*/

std::cout << num_cut << std::endl;
int track_count=0;
TCanvas *c_display = new TCanvas("c_display","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
for(int j=0; j<prod_step.size();j++)
{
 if(prod_step.at(j).y_fin == 12.5 && prod_cut.at(j) == 1) //top y surface
 //if((prod_step.at(j).x_fin == 12.5 || prod_step.at(j).x_fin == -12.5)&& prod_cut.at(j) == 1) //both side faces i.e. in x
 {
  x_1_pos++;
  std::cout << "Cut satisfied" << std::endl;
  print_struct(prod_step.at(j)); //Print only for those satisfying the cuts applied
  angle_y= acos((prod_step.at(j).y_fin-prod_step.at(j).y_in)/sqrt(pow((prod_step.at(j).x_fin-prod_step.at(j).x_in),2)+pow((prod_step.at(j).y_fin-prod_step.at(j).y_in),2)+pow((prod_step.at(j).z_fin-prod_step.at(j).z_in),2)))*180.0/pi; 
  //if(angle_y < 37.0){} //Cone limits on both sides
  /*if(prod_step.at(j).z_fin-prod_step.at(j).z_in > 0 && angle_y < 50.0){} //Cone limits on the farther side
  else
  {*/
  std::vector<float> seq_x,seq_y,seq_z;
  //angle_side->Fill(angle_y); //Angle distribution in cone wrt y direction
  if(prod_step.at(j).z_fin-prod_step.at(j).z_in > 0){angle_side->Fill(-angle_y);}
  else if(prod_step.at(j).z_fin-prod_step.at(j).z_in <= 0){angle_side->Fill(angle_y);}

  if(j==prod_step.size()-1){j_end = SCE_step.size()+1;}
  else{j_end = prod_step.at(j+1).SceCount;}
  for(int i=prod_step.at(j).SceCount;i<j_end;i++)
  {
   if(i!=prod_step.at(j).SceCount && SCE_step.at(i-1).x_in == SCE_step.at(i-1).x_fin && SCE_step.at(i-1).y_in == SCE_step.at(i-1).y_fin && SCE_step.at(i-1).z_in == SCE_step.at(i-1).z_fin && SCE_step.at(i-1).x_in == SCE_step.at(i-2).x_fin && SCE_step.at(i-1).y_in == SCE_step.at(i-2).y_fin && SCE_step.at(i-1).z_in == SCE_step.at(i-2).z_fin){}
   else if(i!=prod_step.at(j).SceCount && SCE_step.at(i-1).x_in == SCE_step.at(i-2).x_fin && SCE_step.at(i-1).y_in == SCE_step.at(i-2).y_fin && SCE_step.at(i-1).z_in == SCE_step.at(i-2).z_fin)
   {
   seq_x.push_back(SCE_step.at(i-1).x_fin);
   seq_y.push_back(SCE_step.at(i-1).y_fin);
   seq_z.push_back(SCE_step.at(i-1).z_fin);
   }
   else 
   {
   seq_x.push_back(SCE_step.at(i-1).x_in);
   seq_x.push_back(SCE_step.at(i-1).x_fin);

   seq_y.push_back(SCE_step.at(i-1).y_in);
   seq_y.push_back(SCE_step.at(i-1).y_fin);

   seq_z.push_back(SCE_step.at(i-1).z_in);
   seq_z.push_back(SCE_step.at(i-1).z_fin);
  }
  }
   print_vector_d(seq_z);
   std::cout << seq_z.size() << std::endl;
  step_indv = new TGraph(seq_z.size(),&seq_z[0],&seq_y[0]); //y-z profile
  filter_step->Add(step_indv);
  track_count++;
 //}
 }

}

 cout << "Number of photons produced " << i << endl;
 cout << "Number of photons not transmitted " << No_TR << endl;
 std::cout << "Number of photons in y cone " << y_1_pos << std::endl;
 std::cout << "Number of photons in x cone " << x_1_pos << std::endl;
 
 //print_vector_struct(prod_step);
 std::cout << "Number of tracks in display " << track_count << std::endl;
 std::cout << "Number of photons in y cone outside TIR " << y_1_35 << std::endl;

 //TCanvas *c_display = new TCanvas("c_display","Graph Draw Options", 200,10,600,400); //represents coordinates of start and end points of canvas
 ///*
 filter_step -> Draw("AL"); //Draw with axes, lines
 c_display->SetRealAspectRatio();
 //*/

 //angle_side->Draw();
 std::cout << "Drew canvas" << std::endl;
}
