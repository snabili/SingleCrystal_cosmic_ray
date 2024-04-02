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

// Framework include files
#include "DualCrystalCalorimeterHit.h"
#include "DDG4/Geant4SensDetAction.inl"
#include "DDG4/Factories.h"
#include <cmath>
#include "DDG4/Geant4Random.h"







namespace CalVision {

  G4double fromEvToNm(G4double energy)
  {
    // there is some bug somewhere.  shouldn't need this factor
    return 1239.84187 / energy*1000.;
  }


  int SCECOUNT=0;
  double Cl_wd = 12.5; //half the crystal width in mm

  double Cl_Lng = 30; //half the crystal length in mm
  //double Cl_Lng = 25; //half the crystal length in mm
  double Gr_wd = 1.0; //Thickness of grease in mm on either side
  //double SiPM_wd = 1.3; //Thickness of killMedia in mm on either side
  //double SiPM_wd = 1.2; //Thickness of killMedia in mm on either side (1.35-0.15 mm)

  double SiPM_wd_in = 0.2; //Thickness of killMedia in mm on either side, surrounded by resin window
  double SiPM_wd_out = 1.0; //Thickness of killMedia in mm on either side, 'outside' resin window

  double Res_wd = 0.15; //Thickness of Silicone (or epoxy?) resin window in mm on either side (for each SiPM)

  //double Res_wd = 1.0; //Magnified Resin thickness for visibility in display

