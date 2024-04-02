//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================
//
// Specialized generic detector constructor
// 
//==========================================================================
#include "DD4hep/DetFactoryHelper.h"
#include "DD4hep/OpticalSurfaces.h"



using namespace std;
using namespace dd4hep;
using namespace dd4hep::detail;

static Ref_t create_detector(Detector& description, xml_h e, SensitiveDetector sens)  {

  std::cout<<"Creating DRCrystal"<<std::endl;

  static double tol = 0.0;
  // material to underly it all
  Material      air       = description.air();



  xml_det_t     x_det     = e;


  // for volume tags in detector
  int           det_id    = x_det.id();
  std::cout<<" det_id is "<<det_id<<std::endl;
  string        det_name  = x_det.nameStr();
  std::cout<<" det_name is .. "<<det_name<<std::endl;








  // look in DDCore/include/Parsers/detail/Dimension.h for arguments
  xml_comp_t    x_dim     = x_det.dimensions();


  double hwidth   = x_dim.width()/2.;
  double hzmax = x_dim.z_length()/2.;
  double Gr_wd = x_dim.gap()/2.; //Thickness of silicone grease in cm
  double SiPM_wd_in = x_dim.depth()/2.; //Thickness of SiPMs in cm
  double SiPM_wd_out = x_dim.end()/2.; //Thickness of SiPMs in cm

  double Resin_wd = x_dim.r_size()/2.; //Thickness of Silicone resin window in cm

  double Rough_long = x_dim.theta(); //Roughness of the face (stddev from the surface normal) for specular lobe reflection

  std::cout<<"half width zmax are "<<hwidth<<" "<<hzmax<<std::endl;
  std::cout<<"grease width sipm width are "<<Gr_wd<<" "<<SiPM_wd_in << " " << SiPM_wd_out <<std::endl;

  OpticalSurfaceManager surfMgr = description.surfaceManager();
  float sq_in = 0.6; //SiPM square side in cm
  float sq_out = 0.64; //SiPM outside (with resin) square side in cm
  // these refer to different fields in the xml file for this detector
  xml_comp_t fX_struct( x_det.child( _Unicode(structure) ) );
  xml_comp_t fX_sipm_l1( fX_struct.child( _Unicode(shape) ) );
  xml_comp_t fX_sipm_l2( fX_struct.child( _Unicode(chamber) ) );
  xml_comp_t fX_sipm_l3( fX_struct.child( _Unicode(disk) ) );
  xml_comp_t fX_sipm_l4( fX_struct.child( _Unicode(envelope) ) );

  xml_comp_t fX_resin_l1( fX_struct.child( _Unicode(eval) ) );
  xml_comp_t fX_resin_l2( fX_struct.child( _Unicode(eval) ) );
  xml_comp_t fX_resin_l3( fX_struct.child( _Unicode(eval) ) );
  xml_comp_t fX_resin_l4( fX_struct.child( _Unicode(eval) ) );

  xml_comp_t fX_siliconel( fX_struct.child( _Unicode(gap) ) );
  xml_comp_t fX_crystal( fX_struct.child( _Unicode(slice) ) );
  xml_comp_t fX_siliconer( fX_struct.child( _Unicode(tube) ) );

  xml_comp_t fX_resin_r1( fX_struct.child( _Unicode(eval) ) );
  xml_comp_t fX_resin_r2( fX_struct.child( _Unicode(eval) ) );
  xml_comp_t fX_resin_r3( fX_struct.child( _Unicode(eval) ) );
  xml_comp_t fX_resin_r4( fX_struct.child( _Unicode(eval) ) );  

  xml_comp_t fX_sipm_r1( fX_struct.child( _Unicode(module) ) );
  xml_comp_t fX_sipm_r2( fX_struct.child( _Unicode(element) ) );
  xml_comp_t fX_sipm_r3( fX_struct.child( _Unicode(frame) ) );
  xml_comp_t fX_sipm_r4( fX_struct.child( _Unicode(ladder) ) );
  xml_comp_t fX_teflon( fX_struct.child( _Unicode(beampipe) ) );

  xml_comp_t fX_sipm_l1_out( fX_struct.child( _Unicode(shape) ) );
  xml_comp_t fX_sipm_l2_out( fX_struct.child( _Unicode(chamber) ) );
  xml_comp_t fX_sipm_l3_out( fX_struct.child( _Unicode(disk) ) );
  xml_comp_t fX_sipm_l4_out( fX_struct.child( _Unicode(envelope) ) );

  xml_comp_t fX_sipm_r1_out( fX_struct.child( _Unicode(module) ) );
  xml_comp_t fX_sipm_r2_out( fX_struct.child( _Unicode(element) ) );
  xml_comp_t fX_sipm_r3_out( fX_struct.child( _Unicode(frame) ) );
  xml_comp_t fX_sipm_r4_out( fX_struct.child( _Unicode(ladder) ) );



  DetElement    sdet      (det_name,det_id);
  Volume        motherVol = description.pickMotherVolume(sdet);


  Box hedra  (10.*hwidth,10.*hwidth, 10.*hzmax);
  Volume        envelope  (det_name,hedra,air);
  PlacedVolume  env_phv   = motherVol.placeVolume(envelope,RotationZYX(0,0,0));

  env_phv.addPhysVolID("system",det_id);
  sdet.setPlacement(env_phv);  // associate the placed volume to the detector element
  sens.setType("calorimeter");
  envelope.setSensitiveDetector(sens); //To make the world sensitive to get steps visible in spew

  Position a_pos(0.,0.,0.);

  // make crystal
  std::cout<<"making crystal"<<std::endl;
  dd4hep::Box c_box(hwidth,hwidth,hzmax);
  dd4hep::Volume s_vol_crystal("crystal",c_box,description.material(fX_crystal.materialStr()));
  s_vol_crystal.setAttributes(description,fX_crystal.regionStr(),fX_crystal.limitsStr(),fX_crystal.visStr());
  if ( fX_crystal.isSensitive() ) {
    s_vol_crystal.setSensitiveDetector(sens);
  }
  DetElement crystal_det("crystal",det_id);
  a_pos={0.,0.,0.};
  PlacedVolume  crystal_phv   = envelope.placeVolume(s_vol_crystal,a_pos);
  crystal_phv.addPhysVolID("slice",1);
  crystal_det.setPlacement(crystal_phv);
  crystal_phv.addPhysVolID("system",det_id);

  OpticalSurface cryS  = surfMgr.opticalSurface("/world/"+det_name+"#dielectricSurface"); //rough, smearing of distribution?
  std::cout << "Default roughness of the ground surface for specular lobe reflection is " << cryS->GetSigmaAlpha() << std::endl;
  
  cryS->SetSigmaAlpha(Rough_long); //smooth even though lobe reflection is happening
  std::cout << "Roughness set in the code is " << cryS->GetSigmaAlpha() << std::endl;

  OpticalSurface cookie  = surfMgr.opticalSurface("/world/"+det_name+"#cookieSurface"); //rough, smearing of distribution?

  BorderSurface haha = BorderSurface(description,sdet, "HallCrys", cryS, crystal_phv,env_phv);
  haha.isValid();

  //Left side silicone cookie
  std::cout<<"making left silicone cookie"<<std::endl;
  dd4hep::Tube s_tube_l(0.,hwidth,Gr_wd,0.*deg,360*deg); //Cylindrical tube
  dd4hep::Volume s_vol_sil_gap_l("Sil_gap_l",s_tube_l,description.material(fX_siliconel.materialStr()));
  s_vol_sil_gap_l.setAttributes(description,fX_siliconel.regionStr(),fX_siliconel.limitsStr(),fX_siliconel.visStr());
  if ( fX_siliconel.isSensitive() ) {
    s_vol_sil_gap_l.setSensitiveDetector(sens);
  }
  DetElement sil_gap_l_det("sil_gap_l",det_id);
  a_pos={0.,0.,-hzmax-Gr_wd};
  PlacedVolume  sil_gap_l_phv   = envelope.placeVolume(s_vol_sil_gap_l,a_pos);
  sil_gap_l_phv.addPhysVolID("slice",2);
  sil_gap_l_det.setPlacement(sil_gap_l_phv);
  sil_gap_l_phv.addPhysVolID("system",det_id);

  BorderSurface haha_left = BorderSurface(description,sdet, "HallCrys_left", cookie, sil_gap_l_phv,env_phv);
  haha_left.isValid();

  //Right side silicone cookie
  std::cout<<"making right silicone cookie"<<std::endl;
  dd4hep::Tube s_tube_r(0.,hwidth,Gr_wd,0.*deg,360*deg); //Cylindrical tube
  dd4hep::Volume s_vol_sil_gap_r("Sil_gap_r",s_tube_r,description.material(fX_siliconer.materialStr()));
  s_vol_sil_gap_r.setAttributes(description,fX_siliconer.regionStr(),fX_siliconer.limitsStr(),fX_siliconer.visStr());
  if ( fX_siliconer.isSensitive() ) {
    s_vol_sil_gap_r.setSensitiveDetector(sens);
  }
  DetElement sil_gap_r_det("sil_gap_r",det_id);
  a_pos={0.,0.,hzmax+Gr_wd};
  PlacedVolume  sil_gap_r_phv   = envelope.placeVolume(s_vol_sil_gap_r,a_pos);
  sil_gap_r_phv.addPhysVolID("slice",3);
  sil_gap_r_det.setPlacement(sil_gap_r_phv);
  sil_gap_r_phv.addPhysVolID("system",det_id);

  BorderSurface haha_right = BorderSurface(description,sdet, "HallCrys_right", cookie, sil_gap_r_phv,env_phv);
  haha_right.isValid();



  float x[4] = {0.425,-0.425,0.425,-0.425};
  float y[4] = {0.425,0.425,-0.425,-0.425};

  xml_comp_t sipm_left[4] = {fX_sipm_l1,fX_sipm_l2,fX_sipm_l3,fX_sipm_l4};
  xml_comp_t resin_left[4] = {fX_resin_l1,fX_resin_l2,fX_resin_l3,fX_resin_l4};
  Position a_pos_shift = {0.,0.,0.};
  //Making left sipms
  for(int i=0;i<4;i++)
  {
  std::cout<<"making sipm left "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box s_box_l(sq_in/2,sq_in/2,SiPM_wd_in);
  dd4hep::Volume s_vol_sipml("Sipml",s_box_l,description.material(sipm_left[i].materialStr()));
  s_vol_sipml.setAttributes(description,sipm_left[i].regionStr(),sipm_left[i].limitsStr(),sipm_left[i].visStr());
  if ( sipm_left[i].isSensitive() ) {
    s_vol_sipml.setSensitiveDetector(sens);
  }
  DetElement sipml_det("sipml",det_id);
  a_pos={x[i],y[i],-hzmax-2*(Gr_wd+Resin_wd)-SiPM_wd_in};
  PlacedVolume  sipml_phv   = envelope.placeVolume(s_vol_sipml,a_pos);
  sipml_phv.addPhysVolID("slice",i+4);
  sipml_det.setPlacement(sipml_phv);
  sipml_phv.addPhysVolID("system",det_id);

  a_pos_shift = {0.,0.,-Resin_wd};
  std::cout<<"making resin left "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box r_box_l_out(sq_out/2,sq_out/2,Resin_wd+SiPM_wd_in);

  dd4hep::Solid resin_l = SubtractionSolid(r_box_l_out,s_box_l,a_pos_shift);

  dd4hep::Volume s_vol_resinl("resinl",resin_l,description.material(resin_left[i].materialStr()));
  s_vol_resinl.setAttributes(description,resin_left[i].regionStr(),resin_left[i].limitsStr(),resin_left[i].visStr());
  if ( resin_left[i].isSensitive() ) {
    s_vol_resinl.setSensitiveDetector(sens);
  }
  DetElement resinl_det("resinl",det_id);
  a_pos={x[i],y[i],-hzmax-2*Gr_wd-Resin_wd-SiPM_wd_in};
  PlacedVolume  resinl_phv   = envelope.placeVolume(s_vol_resinl,a_pos);
  resinl_phv.addPhysVolID("slice",i+8);
  resinl_det.setPlacement(resinl_phv);
  resinl_phv.addPhysVolID("system",det_id);

  }




  xml_comp_t sipm_right[4] = {fX_sipm_r1,fX_sipm_r2,fX_sipm_r3,fX_sipm_r4};
  xml_comp_t resin_right[4] = {fX_resin_r1,fX_resin_r2,fX_resin_r3,fX_resin_r4};  
  //Making right sipms
  for(int i=0;i<4;i++)
  {    
  std::cout<<"making sipm right "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box s_box_r(sq_in/2,sq_in/2,SiPM_wd_in);
  dd4hep::Volume s_vol_sipmr("Sipmr",s_box_r,description.material(sipm_right[i].materialStr()));
  s_vol_sipmr.setAttributes(description,sipm_right[i].regionStr(),sipm_right[i].limitsStr(),sipm_right[i].visStr());
  if ( sipm_right[i].isSensitive() ) {
    s_vol_sipmr.setSensitiveDetector(sens);
  }
  DetElement sipmr_det("sipmr",det_id);
  a_pos={x[i],y[i],hzmax+2*(Gr_wd+Resin_wd)+SiPM_wd_in};
  PlacedVolume  sipmr_phv   = envelope.placeVolume(s_vol_sipmr,a_pos);
  sipmr_phv.addPhysVolID("slice",i+12);
  sipmr_det.setPlacement(sipmr_phv);
  sipmr_phv.addPhysVolID("system",det_id);

  a_pos_shift = {0.,0.,Resin_wd};
  std::cout<<"making resin right "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box r_box_r_out(sq_out/2,sq_out/2,Resin_wd+SiPM_wd_in);

  dd4hep::Solid resin_r = SubtractionSolid(r_box_r_out,s_box_r,a_pos_shift);

  dd4hep::Volume s_vol_resinr("resinr",resin_r,description.material(resin_right[i].materialStr()));
  s_vol_resinr.setAttributes(description,resin_right[i].regionStr(),resin_right[i].limitsStr(),resin_right[i].visStr());
  if ( resin_right[i].isSensitive() ) {
    s_vol_resinr.setSensitiveDetector(sens);
  }
  DetElement resinr_det("resinr",det_id);
  a_pos={x[i],y[i],hzmax+2*Gr_wd+Resin_wd+SiPM_wd_in};
  PlacedVolume  resinr_phv   = envelope.placeVolume(s_vol_resinr,a_pos);
  resinr_phv.addPhysVolID("slice",i+16);
  resinr_det.setPlacement(resinr_phv);
  resinr_phv.addPhysVolID("system",det_id);

  }



  
  //Making left resins
  /*
  for(int i=0;i<4;i++)
  {    
  std::cout<<"making resin left "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box r_box_l(sq_out/2,sq_out/2,Resin_wd);
  dd4hep::Volume s_vol_resinl("resinl",r_box_l,description.material(resin_left[i].materialStr()));
  s_vol_resinl.setAttributes(description,resin_left[i].regionStr(),resin_left[i].limitsStr(),resin_left[i].visStr());
  if ( resin_left[i].isSensitive() ) {
    s_vol_resinl.setSensitiveDetector(sens);
  }
  DetElement resinl_det("resinl",det_id);
  a_pos={x[i],y[i],-hzmax-2*Gr_wd-Resin_wd};
  PlacedVolume  resinl_phv   = envelope.placeVolume(s_vol_resinl,a_pos);
  resinl_phv.addPhysVolID("slice",i+12);
  resinl_det.setPlacement(resinl_phv);
  resinl_phv.addPhysVolID("system",det_id);
  }
  */


  
  //Making right resins
  /*
  for(int i=0;i<4;i++)
  {
  std::cout<<"making resin right "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box r_box_r(sq_out/2,sq_out/2,Resin_wd);
  dd4hep::Volume s_vol_resinr("resinr",r_box_r,description.material(resin_right[i].materialStr()));
  s_vol_resinr.setAttributes(description,resin_right[i].regionStr(),resin_right[i].limitsStr(),resin_right[i].visStr());
  if ( resin_right[i].isSensitive() ) {
    s_vol_resinr.setSensitiveDetector(sens);
  }
  DetElement resinr_det("resinr",det_id);
  a_pos={x[i],y[i],hzmax+2*Gr_wd+Resin_wd};
  PlacedVolume  resinr_phv   = envelope.placeVolume(s_vol_resinr,a_pos);
  resinr_phv.addPhysVolID("slice",i+16);
  resinr_det.setPlacement(resinr_phv);
  resinr_phv.addPhysVolID("system",det_id);
  }
  */



  xml_comp_t sipm_left_out[4] = {fX_sipm_l1_out,fX_sipm_l2_out,fX_sipm_l3_out,fX_sipm_l4_out};
  //Making left sipms not surrounded by resins
  for(int i=0;i<4;i++)
  {
  std::cout<<"making sipm left out "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box s_box_l_out(sq_out/2,sq_out/2,SiPM_wd_out);
  dd4hep::Volume s_vol_sipml_out("Sipml_out",s_box_l_out,description.material(sipm_left_out[i].materialStr()));
  s_vol_sipml_out.setAttributes(description,sipm_left_out[i].regionStr(),sipm_left_out[i].limitsStr(),sipm_left_out[i].visStr());
  if ( sipm_left_out[i].isSensitive() ) {
    s_vol_sipml_out.setSensitiveDetector(sens);
  }
  DetElement sipml_det_out("sipml",det_id);
  a_pos={x[i],y[i],-hzmax-2*(Gr_wd+Resin_wd+SiPM_wd_in)-SiPM_wd_out};
  PlacedVolume  sipml_phv_out   = envelope.placeVolume(s_vol_sipml_out,a_pos);
  sipml_phv_out.addPhysVolID("slice",i+20);
  sipml_det_out.setPlacement(sipml_phv_out);
  sipml_phv_out.addPhysVolID("system",det_id);
  }




  xml_comp_t sipm_right_out[4] = {fX_sipm_r1_out,fX_sipm_r2_out,fX_sipm_r3_out,fX_sipm_r4_out};
  //Making right sipms not surrounded by resins
  for(int i=0;i<4;i++)
  {    
  std::cout<<"making sipm right out "+ std::to_string(i+1) <<std::endl;
  dd4hep::Box s_box_r_out(sq_out/2,sq_out/2,SiPM_wd_out);
  dd4hep::Volume s_vol_sipmr_out("Sipmr_out",s_box_r_out,description.material(sipm_right_out[i].materialStr()));
  s_vol_sipmr_out.setAttributes(description,sipm_right_out[i].regionStr(),sipm_right_out[i].limitsStr(),sipm_right_out[i].visStr());
  if ( sipm_right_out[i].isSensitive() ) {
    s_vol_sipmr_out.setSensitiveDetector(sens);
  }
  DetElement sipmr_det_out("sipmr",det_id);
  a_pos={x[i],y[i],hzmax+2*(Gr_wd+Resin_wd+SiPM_wd_in)+SiPM_wd_out};
  PlacedVolume  sipmr_phv_out   = envelope.placeVolume(s_vol_sipmr_out,a_pos);
  sipmr_phv_out.addPhysVolID("slice",i+24);
  sipmr_det_out.setPlacement(sipmr_phv_out);
  sipmr_phv_out.addPhysVolID("system",det_id);
  }

  std::cout<<"exiting DRCrystal creator"<<std::endl;

  return sdet;
}

DECLARE_DETELEMENT(DD4hep_DRCrystal,create_detector)

DECLARE_DEPRECATED_DETELEMENT(DRCrystal,create_detector)
