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
  double SiPM_wd = x_dim.depth()/2.; //Thickness of SiPMs in cm
  double Rough_long = x_dim.theta(); //Roughness of the face (stddev from the surface normal) for specular lobe reflection

  std::cout<<"half width zmax are "<<hwidth<<" "<<hzmax<<std::endl;
  std::cout<<"grease width sipm width are "<<Gr_wd<<" "<<SiPM_wd<<std::endl;

  OpticalSurfaceManager surfMgr = description.surfaceManager();

  // these refer to different fields in the xml file for this detector
  xml_comp_t fX_struct( x_det.child( _Unicode(structure) ) );
  xml_comp_t fX_sipm_l1( fX_struct.child( _Unicode(shape) ) );
  xml_comp_t fX_sipm_l2( fX_struct.child( _Unicode(chamber) ) );
  xml_comp_t fX_sipm_l3( fX_struct.child( _Unicode(disk) ) );
  xml_comp_t fX_sipm_l4( fX_struct.child( _Unicode(envelope) ) );
  xml_comp_t fX_siliconel( fX_struct.child( _Unicode(gap) ) );
  xml_comp_t fX_crystal( fX_struct.child( _Unicode(slice) ) );
  xml_comp_t fX_siliconer( fX_struct.child( _Unicode(tube) ) );
  xml_comp_t fX_sipm_r1( fX_struct.child( _Unicode(module) ) );
  xml_comp_t fX_sipm_r2( fX_struct.child( _Unicode(element) ) );
  xml_comp_t fX_sipm_r3( fX_struct.child( _Unicode(frame) ) );
  xml_comp_t fX_sipm_r4( fX_struct.child( _Unicode(ladder) ) );
  xml_comp_t fX_teflon( fX_struct.child( _Unicode(beampipe) ) );




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


  // make sipm left 1
  std::cout<<"making sipm left 1"<<std::endl;
  dd4hep::Box s_box_l1(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipml1("Sipml1",s_box_l1,description.material(fX_sipm_l1.materialStr()));
  s_vol_sipml1.setAttributes(description,fX_sipm_l1.regionStr(),fX_sipm_l1.limitsStr(),fX_sipm_l1.visStr());
  if ( fX_sipm_l1.isSensitive() ) {
    s_vol_sipml1.setSensitiveDetector(sens);
  }
  DetElement sipml1_det("sipml1",det_id);
  a_pos={0.425,0.425,-hzmax-2*Gr_wd-SiPM_wd};
  PlacedVolume  sipml1_phv   = envelope.placeVolume(s_vol_sipml1,a_pos);
  sipml1_phv.addPhysVolID("slice",4);
  sipml1_det.setPlacement(sipml1_phv);
  sipml1_phv.addPhysVolID("system",det_id);


  // make sipm left 2
  std::cout<<"making sipm left 2"<<std::endl;
  dd4hep::Box s_box_l2(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipml2("Sipml2",s_box_l2,description.material(fX_sipm_l2.materialStr()));
  s_vol_sipml2.setAttributes(description,fX_sipm_l2.regionStr(),fX_sipm_l2.limitsStr(),fX_sipm_l2.visStr());
  if ( fX_sipm_l2.isSensitive() ) {
    s_vol_sipml2.setSensitiveDetector(sens);
  }
  DetElement sipml2_det("sipml2",det_id);
  a_pos={-0.425,0.425,-hzmax-2*Gr_wd-SiPM_wd};
  PlacedVolume  sipml2_phv   = envelope.placeVolume(s_vol_sipml2,a_pos);
  sipml2_phv.addPhysVolID("slice",5);
  sipml2_det.setPlacement(sipml2_phv);
  sipml2_phv.addPhysVolID("system",det_id);


  // make sipm left 3
  std::cout<<"making sipm left 3"<<std::endl;
  dd4hep::Box s_box_l3(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipml3("Sipml3",s_box_l3,description.material(fX_sipm_l3.materialStr()));
  s_vol_sipml3.setAttributes(description,fX_sipm_l3.regionStr(),fX_sipm_l3.limitsStr(),fX_sipm_l3.visStr());
  if ( fX_sipm_l3.isSensitive() ) {
    s_vol_sipml3.setSensitiveDetector(sens);
  }
  DetElement sipml3_det("sipml3",det_id);
  a_pos={0.425,-0.425,-hzmax-2*Gr_wd-SiPM_wd};
  PlacedVolume  sipml3_phv   = envelope.placeVolume(s_vol_sipml3,a_pos);
  sipml3_phv.addPhysVolID("slice",6);
  sipml3_det.setPlacement(sipml3_phv);
  sipml3_phv.addPhysVolID("system",det_id);

  // make sipm left 4
  std::cout<<"making sipm left 4"<<std::endl;
  dd4hep::Box s_box_l4(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipml4("Sipml4",s_box_l4,description.material(fX_sipm_l4.materialStr()));
  s_vol_sipml4.setAttributes(description,fX_sipm_l4.regionStr(),fX_sipm_l4.limitsStr(),fX_sipm_l4.visStr());
  if ( fX_sipm_l4.isSensitive() ) {
    s_vol_sipml4.setSensitiveDetector(sens);
  }
  DetElement sipml4_det("sipml4",det_id);
  a_pos={-0.425,-0.425,-hzmax-2*Gr_wd-SiPM_wd};
  PlacedVolume  sipml4_phv   = envelope.placeVolume(s_vol_sipml4,a_pos);
  sipml4_phv.addPhysVolID("slice",7);
  sipml4_det.setPlacement(sipml4_phv);
  sipml4_phv.addPhysVolID("system",det_id);



  // make sipm right 1
  std::cout<<"making sipm right 1"<<std::endl;
  dd4hep::Box s_box_r1(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipmr1("Sipmr1",s_box_r1,description.material(fX_sipm_r1.materialStr()));
  s_vol_sipmr1.setAttributes(description,fX_sipm_r1.regionStr(),fX_sipm_r1.limitsStr(),fX_sipm_r1.visStr());
  if ( fX_sipm_r1.isSensitive() ) {
    s_vol_sipmr1.setSensitiveDetector(sens);
  }
  DetElement sipmr1_det("sipmr1",det_id);
  a_pos={0.425,0.425,hzmax+2*Gr_wd+SiPM_wd};
  PlacedVolume  sipmr1_phv   = envelope.placeVolume(s_vol_sipmr1,a_pos);
  sipmr1_phv.addPhysVolID("slice",8);
  sipmr1_det.setPlacement(sipmr1_phv);
  sipmr1_phv.addPhysVolID("system",det_id);

  // make sipm right 2
  std::cout<<"making sipm right 2"<<std::endl;
  dd4hep::Box s_box_r2(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipmr2("Sipmr2",s_box_r2,description.material(fX_sipm_r2.materialStr()));
  s_vol_sipmr2.setAttributes(description,fX_sipm_r2.regionStr(),fX_sipm_r2.limitsStr(),fX_sipm_r2.visStr());
  if ( fX_sipm_r2.isSensitive() ) {
    s_vol_sipmr2.setSensitiveDetector(sens);
  }
  DetElement sipmr2_det("sipmr2",det_id);
  a_pos={-0.425,0.425,hzmax+2*Gr_wd+SiPM_wd};
  PlacedVolume  sipmr2_phv   = envelope.placeVolume(s_vol_sipmr2,a_pos);
  sipmr2_phv.addPhysVolID("slice",9);
  sipmr2_det.setPlacement(sipmr2_phv);
  sipmr2_phv.addPhysVolID("system",det_id);

  // make sipm right 3
  std::cout<<"making sipm right 3"<<std::endl;
  dd4hep::Box s_box_r3(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipmr3("Sipmr3",s_box_r3,description.material(fX_sipm_r3.materialStr()));
  s_vol_sipmr3.setAttributes(description,fX_sipm_r3.regionStr(),fX_sipm_r3.limitsStr(),fX_sipm_r3.visStr());
  if ( fX_sipm_r3.isSensitive() ) {
    s_vol_sipmr3.setSensitiveDetector(sens);
  }
  DetElement sipmr3_det("sipmr3",det_id);
  a_pos={0.425,-0.425,hzmax+2*Gr_wd+SiPM_wd};
  PlacedVolume  sipmr3_phv   = envelope.placeVolume(s_vol_sipmr3,a_pos);
  sipmr3_phv.addPhysVolID("slice",10);
  sipmr3_det.setPlacement(sipmr3_phv);
  sipmr3_phv.addPhysVolID("system",det_id);

  // make sipm right 4
  std::cout<<"making sipm right 4"<<std::endl;
  dd4hep::Box s_box_r4(0.6/2,0.6/2,SiPM_wd);
  dd4hep::Volume s_vol_sipmr4("Sipmr4",s_box_r4,description.material(fX_sipm_r4.materialStr()));
  s_vol_sipmr4.setAttributes(description,fX_sipm_r4.regionStr(),fX_sipm_r4.limitsStr(),fX_sipm_r4.visStr());
  if ( fX_sipm_r4.isSensitive() ) {
    s_vol_sipmr4.setSensitiveDetector(sens);
  }
  DetElement sipmr4_det("sipmr4",det_id);
  a_pos={-0.425,-0.425,hzmax+2*Gr_wd+SiPM_wd};
  PlacedVolume  sipmr4_phv   = envelope.placeVolume(s_vol_sipmr4,a_pos);
  sipmr4_phv.addPhysVolID("slice",11);
  sipmr4_det.setPlacement(sipmr4_phv);
  sipmr4_phv.addPhysVolID("system",det_id);


  std::cout<<"exiting DRCrystal creator"<<std::endl;

  return sdet;
}

DECLARE_DETELEMENT(DD4hep_DRCrystal,create_detector)

DECLARE_DEPRECATED_DETELEMENT(DRCrystal,create_detector)