  class DualCrystalCalorimeterSD {
  public:
    typedef DualCrystalCalorimeterHit Hit;
    // If we need special data to personalize the action, be put it here
    //int mumDeposits = 0;
    //double integratedDeposit = 0;
  };
}

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {
  /// Namespace for the Geant4 based simulation part of the AIDA detector description toolkit
  namespace sim   {

    using namespace CalVision;
    
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //               Geant4SensitiveAction<MyTrackerSD>
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /** \addtogroup Geant4SDActionPlugin
     *
     * @{
     * \package DualCrystalCalorimeterSDAction
     *
     * @}
     */

    /// Define collections created by this sensitivie action object
    template <> void Geant4SensitiveAction<DualCrystalCalorimeterSD>::defineCollections()    {
      m_collectionID = declareReadoutFilteredCollection<CalVision::DualCrystalCalorimeterSD::Hit>();
    }

    /// Method for generating hit(s) using the information of G4Step object.
    template <> bool Geant4SensitiveAction<DualCrystalCalorimeterSD>::process(const G4Step* step,G4TouchableHistory* /*hist*/ ) {


      bool SCEPRINT=(SCECOUNT</*10000*/5);
      //if(SCEPRINT) std::cout<<"scecount is "<<SCECOUNT<<" print is "<<SCEPRINT<<std::endl;



      G4StepPoint *thePrePoint = step->GetPreStepPoint();
      G4StepPoint *thePostPoint = step->GetPostStepPoint();
      //      const G4ThreeVector &thePrePosition = thePrePoint->GetPosition();
      //const G4ThreeVector &thePostPosition = thePostPoint->GetPosition();
      G4VPhysicalVolume *thePrePV = thePrePoint->GetPhysicalVolume();
      G4VPhysicalVolume *thePostPV = thePostPoint->GetPhysicalVolume();
      G4String thePrePVName = "";
      if (thePrePV)
	thePrePVName = thePrePV->GetName();
      G4String thePostPVName = "";
      if (thePostPV)
	thePostPVName = thePostPV->GetName();
      //G4Track *theTrack = step->GetTrack();
      //G4int TrPDGid = theTrack->GetDefinition()->GetPDGEncoding();

      //      if(thePrePVName.contains("slice")==0) {
      //std::cout<<"entering DualCrystalAction"<<std::endl;
      //  std::cout<<" prevolume is "<<thePrePVName<<std::endl;
      //  std::cout<<" postvolume is "<<thePostPVName<<std::endl;
      //  std::cout<<" pid is "<<TrPDGid<<std::endl;
	  //}


      Geant4StepHandler h(step);
      HitContribution contrib = DualCrystalCalorimeterHit::extractContribution(step);

      Geant4HitCollection*  coll    = collection(m_collectionID);
      VolumeID cell = 0;

      try {
        cell = cellID(step);
      } catch(std::runtime_error &e) {
	std::stringstream out;
        out << std::setprecision(20) << std::scientific;
        out << "ERROR: " << e.what()  << std::endl;
        out << "Position: "
            << "Pre (" << std::setw(24) << step->GetPreStepPoint()->GetPosition() << ") "
            << "Post (" << std::setw(24) << step->GetPostStepPoint()->GetPosition() << ") "
            << std::endl;
        out << "Momentum: "
            << " Pre (" <<std::setw(24) << step->GetPreStepPoint() ->GetMomentum()  << ") "
            << " Post (" <<std::setw(24) << step->GetPostStepPoint()->GetMomentum() << ") "
            << std::endl;

	std::cout << out.str();

        return true;
      }


      DualCrystalCalorimeterHit* hit = coll->findByKey<DualCrystalCalorimeterHit>(cell);
      if ( !hit ) {
        Geant4TouchableHandler handler(step);
	DDSegmentation::Vector3D pos = m_segmentation.position(cell);
        Position global = h.localToGlobal(pos);
        hit = new DualCrystalCalorimeterHit(global);
        hit->cellID = cell;
        coll->add(cell, hit);
        printM2("CREATE hit with deposit:%e MeV  Pos:%8.2f %8.2f %8.2f  %s",
                contrib.deposit,pos.X,pos.Y,pos.Z,handler.path().c_str());
	std::cout<<"DRcalo deposit "<<contrib.deposit<<" position ("<<pos.X<<","<<pos.Y<<","<<pos.Z<<") string "<<handler.path().c_str()<<" volume id "<<cell<<std::endl;

        if ( 0 == hit->cellID )  { // for debugging only!
          hit->cellID = cellID(step);
          except("+++ Invalid CELL ID for hit!");
        }
      } else {
	//	std::cout<<"updating old hit"<<std::endl;
      }


      G4Track * track =  step->GetTrack();

      if(SCEPRINT) std::cout<< (track->GetDefinition())->GetParticleName()<<std::endl;

      //photons
      if( track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() )  {
	if(SCEPRINT) std::cout<<"     in volume ID "<<cell<<std::endl;

	SCECOUNT+=1;
	//	if(SCEPRINT) std::cout<<"optical photon"<<std::endl;

	bool OptN = (track->GetCreatorProcess()->G4VProcess::GetProcessName() == "CerenkovPhys")||(track->GetCreatorProcess()->G4VProcess::GetProcessName() == "ScintillationPhys");

	//if(track->GetParentID()!=1) SCEPRINT=1;
	if( (track->GetCreatorProcess()->G4VProcess::GetProcessName() != "CerenkovPhys")&&(track->GetCreatorProcess()->G4VProcess::GetProcessName() != "ScintillationPhys") ) SCEPRINT=1;

	float wavelength=fromEvToNm(track->GetTotalEnergy()/eV);
	int ibin=-1;
	float binsize = (hit->wavelenmax-hit->wavelenmin)/hit->nbin;
	ibin = (wavelength-hit->wavelenmin)/binsize;

  float tof=step->GetPreStepPoint()->GetGlobalTime();
  int ibin_t=-1;
  float binsize_t = (hit->timemax-hit->timemin)/hit->nbin_t;
  ibin_t = (tof-hit->timemin)/binsize_t;
  
  int phstep = track->GetCurrentStepNumber();
	

	if ( track->GetCreatorProcess()->G4VProcess::GetProcessName() == "CerenkovPhys")
  {
	  if(SCEPRINT) std::cout<<" found cerenkov photon"<<std::endl;
	  std::string amedia = ((track->GetMaterial())->GetName());
    if(amedia.find("kill")!=std::string::npos)     
	  //if(((track->GetMaterial())->GetName())=="killMedia") 
	    { 
       if(amedia.find("kill_SiPM_left")!=std::string::npos)  	     //Left SiPMs only
       { 
       double z_init = fabs(step->GetPreStepPoint()->GetPosition().z());
        if(z_init < (Cl_Lng+Gr_wd+Res_wd+0.00001) && z_init > (Cl_Lng+Gr_wd+Res_wd-0.00001)) //Hits only for top surface of the SiPMs
       {
        if(SCEPRINT) 
        {
         //std::cout<< "Reached the left SiPM MMP" << std::endl;
         std::cout<<"killing photon"<<std::endl;
        }
        //std::cout<<"Initial z coordinate " << step->GetPreStepPoint()->GetPosition().z() << std::endl;
        //if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        {
	       hit->ncerenkov+=1;
	       if(ibin>-1&&ibin<hit->nbin) ((hit->ncerwave).at(ibin))+=1;
         if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncertime).at(ibin_t))+=1; //Time of arrival at killMedia for Cerenkov
         if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncerwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time

        }
       }
	      track->SetTrackStatus(fStopAndKill); //kill ALL killMedia photons after the first step, regardless of whether they were created there or not (to avoid overcounting)
       }

       else if(amedia.find("kill_SiPM_right")!=std::string::npos)  	     //Right SiPMs only
       { 
       if(step->GetPreStepPoint()->GetPosition().z() == (Cl_Lng+Gr_wd+Res_wd)) //Hits only for top surface of the SiPMs
       {
        if(SCEPRINT) std::cout<<"killing photon"<<std::endl;
        //if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        {
	       hit->ncerenkov+=1;
	       if(ibin>-1&&ibin<hit->nbin) ((hit->ncerwave).at(ibin))+=1;
         if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncertime).at(ibin_t))+=1; //Time of arrival at killMedia for Cerenkov
         if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncerwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time

        }
        }
	      track->SetTrackStatus(fStopAndKill); //kill ALL killMedia photons after the first step, regardless of whether they were created there or not (to avoid overcounting)
       }
                  
       else //No special condition for the other detectors (which is nothing at this point)
	     { 
        if(SCEPRINT) std::cout<<"killing photon"<<std::endl;
        //if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        {
	       hit->ncerenkov+=1;
	       if(ibin>-1&&ibin<hit->nbin) ((hit->ncerwave).at(ibin))+=1;
         if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncertime).at(ibin_t))+=1; //Time of arrival at killMedia for Cerenkov
         if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncerwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time

        }
	      track->SetTrackStatus(fStopAndKill); //kill ALL killMedia photons after the first step, regardless of whether they were created there or not (to avoid overcounting)
       }

     }
	  
    else {
	    //if( (track->GetParentID()==1)&&(track->GetCurrentStepNumber()==1)  ) hit->ncerenkov+=1;
         	    if( (phstep==1)  )
              {
               hit->ncerenkov+=1;
               if(ibin>-1&&ibin<hit->nbin) ((hit->ncerwave).at(ibin))+=1;
               if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncertime).at(ibin_t))+=1; //Time of production (mainly in crystal) for Cerenkov
               if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->ncerwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time
               /*
               double dialCher= 0.01; //Much bigger factor than in the Dual test beam code

       	       Geant4Event&  evt = context()->event();
               dd4hep::sim::Geant4Random& rnd = evt.random();
	             if(rnd.rndm()>dialCher)
               {
                track->SetTrackStatus(fStopAndKill);
                if(SCEPRINT){std::cout << "Killed photon at production" << std::endl;}
               }
               */
              }
	  }

    //if(phstep>3){track->SetTrackStatus(fStopAndKill);} //Only for reduction of spew with OPTICALPHOTON as gun, requiring multiple photons in one display
           //if(((track->GetMaterial())->GetName())=="Air" && step->GetPreStepPoint()->GetPosition() != step->GetPostStepPoint()->GetPosition())
          if(amedia.find("Air")!=std::string::npos && (fabs(step->GetPreStepPoint()->GetPosition().x() - step->GetPostStepPoint()->GetPosition().x())>0.1 || fabs(step->GetPreStepPoint()->GetPosition().y() - step->GetPostStepPoint()->GetPosition().y())>0.1 || fabs(step->GetPreStepPoint()->GetPosition().z() - step->GetPostStepPoint()->GetPosition().z())>0.1))
          {
           hit->ncerenkov+=1;
           //track->SetTrackStatus(fStopAndKill); //So all the photons go to air including the ones that suffer at least one TIR and are counted in Air and aborted
           //Only count, no abort
           //std::cout<<"escaped cerenkov photon"<<std::endl;
          }
          ///*
          if(amedia.find("Air")!=std::string::npos)
          {
           if(SCEPRINT)
           {
            std::cout << "z position in Air " << step->GetPostStepPoint()->GetPosition().z() << std::endl;
            //std::cout << "z boundary " << Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out+0.01 << std::endl;
            std::cout << "z boundary " << Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out << std::endl;
            std::cout << " x coordinate in Air " << step->GetPreStepPoint()->GetPosition().x() << std::endl;
           }
          if(step->GetPostStepPoint()->GetPosition().z() > (Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out-0.005) || step->GetPostStepPoint()->GetPosition().z() < -(Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out-0.005)) //Reflection at square face
          {
           //std::cout << "False border reflection" <<std::endl;
           track->SetTrackStatus(fStopAndKill);
          }  
          }

          
          if(amedia.find("Air")!=std::string::npos)
          {
           //Reflection at rectangular face but not at the crystal face (outside z = 30 mm)
          if(step->GetPostStepPoint()->GetPosition().x() > (Cl_wd-0.005) || step->GetPostStepPoint()->GetPosition().x() < -(Cl_wd-0.005) || step->GetPostStepPoint()->GetPosition().y() > (Cl_wd-0.005) || step->GetPostStepPoint()->GetPosition().y() < -(Cl_wd-0.005))
          {
           //std::cout << "Potential False reflection at rectangular face" <<std::endl;    
           //std::cout << step->GetPreStepPoint()->GetPosition().z() <<std::endl;
           if((step->GetPreStepPoint()->GetPosition().z()<=(Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out) && step->GetPreStepPoint()->GetPosition().z()>Cl_Lng)||(step->GetPreStepPoint()->GetPosition().z()<-Cl_Lng && step->GetPreStepPoint()->GetPosition().z()>=-(Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out)))
           {
            if(SCEPRINT)std::cout << "False border reflection at rectangular face" <<std::endl;
            track->SetTrackStatus(fStopAndKill);
           }
          }
          /*
          if(step->GetPreStepPoint()->GetPosition().x() == Cl_wd||step->GetPreStepPoint()->GetPosition().x()== -Cl_wd) //Disables all reflections in this perpendicular direction (border surface and TIR)
          {
            track->SetTrackStatus(fStopAndKill);           
          }*/
         }
         //*/
         //return false;
        }
         
	else if (  track->GetCreatorProcess()->G4VProcess::GetProcessName() == "ScintillationPhys"  )
  {
     if(SCEPRINT) std::cout<<" found scintillation photon"<<std::endl;
     std::string amedia = ((track->GetMaterial())->GetName());
     if(amedia.find("kill")!=std::string::npos)
     //if(((track->GetMaterial())->GetName())=="killMedia") 
	    {
       if(amedia.find("kill_SiPM_left")!=std::string::npos)  	     //Left SiPMs only
       { 
        double z_init = fabs(step->GetPreStepPoint()->GetPosition().z());        
        if(z_init < (Cl_Lng+Gr_wd+Res_wd+0.00001) && z_init > (Cl_Lng+Gr_wd+Res_wd-0.00001)) //Hits only for top surface of the SiPMs
       {
        if(SCEPRINT)
        {
         //std::cout<< "Reached the left SiPM MMP" << std::endl;        
         std::cout<<"killing photon"<<std::endl;
        }
        //std::cout<<"Initial z coordinate " << step->GetPreStepPoint()->GetPosition().z() << std::endl;

        //if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        {
	       hit->nscintillator+=1;
	       if(ibin>-1&&ibin<hit->nbin) ((hit->nscintwave).at(ibin))+=1;
         if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscinttime).at(ibin_t))+=1; //Time of arrival at killMedia for scintillation
         if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscintwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time in killMedia
        }
        }
	      track->SetTrackStatus(fStopAndKill); //kill ALL killMedia photons after the first step, regardless of whether they were created there or not (to avoid overcounting)
       }

       else if(amedia.find("kill_SiPM_right")!=std::string::npos)  	     //Right SiPMs only
       { 
       if(step->GetPreStepPoint()->GetPosition().z() == (Cl_Lng+Gr_wd+Res_wd)) //Hits only for top surface of the SiPMs
       {
        if(SCEPRINT) std::cout<<"killing photon"<<std::endl;
        //if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        if(phstep>1)// don't count photons created in kill media i.e. with step number 1 because they are unphysical
        {
	       hit->nscintillator+=1;
	       if(ibin>-1&&ibin<hit->nbin) ((hit->nscintwave).at(ibin))+=1;
         if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscinttime).at(ibin_t))+=1; //Time of arrival at killMedia for scintillation
         if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscintwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time in killMedia
        }
        }
	      track->SetTrackStatus(fStopAndKill); //kill ALL killMedia photons after the first step, regardless of whether they were created there or not (to avoid overcounting)
       }
         
       
      else
      {
	      if(SCEPRINT) std::cout<<"killing photon"<<std::endl;
	      if(phstep>1) // don't count photons created in kill media i.e. with step number 1 because they are unphysical      
        {
	       hit->nscintillator+=1;
	       if((ibin>-1)&&(ibin<hit->nbin)) ((hit->nscintwave).at(ibin))+=1;
         if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscinttime).at(ibin_t))+=1; //Time of arrival at killMedia for scintillation 
         if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscintwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time in killMedia
        }
       track->SetTrackStatus(fStopAndKill); //kill ALL killMedia photons after the first step, regardless of whether they were created there or not (to avoid overcounting)
       }

       }
        
	  else {
	    //if( (track->GetParentID()==1)&&(track->GetCurrentStepNumber()==1) ) hit->nscintillator+=1; 
         	    if( (phstep==1) ) 
              {
               hit->nscintillator+=1;
               if((ibin>-1)&&(ibin<hit->nbin)) ((hit->nscintwave).at(ibin))+=1;
               if(ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscinttime).at(ibin_t))+=1; //Time of production (mainly in crystal) for scintillation
               if(ibin>-1&&ibin<hit->nbin&&ibin_t>-1&&ibin_t<hit->nbin_t) ((hit->nscintwave_time).at(ibin_t).at(ibin))+=1; //2 D, both wavelength and arrival time in killMedia
              }
	  }
    //if(phstep>3){track->SetTrackStatus(fStopAndKill);} //Only for reduction of spew with OPTICALPHOTON as gun, requiring multiple photons in one display
          if(amedia.find("Air")!=std::string::npos && (fabs(step->GetPreStepPoint()->GetPosition().x() - step->GetPostStepPoint()->GetPosition().x())>0.1 || fabs(step->GetPreStepPoint()->GetPosition().y() - step->GetPostStepPoint()->GetPosition().y())>0.1 || fabs(step->GetPreStepPoint()->GetPosition().z() - step->GetPostStepPoint()->GetPosition().z())>0.1))

          {
           hit->nscintillator+=1;
           //std::cout<<"escaped scintillator photon"<<std::endl;
           //std::cout << step->GetPostStepPoint()->GetPosition().z() <<std::endl;
          }
          ///*
          if(amedia.find("Air")!=std::string::npos)
          {
          if(step->GetPostStepPoint()->GetPosition().z() > (Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out-0.005) || step->GetPostStepPoint()->GetPosition().z() < -(Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out-0.005))
          {
           //std::cout << "False border reflection" <<std::endl;
           track->SetTrackStatus(fStopAndKill);
          }           
          }

          if(amedia.find("Air")!=std::string::npos)
          {
           //Reflection at rectangular face but not at the crystal face (outside z = 30 mm)
          if(step->GetPostStepPoint()->GetPosition().x() > (Cl_wd-0.005) || step->GetPostStepPoint()->GetPosition().x() < -(Cl_wd-0.005) || step->GetPostStepPoint()->GetPosition().y() > (Cl_wd-0.005) || step->GetPostStepPoint()->GetPosition().y() < -(Cl_wd-0.005))
          {
           //std::cout << "Potential False reflection at rectangular face" <<std::endl;    
           //std::cout << step->GetPreStepPoint()->GetPosition().z() <<std::endl;
           if((step->GetPreStepPoint()->GetPosition().z()<=(Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out) && step->GetPreStepPoint()->GetPosition().z()>Cl_Lng)||(step->GetPreStepPoint()->GetPosition().z()<-Cl_Lng && step->GetPreStepPoint()->GetPosition().z()>=-(Cl_Lng+Gr_wd+Res_wd+SiPM_wd_in+SiPM_wd_out)))
           {
            if(SCEPRINT)std::cout << "False border reflection at rectangular face" <<std::endl;
            track->SetTrackStatus(fStopAndKill);
           }
          }
         }
          //*/
          //return false;
        }
	else {
          //if(SCEPRINT) std::cout<<"      other photon"<<std::endl;
          //track->SetTrackStatus(fStopAndKill);
          //return false;
	}
 
 	if(SCEPRINT) {
	  std::cout<<"     SCECOUNT = "<<SCECOUNT<<std::endl;
	
	  std::cout<<"     will robinson have photon "<<track->GetCreatorProcess()->G4VProcess::GetProcessName() <<std::endl;
	  std::cout<<"     photon mother is "<<track->GetParentID()<<std::endl;
	  std::cout<<"     photon material is "<<(track->GetMaterial())->GetName()<<std::endl;
	  std::cout<<"     photon creator process is "<<(track->GetCreatorProcess())->GetProcessName()<<std::endl;
	  std::cout<<"     photon  process  type is "<<(track->GetCreatorProcess())->GetProcessType()<<std::endl;
	  std::cout<<"     photon sub process is "<<(track->GetCreatorProcess())->GetProcessSubType()<<std::endl;
	  std::cout<<"     photon current step number is "<<track->GetCurrentStepNumber()<<std::endl;
    //G4StepStatus* bound_proc = step->GetPostStepPoint()->GetStepStatus();
    //G4OpBoundaryProcess* bound_proc = (G4OpBoundaryProcess*)step->GetPostStepPoint()->GetProcess();
    std::cout<<"     photon boundary process is " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<std::endl;
    std::cout<<"     Check for boundary " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessSubType() <<std::endl;
    std::cout<<"     photon pre position is: x coordinate- "<<step->GetPreStepPoint()->GetPosition().x() <<" y coordinate- "<<step->GetPreStepPoint()->GetPosition().y()<<" z coordinate- "<<step->GetPreStepPoint()->GetPosition().z()<<std::endl;
    std::cout<<"     photon post position is: x coordinate- "<<step->GetPostStepPoint()->GetPosition().x() <<" y coordinate- "<<step->GetPostStepPoint()->GetPosition().y() <<" z coordinate- "<<step->GetPostStepPoint()->GetPosition().z()<<std::endl;
 	  std::cout<<"     the pre volume name is "<<thePrePVName<<std::endl;
	  std::cout<<"     the post volume name is "<<thePostPVName<<std::endl;
	//(track->GetCreatorProcess())->DumpInfo();
	  std::cout<<"     photon energy is "<<track->GetTotalEnergy()/eV<<std::endl;
	  std::cout<<"     photon wavelength is "<<fromEvToNm(track->GetTotalEnergy()/eV)<<std::endl;
    std::cout<<"     Arrival time is "<<tof<<std::endl;
    std::cout<<"     Time Bin number is " << (tof-hit->timemin)/((hit->timemax-hit->timemin)/hit->nbin_t)<<std::endl;
    std::cout<<"     number of cherenkov in time bin is " << (hit->ncertime).at((tof-hit->timemin)/((hit->timemax-hit->timemin)/hit->nbin_t))<<std::endl;
    std::cout<<"     number of scintillation in time bin is " << (hit->nscinttime).at((tof-hit->timemin)/((hit->timemax-hit->timemin)/hit->nbin_t))<<std::endl;
    
    std::cout<<"     number of cherenkov in wavelength time bin is " << (hit->ncerwave_time).at((tof-hit->timemin)/((hit->timemax-hit->timemin)/hit->nbin_t)).at((fromEvToNm(track->GetTotalEnergy()/eV)-hit->wavelenmin)/((hit->wavelenmax-hit->wavelenmin)/hit->nbin))<<std::endl;
    std::cout<<"     number of scintillation in wavelength time bin is " << (hit->nscintwave_time).at((tof-hit->timemin)/((hit->timemax-hit->timemin)/hit->nbin_t)).at((fromEvToNm(track->GetTotalEnergy()/eV)-hit->wavelenmin)/((hit->wavelenmax-hit->wavelenmin)/hit->nbin))<<std::endl;        

	  std::cout<<"     number of cherenkov is "<<hit->ncerenkov <<std::endl;

	  std::cout<<"     number of scintillation is "<<hit->nscintillator<<std::endl;
	}


      }

    else {   // particles other than optical photons
	
      if(SCEPRINT) std::cout<<"NOT optical photon"<<std::endl;

        hit->energyDeposit += contrib.deposit;
        hit->truth.emplace_back(contrib);

        //return true;
      }

        mark(h.track);
	
      return true;

    }
	
  }
} // end namespace calvision







namespace dd4hep { namespace sim {

    using namespace CalVision;

    struct WavelengthMinimumCut : public dd4hep::sim::Geant4Filter  {
  /// Energy cut value
      double m_wavelengthCut;
    public:
  /// Constructor.
      WavelengthMinimumCut(dd4hep::sim::Geant4Context* c, const std::string& n);
  /// Standard destructor
      virtual ~WavelengthMinimumCut();
  /// Filter action. Return true if hits should be processed
      virtual bool operator()(const G4Step* step) const  override  final  {
	bool test=true;
	G4Track *theTrack = step->GetTrack();
	if(theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() ) {
	  float energy=theTrack->GetTotalEnergy()/eV;
	  float wave=fromEvToNm(energy);
	  if(wave < m_wavelengthCut) {
	    theTrack->SetTrackStatus(fStopAndKill);
	    test=false;}
	}
	return test;
      }
      virtual bool operator()(const Geant4FastSimSpot* spot) const  override  final  {
	return true;
      }
    };

  /// Constructor.
    WavelengthMinimumCut::WavelengthMinimumCut(Geant4Context* c, const std::string& n)
      : Geant4Filter(c,n) {
      InstanceCount::increment(this);
      declareProperty("Cut",m_wavelengthCut=0.0);
    }

  /// Standard destructor
    WavelengthMinimumCut::~WavelengthMinimumCut() {
      InstanceCount::decrement(this);
    }



    struct WavelengthnmwindCut : public dd4hep::sim::Geant4Filter  {
  /// Energy cut value
      double m_wavelengthstart;
    public:
  /// Constructor.
      WavelengthnmwindCut(dd4hep::sim::Geant4Context* c, const std::string& n);
  /// Standard destructor
      virtual ~WavelengthnmwindCut();
  /// Filter action. Return true if hits should be processed
      virtual bool operator()(const G4Step* step) const  override  final  {
	bool test=true;
	G4Track *theTrack = step->GetTrack();
	if(theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() ) {
	  float energy=theTrack->GetTotalEnergy()/eV;
	  float wave=fromEvToNm(energy);
	  if((wave<m_wavelengthstart) || (wave > m_wavelengthstart+0.5) ) {
	    theTrack->SetTrackStatus(fStopAndKill);
	    test=false;}
	}
	return test;
      }
      virtual bool operator()(const Geant4FastSimSpot* spot) const  override  final  {
	return true;
      }
    };

  /// Constructor.
    WavelengthnmwindCut::WavelengthnmwindCut(Geant4Context* c, const std::string& n)
      : Geant4Filter(c,n) {
      InstanceCount::increment(this);
      declareProperty("Cut",m_wavelengthstart=0.0);
    }

  /// Standard destructor
    WavelengthnmwindCut::~WavelengthnmwindCut() {
      InstanceCount::decrement(this);
    }


  }}  // end using namespace





//--- Factory declaration
namespace dd4hep { namespace sim {
    typedef Geant4SensitiveAction<DualCrystalCalorimeterSD> DualCrystalCalorimeterSDAction;
  }}
DECLARE_GEANT4SENSITIVE(DualCrystalCalorimeterSDAction)
DECLARE_GEANT4ACTION(WavelengthMinimumCut)
DECLARE_GEANT4ACTION(WavelengthnmwindCut)
